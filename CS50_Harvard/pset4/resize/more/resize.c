// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize f infile outfile\n");
        return 1;
    }

    // remember filenames
    char *resize = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];

    // resize Bitmap 'r' number of times.
    // int r = atoi(resize);
    float r;
    sscanf(resize, "%f", &r);// allows for resizing via decimals

    // int test = 1 / r;

    if (r <= 0.0 || r > 100.0)
    {
        fprintf(stderr, "f should be a floating-point value between (0.0, 100.0].\n");
        return 1;
    }

    // int test = 1 / r;
    // printf("test: %i\n", test);
    // printf("test: %s %s\n", infile, outfile);

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


    // update new Bitmap info header
    BITMAPFILEHEADER bf_new;
    BITMAPINFOHEADER bi_new;
    bf_new = bf;
    bi_new = bi;

    // Update width and height in new Bitmap info header, resized 'r' times
    bi_new.biWidth = bi.biWidth * r;
    bi_new.biHeight = bi.biHeight * r;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding for new scanlines
    int padding_new = (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Update size in Bitmap info header, resized 'r' times
    bi_new.biSizeImage = bi_new.biWidth * abs(bi_new.biHeight) * sizeof(RGBTRIPLE) + padding_new * abs(bi_new.biHeight);

    // Update size in Bitmap file header, resized 'r' times
    // bf_new.bfSize = bf_new.bfOffBits + bi_new.biSizeImage;
    bf_new.bfSize = bi_new.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // initiate an array of RGBTRIPLE of new size
    RGBTRIPLE triple_array[bi_new.biWidth];
    // RGBTRIPLE *triple_array = malloc(sizeof(RGBTRIPLE)*(bi_new.biWidth));

    /*****************************************************************
    // For r = 1.0
    *****************************************************************/
    if (r == 1.0)
    {
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    /*****************************************************************
    // For r < 1.0
    *****************************************************************/
    else if (r < 1.0)
    {
        // invert to find factor
        int testt = lroundf(1 / r);
        // printf("test: %i\n", testt);

        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            if (i % testt == 0)
            {
                int count1 = 0;

                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++)
                {
                    if (j % testt == 0)
                    {
                        // temporary storage
                        RGBTRIPLE triple;

                        // read RGB triple from infile
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                        triple_array[count1] = triple;
                        count1++;
                        // printf(" count1 is %i\n", count1);
                    }
                    else
                    {
                        // printf(" count1 is %i\n", count1);
                        // fseek(inptr, (testt - 1) * (bi.biWidth * sizeof(RGBTRIPLE) + padding), SEEK_CUR);
                        fseek(inptr, (testt - 1) * sizeof(RGBTRIPLE), SEEK_CUR);
                    }
                }

                // skip over padding, if any
                fseek(inptr, padding, SEEK_CUR);

                fwrite(&triple_array, sizeof(RGBTRIPLE), bi_new.biWidth, outptr);

                // then add it back (to demonstrate how)
                for (int k = 0; k < padding_new; k++)
                {
                    fputc(0x00, outptr);
                }
            }
            else // skips the rows that are not a factor of 'testt'
            {
                fseek(inptr, bi.biWidth * sizeof(RGBTRIPLE) + padding, SEEK_CUR);
            }
        }
    }

    /*****************************************************************
    // For r > 1.0
    *****************************************************************/
    else if (r > 1.0)
    {
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {

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
    }

    // free(triple_array);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
