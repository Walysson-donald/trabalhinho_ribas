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
    Vamos tentar deixar as variaveis em portugues e por extenso, palavra (ao inves de val), caso     a palavra for grande (>10 letras, talvez) podemos ver um jeito de abreviar caso precisa.

    caso queira fazer sugestao pra manter o codigo limpo add embaixo dessa linha:
    
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>

#define MAXIMA_QUANTIDADE_ALGORISMOS_ARTIGO 3
#define MAXIMO_TAMANHO_PALAVRA 100

typedef struct temp_name_node{
    char *palavra;
    int tamanho;
    struct temp_name_node *proximo;
    struct temp_name_node *anterior;
}Node;

typedef struct{
    int qnt_palavras;
    Node *head;    //imagino que voce codou usando head tail e node, vou manter esses nomes
    Node *tail; 
}Lista;

Lista *criar_lista();

//observ que ao chamar essa fc, deve ser passado quem é o anterior e o proximo do node a ser add
Node *criar_node(Node *anterior, char *palavra, Node *proximo); 

//    note que se indice == 0, implica que palavra deve vir anterior do lista->head,
//    se indicde == 1, implica que palavra deve ir entre lista->head e o proximo.
void adicionar_meio_lista(Lista *lista, char *palavra, int indice);

void adicionar_inicio_lista(Lista *lista, char *palavra);    //vou deixar pra vc add rafa

void adicionar_final_lista(Lista *lista, char *palavra);     //vou deixar pra vc add rafa

void printa_lista(Lista *lista);

void lps_calculo(int lps[], char *P, int M);    //add ai rafa

//vamo fazer ele normal e depois tenta modificar o kmp
int kmp_calculo(int lps[],char *P,char *T,int M);    //add ai rafa

// acho que remoção nao é tão necessaria, talvez uma função pra deletar uma lista inteira é uma boa
void deletar_lista(Lista *lista);

int deletar_final_lista(Lista *lista);

// fc que retorna um FILE* com o texto i que queremos
FILE *abrir_artigo(int numero);

// retorna quantidade de artigo, evite chamar mais que o necessario, funcao ineficiente
int quantidade_artigo_calculo();

// float TFIDF_calculo(); //add ai rafa

// float similaridade(float *A, float *B, int size); //add ai rafa

// passa um File* do artigo e retorna uma Lista * contendo todas as palavras do artigo
Lista *ler_artigo(FILE *artigo);





int main(void) {

    setlocale(LC_ALL, "Portuguese");

    int quantidade_artigo = quantidade_artigo_calculo();
    //  printf("%d", quantidade_artigo);
    //  testes:
    FILE *art;
    Lista *lista;
    for(int i = 1; i <= 1; i++){
        art = abrir_artigo(i);
        lista = criar_lista();
        lista = ler_artigo(art);
        fclose(art);
        free(art);
        deletar_lista(lista);
    }
    //  final testes
    return 0;

}





Lista *criar_lista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->head = NULL;
    lista->tail = NULL;
    lista->qnt_palavras = 0;
    return lista;
}

Node *criar_node(Node *anterior, char *palavra, Node *proximo){
    Node *newnode = malloc(sizeof(Node));
    newnode->anterior = anterior;
    newnode->proximo = proximo;
    newnode->tamanho = strlen(palavra);
    newnode->palavra = malloc(newnode->tamanho + 1);
    strcpy(newnode->palavra, palavra);
    return newnode;
}

void adicionar_inicio_lista(Lista *lista, char *palavra){
    Node *newnode = criar_node(NULL,palavra,NULL);
        if (lista -> head == NULL){
            lista -> head = newnode;
            lista -> tail = newnode; 
        }
        else{
            lista->head->anterior = newnode;
            newnode -> proximo = lista -> head; 
            lista -> head = newnode;
        }
    lista -> qnt_palavras++;
}

