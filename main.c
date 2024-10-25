
/*
recebe um unico char do artigo
verifica se é caracter especial
caso sim trate ele
tolower nele
adiciona na palavra/lista depende de coimo vamos fazer
separa considerando ' '
jfjkhf
asdasd
asdojlililjijlixcv
lxhvxcçlj
*/


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
    teste
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <ctype.h> // necessario para filtra caractere especial

#define MAXIMA_QUANTIDADE_ALGARISMOS_ARTIGO 3
#define MAXIMO_TAMANHO_PALAVRA 200
#define MAXIMO_TAMANHO_QUERY 100

typedef struct temp_name_node{
    char *palavra;
    int tamanho;
    struct temp_name_node *proximo;
    struct temp_name_node *anterior;
}Node;

typedef struct temp_name_node_float{
    float valor;
    struct temp_name_node_float *proximo;
    struct temp_name_node_float *anterior;
}Nodefloat;

typedef struct{
    int tamanho;
    Nodefloat *head;    //imagino que voce codou usando head tail e node, vou manter esses nomes
    Nodefloat *tail; 
}Listafloat;


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
    float itens[500];
    int topo;
}Pilha;

typedef struct Palavra{
    int qnt_artigos_aparece;
    char *conteudo;
}Palavra;

//temos uma string "virgem" que é o filtrado, conforme for identificado caractere especial,
int verifica_caractere_especial(char *charespecial, char substitui, char *str, char *filtrado, int *i, int *j);

// essa funcao retorna um char* alocado dinamicamente, tome cuidado lembre de dar free
char *filtro_especial(char *palavra);

char *filtro_maiusculo_para_minusculo(char *palavra);

Palavra *inicializar_palavra();

Lista *criar_lista();

Listafloat *criar_lista_float();

Nodefloat *criar_node_float(Nodefloat *anterior, float valor, Nodefloat *proximo); 

void adicionar_meio_lista_float(Listafloat *lista, float valor, int indice);

void adicionar_inicio_lista_float(Listafloat *lista, float valor);    //vou deixar pra vc add rafa

void adicionar_final_lista_float(Listafloat *lista, float valor);     //vou deixar pra vc add rafa

float elemento_indice_lista(Listafloat *lista, int ind);

void deletar_lista_float(Listafloat *lista);


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

void deletar_texto(Texto *texto);

int deletar_final_lista(Lista *lista);

// fc que retorna um FILE* com o texto i que queremos
FILE *abrir_artigo(int numero);

// quantidade de palavras que tem em um arquivo
int quantidade_palavras(FILE *arquivo);

// retorna quantidade de artigo, evite chamar mais que o necessario, funcao ineficiente
int quantidade_artigo_calculo();

float TFIDF_calculo(float fc_TF,float IDF); //add ai rafa

// float similaridade(float *A, float *B, int size); //add ai rafa

// passa um File* do artigo e retorna uma Lista * contendo todas as palavras do artigo
Texto *ler_artigo(FILE *artigo);

float fc_TF(int frequencia,int tamanho);

float fc_IDF(int num_docs_palavra_aparece,int num_doc_total);

Pilha *inicializar_pilha();

int isEmpty(Pilha *P);

float pop(Pilha *P);

float desenfileirar(Pilha *P);

void push(Pilha *P,float item);

void fc_matriz_TFIDF(float **TF, float *IDF, int tamanho_vocabulario, int quantidade_artigo, float **matriz_TFIDF, Lista *vocabulario);

void calculo_vetor_busca(char *query, float *IDF, int tamanho_vocabulario, int quantidade_artigo, float **matriz_TFIDF);

int verifica_caso_usuario_queira_recalcular_TFIDF();

Listafloat *similiaridade(int N, int quantidade_artigo, float vetor_busca[], float **matriz_TFIDF,int tamanho_vocabulario);
char* removerAcento(char* str) ;

// char* remover_acentos(char *palavra);

float modulo(float vetor[],int tamanho_vocabulario);

float deletar_final_lista_float(Listafloat *lista);

