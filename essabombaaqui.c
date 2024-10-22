ji/*
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
#include <math.h>

#define MAXIMA_QUANTIDADE_ALGORISMOS_ARTIGO 3
#define MAXIMO_TAMANHO_PALAVRA 100

typedef struct temp_name_node{
    char *palavra;
    int tamanho;
    struct temp_name_node *proximo;
    struct temp_name_node *anterior;
}Node;

typedef struct{
    int tamanho;
    Node *head;    //imagino que voce codou usando head tail e node, vou manter esses nomes
    Node *tail; 
}Lista;

typedef struct Texto{
    char *text;
    int tamanho;
}Texto;

typedef struct Pilha{
    float itens[100];
    int topo;
}Pilha;

typedef struct Palavra{
    int qnt_artigos_aparece;
    char conteudo[100];
}Palavra;

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
int kmp_calculo_com_erros(int lps[],char *P,char *T,int M);    //add ai rafa

// acho que remoção nao é tão necessaria, talvez uma função pra deletar uma lista inteira é uma boa
void deletar_lista(Lista *lista);

int deletar_final_lista(Lista *lista);

// fc que retorna um FILE* com o texto i que queremos
FILE *abrir_artigo(int numero);

int tamanho_arquivo(FILE *arquivo);

// retorna quantidade de artigo, evite chamar mais que o necessario, funcao ineficiente
int quantidade_artigo_calculo();

float TFIDF_calculo(float fc_TF,float IDF); //add ai rafa

// float similaridade(float *A, float *B, int size); //add ai rafa

// passa um File* do artigo e retorna uma Lista * contendo todas as palavras do artigo
Texto *ler_artigo(FILE *artigo);

float fc_TF(int frequencia,int tamanho);

float fc_IDF(int num_docs_palavra_aparece,int num_doc_total);

void inicializar_pilha(Pilha *P);

int isEmpty(Pilha *P);

float pop(Pilha *P);

void push(Pilha *P,float item);

void fc_matriz_TFIDF(Pilha *TF,Pilha *IDF,float matriz_TFIDF[][],int tamanho_vocabulario,int quantidade_artigo);

void calculo_vetor_busca(char vetor_TFIDF[], char query[],Pilha *TF,Pilha *IDF,float matriz_TFIDF[][],int tamanho_vocabulario,int quantidade_artigo);

int verifica_caso_usuario_queira_recalcular_TFIDF();

int main(void) {

    setlocale(LC_ALL, "Portuguese");
    int quantidade_artigo = quantidade_artigo_calculo();    

    // IMPORTANTE:
    // precisa criar um meio de armazenar o tfidf apos ele ser calculado, e se haver um tfidf apenas leia o arquivo ao inves de calcular tudo denovo.
    int opcao;
    if(opcao = verifica_caso_usuario_queira_recalcular_TFIDF()){
        FILE *TFIDFarq = fopen("TFIDF.bin", "rb");

    } // precisa saber mais um pouco de informação sobre como vai ser o TFIDF, talvez a leitura deve ir para um int**
    // ideia: na funcao de calcular tfidf verificamos o verifica_caso_usuario_queira_recalcular_TFIDF() e entao decidimos o que deve ser feito
    
    Pilha *TF,*IDF;
    FILE *vocabulario;
    char query[100];
    char *vetor_TFIDF;
    vetor_TFIDF = malloc(sizeof(char) * 100);
    int j=0;

    int tamanho_vocabulario = tamanho_arquivo(vocabulario);
    float matriz_TFIDF[tamanho_vocabulario][quantidade_artigo];

    fc_matriz_TFIDF(TF,IDF,matriz_TFIDF,tamanho_vocabulario,quantidade_artigo);

    fgets(query,sizeof(query),stdin);

    calculo_vetor_busca(vetor_TFIDF, query, TF, IDF, matriz_TFIDF, tamanho_vocabulario, quantidade_artigo);

    
    return 0;

}





Lista *criar_lista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->head = NULL;
    lista->tail = NULL;
    lista->tamanho = 0;
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
    lista -> tamanho++;
}

void adicionar_meio_lista(Lista *lista, char *palavra, int indice){
    if(indice >= lista->tamanho){
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
    lista->tamanho++;
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
    lista->tamanho++;
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

    if(lista->tamanho == 0) 
        return 0;

    if(lista->tamanho == 1)
        lista->head = NULL;
    
    Node *delete_node = lista->tail;
    free(delete_node->palavra);
    lista->tail->anterior->proximo = NULL;
    lista->tail = lista->tail->anterior;
    free(delete_node);
    lista->tamanho--;
    return 1;
}

void lps_calculo(int lps[],char *P,int M){
    //int M = strlen(P);
    int i=1,len=0;
    lps[0] = 0;

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

int kmp_calculo_com_erros(int lps[], char *P, char *T, int M) {
    // T = Texto
    // P = Padrao
    // M = tamanho de T
    // N = tamanho de P
    int N = strlen(T);
    int i = 0, j = 0;
    int quantidade_palavras_iguais = 0;
    int erros = 0;
    int erro_max = 1;

    while ((N - i+erro_max) >= (M - j)) {
        if (P[j] == T[i]) {
            i++;
            j++;
        } 
        else {
            erros++;
            if (erros > erro_max) {
                if (j != 0) {
                    j = lps[j - 1];
            } 
            else {
                i++;
            }
                erros = 0; 
            } 
            else { 
               i++;
                j++;
            }
        }

        if (j == M) {
            quantidade_palavras_iguais++;
            j = lps[j - 1];
            erros = 0; 
        }
    }
    return quantidade_palavras_iguais;
}

/*
int kmp_calculo_com_erros(int lps[], char *P, Lista *T, int M) {
    int N = (T -> tamanho);
    int i = 0, j = 0;
    int quantidade_palavras_iguais = 0;
    int erros = 0;
    int erro_max = 1;

    while ((N - i+erro_max) >= (M - j)) {
        if (P[j] == T -> head) {
            i++;
            j++;
        } else {
            erros++;
            if (erros > erro_max) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
                erros = 0; 
            } else { 
                i++;
                j++;
            }
        }

        if (j == M) {
            quantidade_palavras_iguais++;
            j = lps[j - 1];
            erros = 0; 
        }
    }
    return quantidade_palavras_iguais;
} 
*/

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
    }while(continuar);
    return i - 1; // -1 pois ele conta o texto 142 como se fosse um texto legit mas nao 'e
}

