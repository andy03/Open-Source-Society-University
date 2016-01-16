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
#include<string.h>
#include<ctype.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames

    char* infile = argv[2];
    char* outfile = argv[3];
    float n = atof(argv[1]);
    
        
       if ((n < 1.0) || (n > 100.0))
    {
        printf("Resize factor must be between 1-100\n");
        return 1;
    }
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
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

      // create variables for old height and width
    int oldwidth = bi.biWidth;
    int oldheight = bi.biHeight;

    // create variables for new height and width
    int newwidth = bi.biWidth * n;
    int newheight = bi.biHeight * n;

    // determine padding
    int oldpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newpadding = (4 - (newwidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update length
    int oldlength = (oldwidth * 3) + oldpadding;

    // update image size
    bi.biSizeImage = abs(newheight) * (newwidth * sizeof(RGBTRIPLE) + newpadding);

    // update file size
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;

    // update height and width
    bi.biWidth = newwidth;
    bi.biHeight = newheight;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

   
   
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldheight); i < biHeight; i++)
    {
     for(int z =0; z<n; z++) 
    {
        fseek(inptr,54+oldlength*i,SEEK_SET);
        // iterate over pixels in scanline
        for (int j = 0; j < oldwidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            for(int p=0;p<n;p++)
            {
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        



        // then add it back (to demonstrate how)
        for (int k = 0; k < newpadding; k++)
        {
            fputc(0x00, outptr);
        }
        
       
    }
    
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
