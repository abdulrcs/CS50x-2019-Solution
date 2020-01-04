import cs50
import sys


def main():
    # Validate the key
    if len(sys.argv) > 1:
        # If the argv is not a digit then exit
        if sys.argv[1].isalpha() == True:
            print("Usage : python caesar.py k")
            exit(1)
        # Set k into argv[1] and set it to integer
        k = int(sys.argv[1])
        # Get the plaintext from the user
        p = cs50.get_string("plaintext: ")
        print("ciphertext: ", end="")
        # Loop i for the length of the plaintext
        for i in p:
            # If the current character is lowercase
            if i.islower():
                # Turn alphabet into ASCII code
                c = ord(i)
                # Turn ascii number into alphabet number ex: a = 1
                alphabet = int(c - 96)
                # Rotate alphabet after z back to a
                cipher = int(alphabet + k) % 26
                if cipher < c and cipher != 0:
                    # ((ASCII for lowercase a) - 1) + cipher
                    cipher = int(96 + cipher)
                    print(chr(cipher), end="")

            # If the current character is uppercase
            elif i.isupper():
                # Turn current character ASCII code
                c = ord(i)
                # Turn ASCII code into alphabet number ex: A = 1
                alphabet = int(c - 64)
                # Rotate alphabet from Z back to A
                cipher = int(alphabet + k) % 26
                if cipher < c and cipher != 0:
                    # ((ASCII for uppercase A) - 1) + cipher
                    cipher = int(64 + cipher)
                    print(chr(cipher), end="")
            else:
                print(i, end="")

        # Print new line after finished
        print("\n", end="")

    else:
        print("Usage : python caesar.py k")
        exit(1)


if __name__ == "__main__":
    main()