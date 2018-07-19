#define _XOPEN_SOURCE_
#include <crypt.h>
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// const char *test = "506AM4LYuoGsQ"; // B
// const char *test = "50oJbpNhk3fwg"; // Xy
// const char *test = "508JLhlfV/2gU"; // XyZ
const char *test = "50JGnXUgaafgc"; // ROLF
char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int max_len = 7;
bool stop = false;


void brute(int cur_pos, int max_pos, char* pass, const char* hash);

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    else
    {
        clock_t begin = clock();


        const char* hash = argv[1];

        for (int i = 0; i < max_len; i++)
        {
            char* pass = (char*) malloc(i);
            brute(0, i, pass, hash);
        }

        clock_t end = clock();
        double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

        printf("%f seconds\n", time_spent);

        return 0;
    }
}

void brute(int cur_pos, int max_pos, char* pass, const char* hash)
{
    for (int j = 0; (j < 52) && !stop; j++)
    {
        pass[cur_pos] = alphabet[j]; //  give an alphabet to each position as per 'i'
        const char* hashed_pass = crypt(pass,"50");
        int results = strcmp(hashed_pass, hash); // check to see if the encrypted brute forced phrase is the same as the given pass.

        if (results == 0) // if results are the same, run this (i.e. print the brute forced value).
        {
            printf("%s \n", pass);
            stop = true;
            break;
        }
        else if (cur_pos + 1 < max_pos)
        {
            brute(cur_pos + 1, max_pos, pass, hash);
            if(stop) break;
        }
    }
}

/* CODE TO PRINT RESULTS INTO A TXT FILE.

    freopen ("myfile.txt","w",stdout);

    // RUN CODES BETWEEN THESE.

    printf ("This sentence is redirected to a file.");
    fclose (stdout);

*/