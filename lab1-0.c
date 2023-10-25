#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define PATTERN_SIZE 17


int main(){
    int patlen, textlen = 0;
    char *text, pattern[PATTERN_SIZE], symbol;
    gets(pattern);
    patlen = strlen(pattern);
    text = (char*)malloc(sizeof(char));
    symbol = getc(stdin);

    while (symbol != EOF){
        textlen++;
        text = (char*)realloc(text, textlen * sizeof(char));
        *(text + textlen - 1) = (char)symbol;
        symbol = getc(stdin);
    }

    return 0;
}
