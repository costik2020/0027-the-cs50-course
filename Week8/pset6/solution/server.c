//
// server.c
//
// Computer Science 50
// Problem Set 6
//

// feature test macro requirements
#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#define _XOPEN_SOURCE_EXTENDED

// limits on an HTTP request's size, based on Apache's
// http://httpd.apache.org/docs/2.2/mod/core.html
#define LimitRequestFields 50
#define LimitRequestFieldSize 4094
#define LimitRequestLine 8190

// number of bytes for buffers
#define BYTES 512

// header files
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// types
typedef char BYTE;

// prototypes
bool connected(void);
void error(unsigned short code);
void freedir(struct dirent** namelist, int n);
void handler(int signal);
char* htmlspecialchars(const char* s);
char* indexes(const char* path);
void interpret(const char* path, const char* query);
void list(const char* path);
bool load(FILE* file, BYTE** content, size_t* length);
const char* lookup(const char* path);
bool parse(const char* line, char* path, char* query);
const char* reason(unsigned short code);
void redirect(const char* uri);
bool request(char** message, size_t* length);
void respond(int code, const char* headers, const char* body, size_t length);
void start(short port, const char* path);
void stop(void);
void transfer(const char* path, const char* type);
char* urldecode(const char* s);

// server's root
char* root = NULL;

// file descriptor for sockets
int cfd = -1, sfd = -1;

// flag indicating whether control-c has been heard
bool signaled = false;

int main(int argc, char* argv[])
{
    // a global variable defined in errno.h that's "set by system 
    // calls and some library functions [to a nonzero value]
    // in the event of an error to indicate what went wrong"
    errno = 0;

    // default to port 8080
    int port = 8080;

    // usage
    const char* usage = "Usage: server [-p port] /path/to/root";

    // parse command-line arguments
    int opt;
    while ((opt = getopt(argc, argv, "hp:")) != -1)
    {
        switch (opt)
        {
            // -h
            case 'h':
                printf("%s\n", usage);
                return 0;

            // -p port
            case 'p':
                port = atoi(optarg);
                break;
        }
    }

    // ensure port is a non-negative short and path to server's root is specified
    if (port < 0 || port > SHRT_MAX || argv[optind] == NULL || strlen(argv[optind]) == 0)
    {
        // announce usage
        printf("%s\n", usage);

        // return 2 just like bash's builtins
        return 2;
    }

    // start server
    start(port, argv[optind]);

    // listen for SIGINT (aka control-c)
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, NULL);

    // a message and its length
    char* message = NULL;
    size_t length = 0;

    // path requested
    char* path = NULL;

    // accept connections one at a time
    while (true)
    {
        // free last path, if any
        if (path != NULL)
        {
            free(path);
            path = NULL;
        }

        // free last message, if any
        if (message != NULL)
        {
            free(message);
            message = NULL;
        }
        length = 0;

        // close last client's socket, if any
        if (cfd != -1)
        {
            close(cfd);
            cfd = -1;
        }

        // check for control-c
        if (signaled)
        {
            stop();
        }

        // check whether client has connected
        if (connected())
        {
            // check for request
            if (request(&message, &length))
            {
                // extract message's request-line
                // http://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html
                const char* haystack = message;
                const char* needle = strstr(haystack, "\r\n");
                if (needle == NULL)
                {
                    error(500);
                    continue;
                }
                char line[needle - haystack + 2 + 1];
                strncpy(line, haystack, needle - haystack + 2);
                line[needle - haystack + 2] = '\0';

                // log request-line
                printf("%s", line);

                // parse request-line
                char abs_path[LimitRequestLine + 1];
                char query[LimitRequestLine + 1];
                if (parse(line, abs_path, query))
                {
                    // URL-decode absolute-path
                    
                    char* p = urldecode(abs_path);
                    if (p == NULL)
                    {	
                    	
                        error(500);
                        continue;
                    }

                    // resolve absolute-path to local path
                    path = malloc(strlen(root) + strlen(p) + 1);
                    if (path == NULL)
                    {
                        error(500);
                        continue;
                    }
                    strcpy(path, root);
                    strcat(path, p);
                    
                    free(p);

                    // ensure path exists
                    if (access(path, F_OK) == -1)
                    {
                        error(404);
                        continue;
                    }

                    // if path to directory
                    struct stat sb;
                    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
                    {
                        // redirect from absolute-path to absolute-path/
                        if (abs_path[strlen(abs_path) - 1] != '/')
                        {
                            char uri[strlen(abs_path) + 1 + 1];
                            strcpy(uri, abs_path);
                            strcat(uri, "/");
                            redirect(uri);
                            continue;
                        }

                        // use path/index.php or path/index.html, if present, instead of directory's path
                        char* index = indexes(path);
                        if (index != NULL)
                        {
                            free(path);
                            path = index;
                        }

                        // list contents of directory
                        else
                        {
                            list(path);
                            continue;
                        }
                    }

                    // look up MIME type for file at path
                    const char* type = lookup(path);
                    if (type == NULL)
                    {
                        error(501);
                        continue;
                    }

                    // interpret PHP script at path
                    if (strcasecmp("text/x-php", type) == 0)
                    {
                        interpret(path, query);
                    }

                    // transfer file at path
                    else
                    {
                        transfer(path, type);
                    }
                }
            }
        }
    }
}

