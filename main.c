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
    struct temp_name_node *anterior;
}Node;

typedef struct{
    int tamanho;
    Node *head;    //imagino que voce codou usando head tail e node, vou manter esses nomes
    Node *tail; 
}Lista;

Lista *criar_lista();

//observ que ao chamar essa fc, deve ser passado quem é o anterior e o proximo do node a ser add
Node *criar_node(Node *anterior, float valor, Node *proximo); 

//    note que se indice == 0, implica que valor deve vir anterior do lista->head,
//    se indicde == 1, implica que valor deve ir entre lista->head e o proximo.
void adicionar_meio_lista(Lista *lista, float valor, int indice);

void adicionar_inicio_lista(Lista *lista, float valor);    //vou deixar pra vc add rafa

void adicionar_final_lista(Lista *lista, float valor);     //vou deixar pra vc add rafa

void lps_calculo(int lps[],char *P,int M);    //add ai rafa

//vamo fazer ele normal e depois tenta modificar o kmp
void kmp_calculo(int lps[],char *P,char *T,int M);    //add ai rafa

// acho que remoção nao é tão necessaria, talvez uma função pra deletar uma lista inteira é uma boa
void deletar_lista(Lista *lista);

// fc que retorna um FILE* com o texto i que queremos
FILE *ler_artigo(int numero);

// retorna quantidade de artigo, evite chamar mais que o necessario, funcao ineficiente
int quantidade_artigo_calculo();

// float TFIDF_calculo(); //add ai rafa

// float similaridade(float *A, float *B, int size); //add ai rafa


int main(void) {
    
    char caminho_texto[30], numero[MAXIMA_QUANTIDADE_ALGORISMOS_ARTIGO + 20000];
    int quantidade_textos = quantidade_artigo_calculo();
    // variaveis deve ser declaradas em cima dessa linha (até a main) e apenas por aqui.

    
    // agora funciona, opera dinamicamente para todo txt do formato "dados/textos/texto_i.txt", em que i é um numero nao tao grande
    // foi modularizado caso precise dessas linhas, esta ai:
    // strcpy(caminho_texto, "dados/textos/texto_");
    // artigo = fopen(strcat(strcat(caminho_texto, "1"), ".txt"), "r");
    // do{
    //     /*
    //     operacoes com o texto, exemplo: captura de texto, formatação, tf-idf, vetorização, armazenamento, podem ser realizadas por aqui
    //     */


    //     // aqui encerra as operações que deve ser feita com o artigo
    //     quantidade_textos++;
    //     sprintf(numero, "%d", quantidade_textos);
    //     if(artigo != NULL)
    //         fclose(artigo);
    //     strcat(strcat(strcpy(caminho_texto, "dados/textos/texto_"), numero), ".txt");
    //     artigo = fopen(caminho_texto, "r");
    // }while( NULL != artigo );
    // free(artigo);
    // quantidade_textos--;
    
    return 0;
}

Lista *criar_lista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->head = NULL;
    lista->tail = NULL;
    lista->tamanho = 0;
    return lista;
}

Node *criar_node(Node *anterior, float valor, Node *proximo){
    Node *newnode = malloc(sizeof(Node));
    newnode->anterior = anterior;
    newnode->proximo = proximo;
    newnode->valor = valor;
    return newnode;
}

void adicionar_inicio_lista(Lista *lista, float valor){
    Node *newnode = criar_node(NULL,valor,NULL);
        if (lista -> head == NULL){
            lista -> head = newnode;
            lista -> tail = newnode; 
        }
        else{
            lista->head->anterior = newnode;
            newnode -> proximo = lista -> head; 
            lista -> head = newnode;
        }
    lista -> tamanho++;
}

void adicionar_meio_lista(Lista *lista, float valor, int indice){
    if(indice >= lista->tamanho){
        adicionar_inicio_lista(lista, valor);
        return;
    }
    if(indice <= 0){
        adicionar_final_lista(lista, valor);
        return;
    }
    Node *auxiliar = lista->head;
    for(int i = 0; i < indice-1; i++){      //chegamos até o node anterior     
        auxiliar = auxiliar->proximo;       //que o auxiliar vai estar 
    }
    Node *novonode = criar_node(auxiliar, valor, auxiliar->proximo);
    auxiliar->proximo->anterior = novonode;
    auxiliar->proximo = novonode; 
    lista->tamanho++;
    //nao precisa lidar com tail e head
}
void adicionar_final_lista(Lista *lista, float valor){
    Node *newnode = criar_node(NULL,valor,NULL);
    if (lista -> tail == NULL){
        lista -> head = newnode;
        lista -> tail = newnode;
    }
    else{
        lista->tail->proximo = newnode;
        newnode -> anterior = lista -> tail;
        lista -> tail = newnode;
    }
    lista->tamanho++;
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

void lps_calculo(int lps[],char *P,int M){
    //int M = strlen(P);
    int i=0,len=0;
    while(i<M){
        if (P[i] == P[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if (len > 0){
                len = lps[len+1];
            }
            else{
                lps[i] = 0;
                i++;
            }                
        }        
    }
}

void kmp_calculo(int lps[],char *P,char *T,int M){
    int N = strlen(T);
    int i=0,j=0,k=0;
    int result[100];

    while((N-i) >= (M-j)){
        if(P[M] == T[i]){
            i++;
            j++;
        }
        if(j == M){
            result[k] = i-j;
            k++;
            j = lps[j-1];
        }
        else if ((P[M] != T[i]) && (i < N)){
            if(j != 0){
                j = lps[j-1];
            }
            else{
                i++;
            }
        }
    }

}

int quantidade_artigo_calculo(){
    FILE *arq;
    int i = 1, continuar = 0;
    do{
        arq = ler_artigo(i);
        if(arq != NULL){
            fclose(arq);
            i++;
            continuar = 1;
        }else{
            continuar = 0;
        }
        free(arq);
    }while(continuar);
    return i - 2; // -1 pq starta em 1, outro -1 pois ele conta o texto 142 como se fosse um texto legit mas nao 'e
}

FILE *ler_artigo(int numero){
    FILE *arq = malloc(sizeof(FILE*));
    char caminho_artigo[100] = "dados/textos/texto_", numero_str[MAXIMA_QUANTIDADE_ALGORISMOS_ARTIGO + 2];
    sprintf(numero_str, "%d", numero);
    strcat(strcat(caminho_artigo, numero_str), ".txt");
    arq = fopen(caminho_artigo, "r");
    return arq;
}