void adicionar_meio_lista(Lista *lista, char *palavra, int indice){
    if(indice >= lista->qnt_palavras){
        adicionar_inicio_lista(lista, palavra);
        return;
    }
    if(indice <= 0){
        adicionar_final_lista(lista, palavra);
        return;
    }
    Node *auxiliar = lista->head;
    for(int i = 0; i < indice-1; i++){      //chegamos até o node anterior     
        auxiliar = auxiliar->proximo;       //que o auxiliar vai estar 
    }
    Node *novonode = criar_node(auxiliar, palavra, auxiliar->proximo);
    auxiliar->proximo->anterior = novonode;
    auxiliar->proximo = novonode; 
    lista->qnt_palavras++;
    //nao precisa lidar com tail e head
}

void adicionar_final_lista(Lista *lista, char *palavra){
    Node *newnode = criar_node(NULL,palavra,NULL);
    if (lista -> tail == NULL){
        lista -> head = newnode;
        lista -> tail = newnode;
    }
    else{
        lista->tail->proximo = newnode;
        newnode -> anterior = lista -> tail;
        lista -> tail = newnode;
    }
    lista->qnt_palavras++;
}

void deletar_lista(Lista *lista){
    Node *delete_node = lista->head;
    while(delete_node != NULL){
        Node *auxiliar = delete_node;
        free(delete_node->palavra);
        free(delete_node);
        delete_node = auxiliar->proximo;
    }
    free(lista);
}   

int deletar_final_lista(Lista *lista){

    if(lista->qnt_palavras == 0) 
        return 0;

    if(lista->qnt_palavras == 1)
        lista->head = NULL;
    
    Node *delete_node = lista->tail;
    free(delete_node->palavra);
    lista->tail->anterior->proximo = NULL;
    lista->tail = lista->tail->anterior;
    free(delete_node);
    lista->qnt_palavras--;
    return 1;
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

int kmp_calculo(int lps[],char *P,char *T,int M){ //alterar
    int N = strlen(T);
    int i=0,j=0;
    int quantidade_palavras_iguais = 0;

    while((N-i) >= (M-j)){
        if(P[M] == T[i]){
            i++;
            j++;
        }
        if(j == M){
            quantidade_palavras_iguais++;
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
    return quantidade_palavras_iguais;
}

int quantidade_artigo_calculo(){
    FILE *arq;
    int i = 1, continuar = 0;
    do{
        arq = abrir_artigo(i);
        if(arq != NULL){
            fclose(arq);
            i++;
            continuar = 1;
        }else{
            continuar = 0;
        }
        free(arq);
    }while(continuar);
    return i - 1; // -1 pois ele conta o texto 142 como se fosse um texto legit mas nao 'e
}

FILE *abrir_artigo(int numero){
    FILE *arq = malloc(sizeof(FILE));
    char caminho_artigo[100] = "dados/textos/texto_", numero_string[MAXIMA_QUANTIDADE_ALGORISMOS_ARTIGO + 2];
    sprintf(numero_string, "%d", numero);
    strcat(strcat(caminho_artigo, numero_string), ".txt");
    arq = fopen(caminho_artigo, "r");
    return arq;
}

Lista *ler_artigo(FILE *artigo){
    Lista *lista = malloc(sizeof(lista));
    char palavra[MAXIMO_TAMANHO_PALAVRA + 1];

    int anterior_ftell = -1;
    int atual_ftell = -1;

    do{
        anterior_ftell = atual_ftell;
        fscanf(artigo," %s", palavra);
        // fgets(palavra, sizeof(palavra), artigo); 
        adicionar_inicio_lista(lista, palavra);
        // printf(" %s ",palavra); // caso precise verificar oq está na lista lida basta descomentar essa linha
        atual_ftell = ftell(artigo);
    }while(atual_ftell != anterior_ftell);
    deletar_final_lista(lista);
    return lista;
}

void printa_lista(Lista *lista){
    Node *auxnode = lista->head;
    int i = 1;
    while(auxnode != NULL){
        printf("elemento %d: %s\n", i, palavra);
        auxnode = auxnode->proximo;
        i++;
    }
}