/**
 * Checks (without blocking) whether a client has connected to server. 
 * Returns true iff so.
 */
bool connected(void)
{
    struct sockaddr_in cli_addr;
    memset(&cli_addr, 0, sizeof(cli_addr));
    socklen_t cli_len = sizeof(cli_addr);
    cfd = accept(sfd, (struct sockaddr*) &cli_addr, &cli_len);
    if (cfd == -1)
    {
        return false;
    }
    return true;
}

/**
 * Responds to client with specified status code.
 */
void error(unsigned short code)
{
    // determine code's reason-phrase
    const char* phrase = reason(code);
    if (phrase == NULL)
    {
        return;
    }

    // template for response's content
    char* template = "<html><head><title>%i %s</title></head><body><h1>%i %s</h1></body></html>";

    // render template
    char body[(strlen(template) - 2 - ((int) log10(code) + 1) - 2 + strlen(phrase)) * 2 + 1];
    int length = sprintf(body, template, code, phrase, code, phrase);
    if (length < 0)
    {
        body[0] = '\0';
        length = 0;
    }

    // respond with error
    char* headers = "Content-Type: text/html\r\n";
    respond(code, headers, body, length);
}

/**
 * Frees memory allocated by scandir.
 */
void freedir(struct dirent** namelist, int n)
{
    if (namelist != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            free(namelist[i]);
        }
        free(namelist);
    }
}
 
/**
 * Handles signals.
 */
void handler(int signal)
{
    // control-c
    if (signal == SIGINT)
    {
        signaled = true;
    }
}

/**
 * Escapes string for HTML. Returns dynamically allocated memory for escaped
 * string that must be deallocated by caller.
 */
