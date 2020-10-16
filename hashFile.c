#include "hashFile.h"

int hashFile(FILE *input)
{
    int hashResult = 0;
    FILE* ascii = tmpfile(); 
    if (ascii == NULL) 
    { 
        printf("Unable to create temp file"); 
        return NULL; 
    } 
    else
    {
        char letter;
        char number;
        int hasNext = 0;
        int numberIndex = 0;
        char *lineNumberString = malloc(sizeof(char) * FOLDING_DIGITS_COUNT);
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
            if (numberIndex == FOLDING_DIGITS_COUNT - 1)
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
    return hashResult % FOLDING_MOD;
}