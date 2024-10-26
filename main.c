#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <ctype.h> // necessario para filtra caractere especial

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


typedef struct{
    int tamanho;
    Node *head;
    Node *tail; 
}Lista;


typedef struct Texto{
    char *text;
    int tamanho;
}Texto;

void filtro_maiusculo_para_minusculo(char *palavra);

// Palavra *inicializar_palavra();

Lista *criar_lista();

Lista_resposta *criar_lista_res();

Node_resposta *criar_node_res(Node_resposta *anterior, float valor, char *palavra, Node_resposta *proximo); 

void adicionar_meio_lista_res(Lista_resposta *lista, float valor, char *palavra, int indice);

void adicionar_inicio_lista_res(Lista_resposta *lista, float valor, char *palavra);

void adicionar_final_lista_res(Lista_resposta *lista, float valor, char *palavra);

// float elemento_indice_res(Lista_resposta *lista, int ind);

void deletar_lista_res(Lista_resposta *lista);

char *elemento_indice_lista_res(Lista_resposta *lista, int ind);

void printa_lista_res(Lista_resposta *lista);

//observ que ao chamar essa fc, deve ser passado quem é o anterior e o proximo do node a ser add
Node *criar_node(Node *anterior, char *palavra, Node *proximo); 

//    note que se indice == 0, implica que palavra deve vir anterior do lista->head,
//    se indicde == 1, implica que palavra deve ir entre lista->head e o proximo.
void adicionar_meio_lista(Lista *lista, char *palavra, int indice);

void adicionar_inicio_lista(Lista *lista, char *palavra);    //vou deixar pra vc add rafa

void adicionar_final_lista(Lista *lista, char *palavra);     //vou deixar pra vc add rafa

char *elemento_indice_lista(Lista *lista, int ind);

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

float TFIDF_calculo(float fc_TF,float IDF);

// passa um File* do artigo e retorna uma Lista * contendo todas as palavras do artigo
Texto *ler_artigo(FILE *artigo);

double fc_TF(float frequencia,float tamanho);

float fc_IDF(float num_docs_palavra_aparece,float num_doc_total);

void fc_matriz_TFIDF(float **TF, float *IDF, int tamanho_vocabulario, int quantidade_artigo, double **matriz_TFIDF, Lista *vocabulario);

double* calculo_vetor_busca(char *query, float *IDF, int tamanho_vocabulario, Lista *vocabulario);

int verifica_caso_usuario_queira_recalcular_TFIDF();

void similiaridade(int N, int quantidade_artigo, double *vetor_busca, double **matriz_TFIDF,int tamanho_vocabulario, Lista *titulo);

char* removerAcento(char* str) ;

// char* remover_acentos(char *palavra);

float modulo(double *vetor,int tamanho_vocabulario);

void deletar_final_lista_res(Lista_resposta *lista);

void adicionar_lista_res_com_prioridade(Lista_resposta *lista, float valor, char *palavra, int N);

Lista *leitura_arquivo_para_lista(FILE* arquivo);

Lista *recolher_titulos_artigos_para_lista();

void matriz_binario(float **matrix, int linhas, int colunas);

int quantidade_palavra_em_string(char *str);

int buscar_palavra_lista(Lista *vocabulario, char *palavra_query);


