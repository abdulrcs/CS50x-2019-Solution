#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Open the memory card file
    FILE *file = fopen(argv[1], "r");
    // Check if the file returns null
    if (file == NULL)
    {
        fprintf(stderr, "Could not open the file\n");
        return 2;
    }
    // Counter to keep track of file number
    int i = 0;
    // Set the buffer to 512 bytes
    unsigned char buffer[512];
    // Set a char for the file name
    char filename[8];
    // Declaring the output file
    FILE *img = NULL;
    while (fread(buffer, 512, 1, file) != 0)
    {
        // Start of a new JPG ?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If already found a JPG, close the image.
            if (i > 0)
            {
                fclose(img);
            }
            // Create file name for i'th image
            sprintf(filename, "%03i.jpg", i);
            // Open i'th image file
            img = fopen(filename, "w");
            // Increase the counter
            i++;
        }
        // Write everytime until find a new header
        if (i > 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    // Close the output file
    fclose(img);
    // Close the input file
    fclose(file);
}