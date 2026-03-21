#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no { 
    int vizinho;
    struct no* proximaAresta;
} no;

char paises[200][31];
int total = 0;

int getPais(char* nome) {

    for(int i = 0; i < total; i++) {
        if(strcmp(paises[i], nome) == 0)
            return i;
    }

    strcpy(paises[total], nome);
    total++;
    return total-1;
}

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;
}

void inicializarGrafo(no** adj, int* cor, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
        cor[i] = 0;
    }
}

void limparCor(int* cor) {
    for(int i = 0; i < 194; i++) {
        cor[i] = 0;
    }
}

int dfsEncontra(int source, int sink, int* cor, no** adj) {
    cor[source] = 1; // Marcamos esse vértice como sendo explorado
    if(source == sink) return 1; // Retornamos 1 se encontramos

    // Percorrer estrutura de adjacência
    for(no* aresta = adj[source]; aresta != NULL; aresta = aresta->proximaAresta) {
        if(cor[aresta->vizinho] == 0) {
            if(dfsEncontra(aresta->vizinho, sink, cor, adj))
                return 1; // Se encontrou por esse ramo, propagamos o sucesso
        }
    }

    // Se a lista de adjacência dele foi percorrida inteira, então ele é um vértice completamente explorado
    cor[source] = 2;

    // Se não encontramos por esse ramo, retornamos 0 pra essa iteração
    return 0;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    getchar();
    no** adj = malloc(194 * sizeof(no*));
    int* cor = malloc(194 * sizeof(int));
    inicializarGrafo(adj, cor, 194);
    char fraseTrue[100];
    char fraseCheck[100];
    char* palavras[5];
    int l = 0;
    
    // Frases dadas como verdade
    for(int i = 0; i < n; i++) {
        fgets(fraseTrue, sizeof(fraseTrue), stdin);
        char* palavra = strtok(fraseTrue, " \n"); // Dividir em palavras
    
        while(palavra != NULL) {
            // printf("%s ", palavra);
            palavras[l] = palavra;
            palavra = strtok(NULL, " \n");
            l++;
        }

        l = 0;
    
        // Uso a função do nomePais pra converter os países pra números, e adicione uma aresta direcionada de um pro outro
        adicionarAresta(getPais(palavras[0]), getPais(palavras[4]), adj);
        // printf("Aresta adiciona de %d para %d\n", nomePais(palavras[0]), nomePais(palavras[4]));
    }

    limparCor(cor);

    int k = 0;
    // Frases que temos que verificar
    for(int j = 0; j < m; j++) {
        fgets(fraseCheck, sizeof(fraseCheck), stdin);
        char* palavra = strtok(fraseCheck, " \n"); // Dividir em palavras

        while(palavra != NULL) {
            // printf("%s", palavra);
            palavras[k] = palavra;
            palavra = strtok(NULL, " \n");
            k++;
        }

        k = 0;
        // printf("%d %d", nomePais(palavras[0]), nomePais(palavras[4]));


        // Se encontrarmos essa relação, então o fato dito é completamente verdade
        if(dfsEncontra(getPais(palavras[0]), getPais(palavras[4]), cor, adj)) {
            printf("Fact\n");
            limparCor(cor);
        // Se partirmos do contrário e tivermos um caminho levando até aquele outro país, então o fato é um resultado alternativo
        } else {
            limparCor(cor);
            if(dfsEncontra(getPais(palavras[4]), getPais(palavras[0]), cor, adj)) {
                printf("Alternative Fact\n");
            // Se não encontrarmos de jeito nenhum, então retornamos que aquilo é uma mentira
            } else {
                printf("Pants on Fire\n");
            }
        }
        limparCor(cor);
    }
}