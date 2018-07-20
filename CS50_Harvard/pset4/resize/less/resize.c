// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *resize = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];

    // resize Bitmap 'r' number of times.
    int r = atoi(resize);

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
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

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding for new scanlines
    int padding_new = (4 - (bi.biWidth * r * sizeof(RGBTRIPLE)) % 4) % 4;

    // update new Bitmap info header
    BITMAPFILEHEADER bf_new;
    BITMAPINFOHEADER bi_new;
    bf_new = bf;
    bi_new = bi;

    // Update width and height in new Bitmap info header, resized 'r' times
    bi_new.biWidth = bi.biWidth * r;
    bi_new.biHeight = bi.biHeight * r;

    // Update size in Bitmap info header, resized 'r' times
    bi_new.biSizeImage = bi_new.biWidth * abs(bi_new.biHeight) * sizeof(RGBTRIPLE) + padding_new * abs(bi_new.biHeight);

    // Update size in Bitmap file header, resized 'r' times
    // bf_new.bfSize = bf_new.bfOffBits + bi_new.biSizeImage;
    bf_new.bfSize = bi_new.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // initiate an array of RGBTRIPLE of new size
        RGBTRIPLE triple_array[bi_new.biWidth];

        // initiate counter for array position
        int count = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to array 'r' times
            for (int n = 0; n < r; n++)
            {
                triple_array[count] = triple;
                count++;
            }
        }

        // write array into output 'r' times.
        for (int k = 0; k < r; k++)
        {
            for (int m = 0; m < bi_new.biWidth; m++)
            {
                fwrite(&triple_array[m], sizeof(RGBTRIPLE), 1, outptr);
            }

            // add new padding
            for (int p = 0; p < padding_new; p++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
