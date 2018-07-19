#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


// INCOMPLETE! 2017 10 28

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./vinegere k\n");
        return 1;
    }

    else
    {

        string k = argv[1];
        printf("key: %s\n", k); // return the 'key' input to confirm with user.

        int temp[strlen(k)];
        for(int i = 0; i < strlen(k); i++)
        {
            if(k[i] > 64 && k[i] < 91)
            {
                temp[i] = (int) k[i] - 65;
                printf("k %i, t2 %i\n", (int) k[i], temp[i]); // print to check results
            }
            else if(k[i] > 96 && k[i] < 123)
            {
                temp[i] = (int) k[i] - 97;
                printf("k %i, t2 %i\n", (int) k[i], temp[i]); // print to check results
            }
            else
            {
                printf("Usage: ./vinegere k\n");
                return 1;
            }
        }

        //printf("test: %lu \n", strlen(temp));

        printf("plaintext: ");
        string ptext = get_string();

        // printf("cyphertext: %s\n", ptext);

        string results = malloc(strlen(ptext));


        for(int i = 0, j = 0; i < strlen(ptext); i++)
        {
            printf("j = %i", j);
            if(j >= strlen(k))
            {
                j = 0;
            }

            if((int) ptext[i] > 64 && (int) ptext[i] < 91)
            {
                /*
                printf("j = %i | %c, %i | k = %i \n", j, ptext[i], (int) ptext[i], temp[j]);
                printf("temp: %i \n", (((int) ptext[i] + temp[j]) % 91));
                printf("temp2: %i \n", 65 + (((int) ptext[i] + temp[j]) % 91));
                results[i] = 65 + (((int) ptext[i] + temp[j]) % 91);
                j++;
                printf("j = %i | Re: %c \n", j, results[i]);
                */

                int chg = (int) ptext[i] + temp[j];

                if(chg > 90)
                {
                    results[i] = 65 + (((int) ptext[i] + temp[j]) % 91);
                }
                else
                {
                    results[i] = (int) ptext[i] + temp[j];
                }
                j++;
            }
            else if ((int) ptext[i] > 96 && (int) ptext[i] < 123)
            {
                /*
                printf("j = %i | %c, %i | k = %i \n", j, ptext[i], (int) ptext[i], temp[j]);
                printf("temp: %i \n", (((int) ptext[i] + temp[j]) % 123));
                printf("temp2: %i \n", 97 + (((int) ptext[i] + temp[j]) % 123));

                results[i] = 97 + (((int) ptext[i] + temp[j]) % 123);
                j++;
                printf("j = %i | Re: %c \n", j, results[i]);
                */

                int chg = (int) ptext[i] + temp[j];

                if(chg > 122)
                {
                    results[i] = 97 + (((int) ptext[i] + temp[j]) % 123);
                }
                else
                {
                    results[i] = (int) ptext[i] + temp[j];
                }
                j++;
            }
            else {
                results[i] = (int) ptext[i];
            }

            printf("j = %i", j);
            // printf("Letter: %c; Number: %i \n", ptext[i], (int) ptext[i] );

            // results[i] = (int) ptext[i] + i; // just testing

        }

        printf("Results: %s \n", results);

        return 0;
    }

}