char* htmlspecialchars(const char* s)
{
    // ensure s is not NULL
    if (s == NULL)
    {
        return NULL;
    }

    // allocate enough space for an unescaped copy of s
    char* t = malloc(strlen(s) + 1);
    if (t == NULL)
    {
        return NULL;
    }
    t[0] = '\0';

    // iterate over characters in s, escaping as needed
    for (int i = 0, old = strlen(s), new = old; i < old; i++)
    {
        // escape &
        if (s[i] == '&')
        {
            const char* entity = "&amp;";
            new += strlen(entity);
            t = realloc(t, new);
            if (t == NULL)
            {
                return NULL;
            }
            strcat(t, entity);
        }

        // escape "
        else if (s[i] == '"')
        {
            const char* entity = "&quot;";
            new += strlen(entity);
            t = realloc(t, new);
            if (t == NULL)
            {
                return NULL;
            }
            strcat(t, entity);
        }

        // escape '
        else if (s[i] == '\'')
        {
            const char* entity = "&#039;";
            new += strlen(entity);
            t = realloc(t, new);
            if (t == NULL)
            {
                return NULL;
            }
            strcat(t, entity);
        }

        // escape <
        else if (s[i] == '<')
        {
            const char* entity = "&lt;";
            new += strlen(entity);
            t = realloc(t, new);
            if (t == NULL)
            {
                return NULL;
            }
            strcat(t, entity);
        }

        // escape >
        else if (s[i] == '>')
        {
            const char* entity = "&gt;";
            new += strlen(entity);
            t = realloc(t, new);
            if (t == NULL)
            {
                return NULL;
            }
            strcat(t, entity);
        }

        // don't escape
        else
        {
            strncat(t, s + i, 1);
        }
    }

    // escaped string
    return t;
}

/**
 * Checks, in order, whether index.php or index.html exists inside of path.
 * Returns path to first match if so, else NULL.
 */


char* indexes(const char* path)
{
// I hard coded 200 in malloc () to alocate memory for newpath


DIR* pdir;
// Or i can use . notation to express the current directory
pdir=opendir(path);
if (pdir==NULL)
	{
	printf("Unable to open the directory pointer opendir() \n");
	return NULL;
	}


struct dirent *sdirectories;

while ((sdirectories=readdir(pdir) )!= NULL   )
	{
	// printf("%s  \n",sdirectories->d_name);
	// ((strcmp(name,"index.php")==0)
	char name[50];
	strcpy(name,sdirectories->d_name);
	if (strcmp(name,"index.html")==0)                        
		{
		char* newpath=malloc(sizeof(char)*200);
		strcpy(newpath,path);
		
		
		strcat(newpath,"index.html");
		
		return newpath;
		}
		else if  (strcmp(name,"index.php")==0)
		{
		char* newpath=malloc(sizeof(char)*200);
		strcat(newpath,path);
		strcat(newpath,"/index.php");
		return newpath;
		}
	
	}
   
    return NULL;
}







/**
 * Interprets PHP file at path using query string.
 */
void interpret(const char* path, const char* query)
{
    // ensure path is readable
    if (access(path, R_OK) == -1)
    {
        error(403);
        return;
    }

    // open pipe to PHP interpreter
    char* format = "QUERY_STRING=\"%s\" REDIRECT_STATUS=200 SCRIPT_FILENAME=\"%s\" php-cgi";
    char command[strlen(format) + (strlen(path) - 2) + (strlen(query) - 2) + 1];
    if (sprintf(command, format, query, path) < 0)
    {
        error(500);
        return;
    }
    
    FILE* file = popen(command, "r");
    
    
    
    
    
    if (file == NULL)
    {
        error(500);
        return;
    }

    // load interpreter's content
    char* content;
    size_t length;
    if (load(file, &content, &length) == false)
    {
    
        error(500);
        return;
    }

    // close pipe
    pclose(file);

    // subtract php-cgi's headers from content's length to get body's length
    char* haystack = content;
    char* needle = strstr(haystack, "\r\n\r\n");
    if (needle == NULL)
    {
        free(content);
        error(500);
        return;
    }

    // extract headers
    char headers[needle + 2 - haystack + 1];
    strncpy(headers, content, needle + 2 - haystack);
    headers[needle + 2 - haystack] = '\0';

    // respond with interpreter's content
    respond(200, headers, needle + 4, length - (needle - haystack + 4));

    // free interpreter's content
    free(content);
}

/**
 * Responds to client with directory listing of path.
 */
