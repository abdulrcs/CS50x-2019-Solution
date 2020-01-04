#include <cs50.h>
#include <stdio.h>

// Calls the prototype for the function
int get_positive(string prompt);
void height(int n);

int main(void)
{
    int n = get_positive("Height: ");
    height(n);
}

// Prompt user for number above 1 and less than 8
int get_positive(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8);
    return n;
}

void height(int n)
{
    for (int i = 0; i < n; i++)
    {
        // Output space while (height - 1) is less than number of repeat
        for (int p = n - 1; p > i; p--)
        {
            printf(" ");
        }
        // Output hashtag while j is less than equal to the number of repeat
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
