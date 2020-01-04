#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Calls prototype for float f and the input function
float f;
float get_pfloat(string prompt);

int main(void)
{
    // User input the change owed
    f = get_pfloat("Change owed : ");
    // Convert dollar to cents and round it
    int cents = round(f * 100);
    // Check the remaining cents after dividing by a quarter / 25 cents
    int remaining = cents % 25;
    // Set the quarter coins
    int cents1 = cents / 25;
    // Check the remaining cents after dividing by a dime / 10 cents
    int remaining2 = remaining % 10;
    // Set the dime coins
    int cents2 = remaining / 10;
    // Check the remaining cents after dividing by a nickels / 5 cents
    int remainingcents = remaining2 % 5;
    // Set the nickles coins
    int cents3 = remaining2 / 5;
    // Add the number of quarter, dime, nickles, and cents
    int coins = cents1 + cents2 + cents3 + remainingcents;
    printf("%i\n", coins);
}

// The function to get a number greater than 0
float get_pfloat(string prompt)
{
    do
    {
        f = get_float("%s", prompt);
    }
    // if the input is less than zero, loop until input is greater than 0
    while (f < 0);
    return f;
}