void list(const char* path)
{
    // ensure path is readable and executable
    if (access(path, R_OK | X_OK) == -1)
    {
        error(403);
        return;
    }

    // open directory
    DIR* dir = opendir(path);
    if (dir == NULL)
    {
        return;
    }

    // buffer for list items
    char* list = malloc(1);
    list[0] = '\0';

    // iterate over directory entries
    struct dirent** namelist = NULL;
    int n = scandir(path, &namelist, NULL, alphasort);
    for (int i = 0; i < n; i++)
    {
        // omit . from list
        if (strcmp(namelist[i]->d_name, ".") == 0)
        {
            continue;
        }

        // escape entry's name
        char* name = htmlspecialchars(namelist[i]->d_name);
        if (name == NULL)
        {
            free(list);
            freedir(namelist, n);
            error(500);
            return;
        }

        // append list item to buffer
        char* template = "<li><a href=\"%s\">%s</a></li>";
        list = realloc(list, strlen(list) + strlen(template) - 2 + strlen(name) - 2 + strlen(name) + 1);
        if (list == NULL)
        {
            free(name);
            freedir(namelist, n);
            error(500);
            return;
        }
        if (sprintf(list + strlen(list), template, name, name) < 0)
        {
            free(name);
            freedir(namelist, n);
            free(list);
            error(500);
            return;
        }

        // free escaped name
        free(name);
    }

    // free memory allocated by scandir
    freedir(namelist, n);

    // prepare response
    const char* relative = path + strlen(root);
    char* template = "<html><head><title>%s</title></head><body><h1>%s</h1><ul>%s</ul></body></html>";
    char body[strlen(template) - 2 + strlen(relative) - 2 + strlen(relative) - 2 + strlen(list) + 1];
    int length = sprintf(body, template, relative, relative, list);
    if (length < 0)
    {
        free(list);
        closedir(dir);
        error(500);
        return;
    }

    // free buffer
    free(list);

    // close directory
    closedir(dir);

    // respond with list
    char* headers = "Content-Type: text/html\r\n";
    respond(200, headers, body, length);
}

/**
 * Loads a file into memory dynamically allocated on heap.
 * Stores address thereof in *content and length thereof in *length.
 */

bool load(FILE* file, BYTE** content, size_t* length)
{

size_t size=0;
FILE* pf=file;
if (pf==NULL)
	{
	printf("File is NULL \n");
	return  false;
	}

char* storebytes;
//BYTE is 8 bits
char buffer;
int nrOfItems=0;

storebytes=malloc(sizeof(char)*100);


while (true)
	{
	// Read 8 bits into the buffer from the file
	//typedef char BYTE; is at the top of .c file
	nrOfItems=fread(&buffer,sizeof(BYTE),1,pf);
	
	
	//Check for file read errors
	if (ferror(pf) !=0 )
		{
		if (storebytes != NULL)
			{
			
			free(storebytes);
			storebytes=NULL;
			}
			
			
		return false;
		}
	
	//If you read something add the buffer into the array of bytes
	if (nrOfItems > 0)
		{
		storebytes=realloc(storebytes,size+nrOfItems);
		if (storebytes==NULL)
			{
			printf("Something went wrrong with memory reallocation \n");
			return false;
			}
		
		//I think storebytes+size is pointer arithmetic to not overwrritet
		//But to copy at the end of the storebytes array somehow
		memcpy(storebytes+size,&buffer,nrOfItems);
		size=size + nrOfItems;
		}
	
	//Check for end of file
	if (feof(pf) !=0)
		{
		break;
		}
		
		
	}



//"Return" the location of the string
*content=storebytes;

// "Return" length of the string in memory   
  if (size!=0)
  	{
  	*length=size;
  	return true;
  	}  
    
    
    return false;
}





/**
 * Returns MIME type for supported extensions, else NULL.
 */
