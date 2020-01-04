import cs50
import sys


def main():
    if len(sys.argv) == 2:
        # Set the argv[1] into text file
        text = sys.argv[1]
        # Open the text file into variable t
        t = open(text, "r")
        # Create a set called ban
        ban = set()
        # Loop through the text file and delete "\n"
        for i in t:
            striped = i.strip('\n')
            ban.add(striped)
        # Prompt user for the message
        w = cs50.get_string("What message would you like to censor? ")
        # Split the message into a list
        token = w.split(' ')
        # Loop for every line in token
        for j in token:
            # Loop for every line in ban
            for k in ban:
                # If the token is equals to the ban
                if j.lower() == k.lower():
                    # Censor the token with "*" times the length of the token
                    j = ("*" * len(j))
            # Print the token every iteration
            print(j, end=" ")
        # End it with a new line
        print("\n", end="")

    else:
        print("Usage: python bleep.py banned.txt")
        exit(1)


if __name__ == "__main__":
    main()