FILE *abrir_artigo(int numero){
    FILE *artigo;
    char caminho_artigo[100] = "dados/textos/texto_", numero_string[MAXIMA_QUANTIDADE_ALGORISMOS_ARTIGO + 2];
    sprintf(numero_string, "%d", numero);
    strcat(strcat(caminho_artigo, numero_string), ".txt");
    artigo = fopen(caminho_artigo, "r");
    return artigo;
}

/*
Texto *ler_artigo(FILE *artigo) {

    fseek(artigo, 0, SEEK_END);
    long tamanho_arquivo = ftell(artigo);
    rewind(artigo);

    Texto *texto = malloc((tamanho_arquivo + 1) * sizeof(char));

    fread(texto -> text, sizeof(char), tamanho_arquivo, artigo);
    texto -> text[tamanho_arquivo] = '\0'; 

    return texto;
} */


Texto* ler_artigo(FILE *artigo) {

    Texto *texto = malloc(sizeof(Texto));


    texto->text = NULL;
    texto-> tamanho = 0;

    char palavra[MAXIMO_TAMANHO_PALAVRA + 1];
    int anterior_ftell = -1;
    int atual_ftell = -1;

    int tamanho_total = 0;

    do {
        anterior_ftell = atual_ftell;
        if (fscanf(artigo, " %s", palavra) == EOF) break;

        texto->tamanho++;

        tamanho_total += strlen(palavra) + 1; 

        texto->text = realloc(texto->text, tamanho_total * sizeof(char));

        if (texto->tamanho == 1) {
            strcpy(texto->text, palavra);
        } else {
            strcat(texto->text, " ");   
            strcat(texto->text, palavra);
        }

        atual_ftell = ftell(artigo);
    } while (atual_ftell != anterior_ftell);

    return texto;
}


void printa_lista(Lista *lista){
    Node *auxnode = lista->head;
    int i = 1;
    while(auxnode != NULL){
        printf("elemento %d: %s\n", i, auxnode -> palavra);
        auxnode = auxnode->proximo;
        i++;
    }
}

float fc_TF(int frequencia,int tamanho ){
    return (frequencia/tamanho);
}

float fc_IDF(int num_docs_palavra_aparece,int num_doc_total){
    return (log(num_doc_total/(num_docs_palavra_aparece+1)));
}

float TFIDF_calculo(float TF,float IDF){

    return (TF*IDF);
}

