/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */ 
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
	// size n of the large imagine
	int n = atoi(argv[1]);
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf,bfo;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fseek(inptr,-(sizeof(BITMAPFILEHEADER)),SEEK_CUR);
    fread(&bfo, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi,bio;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    fseek(inptr,-(sizeof(BITMAPINFOHEADER)),SEEK_CUR);
    fread(&bio, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    
    //change the bitmapheaders for the output file 
    bio.biWidth=bi.biWidth*n;
    bio.biHeight=bi.biHeight*n;
    // determine padding for scanlines
    int paddingIn =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	int paddingOut=  (4 - (bio.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bio.biSizeImage=3*(abs(bio.biHeight)*bio.biWidth)+
    paddingOut*abs(bio.biHeight);
    
    bfo.bfSize=bio.biSizeImage+
    (sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER));
   
    

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);

    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
    	// loop n rows in the out file 
    	for (int z=0;z<n;z++)
    		{
    		// iterate over pixels in scanline
    		 for (int j = 0; j < bi.biWidth; j++)
				{
				    // temporary storage
				    RGBTRIPLE triple;

				    // read RGB triple from infile
				    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
				  	// write RGB triple to outfile n times
						for (int k=0;k<n;k++)
							{
							fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
							}
						

				}
				// Add pdding to the large output file	
				for (int k=0;k<paddingOut;k++)
					{
					fputc(0x00,outptr);
					}
		   	
        	if (z+1 < n)
        		{
        		fseek(inptr,-(3*bi.biWidth),SEEK_CUR);
        		}

    		}
        


        // skip over padding, if any
        fseek(inptr, paddingIn, SEEK_CUR);

        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}


// Functions that need to be here


