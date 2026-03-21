#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    struct no *proximaAresta;
} no;

void inicializarGrafo(no** adj, int* cor, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
        cor[i] = 0;
    }
}

void resetarCor(int* cor, int n) {
    for(int i = 0; i < n; i++) {
        cor[i] = 0;
    }
}

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;

    if(adj[v] == NULL || w < adj[v]->vizinho) { // Se estiver vazia ou se a posição dele for na primeira
        n1->proximaAresta = adj[v];
        adj[v] = n1;
    } else {   // Meio pro fim
        no* aresta = adj[v];
        while(aresta->proximaAresta != NULL && aresta->proximaAresta->vizinho < w) {
            aresta = aresta->proximaAresta;
        }

        n1->proximaAresta = aresta->proximaAresta;
        aresta->proximaAresta = n1;
    }
}

void dfs(int inicio, int* cor, no** adj, int *ordemRaiz, int* pos, int* iteracoes, int *tamanhoSA) {
    cor[inicio] = 1;
    pos[inicio] = *iteracoes;
    ordemRaiz[(*iteracoes)++] = inicio;
    tamanhoSA[inicio] = 1;

    for(no* aresta = adj[inicio]; aresta != NULL; aresta = aresta->proximaAresta) {
        if(cor[aresta->vizinho] == 0) {
            dfs(aresta->vizinho, cor, adj, ordemRaiz, pos, iteracoes, tamanhoSA);
            tamanhoSA[inicio] += tamanhoSA[aresta->vizinho];
        }
    }

    cor[inicio] = 2;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    int *hierarquia = malloc((n-1) * sizeof(int));
    int *cor = malloc(n * sizeof(int));
    no** adj = malloc(n * sizeof(no*));
    int *ordemRaiz = malloc(n * sizeof(int));
    int *pos = malloc(n * sizeof(int));
    int *tamanhoSA = malloc(n * sizeof(int));

    int *iteracoes = malloc(sizeof(int));
    
    inicializarGrafo(adj, cor, n);
    
    for(int i = 0; i < n - 1; i++) {
        int posicao;
        scanf("%d", &posicao);
        hierarquia[i] = posicao;
    }
    
    for(int i = 0; i < n - 1; i++) {
        adicionarAresta(hierarquia[i] - 1, i + 1, adj);
    }

    *iteracoes = 0;
    dfs(0, cor, adj, ordemRaiz, pos, iteracoes, tamanhoSA);
    
    for(int j = 0; j < q; j++) {
        int u, k;
        scanf("%d %d", &u, &k);

        if(tamanhoSA[u - 1] < k) {
            printf("%d\n", -1);
        } else {
            printf("%d\n", ordemRaiz[pos[u - 1] + k - 1] + 1);
        }
    }

}