void adicionar_lista_float_com_prioridade(Listafloat *lista, float valor, int N);

Lista *leitura_arquivo_para_lista(FILE* arquivo);

Lista *recolher_titulos_artigos_para_lista();

void matriz_binario(float **matrix, int linhas, int colunas);

//  lista float para a resposta
//  

int main(void) {

    setlocale(LC_ALL, "Portuguese");
    int quantidade_artigo = quantidade_artigo_calculo();    
    // printf("\n%d\n\n", quantidade_artigo);

    // IMPORTANTE:
    // precisa criar um meio de armazenar o tfidf apos ele ser calculado, e se haver um tfidf apenas leia o arquivo ao inves de calcular tudo denovo.
    // int opcao;
    // if(opcao = verifica_caso_usuario_queira_recalcular_TFIDF()){
    //     FILE *TFIDFarq = fopen("TFIDF.bin", "rb");
    
    // } // precisa saber mais um pouco de informação sobre como vai ser o TFIDF, talvez a leitura deve ir para um int**
    // ideia: na funcao de calcular tfidf verificamos o verifica_caso_usuario_queira_recalcular_TFIDF() e entao decidimos o que deve ser feito
    
    float **TF, *IDF;
    FILE *vocabulario;
    char query[MAXIMO_TAMANHO_QUERY];
    float **matriz_TFIDF;
    int tamanho_vocabulario;
    Lista *vocabulario_palavras, *titulos_artigos;
    vocabulario = fopen("dados/vocabulary.txt", "r");

    tamanho_vocabulario = quantidade_palavras(vocabulario);
    fclose(vocabulario);
    // printf("%d",tamanho_vocabulario);

    vocabulario_palavras = leitura_arquivo_para_lista(vocabulario); // todas as palavras do vocabulario armazenado nessa lista


    titulos_artigos = recolher_titulos_artigos_para_lista();
    


    // basicamente: cada linha corresponde a uma palavra do vocabulario e cada coluna corresponde a um artigo do diretorio especifico
    matriz_TFIDF = malloc(sizeof(float*) * tamanho_vocabulario);
    TF = malloc(sizeof(float*) * tamanho_vocabulario);
    IDF = malloc(sizeof(float) * quantidade_artigo); 
    for(int i = 0; i < tamanho_vocabulario; i++)
    {
        matriz_TFIDF[i] = malloc(sizeof(float) * quantidade_artigo);
        TF[i] = malloc(sizeof(float) * quantidade_artigo);
    }

    fc_matriz_TFIDF(TF, IDF, tamanho_vocabulario, quantidade_artigo, matriz_TFIDF, vocabulario_palavras);

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            printf("%f\t ",matriz_TFIDF[i][j]);
        }
        printf("\n");
    }
    do{
        printf("(digite 0 para encerrar o programa)\n");
        printf("digite sua query: ");
        fgets(query,sizeof(query),stdin);

        if(query[0] != '0')
            calculo_vetor_busca(query, IDF, tamanho_vocabulario, quantidade_artigo, matriz_TFIDF);
        // Nodefloat *similiaridade();
        
    }while(query[0] != '0');
    printf("encerrando codigo\n");

    free(IDF);
    for(int i=0;i<quantidade_artigo;i++){
        free(matriz_TFIDF[i]);
        free(TF[i]);
    }
    free(TF);
    free(matriz_TFIDF);

    printf("\n\nfinal\n\n");
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
    return i - 1; // -1 pois ele comeca com i = 1
}

FILE *abrir_artigo(int numero){
    FILE *artigo;
    char caminho_artigo[100] = "dados/textos/texto_", numero_string[MAXIMA_QUANTIDADE_ALGARISMOS_ARTIGO + 2];
    sprintf(numero_string, "%d", numero);
    strcat(strcat(caminho_artigo, numero_string), ".txt");
    artigo = fopen(caminho_artigo, "r");
    return artigo;
}

