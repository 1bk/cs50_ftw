
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int function(string note);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./test note\n");
        return 1;
    }
    else
    {
        const string nn = argv[1];
        int result = function(nn);

        printf("Frequncy of %s is %i!\n", nn, result);
    }
}

int function(string note)
{
    string skeys[] = {"A","A#","B","C","C#","D","D#","E","F","F#","G","G#"};
    string fkeys[] = {"A","Bb","B","C","Db","D","Eb","E","F","Gb","G","Ab"};

    // string fnote = "A4@1/8";
    // string lnote = "Bb5";
    string lnote = note;
    // string rnote = "1/8";

    int lnote_len = strlen(lnote);
    // printf("Length of note = %i. \n", lnote_len);
    int oct;

    if (lnote_len == 2)
    {
        oct = lnote[1] - '0'; // converts char into integer.
        string key = malloc(2);
        key[0] = lnote[0];
        key[1] = '\0';
        // printf("Key = %s, Octave = %i. \n", key, oct);

        int counter = 0;

        while (strcmp(key,skeys[counter]) != 0)
        {
            counter++;
        }

        if (counter < 3)
        {
           double mult = pow(2, (oct - 4));
        //   printf("Multiplier %i, Power %i. \n", mult, counter);
           double fact = pow(2.0, (counter/12.0));
        //   printf("Factor = %f. \n", fact);
           double freq = (440) * mult * fact;
        //   printf("Frequency = %f. \n", freq);
           int rfreq = (int) round(freq);
        //   printf("Frequency (rounded) = %i. \n", rfreq);

           return rfreq;
        }
        else if (counter > 2 && counter < 13)
        {
           double mult = pow(2, (oct - 5));
        //   printf("Multiplier %i, Power %i. \n", mult, counter);
           double fact = pow(2.0, (counter/12.0));
        //   printf("Factor = %f. \n", fact);
           double freq = (440) * mult * fact;
        //   printf("Frequency = %f. \n", freq);
           int rfreq = (int) round(freq);
        //   printf("Frequency (rounded) = %i. \n", rfreq);

           return rfreq;
        }
        else
        {
            // printf("Error in counters.\n");
            return 999999;
        }
    }
    else if (lnote_len == 3)
    {
        oct = lnote[2] - '0';
        string key = malloc(3);
        key[0] = lnote[0];
        key[1] = lnote[1];
        key[2] = '\0';
        // printf("Key = %s, Octave = %i. \n", key, oct);

        int counter = 0;

        if (key[1] == '#')
        {
            while (strcmp(key,skeys[counter]) != 0)
            {
                // printf("skey: %s, fkey: %s. \n", skeys[counter], fkeys[counter]);
                counter++;
            }
        }
        else if (key[1] == 'b')
        {
            while (strcmp(key,fkeys[counter]) != 0)
            {
                // printf("skey: %s, fkey: %s. \n", skeys[counter], fkeys[counter]);
                counter++;
            }
        }
        else
        {
            // printf("Error in counter.\n");
            return 999999;
        }

        if (counter < 3)
        {
            double mult = pow(2, (oct - 4));
            //    printf("Multiplier %i, Power %i. \n", mult, counter);
            double fact = pow(2.0, (counter/12.0));
            // printf("Factor = %f. \n", fact);
            double freq = (440) * mult * fact;
            // printf("Frequency = %f. \n", freq);
            int rfreq = (int) round(freq);
            //    printf("Frequency (rounded) = %i. \n", rfreq);

            return rfreq;
        }
        else if (counter > 2 && counter < 13)
        {
            double mult = pow(2, (oct - 5));
            //   printf("Multiplier %i, Power %i. \n", mult, counter);
            double fact = pow(2.0, (counter/12.0));
            //   printf("Factor = %f. \n", fact);
            double freq = (440) * mult * fact;
            //   printf("Frequency = %f. \n", freq);
            int rfreq = (int) round(freq);
            //   printf("Frequency (rounded) = %i. \n", rfreq);

            return rfreq;
        }
        else
        {
            // printf("Error in counters.\n");
            return 999999;
        }
    }
    else
    {
        // printf("Error in left note length. \n");
        return 999999;
    }
}
