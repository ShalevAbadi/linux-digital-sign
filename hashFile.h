#include <stdio.h>
#include <string.h>

#define LETTERS_PER_LINE 3
#define SIGNATURE_PREFIX "\n<Singed by BA signatures>\n"
int hashFile(FILE *input);