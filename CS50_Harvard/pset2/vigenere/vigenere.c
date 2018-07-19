#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


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
        int klen = strlen(k);


        int temp[klen];
        for(int i = 0; i < klen; i++)
        {
            if(k[i] > 64 && k[i] < 91)
            {
                temp[i] = (int) k[i] - 65;
            }
            else if(k[i] > 96 && k[i] < 123)
            {
                temp[i] = (int) k[i] - 97;
            }
            else
            {
                printf("Usage: ./vinegere k\n");
                return 1;
            }
        }


        printf("plaintext: ");
        string p = get_string(); // get user input to encrypt.
        int plen = strlen(p);

        string r = malloc(plen);
        for(int i = 0, j = 0; i < plen; i++)
        {
            if(j >= klen)
            {
                j = 0;
            }

            if((int) p[i] > 64 && (int) p[i] < 91)
            {
                int chg = (int) p[i] + temp[j];

                if(chg > 90)
                {
                    r[i] = 65 + ((int) p[i] + temp[j]) % 91;
                }
                else
                {
                    r[i] = (int) p[i] + temp[j];
                }
                j++;
            }
            else if ((int) p[i] > 96 && (int) p[i] < 123)
            {
                int chg = (int) p[i] + temp[j];

                if(chg > 122)
                {
                    r[i] = 97 + ((int) p[i] + temp[j]) % 123;
                }
                else
                {
                    r[i] = (int) p[i] + temp[j];
                }
                j++;
            }
            else
            {
                r[i] = (int) p[i];
            }
        }

        printf("ciphertext: %s\n", r);
        return 0;
    }
}