#include <cs50.h>
#include <stdio.h>

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
    //Repeat until the number of repeat "i" is less than height +1 every repeat
    for (int i = 0; i < n; i++)
    {
        //Output space while the number of (height - 1) is less than number of repeat then -1
        for (int p = n - 1; p > i; p--)
        {
            printf(" ");
        }
        //Output hashtag while j is less than equal to the number of repeat +1 every repeat
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //Output 2 spaces between 2 triangle
        printf("  ");
        //Output another triangle
        for (int x = 0; x <= i; x++)
        {
            printf("#");
        }
        printf("\n");
    }
}
