
#define LimitRequestLine 8190

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char * error(int n);
const char* reason(unsigned short code);
void respond(int code);
bool parse(const char* line, char* abs_path, char* query);



int main(void)
{
// Declar the abs_path and query variables
char abs_path[LimitRequestLine + 1];
char query[LimitRequestLine + 1];
bool testValue=false;
if (testValue)
	{
	printf("true very true");	
	}

// Request line test
// GET /hello.php HTTP/1.1
const char * line="GET /cat.html HTTP/1.1";

if (parse(line,abs_path,query)==true)
	{
	printf("The line is a GOOD request \n");
	}
	else
	{
	printf("The line is a BAD request \n");
	}

printf("abs_path:%s   \n",abs_path);
printf("query:%s  \n",query);

return 0;
}


bool parse(const char* line, char* abs_path, char* query)
{
    // line is a Request line
    // the template is:
    // method request-target http-version \r\n
    // GET /hello.php HTTP/1.1
    
    // Check if the line is actualy a Request line 
    
    
    //If the methodo is not GET
    char method[10];
    int i=0;
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
     	respond(405);
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
    	respond(501);
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
    		respond(400);
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
    http2[h+1]='\0';
    
    if (strcmp(http2,"HTTP/1.1") !=0)
    	{
    	respond(505);
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
   
   	if (line[i]==' ')
   		{
   		query='\0';
   		return true;
   		}
   	if ( (line[i]=='?') && (line[i+1]==' ') )
   		{
   		query='\0';
   		return true;
   		}
   	if ((line[i]=='?') && (line[i+1]=='q'))
   		{
   		i++;
   		p=0;
   		
   		while (line[i] != ' ')
   			{
   			query[p]=line[i];
   			i++;
   			p++;
   			}
   		query[p+1]='\0';
   		return true;	
   		}		
   		
    
    
    
    
    error(501);
    
    return false;
}

char * error(int n)
{
printf("Error !!!");
return "Error";
}

// Maps Error codes to error messages
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


// Responds with appropiate error code using reason()
void respond(int code)
{
char * phrase=reason(code);
printf("\n");
printf("%d %s",code,phrase);
printf("\n");
}






