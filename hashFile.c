#include "hashFile.h"

int hashFile(FILE *input)
{
    FILE *ascii;
    int hashResult = 0;
    if ((ascii = fopen("mid.tmp", "w+r")) == NULL)
    {
        printf("Error - Couldn't open the ascii file");
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
                hashResult = (hashResult + atoi(lineNumberString)) % 1000;
                hasNext = 1;
            }
            lineNumberString[numberIndex] = number;
            if (numberIndex == LETTERS_PER_LINE - 1)
            {
                hashResult = (hashResult + atoi(lineNumberString)) % 1000;
                numberIndex = 0;
            }
            else
            {
                numberIndex += 1;
            }
        }
    }
    return hashResult % 100;
}