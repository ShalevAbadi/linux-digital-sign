#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rsa.h"

#define LETTERS_PER_LINE 8

unsigned long long hashFile(FILE *input)
{
    FILE *ascii;
    unsigned long long hashResult = 0;
    if ((ascii = fopen("ascii.txt", "r+")) == NULL)
    {
        printf("Error - Couldn't open the file");
    }
    else
    {
        char letter;
        char number;
        int hasNext = 0;
        int numberIndex = 0;
        char *lineValue = malloc(sizeof(char) * LETTERS_PER_LINE);
        char *lineNumberString = malloc(sizeof(char) * LETTERS_PER_LINE);
        while ((letter = fgetc(input)) != EOF)
        {
            if (letter != EOF)
            {
                fprintf(ascii, "%d", letter);
            }
        }
        fseek(ascii, 0, SEEK_SET);
        while (!hasNext)
        {
            number = fgetc(ascii);
            if (number == EOF)
            {
                hashResult = hashResult + atoi(lineNumberString);
                hasNext = 1;
            }
            lineNumberString[numberIndex] = number;
            if (numberIndex == LETTERS_PER_LINE - 1)
            {
                hashResult = hashResult + atoi(lineNumberString);
                numberIndex = 0;
            }
            else
            {
                numberIndex += 1;
            }
        }
    }
    return hashResult;
}

int main()
{
    FILE *input;
    if ((input = fopen("input.txt", "r")) == NULL)
    {
        printf("Error - Couldn't open the file");
    }
    rsa(hashFile(input));
}