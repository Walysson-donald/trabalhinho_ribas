/*
    Nome de variavel com duas palvras: nome1_nome2 (da pra mudar caso se queira).
    Sem comentarios extremamente zueiros, uma piada cá ou lá taokei, maioria dos comentarios,      quando tiver, deve ser explicativos.
    Structs typdef deve conter a primeira letra maiuscula.
    Segue estrutura de {} (tanto para for, if ou outra coisa), que vamos usar:
    if (1 == 1){
        printf("Hello World!");
        ...
    }
    Codigo deve ser modularizado, conter diversas funcoes que vamos precisar, obrigatoriamente     vamos usar o cabeçalho da função em cima da main, e desenvolver ela por extenso a baixo da     main.
    Vamos tentar deixar as variaveis em portugues e por extenso, valor (ao inves de val), caso     a palavra for grande (>10 letras, talvez) podemos ver um jeito de abreviar caso precisa.

    caso queira fazer sugestao pra manter o codigo limpo add embaixo dessa linha:
    
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXIMA_QUANTIDADE_ALGORISMOS_ARTIGO 3

typedef struct temp_name_node{
    float valor;
    struct temp_name_node *proximo;
    struct temp_name_node *antes;
}Node;

typedef struct{
    int tamanho;
    Node *head;    //imagino que voce codou usando head tail e node, vou manter esses nomes
    Node *tail; 
}Lista;

Lista *criar_lista();

//observ que ao chamar essa fc, deve ser passado quem é o antes e o proximo do node a ser add
Node *criar_node(Node *antes, float valor, Node *proximo); 

//    note que se indice == 0, implica que valor deve vir antes do lista->head,
//    se indicde == 1, implica que valor deve ir entre lista->head e o proximo.
void adicionar_meio_lista(Lista *lista, float valor, int indice);

// void adicionar_inicio_lista(Lista *lista, float valor);    //vou deixar pra vc add rafa

// void adicionar_final_lista(Lista *lista, float valor);     //vou deixar pra vc add rafa

// void lps_calculo(...)    //add ai rafa

//vamo fazer ele normal e depois tenta modificar o kmp
// void kmp_calculo(...)    //add ai rafa

// acho que remoção nao é tão necessaria, talvez uma função pra deletar uma lista inteira é uma boa
void deletar_lista(Lista *lista);

// void 


int main(void) {
    
    char caminho_texto[30], numero[MAXIMA_QUANTIDADE_ALGORISMOS_ARTIGO + 20000];
    char str[100];
    int i = 1;
    FILE *artigo;
    
    strcpy(caminho_texto, "dados/textos/texto_");
    // variaveis deve ser declaradas em cima dessa linha (até a main) e apenas por aqui.

    //talvez da pra deixar em funcao isso aqui em baixo
    // artigo = fopen("dados/textos/texto_1.txt" ,"r");
    printf("a");
    // essa bosta nao funciona, se esse while ta nao comentado o codigo nem roda0
    // objetivo: programa reconhecer quantos arquivos existem no /dados/textos
    // artigo = fopen(strcat(strcat(caminho_texto, "1"), ".txt"), "r");
    while( NULL != (artigo = fopen(strcat(strcat(caminho_texto, "1"), ".txt"), "r")) ){
        printf("a");
        i++;
        // fscanf(artigo, "%s", str);
        sprintf(numero, "%d", i);
        fclose(artigo);
    }
    
    // char str[80] = "dados/textos/texto_";
    //     char str1[500];
    //    FILE* arq = fopen(strcat(strcat(str, "1"), ".txt"), "r");
    //     fscanf(arq, "%s", str1);
    //     printf("%s",str1);
    //    return(0);
    

    return 0;
}





Lista *criar_lista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->head = NULL;
    lista->tail = NULL;
    lista->tamanho = 0;
    return lista;
}

Node *criar_node(Node *antes, float valor, Node *proximo){
    Node *newnode = malloc(sizeof(Node));
    newnode->antes = antes;
    newnode->proximo = proximo;
    newnode->valor = valor;
    return newnode;
}

void adicionar_meio_lista(Lista *lista, float valor, int indice){
    if(indice >= lista->tamanho){
        // adicionar_inicio_lista(lista, valor);
        return;
    }
    if(indice <= 0){
        // adicionar_final_lista(lista, valor);
        return;
    }
    Node *auxiliar = lista->head;
    for(int i = 0; i < indice-1; i++){      //chegamos até o node antes     
        auxiliar = auxiliar->proximo;       //que o auxiliar vai estar 
    }
    Node *novonode = criar_node(auxiliar, valor, auxiliar->proximo);
    auxiliar->proximo->antes = novonode;
    auxiliar->proximo = novonode; 
    lista->tamanho++;
    //nao precisa lidar com tail e head
}

void deletar_lista(Lista *lista){
    Node *delete_node = lista->head;
    while(delete_node != NULL){
        Node *auxiliar = delete_node;
        free(delete_node);
        delete_node = auxiliar->proximo;
    }
    free(lista);
}