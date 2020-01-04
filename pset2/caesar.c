#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Validate the key
    if (argc == 2)
    {
        // Loop while the iteration times is less than length of key
        for (int n = 0; n < strlen(argv[1]); n++)
        {
            if (isdigit(argv[1][n]) == 0)
            {
                printf("Usage : ./caesar key\n");
                return 1;
            }
        }
        // Convert the string into int
        int k = atoi(argv[1]);
        // Get the plaintext from the user
        string p = get_string("plaintext: ");
        printf("ciphertext: ");
        // Loop while the iteration times is less than length of plaintext
        for (int i = 0; i < strlen(p); i++)
        {
            // Convert the char of plaintext into an int / an ascii
            int c = (int) p[i];
            // If the character is lowercase then do this
            if (islower(p[i]))
            {
                int alphabet = c - 96; // Turns ascii code into alphabet ex : a = 1
                int cipher = (alphabet + k) % 26; // Rotate alphabet after z back to a
                if (cipher < c && cipher != 0)
                {
                    cipher = 96 + cipher; // (Ascii lowercase a - 1) + cipher
                    printf("%c", cipher);
                }
            }
            // If the character is uppercase then do this
            else if (isupper(p[i]))
            {
                int alphabet = c - 64; // Turns ascii code into alphabet ex : A = 1
                int cipher = (alphabet + k) % 26; // Rotate alphabet from z back to a
                if (cipher < c && cipher != 0)
                {
                    cipher = 64 + cipher; // (Ascii of uppercase a - 1) + cipher
                    printf("%c", cipher);
                }
            }
            else
            {
                printf("%c", c);
            }
        }
        printf("\n");
    }
    else
    {
        printf("Usage : ./caesar key\n");
        return 1;
    }
}
