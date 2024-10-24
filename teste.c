#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <wchar.h>
#include <ctype.h>

void verifica_caractere_especial(char *comparar, char substitui, char *str, char *filtrado,int *i, int *j){
    if(strncmp(str+*i, comparar, 2) == 0){
        filtrado[*j] = 'a';
        (*j)++;
        (*i)++;
    }
}

void main(){
    FILE *arq = fopen("dados/textos/texto_1.txt", "r");
    char str[10] = "aáçd";
    char filtrado[10];
    int j = 0;
    for(int i = 0; str[i] != '\0'; i++){
        verifica_caractere_especial("ç", 'c', str, filtrado, &i, &j);
        verifica_caractere_especial("á", 'a', str, filtrado, &i, &j);
        //... aqui continua os filtros...
        if(isprint(str[i])) 
        {
            filtrado[j] = str[i];
            j++;
        }
    }
    filtrado[j] = '\0';
    printf("%s",filtrado);
}