int main(void) {

    setlocale(LC_ALL, "Portuguese");
    int quantidade_artigo = quantidade_artigo_calculo();    

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
    double **matriz_TFIDF;
    int tamanho_vocabulario, N;
    Lista *vocabulario_palavras, *titulos_artigos;

    vocabulario = fopen("dados/vocabulary.txt", "r");
    tamanho_vocabulario = quantidade_palavras(vocabulario);
    vocabulario_palavras = leitura_arquivo_para_lista(vocabulario); // todas as palavras do vocabulario armazenado nessa lista
    fclose(vocabulario);

    titulos_artigos = recolher_titulos_artigos_para_lista();
    


    // basicamente: cada linha corresponde a uma palavra do vocabulario e cada coluna corresponde a um artigo
    matriz_TFIDF = malloc(sizeof(double*) * tamanho_vocabulario);
    TF = malloc(sizeof(float*) * tamanho_vocabulario);
    IDF = malloc(sizeof(float) * quantidade_artigo); 
    for(int i = 0; i < tamanho_vocabulario; i++)
    {
        matriz_TFIDF[i] = malloc(sizeof(double) * quantidade_artigo);
        TF[i] = malloc(sizeof(float) * quantidade_artigo);
    }

    fc_matriz_TFIDF(TF, IDF, tamanho_vocabulario, quantidade_artigo, matriz_TFIDF, vocabulario_palavras);

    do{
        double *vetor_busca;
        printf("(digite 0 para encerrar o programa)\n");
        printf("digite sua query: ");
        scanf("%d", &N);
        fgets(query,sizeof(query),stdin);
        if(N != 0){
            vetor_busca = calculo_vetor_busca(query, IDF, tamanho_vocabulario, vocabulario_palavras);
            printf("Os N = %d artigos mais relevantes para a busca: %s, são:\n", N, query);
            similiaridade(N, quantidade_artigo, vetor_busca, matriz_TFIDF, tamanho_vocabulario, titulos_artigos);
        }
    }while(N != 0);
    
    for(int i=0; i < tamanho_vocabulario; i++){
        free(matriz_TFIDF[i]);
        free(TF[i]);
    }
    free(IDF);
    free(TF);
    free(matriz_TFIDF);

    printf("codigo encerrado com sucesso\n");
    
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
    // if(artigo == NULL){
    //     printf("Erro ao ler o artigo!\n");
    // }
    return artigo;
}