const char* lookup(const char* path)
{
	// Find extension inside path
	char ext[10];
	int i=0;
	while (path[i] != '\0')
		{
		if (path[i]=='.')
			{
			i++;
			int j=0;
			while(path[i] != '\0')
				{
			
			
				ext[j]=path[i];
				j++;
				i++;
				}
			ext[j]='\0';
			break;
			}
		i=i+1;
		}
		
	//Return the answer based on extension it finds
	char * A_edata[8]={"css","html","gif","ico","jpg","js","php","png"};
	char * A_root[8]= {"text/css","text/html","image/gif","image/x-icon","image/jpeg","text/javascript","text/x-php","image/png"};

	for (int i=0;i<8;i++)
		{
		if (strcmp(ext,A_edata[i])==0)
			{
			char * answer;
			answer=malloc(sizeof(char)*20);
			strcpy(answer,A_root[i]);
			
			return answer;
			}
		}



	
	
	return NULL;
	}







/**
 * Parses a request-line, storing its absolute-path at abs_path 
 * and its query string at query, both of which are assumed
 * to be at least of length LimitRequestLine + 1.
 */
bool parse(const char* line, char* abs_path, char* query)
{
 	
    // line is a Request line
    // the template is:
    // method request-target http-version \r\n
    // GET /hello.php HTTP/1.1
    
    // Check if the line is actualy a Request line 
    
    
    //If the methodo is not GET
    
    // NEED TO CLEAN FREE abs_path from junk
    for (int c=0;c<=LimitRequestLine;c++)
    	{
    	abs_path[c]='\0';
    	}
    
    char method[10];
    int i=0;
    char endo='\0';
    while (true)
     {
     if (line[i]==' ')
     	break;
     	
     method[i]=line[i];
     i++;
     }
     method[i]='\0';
     if (strcmp(method,"GET")!=0)
     	{
     	//ERROR
     	error(405);
     	return false;
     	}
    
    //If the request-target doesn't begin with /
    // GET /hello.php HTTP/1.1
     i=0;
    while(line[i]!=' ')
    	{
        i++;
    	}
    if (line[i+1]!='/')
    	{
    	error(501);
    	return false;
    	}
    //If the request-target contains "
     i=0;
    while(line[i]!=' ')
    	{
    	i++;
    	}
    i++;
    // Look for the second space in request target
    while( line[i]!=' ')
    	{
    	if (line[i]=='\"')
    		{ 
    		error(400);
    		return false;
    		}
    	i++;
    	}	
    
    
    //If the HTTP version is not  HTTP/1.1 
    //   GET /hello.php HTTP/1.1
    // line[i] is here ^
   i++;
   char http2[10];
   int h=0;
    for(int k=i;k<=i+7;k++)
    	{
    	http2[h]=line[k];
    	h++;
    	}
    http2[h]='\0';
    
    
    if (strcmp(http2,"HTTP/1.1") !=0)
    	{
    	error(505);
    	return false;
    	}
    
    // Extract the abs_path and query from the request-target
    // GET /hello.php HTTP/1.1
    // GET /hello.php? HTTP/1.1
    // GET /hello.php?q=Alice HTTP/1.1
    //Extract the abs_path
       
    
    i =0;
    while (line[i] !=' ')
    	{
    	i++;
    	}
    i++;
    int p=0;
    while( (line[i] !=' ') && (line[i] !='?') )
    	{
    	//printf("LOOK \n");
    	abs_path[p]=line[i];
    	i++;
    	p++;
   		}
   	abs_path[p+1]='\0';
   	
   	
   	//Extract the query
   	// GET /hello.php HTTP/1.1
    // GET /hello.php? HTTP/1.1
    // GET /hello.php?q=Alice HTTP/1.1
    // GET /hello.php?name=Alice HTTP/1.1
   
   	if (line[i]==' ')
   		{
   		//query='\0';
   		strncat(query,&endo,1);
   		return true;
   		}
   	if ( (line[i]=='?') && (line[i+1]==' ') )
   		{
   		//query='\0';
   		strncat(query,&endo,1);
   		return true;
   		}
   	p=0;
   	i++;
   	while (line[i] !=' ')
   		{
   		
   		query[p]=line[i];
   		p++;
   		i++;
   		}
   	if (p !=0)
   		{
   		query[p]='\0';
   		return true;
   		}	
   	
   
   	
   	
   	
   	
    error(501);
    
    return false;
}




