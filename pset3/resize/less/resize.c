// Resize bmp fie by a factor of n
// Problem set 4
// Using the rewrite method

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }

    // remember the n factor
    int n = atoi(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // declaring width and height for the new file
    int Width1 = bi.biWidth;
    int Height1 = bi.biHeight;
    int Width2 = Width1 * n;
    int Height2 = Height1 * n;

    // declaring old padding and new padding
    int padding1 = (4 - (Width1 * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding2 = (4 - (Width2 * sizeof(RGBTRIPLE)) % 4) % 4;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // update the header
    bi.biHeight = Height2;
    bi.biWidth = Width2;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * Width2) + padding2) * abs(Height2);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // create an array for the rewrite
    RGBTRIPLE array[Width2 * sizeof(RGBTRIPLE)];

    // for each row
    for (int i = 0, biHeight = abs(Height1); i < biHeight; i++)
    {
        // for each pixel
        for (int j = 0; j < Width1; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write triple to an array
            for (int k = 0; k < n; k++)
            {
                array[(j * n) + k] = triple;
            }
        }

        // skip over padding, if any
        fseek(inptr, padding1, SEEK_CUR);

        // write the current array n times
        for (int j = 0; j < n; j++)
        {
            // write the array to the output
            fwrite(array, sizeof(RGBTRIPLE), Width2, outptr);

            // write the padding
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}