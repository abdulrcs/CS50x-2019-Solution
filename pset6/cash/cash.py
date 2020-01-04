import cs50
while True:
    f = cs50.get_float("Change owed: ")
    if f > 0:
        break
# Convert dollar to cents and round it
cents = int(round(f * 100))
# Check the remaining cents after dividing by a quarter / 25 cents
remaining = int(cents % 25)
# Set the quarter coins
cents1 = int(cents / 25)
# Check the remaining cents after dividing by a dime / 10 cents
remaining2 = int(remaining % 10)
# Set the dime coins
cents2 = int(remaining / 10)
# Check the remaining cents after dividing by a nickels / 5 cents
remainingcents = int(remaining2 % 5)
# Set the nickles coins
cents3 = int(remaining2 / 5)
# Add the number of quarter, dime, nickles, and cents
coins = int(cents1 + cents2 + cents3 + remainingcents)
print(int(coins))