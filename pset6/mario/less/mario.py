import cs50
while True:
    # Prompt user for integer
    n = cs50.get_int("Height : ")
    # If the height is around 1~8 then break
    if n >= 1 and n <= 8:
        break

for i in range(n):
    p = n-1
    # Output space while (height - 1) is less than number of repeat
    while p > i:
        p -= 1
        print(" ", end="")
    j = 0
    # Output hashtag while j is less than equal to the number of repeat
    while j <= i:
        j += 1
        print("#", end="")
    print("\n", end="")