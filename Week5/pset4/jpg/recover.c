#include"myHeader.h"


bool isJpeg(unsigned char b[512]);


int main(int argc, char* argv[])
{
// Open the card
FILE * jpegFile;
jpegFile=malloc(512*2048);
FILE * card=fopen("card.raw","r");
bool prevJpeg=false;
bool writeJpeg=false;
// JPEG indexing
int i=0;

while (!feof(card))
	{
	
	unsigned char block[512];
	fread(block,512,1,card);
	
	bool found=isJpeg(block);
	
	if(found)
		{
		if (prevJpeg)
			{
			fclose(jpegFile);
			}
		writeJpeg=true;
		//Name of the new jpeg files ...
		char * title;
		title =malloc(sizeof(char)*10);
		
		if (i<10)
			{
			sprintf(title,"00%d.jpeg",i);
			}
		else
			{
			sprintf(title,"0%d.jpeg",i);
			}	
		i++;
		
		jpegFile=fopen(title,"w");		
		}
	if(writeJpeg)
		{
		fwrite(block,512,1,jpegFile);
		prevJpeg=true;
		}	
	
	 
	
	}

return 0;	
}



bool isJpeg(unsigned char b[512])
	{
	if ((b[0]==0xff) && (b[1]==0xd8) && (b[2]==0xff))
		{
		if ( (b[3]==0xe0)||  (b[3]==0xe1)||  (b[3]==0xe2)||  (b[3]==0xe3)|| 
		 (b[3]==0xe4)||  (b[3]==0xe5)||  (b[3]==0xe6)||  (b[3]==0xe7)|| 
		 (b[3]==0xe8)||  (b[3]==0xe9)||  (b[3]==0xea)||  (b[3]==0xeb)|| 
		 (b[3]==0xec)||  (b[3]==0xed)||  (b[3]==0xee)||  (b[3]==0xef)     )
		 	{
		 	return true;
		 	}
		}
	return false;
	}
	

	
	
	
	
	