/**
 * Returns status code's reason phrase.
 *
 * http://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html#sec6
 * https://tools.ietf.org/html/rfc2324
 */
const char* reason(unsigned short code)
{
    switch (code)
    {
        case 200: return "OK";
        case 301: return "Moved Permanently";
        case 400: return "Bad Request";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 414: return "Request-URI Too Long";
        case 418: return "I'm a teapot";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 505: return "HTTP Version Not Supported";
        default: return NULL;
    }
}

/**
 * Redirects client to uri.
 */
void redirect(const char* uri)
{
    char* template = "Location: %s\r\n";
    char headers[strlen(template) - 2 + strlen(uri) + 1];
    if (sprintf(headers, template, uri) < 0)
    {
        error(500);
        return;
    }
    respond(301, headers, NULL, 0);
}

/**
 * Reads (without blocking) an HTTP request's headers into memory dynamically allocated on heap.
 * Stores address thereof in *message and length thereof in *length.
 */
bool request(char** message, size_t* length)
{
    // ensure socket is open
    if (cfd == -1)
    {
        return false;
    }

    // initialize message and its length
    *message = NULL;
    *length = 0;

    // read message 
    while (*length < LimitRequestLine + LimitRequestFields * LimitRequestFieldSize + 4)
    {
        // read from socket
        BYTE buffer[BYTES];
        ssize_t bytes = read(cfd, buffer, BYTES);
        if (bytes < 0)
        {
            if (*message != NULL)
            {
                free(*message);
                *message = NULL;
            }
            *length = 0;
            break;
        }

        // append bytes to message 
        *message = realloc(*message, *length + bytes + 1);
        if (*message == NULL)
        {
            *length = 0;
            break;
        }
        memcpy(*message + *length, buffer, bytes);
        *length += bytes;

        // null-terminate message thus far
        *(*message + *length) = '\0';

        // search for CRLF CRLF
        int offset = (*length - bytes < 3) ? *length - bytes : 3;
        char* haystack = *message + *length - bytes - offset;
        char* needle = strstr(haystack, "\r\n\r\n");
        if (needle != NULL)
        {
            // trim to one CRLF and null-terminate
            *length = needle - *message + 2;
            *message = realloc(*message, *length + 1);
            if (*message == NULL)
            {
                break;
            }
            *(*message + *length) = '\0';

            // ensure request-line is no longer than LimitRequestLine
            haystack = *message;
            needle = strstr(haystack, "\r\n");
            if (needle == NULL || (needle - haystack + 2) > LimitRequestLine)
            {
                break;
            }

            // count fields in message
            int fields = 0;
            haystack = needle + 2;
            while (*haystack != '\0')
            {
                // look for CRLF
                needle = strstr(haystack, "\r\n");
                if (needle == NULL)
                {
                    break;
                }

                // ensure field is no longer than LimitRequestFieldSize
                if (needle - haystack + 2 > LimitRequestFieldSize)
                {
                    break;
                }

                // look beyond CRLF
                haystack = needle + 2;
            }

            // if we didn't get to end of message, we must have erred
            if (*haystack != '\0')
            {
                break;
            }

            // ensure message has no more than LimitRequestFields
            if (fields > LimitRequestFields)
            {
                break;
            }

            // valid
            return true;
        }
    }

    // invalid
    if (*message != NULL)
    {
        free(*message);
    }
    *message = NULL;
    *length = 0;
    return false;
}

/**
 * Responds to a client with status code, headers, and body of specified length.
 */
