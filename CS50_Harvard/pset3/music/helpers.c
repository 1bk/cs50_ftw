// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    if (strlen(fraction) == 3 && fraction[1] == '/')
    {
        // Assuming format is 'X/Y'; convert strings into 'int' type.
        int X = fraction[0] - '0';
        int Y = fraction[2] - '0';

        // Checks the remainder which then corresponds to how many whole eighth notes
        // to count as per following if conditions.
        int m = Y / 2;

        // Based on remainder, multiply numerator with the amount required for
        // denominator to be equal to eight.
        if (m == 4)
        {
            return X * 1;
        }
        else if (m == 2)
        {
            return X * 2;
        }
        else if (m == 1)
        {
            return X * 4;
        }
        else
        {
            return printf("Wrong duration format. \n");
        }
    }
    else
    {
        return printf("Wrong duration format. \n");
    }

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    string skeys[] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    string fkeys[] = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};

    string lnote = note;

    int lnote_len = strlen(lnote);
    // printf("Length of note = %i. \n", lnote_len);
    int oct;

    if (lnote_len == 2)
    {
        oct = lnote[1] - '0'; // converts char into integer.
        string key = malloc(2); // allocated the string 'key' memory for 2 characters.
        key[0] = lnote[0]; // inserts the currebt 'key' into the string.
        key[1] = '\0'; // tells C the end of the string.
        // printf("Key = %s, Octave = %i. \n", key, oct);

        int counter = 0; // initiates the counter that indicates the distance away from "A".

        while (strcmp(key, skeys[counter]) != 0) // check to see the 'distance' of the current key away from "A"
        {
            counter++;
        }

        if (counter < 3) // for cases where key is A to B. Note: becuase each octave starts at Cs and ends at As.
        {
            double mult = pow(2, (oct - 4));
            // printf("Multiplier %i, Power %i. \n", mult, counter);
            double fact = pow(2.0, (counter / 12.0));
            // printf("Factor = %f. \n", fact);
            double freq = (440) * mult * fact;
            // printf("Frequency = %f. \n", freq);
            int rfreq = (int) round(freq);
            // printf("Frequency (rounded) = %i. \n", rfreq);

            return rfreq;
        }
        else if (counter > 2 && counter < 13) // for cases where key is C to G. Note: becuase each octave starts at Cs and ends at As.
        {
            double mult = pow(2, (oct - 5));
            // printf("Multiplier %i, Power %i. \n", mult, counter);
            double fact = pow(2.0, (counter / 12.0));
            // printf("Factor = %f. \n", fact);
            double freq = (440) * mult * fact;
            // printf("Frequency = %f. \n", freq);
            int rfreq = (int) round(freq);
            // printf("Frequency (rounded) = %i. \n", rfreq);

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
            while (strcmp(key, skeys[counter]) != 0)
            {
                // printf("skey: %s, fkey: %s. \n", skeys[counter], fkeys[counter]);
                counter++;
            }
        }
        else if (key[1] == 'b')
        {
            while (strcmp(key, fkeys[counter]) != 0)
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

        if (counter < 3) // for cases where key is A to B. Note: becuase each octave starts at Cs and ends at As.
        {
            double mult = pow(2, (oct - 4));
            //    printf("Multiplier %i, Power %i. \n", mult, counter);
            double fact = pow(2.0, (counter / 12.0));
            // printf("Factor = %f. \n", fact);
            double freq = (440) * mult * fact;
            // printf("Frequency = %f. \n", freq);
            int rfreq = (int) round(freq);
            // printf("Frequency (rounded) = %i. \n", rfreq);

            return rfreq;
        }
        // for cases where key is C to G# or Ab. Note: becuase each octave starts at Cs and ends at As.
        else if (counter > 2 && counter < 13)
        {
            double mult = pow(2, (oct - 5));
            // printf("Multiplier %i, Power %i. \n", mult, counter);
            double fact = pow(2.0, (counter / 12.0));
            // printf("Factor = %f. \n", fact);
            double freq = (440) * mult * fact;
            // printf("Frequency = %f. \n", freq);
            int rfreq = (int) round(freq);
            // printf("Frequency (rounded) = %i. \n", rfreq);

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
// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "\0") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