/*
Texto *ler_artigo(FILE *artigo) {

    fseek(artigo, 0, SEEK_END);
    long quantidade_palavras = ftell(artigo);
    rewind(artigo);

    Texto *texto = malloc((quantidade_palavras + 1) * sizeof(char));

    fread(texto -> text, sizeof(char), quantidade_palavras, artigo);
    texto -> text[quantidade_palavras] = '\0'; 

    return texto;
} */


Texto* ler_artigo(FILE *artigo) {
    Texto *texto = malloc(sizeof(Texto));

    texto->text = NULL;
    texto-> tamanho = 0;

    char palavra[MAXIMO_TAMANHO_PALAVRA + 1];
    int tamanho_total = 0;
    
    while((fscanf(artigo, " %s", palavra) != EOF)){
        texto->tamanho++;

        // filtro deve retornar um char* alocado dinamicamente
        char *palavra_filtrada = removerAcento(palavra);
        filtro_maiusculo_para_minusculo(palavra_filtrada);

        tamanho_total += strlen(palavra_filtrada) + 1; 
        texto->text = realloc(texto->text, tamanho_total * sizeof(char));

        if (texto->tamanho == 1) {
            strcpy(texto->text, palavra_filtrada);
        } else {
            strcat(texto->text, " ");   
            strcat(texto->text, palavra_filtrada);
        }
        free(palavra_filtrada);
    }
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
    return log10(num_doc_total/(num_docs_palavra_aparece+1));
}