void respond(int code, const char* headers, const char* body, size_t length)
{
    // determine Status-Line's phrase
    // http://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html#sec6.1
    const char* phrase = reason(code);
    if (phrase == NULL)
    {
        return;
    }

    // respond with Status-Line
    if (dprintf(cfd, "HTTP/1.1 %i %s\r\n", code, phrase) < 0)
    {
        return;
    }

    // respond with headers
    if (dprintf(cfd, "%s", headers) < 0)
    {
        return;
    }

    // respond with CRLF
    if (dprintf(cfd, "\r\n") < 0)
    {
        return;
    }

    // respond with body
    if (write(cfd, body, length) == -1)
    {
        return;
    }

    // log response line
    if (code == 200)
    {
        // green
        printf("\033[32m");
    }
    else
    {
        // red
        printf("\033[33m");
    }
    printf("HTTP/1.1 %i %s", code, phrase);
    printf("\033[39m\n");
}

/**
 * Starts server on specified port rooted at path.
 */
void start(short port, const char* path)
{
    // path to server's root
    root = realpath(path, NULL);
    if (root == NULL)
    {
        stop();
    }

    // ensure root is executable
    if (access(root, X_OK) == -1)
    {
        stop();
    }

    // announce root
    printf("\033[33m");
    printf("Using %s for server's root", root);
    printf("\033[39m\n");

    // create a socket
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        stop();
    }

    // allow reuse of address (to avoid "Address already in use")
    int optval = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    // assign name to socket
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
    {
        printf("\033[33m");
        printf("Port %i already in use", port);
        printf("\033[39m\n");
        stop();
    }

    // listen for connections
    if (listen(sfd, SOMAXCONN) == -1)
    {
        stop();
    }

    // announce port in use
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    if (getsockname(sfd, (struct sockaddr*) &addr, &addrlen) == -1)
    {
        stop();
    }
    printf("\033[33m");
    printf("Listening on port %i", ntohs(addr.sin_port));
    printf("\033[39m\n");
}

/**
 * Stop server, deallocating any resources.
 */
void stop(void)
{
    // preserve errno across this function's library calls
    int errsv = errno;

    // announce stop
    printf("\033[33m");
    printf("Stopping server\n");
    printf("\033[39m");

    // free root, which was allocated by realpath
    if (root != NULL)
    {
        free(root);
    }

    // close server socket
    if (sfd != -1)
    {
        close(sfd);
    }

    // stop server
    exit(errsv);
}

/**
 * Transfers file at path with specified type to client.
 */
void transfer(const char* path, const char* type)
{
    // ensure path is readable
    if (access(path, R_OK) == -1)
    {
        error(403);
        return;
    }

    // open file
    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        error(500);
        return;
    }

    // load file's content
    BYTE* content;
    size_t length;
    if (load(file, &content, &length) == false)
    {
        error(500);
        return;
    }

    // close file
    fclose(file);

    // prepare response
    char* template = "Content-Type: %s\r\n";
    char headers[strlen(template) - 2 + strlen(type) + 1];
    if (sprintf(headers, template, type) < 0)
    {
        error(500);
        return;
    }

    // respond with file's content
    respond(200, headers, content, length);

    // free file's content
    free(content);
}

/**
 * URL-decodes string, returning dynamically allocated memory for decoded string
 * that must be deallocated by caller.
 */
char* urldecode(const char* s)
{
    // check whether s is NULL
    if (s == NULL)
    {
        return NULL;
    }

    // allocate enough (zeroed) memory for an undecoded copy of s
    char* t = calloc(strlen(s) + 1, 1);
    if (t == NULL)
    {
        return NULL;
    }
    
    // iterate over characters in s, decoding percent-encoded octets, per
    // https://www.ietf.org/rfc/rfc3986.txt
    for (int i = 0, j = 0, n = strlen(s); i < n; i++, j++)
    {
        if (s[i] == '%' && i < n - 2)
        {
            char octet[3];
            octet[0] = s[i + 1];
            octet[1] = s[i + 2];
            octet[2] = '\0';
            t[j] = (char) strtol(octet, NULL, 16);
            i += 2;
        }
        else if (s[i] == '+')
        {
            t[j] = ' ';
        }
        else
        {
            t[j] = s[i];
        }
    }

    // escaped string
    return t;
}
