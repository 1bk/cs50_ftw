// recovers JPEGs from forensic image.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover FILE.raw\n");
        return 1;
    }

    // remember filename
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");

    // check for error in opening input file.
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // initiate output file and set it to NULL.
    FILE *outptr = NULL;

    // allocate 512 bytes of memory and point to its address
    unsigned char *buffer = malloc(512);

    // initiate JPEG name and file counter (for number of JPEG found).
    char *filename = malloc(8);
    int counter = 0;


    // start of loop through the input file.
    // note: loop continues as long as fread below == 1.
    //       this is be want 1 block of size 512 bytes returned each time.
    //       if fread cannot return that, means we reach the EOF so it is either 0 or less than 1.
    //       see 'man fread' in terminal for more information in its "RETURN VALUE".
    while (fread(buffer, sizeof(buffer), 1, inptr) == 1)
    {
        // finds the begining of a JPEG
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) // explaination here: https://cs50.stackexchange.com/questions/23071/jpgs-fourth-byte
        {

            // if found a new JPEG header, then...
            // check if output file is open, if yes then close it, then reset 'outptr' to NULL.
            if (outptr != NULL)
            {
                fclose(outptr);
                outptr = NULL;
            }

            // assign a new file name the current counter.
            sprintf(filename, "%03i.jpg", counter);

            // open 'outptr' and name it 'filename' assigned above and allow writing permission.
            outptr = fopen(filename, "w");

            // checking?
            if (outptr == NULL)
            {
                printf("Cannot open %s.\n", filename);
                return 3;
            }

            // if no errors, write into output file from buffer
            fwrite(buffer, sizeof(buffer), 1, outptr);

            // increment the counter of JPEG found.
            counter++;
        }
        else
        {
            // if reach this 'else' implies still have not found new JPEG header.
            // hence continue writing (the current 512 block) into the current opened output (JPEG) file.
            if (outptr != NULL)
            {
                fwrite(buffer, sizeof(buffer), 1, outptr);
            }
        }
    }

    // here means while loop ended as programme reached a block with less than 512 bytes.
    // hence close outptr and inputr file, and halt.
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    if (inptr != NULL)
    {
        fclose(inptr);
    }

    // free up memory allocated for the buffer and file names.
    free(buffer);
    free(filename);

    return 0;
}