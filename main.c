/*
    nosso trabalho ta tipo:
    https://youtube.com/shorts/lp4_rxJPJGQ?si=hK6MqEl4kswFJ5PQ
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <ctype.h> //    necessario para filtrar caractere especial

#define MAXIMA_QUANTIDADE_ALGARISMOS_ARTIGO 3
#define MAXIMO_TAMANHO_PALAVRA 200
#define MAXIMO_TAMANHO_QUERY 100
#define MAXIMA_QUANTIDADE_TAMANHO_TITULO 500

typedef struct temp_name_node{
    char *palavra;
    int tamanho;
    struct temp_name_node *proximo;
    struct temp_name_node *anterior;
}Node;


typedef struct temp_name_node_float{
    double valor;
    char *palavra;
    struct temp_name_node_float *proximo;
    struct temp_name_node_float *anterior;
}Node_resposta;


typedef struct{
    int tamanho;
    Node_resposta *head;
    Node_resposta *tail;
}Lista_resposta;            
//  uma lista composta com noded de char*(str) e um double associados, útil para organizar a resposta no final

typedef struct{
    int tamanho;
    Node *head;
    Node *tail; 
}Lista;

//  usado para armazenar o conteudo de cada texto(artigo) e seu tamanho
typedef struct Texto{
    char *text;
    int tamanho;
}Texto;

//  funçoes basicas da lista resposta

Lista_resposta *criar_lista_res();

Node_resposta *criar_node_res(Node_resposta *anterior, float valor, char *palavra, Node_resposta *proximo); 

//  note que se indice == 0, implica que palavra deve vir anterior do lista->head,
//  se indicde == 1, implica que palavra deve ir entre lista->head e o proximo.
void adicionar_meio_lista_res(Lista_resposta *lista, float valor, char *palavra, int indice);

void adicionar_inicio_lista_res(Lista_resposta *lista, float valor, char *palavra);

void adicionar_final_lista_res(Lista_resposta *lista, float valor, char *palavra);

void deletar_final_lista_res(Lista_resposta *lista);

void deletar_lista_res(Lista_resposta *lista);

//  dado um int ind e lista, fc busca o ind-ésimo+1 elemento da lista, 0 é o primeiro da lista, retorta o char *palavra
char *elemento_indice_lista_res(Lista_resposta *lista, int ind);

void printa_lista_res(Lista_resposta *lista);

void adicionar_lista_res_com_prioridade(Lista_resposta *lista, double valor, char *palavra, int N);

//  fim das funçoes basicas da lista resposta

// funcoes basica para lista de char*
Node *criar_node(Node *anterior, char *palavra, Node *proximo); 

Lista *criar_lista();

//   note que se indice == 0, implica que palavra deve vir anterior do lista->head,
//   se indicde == 1, implica que palavra deve ir entre lista->head e o proximo.
void adicionar_meio_lista(Lista *lista, char *palavra, int indice);

void adicionar_inicio_lista(Lista *lista, char *palavra);    

void adicionar_final_lista(Lista *lista, char *palavra);     

char *elemento_indice_lista(Lista *lista, int ind);

void printa_lista(Lista *lista);    // usada para debug

void deletar_lista(Lista *lista);

int deletar_final_lista(Lista *lista);
// fim das funcoes basica para lista de char*

void deletar_texto(Texto *texto);

void lps_calculo(int lps[], char *P, int M);//  encontra o lps da str P

int kmp_calculo_com_erros(int lps[],char *P,char *T,int M); //  função que calcula o kmp com até 1 erro

//   funçao que retorna um FILE* com o arrtigo i que queremos, primeiro artigo é o 1, entao contagem requer comecar pelo 1.
FILE *abrir_artigo(int numero);

//   quantidade de palavras que tem em um arquivo
int quantidade_palavras(FILE *arquivo);

//   retorna quantidade de artigos 
int quantidade_artigo_calculo();


//   passa um File* do artigo e retorna uma Lista * contendo todas as palavras do artigo
Texto *ler_artigo(FILE *artigo);

//  funçoes para calculo do TFIDF
float fc_TF(float frequencia,float tamanho);

float fc_IDF(float num_docs_palavra_aparece,float num_doc_total);

double TFIDF_calculo(float fc_TF,float IDF);

void fc_matriz_TFIDF(float **TF, float *IDF, int tamanho_vocabulario, int quantidade_artigo, double **matriz_TFIDF, Lista *vocabulario);

//  calcula o vetor de busca que sera usado na query para encontrar a similaridade
double* calculo_vetor_busca(char *query, float *IDF, int tamanho_vocabulario, Lista *vocabulario);

// int verifica_caso_usuario_queira_recalcular_TFIDF();                       //   talvez deletar essa funcao, nao util

//  realiza a comparação entre o vetor de busca e o vocabulario em cada documento
void similaridade(int N, int quantidade_artigo, double *vetor_busca, double **matriz_TFIDF,int tamanho_vocabulario, Lista *titulo);

// altera a str recebida para ter todas letras minusculas
void filtro_maiusculo_para_minusculo(char *palavra); 

//  recebe uma str e verifica se há acentuação, se houver remove e retorna um ponteiro dinamicamento alocado sem os acentos
char* removerAcento(char* str);

//  calculo do modulo que é utilizado no calculo da similaridade
double modulo(double *vetor,int tamanho_vocabulario);

//  armazena um arquivo em uma lista
Lista *leitura_arquivo_para_lista(FILE* arquivo);

//  retorna uma lista com os titulos a serem retornados ao fim do calculo de similiaridade e comparações
Lista *recolher_titulos_artigos_para_lista();

// //  armazena a matriz em um arquivo binario
// void matriz_binario(float **matrix, int linhas, int colunas);                       //  talvez deletar essa funcao, nao util

//  retorna a qnt de palavras em uma str passada como parametro, *conta qnt de espaços na str + 1*
int quantidade_palavra_em_string(char *str);

//  verifica se a palavra na query se encontra no vocabulario e retorna o indice do mesmo
int buscar_palavra_lista(Lista *vocabulario, char *palavra_query);


int main(void) {

    setlocale(LC_ALL, "Portuguese");
    
    //  declaracao das variaveis
    int quantidade_artigo = quantidade_artigo_calculo();
    float **TF, *IDF;
    FILE *vocabulario;
    char query[MAXIMO_TAMANHO_QUERY];
    double **matriz_TFIDF;
    int tamanho_vocabulario, N;
    Lista *vocabulario_palavras, *titulos_artigos;

    vocabulario = fopen("dados/vocabulary.txt", "r");
    tamanho_vocabulario = quantidade_palavras(vocabulario);
    vocabulario_palavras = leitura_arquivo_para_lista(vocabulario); //   todas as palavras do vocabulario armazenado nessa lista
    fclose(vocabulario);

    titulos_artigos = recolher_titulos_artigos_para_lista();//  titulos a serem retornados no fim dos calculos de similaridade e comparaçoes

    //   basicamente: cada linha corresponde a uma palavra do vocabulario e cada coluna corresponde a um artigo
    matriz_TFIDF = malloc(sizeof(double*) * tamanho_vocabulario);
    TF = malloc(sizeof(float*) * tamanho_vocabulario);
    IDF = malloc(sizeof(float) * quantidade_artigo); 
    for(int i = 0; i < tamanho_vocabulario; i++)
    {
        matriz_TFIDF[i] = malloc(sizeof(double) * quantidade_artigo);
        TF[i] = malloc(sizeof(float) * quantidade_artigo);
    }

    //  calcula a matriz TFIDF
    fc_matriz_TFIDF(TF, IDF, tamanho_vocabulario, quantidade_artigo, matriz_TFIDF, vocabulario_palavras);

    do{
        double *vetor_busca;
        printf("(digite 0 para encerrar o programa)\n");//  caso nao deseje utilizar mais o programa
        printf("digite sua query: ");
        scanf(" %d", &N);// numero de artigos a serem retornados
        scanf(" %[^\n]s", query);// query digitada pelo usuario
        if(N > 0){
            char *query_filtrado = removerAcento(query);//  filtra a query para melhor funcionamento
            printf("Para a busca: %s, Os N = %d artigos mais relevantes são:\n", query_filtrado, N);
            vetor_busca = calculo_vetor_busca(query_filtrado, IDF, tamanho_vocabulario, vocabulario_palavras);//    calcula o vetor busca relatiovo a query digitada
            similaridade(N, quantidade_artigo, vetor_busca, matriz_TFIDF, tamanho_vocabulario, titulos_artigos);//  calcula a similiaridade e printa ao final da funcao
            free(query_filtrado);
        }
    }while(N > 0);//    garante que o codigo funcione enquanto nao se digitar 0 para a quantia de artigos a serem retornados
    
    //  liberaçao das memorias alocadas dinamicamente
    for(int i=0; i < tamanho_vocabulario; i++){
        free(matriz_TFIDF[i]);
        free(TF[i]);
    }
    free(IDF);
    free(TF);
    free(matriz_TFIDF);
    deletar_lista(titulos_artigos);
    deletar_final_lista(vocabulario_palavras);
    printf("codigo encerrado com sucesso\n");
    
    return 0;

} 

//  funçoes basicas para uma lista
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
    for(int i = 0; i < indice-1; i++){      //  chegamos até o node anterior onde será adicionado o novonode
        auxiliar = auxiliar->proximo;       
    }
    Node *novonode = criar_node(auxiliar, palavra, auxiliar->proximo);
    auxiliar->proximo->anterior = novonode;
    auxiliar->proximo = novonode; 
    lista->tamanho++;
    //  nao precisa lidar com tail e head
}

void adicionar_final_lista(Lista *lista, char *palavra){
    Node *newnode = criar_node(NULL, palavra, NULL);
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
    //   P = Padrao
    //   M = tamanho de P
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
                len = lps[len-1];
            }
            else{
                lps[i] = 0;
                i++;
            }                
        }        
    }
}

int kmp_calculo_com_erros(int lps[], char *P, char *T, int M) {
    //   T = Texto
    //   P = Padrao
    //   M = tamanho de T
    //   N = tamanho de P
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
    return quantidade_palavras_iguais;//  retorna a frequencia da ocorrrencia de cada palavra
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
    }while(continuar);
    return i - 1; //   -1 pois ele comeca com i = 1
}

FILE *abrir_artigo(int numero){
    FILE *artigo;
    char caminho_artigo[100] = "dados/textos/texto_", numero_string[MAXIMA_QUANTIDADE_ALGARISMOS_ARTIGO + 2];
    sprintf(numero_string, "%d", numero);
    strcat(strcat(caminho_artigo, numero_string), ".txt");
    artigo = fopen(caminho_artigo, "r");

    return artigo;
}


Texto* ler_artigo(FILE *artigo) {
    Texto *texto = malloc(sizeof(Texto));

    texto->text = NULL;
    texto-> tamanho = 0;

    char palavra[MAXIMO_TAMANHO_PALAVRA + 1];
    int tamanho_total = 0;
    if(artigo == NULL){
        printf("artigo == NULL, impossivel abrir\n");
        return NULL;
    }
    while((fscanf(artigo, " %s", palavra) != EOF)){
        texto->tamanho++;// para saber a qnt de palavra de cada texto

        char *palavra_filtrada = removerAcento(palavra);
        if(palavra_filtrada == NULL)
            continue;
        filtro_maiusculo_para_minusculo(palavra_filtrada);

        tamanho_total += strlen(palavra_filtrada) + 1; 
        texto->text = realloc(texto->text, tamanho_total * sizeof(char));

        if (texto->tamanho == 1) {
            strcpy(texto->text, palavra_filtrada);
        } else {
            strcat(texto->text, " ");   
            strcat(texto->text, palavra_filtrada);
        }
        
        free(palavra_filtrada); // na linha "char *palavra_filtrada = removerAcento(palavra);", removerAcento(palavra) aloca um char dinamico
    }
    return texto;
}

void printa_lista(Lista *lista){
    if(lista->tamanho == 0){
        printf("lista vazia\n");
        return;
    }
    Node *auxnode = lista->head;
    int i = 1;
    while(auxnode != NULL){
        printf("elemento %d: %s\n", i, auxnode -> palavra);
        auxnode = auxnode->proximo;
        i++;
    }
}


//  funcoes para o calculo do TFIDF
float fc_TF(float frequencia,float tamanho ){
    return frequencia/tamanho;
}

float fc_IDF(float num_docs_palavra_aparece,float num_doc_total){
    return log10(num_doc_total/(num_docs_palavra_aparece+1));
}

double TFIDF_calculo(float TF,float IDF){

    return (TF*IDF);
}


int quantidade_palavras(FILE *arquivo) {

    if(arquivo == NULL)
    {
        printf("erro ao ler o arquivo");
        return 0;
    }

    int qnt_palavras = 0;
    char palavra[MAXIMO_TAMANHO_PALAVRA];

    while(fscanf(arquivo, "%s", palavra) != EOF){// percorre o arquivo ate o final contabilizando cada palavra
        qnt_palavras++;
    }

    return qnt_palavras;//  retorna a quantidade de palavaras em cada arquivo
}

int verifica_caso_usuario_queira_recalcular_TFIDF(){
    char escolha;
    do{
        printf("Primeira vez executando esse código ou deseja re-calcular TF-IDF? (s/n)\n");
        scanf(" %c", &escolha);
        escolha = 's';
        if(escolha != 's' && escolha != 'n')
            printf("sua escolha deve ser sim (s) ou não (n)!\n");
    }while(escolha != 's' && escolha != 'n');
    if(escolha == 's')
        return 1;
    return 0;
}


void fc_matriz_TFIDF(float **TF, float *IDF, int tamanho_vocabulario, int quantidade_artigo, double **matriz_TFIDF, Lista *vocabulario){
    FILE *art;
    Texto *T; // armazena temporariamente cada artigo e quantidade de vezes que aparece
    Node *nodeaux = vocabulario->head; //    variavel auxiliar para percorrer o vocabulario
    int i = 0;

    while (nodeaux != NULL) { //  calcula para todos os elementos do vocabulario
        // utilizado para debug:
        // printf("palavra: %s na posicao:\t\t %d ... calculando\n",nodeaux->palavra, i); 

        int qnt_artigos_aparece = 0;//  quantos artigos que a palavra, de um certo node do vocabulario, aparece 
        int M = strlen(nodeaux->palavra);//  tamanho da palavra do vocabulario
        int lps[M];
        lps_calculo(lps, nodeaux->palavra, M);
        for(int j = 1; j <= quantidade_artigo; j++){//  dado uma palavra do vocabulario, iteramos por todos os artigos e calculamos IDF e TF
            int frequencia;
            float tf;

            art = abrir_artigo(j);
            if(art == NULL)     
                break;
            T = ler_artigo(art);
            if(T == NULL)
                break;
            
            frequencia = kmp_calculo_com_erros(lps, nodeaux->palavra, T -> text, M);//  quantas vezes a palavra aparece no texto
            tf = fc_TF((float)frequencia,(float) T -> tamanho);// frequencia que aparece em relaçao as outras palavras

            if (tf != 0){
                qnt_artigos_aparece++;//    contagem de quantos artigos a palavra do vocabulario aparece
            }

            TF[i][j-1] = tf;// note j-1, nossa contagem do for começa do j = 1

            deletar_texto(T);// deleta o texto criado para armazenar temporariamente o artigo
            fclose(art);
        }

        IDF[i] = fc_IDF((float)qnt_artigos_aparece, (float)quantidade_artigo);//    calcula IDF
        i++;
        nodeaux = nodeaux->proximo;//   passa para o proximo termo do vocabulario
        
    }

    for(int i = 0; i < tamanho_vocabulario; i++){
        for(int j = 0; j < quantidade_artigo; j++){ 
            matriz_TFIDF[i][j] = TFIDF_calculo(TF[i][j], IDF[i]);   //  observe: coluna *matriz_TFIDF + j, ou matriz_TFIDF[0] + j, sao os tfidf de todas palavras do vocabulario (em ordem do arquivo vocab..) do artigo j
        }                                                        
    }
}   

double* calculo_vetor_busca(char *query, float *IDF, int tamanho_vocabulario, Lista *vocabulario){
    double *vetor_busca;
    char *palavra_query;
    int quantidade_palavras;
    int i;
    vetor_busca = calloc(tamanho_vocabulario, sizeof(double));
    
    quantidade_palavras = quantidade_palavra_em_string(query);
    
    palavra_query = strtok(query, " "); 

    while(palavra_query != NULL){
        i = buscar_palavra_lista(vocabulario, palavra_query);// procura a palavra da query no vocabulario e retorna o indice em que ela aparece
        if(i != -1)
            vetor_busca[i]++;   // frequencia +1 da palavra_query na mesmo posicao do vocabulario 
        palavra_query = strtok(NULL, " ");  // busca proxima palavra
    }

    for(i = 0; i < tamanho_vocabulario; i++){
        if(vetor_busca[i] != 0){
            vetor_busca[i] /= (double)quantidade_palavras;  //  completacao do TF, seu denominador
            vetor_busca[i] *= (double)IDF[i];               //  multiplicando pelo IDF, agora temos o TFIDF do vetor busca na posicao i
        }
    }
    
    return vetor_busca;
    
}

void similaridade(int N, int quantidade_artigo, double *vetor_busca, double **matriz_TFIDF,int tamanho_vocabulario, Lista *titulo){

    Lista_resposta *resposta = criar_lista_res();       //  embora é chamado lista se comporta como uma fila com insercao priorirataria 
    
    for(int j = 0; j < quantidade_artigo; j++){
        
        double numerador=0, A = 0, B, result;
        //  calcula o numerador da similaridade(produto interno entre vetor de busca e cada coluna da matriz TFIDF)
        for(int i=0; i < tamanho_vocabulario; i++){
            numerador += vetor_busca[i] * matriz_TFIDF[i][j];
        }

        //  modulo de cada vetor para encontrar o denominador
        for(int i = 0; i < tamanho_vocabulario; i++){
            A += powf(matriz_TFIDF[i][j],2);
        }
        A = sqrtf(A);// fim do calculo modulo de A (matriz tfidf do artigo j)

        B = modulo(vetor_busca, tamanho_vocabulario);

        if(A * B == 0){
            continue;// caso A * B == 0, nao podemos dividir o numerador por A * B, por isso, prossegue para o proximo artigo
        }
        
        result = numerador/(A * B);//  result é o valor de similaridade entre vetor busca com coluna j do tfidf (artigo j)

        if(resposta->tamanho == 0){//  buscamos um result != 0 quando tamanho da lista resposta é 0, mais a frente é necessario que a lis. res. tamanho seja > 0
            if(result == 0){
                continue;
            }
            adicionar_inicio_lista_res(resposta, result, elemento_indice_lista(titulo, j));
            continue;
        }
        
        if(resposta->tail->valor <= result){// tail é o elemento com menor similaridade
            if(resposta->tamanho == N){
                deletar_final_lista_res(resposta);// caso esteja cheia, deve deletar o elemento com menor similaridade.
            }
            //  funcao calcula onde deve ser adicionado o elemento, baseado no result (S), e os valores S da lista
            //  elemento_indice_lista(titulo, j) retorna o titulo do j-esimo do artigo j, observe toda contagem começa a partir do 0
            adicionar_lista_res_com_prioridade(resposta, result, elemento_indice_lista(titulo, j), N);
        }

    }
    if(N != resposta->tamanho){
        printf("...Apenas foi possível achar %d artigos relevantes:\n", resposta->tamanho);
    }
    printa_lista_res(resposta);
    deletar_lista_res(resposta);
    free(vetor_busca);
}

double modulo(double *vetor,int tamanho_vocabulario){
    double soma=0;
    for(int i=0;i<tamanho_vocabulario;i++){
        soma += powf(vetor[i],2);
    } 
    return sqrtf(soma);
}

void deletar_texto(Texto *texto){
    free(texto->text);
    free(texto);
    texto = NULL;
}

Lista_resposta *criar_lista_res(){
    Lista_resposta *lista = malloc(sizeof(Lista_resposta));
    lista->head = NULL;
    lista->tail = NULL;
    lista->tamanho = 0;
    return lista;
}

Node_resposta *criar_node_res(Node_resposta *anterior, float valor, char *palavra, Node_resposta *proximo){
    Node_resposta *newnode = malloc(sizeof(Node_resposta));
    newnode->anterior = anterior;
    newnode->proximo = proximo;
    newnode->valor = valor;
    newnode->palavra = malloc(strlen(palavra) + 1);
    strcpy(newnode->palavra, palavra);
    
    return newnode;
}

void adicionar_inicio_lista_res(Lista_resposta *lista, float valor, char *palavra){
    Node_resposta *newnode = criar_node_res(NULL,valor, palavra, NULL);
        if (lista -> tail == NULL){
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

void adicionar_meio_lista_res(Lista_resposta *lista, float valor, char *palavra, int indice){
    if(indice >= lista->tamanho){
        adicionar_inicio_lista_res(lista, valor, palavra);
        return;
    }
    if(indice <= 0){
        adicionar_final_lista_res(lista, valor, palavra);
        return;
    }
    Node_resposta *auxiliar = lista->head;
    for(int i = 0; i < indice-1; i++){      //  chegamos até o node anterior     
        auxiliar = auxiliar->proximo;       //  que o auxiliar vai estar 
    }
    Node_resposta *novonode = criar_node_res(auxiliar, valor, palavra, auxiliar->proximo);
    auxiliar->proximo->anterior = novonode;
    auxiliar->proximo = novonode; 
    lista->tamanho++;
    //  nao precisa lidar com tail e head
}



void adicionar_final_lista_res(Lista_resposta *lista, float valor, char *palavra){
    Node_resposta *newnode = criar_node_res(NULL,valor, palavra, NULL);
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

void deletar_lista_res(Lista_resposta *lista){
    Node_resposta *aux = lista->head;
    while(aux != NULL)
    {
        Node_resposta *delete = aux;
        free(delete->palavra);
        free(delete);
        aux = aux->proximo;
    }
    free(lista);
}

char *elemento_indice_lista_res(Lista_resposta *lista, int ind){ // ind == indice
    if(ind < 0){
        printf("indice nao pode ser <0, alterando para 0\n");
        ind = 0;
    }
    if(ind >= lista->tamanho){
        printf("indice nao pode ser >= que o tamanho da lista, alterando para tamanho lista -1\n");
        ind = lista->tamanho-1;
    }
    Node_resposta *aux = lista->head;
    for(int i = 0; i < ind; i++){
        aux = aux->proximo;
    }
    return aux->palavra;
}

char *elemento_indice_lista(Lista *lista, int ind){ //  ind == indice
    if(ind < 0){
        printf("indice nao pode ser <0, alterando para 0\n");
        ind = 0;
    }
    if(ind >= lista->tamanho){
        printf("indice nao pode ser >= que o tamanho da lista, alterando para tamanho lista -1\n");
        ind = lista->tamanho-1;
    }
    Node *aux = lista->head;
    for(int i = 0; i < ind; i++){
        aux = aux->proximo;
    }
    return aux->palavra;
}

//  para garantir melhor funcionamento
void filtro_maiusculo_para_minusculo(char *palavra){
    for(int i = 0; palavra[i] != '\0'; i++){
        if(isupper(palavra[i])){
            palavra[i] = tolower(palavra[i]);
        }
    }
}

void adicionar_lista_res_com_prioridade(Lista_resposta *lista, double valor, char *palavra, int N){
    if(lista->tamanho == 0){// caso N = 1 pode entrar nesse for, previne segmentation fault, previne problemas
        adicionar_inicio_lista_res(lista, valor, palavra);
        return;
    }
    Node_resposta *aux = lista->head;
    int i = 0;
    while(aux != NULL){
        if(valor > (aux->valor)){// iterando entre todo elemento da lista, buscamos um em que valor (similaridade) seja > que o valor do node
            //  digamos que logo na primeira iteração já verifica que valor > aux->valor (i = 0), então ao executar funcao abaixo o elemento é adicionado no comeco
            //  se i = 1, elemento é adicionado entre o primeiro e segundo elemento da lista, garantindo a ordem decrescente de similaridade
            adicionar_meio_lista_res(lista, valor, palavra, i);
            return;
        }
        i++;
        aux = aux->proximo;
    }
    if(lista->tamanho < N){// só ira entrar aqui quando o valor da palavra(titulo) a ser adicionado é < que todos elementos
        adicionar_final_lista_res(lista, valor, palavra);
    }
}

void deletar_final_lista_res(Lista_resposta *lista){
    if(lista->tail == NULL) {
        printf("erro ao deletar final da lista\n");
        return;
    }
    Node_resposta *delet_node = lista->tail;
    if(lista->tail == lista->head){
        lista->head = NULL;
        lista->tail = NULL;
    }else{
        lista->tail->anterior->proximo = NULL;
        lista->tail = lista->tail->anterior;
    }
    free(delet_node->palavra);
    free(delet_node);
    lista->tamanho--;
}


char* removerAcento(char* str) {
    char* com_acento[] = {
        "á", "à", "â", "ã", "ä", "é", "è", "ê", "ë", "í", "ì", "î", "ï",
        "ó", "ò", "ô", "õ", "ö", "ú", "ù", "û", "ü", "ç", "Á", "À", "Â", "Ã", "Ä",
        "É", "È", "Ê", "Ë", "Í", "Ì", "Î", "Ï", "Ó", "Ò", "Ô", "Õ", "Ö", "Ú", "Ù", "Û", "Ü", "Ç"
    };
    char* sem_acento[] = {
        "a", "a", "a", "a", "a", "e", "e", "e", "e", "i", "i", "i", "i",
        "o", "o", "o", "o", "o", "u", "u", "u", "u", "c", "A", "A", "A", "A", "A",
        "E", "E", "E", "E", "I", "I", "I", "I", "O", "O", "O", "O", "O", "U", "U", "U", "U", "C"
    };
    char *resultado = (char *) malloc((strlen(str) + 1) * sizeof(char));
    if (!resultado) return NULL;

    char* p = resultado;

    while (*str) {
        int encontrado = 0;
        for (int i = 0; i < sizeof(com_acento) / sizeof(com_acento[0]); ++i) {
            size_t len = strlen(com_acento[i]);
            if (strncmp(str, com_acento[i], len) == 0) {
                strcpy(p, sem_acento[i]);
                p += strlen(sem_acento[i]);
                str += len;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            *p++ = *str++;
        }
    }
    *p = '\0';
    return resultado;
}

Lista *leitura_arquivo_para_lista(FILE* arquivo){
    Lista *lista = criar_lista();
    rewind(arquivo);
    char palavra[MAXIMO_TAMANHO_PALAVRA + 1];
    while(fscanf(arquivo, "%s", palavra) != EOF){
        char *palavra_filtrada = removerAcento(palavra);
        filtro_maiusculo_para_minusculo(palavra_filtrada);
        adicionar_final_lista(lista, palavra_filtrada);
        free(palavra_filtrada);
    }
    return lista;
}

//  retorna lista com os N titulos mais relevantes
Lista *recolher_titulos_artigos_para_lista(){
    char titulo_palavra[MAXIMA_QUANTIDADE_TAMANHO_TITULO + 1];
    FILE *artigo;
    Lista *titulos = criar_lista();
    int i = 1;
    do{
        artigo = abrir_artigo(i);
        if(artigo != NULL)
        {
            fgets(titulo_palavra, sizeof(titulo_palavra), artigo);
            adicionar_final_lista(titulos, titulo_palavra);
            fclose(artigo);
        }
        i++;
    }while(artigo != NULL);
    return titulos;
}

//  verifica se a palavra da query existe no vocabulario e retorna seu indice na lista caso exista
int buscar_palavra_lista(Lista *vocabulario, char *palavra_query){
    if(vocabulario == NULL){
        printf("vocabulario lista é nula, erro\n");
        return -1;
    }
    int indice = 0;
    Node *nodeaux = vocabulario->head;
    while(nodeaux != NULL){
        if(strcmp(nodeaux->palavra, palavra_query) == 0){
            break;
        }
        indice++;
        nodeaux = nodeaux->proximo;
    }
    if(nodeaux == NULL)     
    {
        return -1;
        printf("palavras: %s, não faz parte do vocabulario\n", palavra_query);
    }
    return indice;
}

int quantidade_palavra_em_string(char *str){
    if(str == NULL) {
        printf("str == NULL\n");
        return 0;
    }
    int qnt = 1;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == ' '){
            qnt++;
        }
    }
    return qnt;
}

void printa_lista_res(Lista_resposta *lista){
    if(lista->tamanho == 0){
        printf("lista vazia\n");
        return;
    }
    Node_resposta *aux = lista->head;
    while(aux != NULL){
        printf("%s\n", aux->palavra);
        aux = aux->proximo;
    }
}