int tamanho_arquivo(FILE *arquivo) {

    if(arquivo == NULL)
    {
        printf("erro ao ler o arquivo");
        return 0;
    }
    
    fseek(arquivo, 0, SEEK_END);
    
    int tamanho = ftell(arquivo);
    
    rewind(arquivo);
    
    return tamanho;
}

int verifica_caso_usuario_queira_recalcular_TFIDF(){
    char escolha;
    do{
        printf("Primeira vez executando esse código ou deseja re-calcular TF-IDF? (s/n)\n");
        scanf(" %c", &escolha);
        if(escolha != 's' && escolha != 'n')
            printf("sua escolha deve ser sim (s) ou não (n)!\n");
    }while(escolha != 's' && escolha != 'n');
    if(escolha == 's')
        return 1;
    return 0;
}

void inicializar_pilha(Pilha *P){
    P -> topo = -1;
}

int isEmpty(Pilha *P){
    return (P -> topo == -1);
}

void push(Pilha *P,float item){
    P->topo++;
    P->itens[P->topo] = item;
}

float pop(Pilha *P){

    if(isEmpty(P)){
        printf("Pilha vazia");
        return;
    }
    Pilha *aux;
    inicializar_pilha(aux);
    while(!isEmpty(P)){
        push(aux,pop(P));
    }
    float inicio_fila = pop(aux);

    while(!isEmpty(aux)){
        push(P,pop(aux));
    }
    return inicio_fila;
}

void fc_matriz_TFIDF(Pilha *TF,Pilha *IDF,float matriz_TFIDF[][],int tamanho_vocabulario,int quantidade_artigo){
    
    FILE *art;
    Texto *T;
    Palavra *palavra;
    
    FILE *vocabulario = fopen("vocabulary.txt", "r");

    while (fgets(palavra->conteudo, sizeof(palavra->conteudo), vocabulario) != NULL) {
        palavra->conteudo[strcspn(palavra->conteudo, "\n")] = 0;

        int M = strlen(palavra->conteudo);
        int lps[M];
        lps_calculo(lps,palavra->conteudo,M);

        for(int i = 1; i < quantidade_artigo; i++){
            art = abrir_artigo(i);
            T = ler_artigo(art);
            
            int frequencia = kmp_calculo_com_erros(lps,palavra->conteudo,T -> text,M);
            float tf = fc_TF(frequencia, T -> tamanho);
            if (tf>0){
                palavra -> qnt_artigos_aparece++;
            }

            push(TF,tf);

            fclose(art);
    }
        float idf = fc_IDF(palavra->qnt_artigos_aparece,quantidade_artigo);
        push(IDF,idf);
    }

    for(int i=0;i<tamanho_vocabulario;i++){
        for(int j=0;j<quantidade_artigo;j++){
            matriz_TFIDF[i][j] = TFIDF_calculo(pop(TF),pop(IDF));
        }
    }

    fclose(vocabulario);
}

void calculo_vetor_busca(char vetor_TFIDF[], char query[],Pilha *TF,Pilha *IDF,float matriz_TFIDF[][],int tamanho_vocabulario,int quantidade_artigo){

query[strcspn(query, "\n")] = 0;

    FILE *art;
    Texto *T;
    Palavra *palavra;
    int tamanho_vetor;
    int count=0;
    
    palavra -> conteudo = strtok(query, " "); 

    while (palavra != NULL) {
           
        int M = strlen(palavra->conteudo);
        int lps[M];
        lps_calculo(lps,palavra->conteudo,M);

        for(int i = 1; i < quantidade_artigo; i++){
            art = abrir_artigo(i);
            T = ler_artigo(art);
            
            int frequencia = kmp_calculo_com_erros(lps,palavra->conteudo,T -> text,M);
            float tf = fc_TF(frequencia, T -> tamanho);
            if (tf>0){
                palavra -> qnt_artigos_aparece++;
            }

            push(TF,tf);

            fclose(art);
    }
        float idf = fc_IDF(palavra->qnt_artigos_aparece,quantidade_artigo);
        push(IDF,idf);

        count++;
    palavra = strtok(NULL, " ");
    }
    
    for(int i=0;i<count;i++){
    vetor_TFIDF[i] = TFIDF_calculo(pop(TF),pop(IDF));
    }

    tamanho_vetor = strlen(vetor_TFIDF);
    vetor_TFIDF = realloc(vetor_TFIDF, sizeof(char) * tamanho_vetor);

}

float similiaridade(float matriz_TFIDF[][],char vetor_TFIDF[],Pilha *S){
    int i=0,j=0;
    
    
    
}
