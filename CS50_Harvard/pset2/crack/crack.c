#define _XOPEN_SOURCE_ // crypt function dependancies
#include <crypt.h> // crypt function dependancies
#include <cs50.h> // Standard
#include <ctype.h> // Standard
#include <stdio.h> // Standard
#include <stdlib.h>// Standard
#include <string.h> // Standard
#include <unistd.h> // crypt function dependancies
// #include <time.h> // To check runtime

/*
anushree:50xcIMJ0y.RXo = YES - cracked in  0.508209 seconds
brian:50mjprEcqC/ts = CA - cracked in 0.006950 seconds
bjbrown:50GApilQSG3E2 = UPenn - cracked in 1284.980328 seconds
lloyd:50n0AAUD.pL8g = lloyd - cracked in 325.011859 seconds
malan:50CcfIk1QrPr6 = maybe cracked in 345.504149 seconds
maria:509nVI8B9VfuA = TF - cracked in 0.009426 seconds
natmelo:50JIIyhDORqMU = nope - cracked in 7.339336 seconds
rob:50JGnXUgaafgc = ROFL - cracked in 23.065978 seconds
stelios:51u8F0dkeDSbY = NO - cracked in 0.008418 seconds
zamyla:50cI2vYkF0YU2 = LOL - cracked in 0.382609 seconds
*/

char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int max_len = 8;
bool stop = false;

void brute(int cur_pos, int max_pos, char *pass, const char *hash);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    else
    {
        // clock_t begin = clock();

        const char *hash = argv[1];

        for (int i = 0; i < max_len; i++)
        {
            char *pass = (char *) malloc(i);
            brute(0, i, pass, hash);
        }

        // clock_t end = clock();
        // double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        // printf("cracked in %f seconds\n", time_spent);

        return 0;
    }
}

void brute(int cur_pos, int max_pos, char *pass, const char *hash)
{
    for (int j = 0; (j < 52) && !stop; j++)
    {
        pass[cur_pos] = alphabet[j]; //  give an alphabet to each position as per 'i'
        const char *hashed_pass = crypt(pass, "50");
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
            if (stop)
            {
                break;
            }
        }
    }
}