#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


#define PATTERN_SIZE 17
#define SHIFT 1


int shift(int index, char *pattern, int *table, char symbol){
    if (strchr(pattern, symbol) == NULL &&
        index == strlen(pattern) - SHIFT || index == 0)
        return strlen(pattern);
    else if(strchr(pattern,symbol) == NULL &&
            index != strlen(pattern) - SHIFT)
        return table[strlen(pattern) - SHIFT];
    else
        return table[strchr(pattern,symbol) - pattern];

}


int changeIndx(int textIndx, int patlen, char *pattern,
               char *text, int *table){
    int nowIndx = textIndx;
    for (int i = patlen - SHIFT; i >= 0; i--) {
        if (pattern[i] == text[nowIndx]) {
            printf("%d ", nowIndx + SHIFT);
            if (i != 0)
                nowIndx--;
            else
                return textIndx + patlen;
        }
        else {
            printf("%d ", nowIndx + SHIFT);
            nowIndx = textIndx + shift(i, pattern, table, text[nowIndx]);
            return nowIndx;
        }
    }
}


void boyerMooreSearch(char* text, char* pattern,
                      int patlen,int textlen, int *table) {
    int textIndx = patlen - SHIFT;
    while(textIndx < textlen - SHIFT)
        textIndx = changeIndx(textIndx, patlen, pattern,
                              text, table);
}


void fillTable(int *table, char *pattern, int patlen){
    table[patlen - SHIFT] = patlen - SHIFT;
    for (int i = patlen - 2; i >= 0; i--) {
        if (strrchr(pattern, pattern[i]) - pattern == i)
            table[i] = patlen - i - SHIFT;
        else
            table[i] = table[strrchr(pattern, pattern[i]) - pattern];
    }
}


int main(){
    int patlen, textlen = 1, *table, symbol;
    char *text, pattern[PATTERN_SIZE];
    gets(pattern);
    patlen = strlen(pattern);
    text = (char*)malloc(sizeof(char));
    table = (int*)malloc(patlen * sizeof(int));
    symbol = getc(stdin);

    while (symbol != EOF){
        text[textlen - 1] = (char) symbol;
        textlen++;
        text = (char*)realloc(text, textlen * sizeof(char));
        symbol = getc(stdin);
    }

    if (textlen - SHIFT == 0) {
        return 0;
    }

    fillTable(table, pattern, patlen);
    boyerMooreSearch(text, pattern, patlen, textlen, table);


    return 0;
}