float TFIDF_calculo(float TF,float IDF){

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

    while(fscanf(arquivo, "%s", palavra) != EOF){
        qnt_palavras++;
        // printf("1");
    }

    // printf("%d",qnt_palavras);
    return qnt_palavras;
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

Palavra *inicializar_palavra(){
    Palavra *palavra = malloc(sizeof(Palavra));
    palavra->conteudo = NULL;
    palavra->qnt_artigos_aparece = 0;
    return palavra;
}

void fc_matriz_TFIDF(float **TF, float *IDF, int tamanho_vocabulario, int quantidade_artigo, float **matriz_TFIDF, Lista *vocabulario){
    

    FILE *art;
    Texto *T;
    // FILE *vocabulario = fopen("dados/vocabulary.txt", "r"); //deletar essa linha substituindo por:
    Node *Nodeaux = vocabulario->head;

    // palavra->conteudo = malloc(MAXIMO_TAMANHO_PALAVRA);
    // char *palavra_nao_filtrada = malloc(MAXIMO_TAMANHO_PALAVRA);
    int i = 0;

    while (Nodeaux != NULL) { 
        int qnt_artigos_aparece = 0;
        char *palavra_filtrada = removerAcento(Nodeaux->palavra);
        filtro_maiusculo_para_minusculo(palavra_filtrada);

        // printf("\n%s\n", palavra->conteudo);

        int M = strlen(palavra_filtrada);
        int lps[M];
        lps_calculo(lps, palavra_filtrada, M);
        
        for(int j = 1; j <= 1; j++){ //mudar
            art = abrir_artigo(i);
            T = ler_artigo(art);

            // printf("%d\n\n\n\n\n\n\n\n", strlen(T->text));
            
            // printf("%d %s\n\n\n", i, T->text);

            int frequencia = kmp_calculo_com_erros(lps, palavra_filtrada, T -> text, M);
            float tf = fc_TF(frequencia, T -> tamanho);
            if (tf > 0){
                qnt_artigos_aparece++;
            }

            TF[i][j-1] = tf;
            

            deletar_texto(T);
            free(palavra_filtrada);
        }
        float idf = fc_IDF(qnt_artigos_aparece, quantidade_artigo);
        IDF[i] = idf;
        i++;
        Nodeaux = Nodeaux->proximo;
        break; // apenas para debugar retirar isso daqui
    }

    for(int i = 0; i < tamanho_vocabulario; i++){
        
        for(int j = 0; j < quantidade_artigo; j++){ 
            matriz_TFIDF[i][j] = TFIDF_calculo(TF[i][j], IDF[i]);   //observe: coluna *matriz_TFIDF + j, ou matriz_TFIDF[0] + j sao os tfidf de todas 
        }                                                           //palavras do vocabulario (em ordem do arquivo vocab..) do artigo j
    }

}

void calculo_vetor_busca(char *query, float *IDF, int tamanho_vocabulario, int quantidade_artigo, float **matriz_TFIDF){
    float *vetor_busca;
    vetor_busca = malloc(sizeof(float) * tamanho_vocabulario);
    for(int i = 0; i < tamanho_vocabulario; i++)
        vetor_busca[i] = 0;
    
    int N;
    query[strcspn(query, "\n")] = 0;
    
    FILE *art;
    Texto *T;
// Palavra *palavra = inicializar_palavra();
    int tamanho_vetor;
    int count=0;

    // palavra -> conteudo = strtok(query, " "); 

    N = atoi(query);

    // palavra -> conteudo = strtok(NULL, " ");

    int j = 0;
    // while (palavra->conteudo != NULL) { //arrumar isso

        // int M = strlen(palavra->conteudo);
        // int lps[M];
        // lps_calculo(lps,palavra->conteudo,M);

        // for(int i = 1; i <= quantidade_artigo; i++){
        //     art = abrir_artigo(i);
        //     T = ler_artigo(art);
            
        //     int frequencia = kmp_calculo_com_erros(lps,palavra->conteudo,T -> text,M);
        //     float tf = fc_TF(frequencia, T -> tamanho);
        //     if (tf>0){
        //         palavra -> qnt_artigos_aparece++;
        //     }
        //     TF[i-1][j] = tf;
            

        //     fclose(art);
        // }

        // float idf = fc_IDF(palavra->qnt_artigos_aparece,quantidade_artigo);
        // j++;
    

        // count++;
        // IDF[count];
        // palavra -> conteudo = strtok(NULL, " ");
    // }
    
    // for(int i=0;i<count;i++){
    //     vetor_busca[i] = TFIDF_calculo(TF[i][j],IDF[i]);
    // }

    // tamanho_vetor = count;
    
    // free(palavra);
}

// funcao deve calcular a similaridade entre o vetor de busca e a matriz tfidf, retorna uma listafloat dos N documentos com maiores S similaridade
Listafloat *similiaridade(int N, int quantidade_artigo, float vetor_busca[], float **matriz_TFIDF,int tamanho_vocabulario){
    //esta errado, precisa ser uma lista de titulos
    Listafloat *S = criar_lista_float();

    for(int j = 0; j < quantidade_artigo; j++){
        float numerador=0, A, B, result;
        for(int i=0; i < tamanho_vocabulario; i++){
            numerador += vetor_busca[i] * matriz_TFIDF[i][j];
        }
        A = modulo( matriz_TFIDF[0] + j, tamanho_vocabulario);
        B = modulo(vetor_busca, tamanho_vocabulario);
        result = numerador/(A * B);
        adicionar_lista_float_com_prioridade(S, result, N); // caso valor nao satisfatorio, nao será adicionado valor

    }

    // for(int i=0;i<tamanho_vocabulario;i++){
    //     numerador += (vetor_busca[i] * vetor_coluna[i]);
    // }
    return S;
}

float modulo(float vetor[],int tamanho_vocabulario){
    float soma=0;
    for(int i=0;i<tamanho_vocabulario;i++){
        soma += pow(vetor[i],2);
    } 
    return sqrt(soma);
}



void deletar_texto(Texto *texto){
    free(texto->text);
    free(texto);
    texto = NULL;
}

Listafloat *criar_lista_float(){
    Listafloat *lista = malloc(sizeof(Listafloat));
    lista->head = NULL;
    lista->tail = NULL;
    lista->tamanho = 0;
    return lista;
}

Nodefloat *criar_node_float(Nodefloat *anterior, float valor, Nodefloat *proximo){
    Nodefloat *newnode = malloc(sizeof(Nodefloat));
    newnode->anterior = anterior;
    newnode->proximo = proximo;
    newnode->valor = valor;
    return newnode;
}

void adicionar_inicio_lista_float(Listafloat *lista, float valor){
    Nodefloat *newnode = criar_node_float(NULL,valor,NULL);
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

void adicionar_meio_lista_float(Listafloat *lista, float valor, int indice){
    if(indice >= lista->tamanho){
        adicionar_inicio_lista_float(lista, valor);
        return;
    }
    if(indice <= 0){
        adicionar_final_lista_float(lista, valor);
        return;
    }
    Nodefloat *auxiliar = lista->head;
    for(int i = 0; i < indice-1; i++){      //chegamos até o node anterior     
        auxiliar = auxiliar->proximo;       //que o auxiliar vai estar 
    }
    Nodefloat *novonode = criar_node_float(auxiliar, valor, auxiliar->proximo);
    auxiliar->proximo->anterior = novonode;
    auxiliar->proximo = novonode; 
    lista->tamanho++;
    //nao precisa lidar com tail e head
}
void adicionar_final_lista_float(Listafloat *lista, float valor){
    Nodefloat *newnode = criar_node_float(NULL,valor,NULL);
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

void deletar_lista_float(Listafloat *lista){
    Nodefloat *aux = lista->head;
    while(aux != NULL)
    {
        Nodefloat *delete = aux;
        free(delete);
        aux = aux->proximo;
    }
    free(lista);
}

float elemento_indice_lista(Listafloat *lista, int ind){ //ind == indice
    if(ind < 0){
        printf("indice nao pode ser <0, alterando para 0\n");
        ind = 0;
    }
    if(ind >= lista->tamanho){
        printf("indice nao pode ser >= que o tamanho da lista, alterando para tamanho lista -1\n");
        ind = lista->tamanho-1;
    }
    Nodefloat *aux = lista->head;
    for(int i = 0; i < ind; i++){
        aux = aux->proximo;
    }
    return aux->valor;
}


char *filtro_maiusculo_para_minusculo(char *palavra){
    for(int i = 0; palavra[i] != '\0'; i++){
        if(isupper(palavra[i])){
            palavra[i] = tolower(palavra[i]);
        }
    }
}

void adicionar_lista_float_com_prioridade(Listafloat *lista, float valor, int N){
    Nodefloat *aux = lista->head;
    int i = 0;
    while(aux != NULL){
        i++;
        if(valor > aux->valor){
            if(lista->tamanho == N){
                deletar_final_lista_float(lista);
            }
            adicionar_meio_lista_float(lista, valor, i);
            return;
        }
        aux = aux->proximo;
    }
    if(lista->tamanho < N){
        adicionar_final_lista_float(lista, valor);
    }
}

float deletar_final_lista_float(Listafloat *lista){
    if(lista->tail == NULL) {
        printf("erro ao deletar final da lista\n");
        return -1;
    }
    float res;
    Nodefloat *delet_node = lista->tail;
    lista->tail->anterior->proximo = NULL;

    if(lista->tail == lista->head){
        lista->head = NULL;
    }

    lista->tail = lista->tail->anterior;
    res = delet_node->valor;
    free(delet_node);
    lista->tamanho--;
    return res;
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
    char palavra[MAXIMO_TAMANHO_PALAVRA];
    while(fscanf(arquivo, "%s", palavra) != EOF){
        adicionar_final_lista(lista, palavra);
    }
    return lista;
}

Lista *recolher_titulos_artigos_para_lista(){
    char titulo_palavra[600];
    FILE *artigo;
    Lista *titulos = criar_lista();
    int i = 1;
    do{
        artigo = abrir_artigo(i);
        if(artigo != NULL)
        {
            fgets(titulo_palavra, sizeof(titulo_palavra), artigo);
            adicionar_final_lista(titulos, titulo_palavra);
        }
        fclose(artigo);
        i++;
    }while(artigo != NULL);
    return titulos;
}

void matriz_binario(float **matrix, int linhas, int colunas){

    FILE *file = fopen("arquivo.b", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fwrite(&linhas, sizeof(float), 1, file);
    fwrite(&colunas, sizeof(float), 1, file);
    
    for (int i = 0; i < linhas; i++) {
        fwrite(matrix[i], sizeof(float), colunas, file);
    }
    
    fclose(file);
}