Texto* ler_artigo(FILE *artigo) {
    Texto *texto = malloc(sizeof(Texto));

    texto->text = NULL;
    texto-> tamanho = 0;

    char palavra[MAXIMO_TAMANHO_PALAVRA + 1];
    int tamanho_total = 0;
    if(artigo == NULL)
        printf("1\n\n\n");
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
        // free(palavra_filtrada);
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



double fc_TF(float frequencia,float tamanho ){
    return frequencia/tamanho;
}

float fc_IDF(float num_docs_palavra_aparece,float num_doc_total){
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


void fc_matriz_TFIDF(float **TF, float *IDF, int tamanho_vocabulario, int quantidade_artigo, double **matriz_TFIDF, Lista *vocabulario){
    FILE *art;
    Texto *T;
    Node *nodeaux = vocabulario->head;
    int i = 0;

    while (nodeaux != NULL) { 
        int qnt_artigos_aparece = 0;

        int M = strlen(nodeaux->palavra);
        int lps[M];
        lps_calculo(lps, nodeaux->palavra, M);
        
        for(int j = 1; j <= quantidade_artigo; j++){ 
            art = abrir_artigo(j);
            if(art == NULL)     
                break;
            T = ler_artigo(art);

            int frequencia = kmp_calculo_com_erros(lps, nodeaux->palavra, T -> text, M);

            double tf = fc_TF((float)frequencia,(float) T -> tamanho);
            
            if (tf != 0){
                qnt_artigos_aparece++;
            }
            TF[i][j-1] = tf;
            
            deletar_texto(T);
        }
        

        float idf = fc_IDF((float)qnt_artigos_aparece, (float)quantidade_artigo);
        IDF[i] = idf;
        i++;
        nodeaux = nodeaux->proximo;
    }

    for(int i = 0; i < tamanho_vocabulario; i++){
        
        for(int j = 0; j < quantidade_artigo; j++){ 
            
            matriz_TFIDF[i][j] = TFIDF_calculo(TF[i][j], IDF[i]);   //observe: coluna *matriz_TFIDF + j, ou matriz_TFIDF[0] + j, sao os tfidf de todas palavras do vocabulario (em ordem do arquivo vocab..) do artigo j
        }                                                        
    }

}

double* calculo_vetor_busca(char *query, float *IDF, int tamanho_vocabulario, Lista *vocabulario){
    double *vetor_busca;
    char *palavra_query;
    int quantidade_palavras;
    
    vetor_busca = malloc(sizeof(double) * tamanho_vocabulario);
    for(int i = 0; i < tamanho_vocabulario; i++)
        vetor_busca[i] = 0;
    
    // Palavra *palavra = inicializar_palavra();
    quantidade_palavras = quantidade_palavra_em_string(query);
    palavra_query = strtok(query, " "); 

    // int j = 0;
    while(palavra_query != NULL){
        int i = buscar_palavra_lista(vocabulario, palavra_query);
        if(i != -1)
            vetor_busca[i]++;
            // vetor_busca[i]++;
        palavra_query = strtok(NULL, " ");
    }

    for(int i = 0; i < tamanho_vocabulario; i++){
        if(vetor_busca[i] != 0){
            vetor_busca[i] /= quantidade_palavras;  //completacao do TF, seu denominador
            vetor_busca[i] *= IDF[i];               //multiplicando pelo IDF, agora temos o TFIDF do vetor busca na posicao i
        }
    }
    
    return vetor_busca;
    
}

void similiaridade(int N, int quantidade_artigo, double *vetor_busca, double **matriz_TFIDF,int tamanho_vocabulario, Lista *titulo){

    Lista_resposta *resposta = criar_lista_res();       //embora é chamado lista se comporta como uma fila com insercao priorirataria 
    for(int j = 0; j < quantidade_artigo; j++){
        
        double numerador=0, A, B, result;
        for(int i=0; i < tamanho_vocabulario; i++){
            numerador += vetor_busca[i] * matriz_TFIDF[i][j];
        }

        A = modulo(matriz_TFIDF[0] + j, tamanho_vocabulario);
        B = modulo(vetor_busca, tamanho_vocabulario);
        if(A * B == 0){
            continue;
        }
            printf("%d\n",j);
        result = numerador/(A * B);        // result é o valor de similaridade entre vetor busca com coluna j do tfidf (documento j)
        if(resposta->tamanho == 0){
            adicionar_inicio_lista_res(resposta, result, elemento_indice_lista(titulo, j));
            continue;
        }
        if(resposta->tail->valor < result){
            if(resposta->tamanho == N){
                deletar_final_lista_res(resposta);
            }
            adicionar_lista_res_com_prioridade(resposta, result, elemento_indice_lista(titulo, j), N);     //falta aqui verificar se funciona correto
        }
        // printf("a\n\n\n\n\n\n");
        // Lista *walysson = criar_lista();
        // Lista *william = criar_lista();
    }
    printa_lista_res(resposta);
    deletar_lista_res(resposta);
    free(vetor_busca);
}

float modulo(double *vetor,int tamanho_vocabulario){
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
    for(int i = 0; i < indice-1; i++){      //chegamos até o node anterior     
        auxiliar = auxiliar->proximo;       //que o auxiliar vai estar 
    }
    Node_resposta *novonode = criar_node_res(auxiliar, valor, palavra, auxiliar->proximo);
    auxiliar->proximo->anterior = novonode;
    auxiliar->proximo = novonode; 
    lista->tamanho++;
    //nao precisa lidar com tail e head
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

char *elemento_indice_lista_res(Lista_resposta *lista, int ind){ //ind == indice
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

char *elemento_indice_lista(Lista *lista, int ind){ //ind == indice
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

void filtro_maiusculo_para_minusculo(char *palavra){
    for(int i = 0; palavra[i] != '\0'; i++){
        if(isupper(palavra[i])){
            palavra[i] = tolower(palavra[i]);
        }
    }
}

void adicionar_lista_res_com_prioridade(Lista_resposta *lista, float valor, char *palavra, int N){
    Node_resposta *aux = lista->head;
    int i = 0;
    while(aux != NULL){
        if(valor > aux->valor){
            adicionar_meio_lista_res(lista, valor, palavra, i);
            return;
        }
        i++;
        aux = aux->proximo;
    }
    if(lista->tamanho < N){
        adicionar_final_lista_res(lista, valor, palavra);
    }
}

void deletar_final_lista_res(Lista_resposta *lista){
    if(lista->tail == NULL) {
        printf("erro ao deletar final da lista\n");
        return;
    }
    
    Node_resposta *delet_node = lista->tail;
    lista->tail->anterior->proximo = NULL;

    if(lista->tail == lista->head){
        lista->head = NULL;
    }
    lista->tail = lista->tail->anterior;
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
        // printf("%s\n",palavra_filtrada);
        adicionar_final_lista(lista, palavra_filtrada);
        free(palavra_filtrada);
    }
    return lista;
}

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

int buscar_palavra_lista(Lista *vocabulario, char *palavra_query){
    printf("%s",palavra_query);
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
    Node_resposta *aux = lista->head;
    while(aux != NULL){
        printf("%s\n", aux->palavra);
        aux = aux->proximo;
    }
}