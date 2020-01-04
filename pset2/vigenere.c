#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Prototype for the shift function
int shift(char c);

int main(int argc, string argv[])
{
    // Validate the key
    if (argc == 2)
    {
        // Loop while the iteration times is less than length of key
        for (int n = 0; n < strlen(argv[1]); n++)
        {
            if (isalpha(argv[1][n]) == false)
            {
                printf("Usage : ./vigenere keyword\n");
                return 1;
            }
        }
        // Ask user for plaintext
        string p = get_string("plaintext: ");
        printf("ciphertext: ");
        // The key is using shift function every j'th charater
        for (int i = 0; i < strlen(p); i++)
        {
            // Convert the i'th character of plaintext into integer
            int c = (int) p[i];
            int k = shift(argv[1][i % strlen(argv[1])]);
            if (islower(p[i]))
            {
                int alphabet = c - 96; // Turns ascii code into alphabet ex : a = 1
                int cipher = (alphabet + k) % 26; // Rotate alphabet after z back to a
                if (cipher < c && cipher != 0)
                {
                    cipher = 96 + cipher; // (Ascii lowercase a) + cipher
                    printf("%c", cipher);
                }
                else if (cipher == 0)
                {
                    cipher = c + k;
                    printf("%c", cipher);
                }
                else
                {
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
                    cipher = 64 + cipher; // (Ascii of uppercase a) + cipher
                    printf("%c", cipher);
                }
                else if (cipher == 0)
                {
                    cipher = c + k;
                    printf("%c", cipher);
                }
                else
                {
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
        printf("Usage : ./vigenere keyword\n");
        return 1;
    }
}

int shift(char c)
{
    int a = (int) c;
    if (isupper(c)) // If the character is uppercase
    {
        a = a - 65; // Substracted by 65 because A is 65 in ascii
    }
    else if (islower(c))
    {
        a = a - 97; // Substracted by 97 because a is 97 in ascii
    }
    else
    {
        a = c;
    }
    return a;
}
