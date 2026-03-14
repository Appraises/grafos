#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    int pai;
    struct no* proximaAresta;
} no;

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->pai = v;
    n1->proximaAresta = adj[v];
    adj[v] = n1; 

    // Bidirecional
    no* n2 = malloc(sizeof(no));
    n2->vizinho = v;
    n2->pai = w;
    n2->proximaAresta = adj[w];
    adj[w] = n2; 
}

void inicializarGrafo(no** adj, int* cor, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
        cor[i] = 0;
    }
}

void dfs(no** adj, int* cor, int verticeExplorar, int* compConexas) {
    cor[verticeExplorar] = 1;
    for(no* aresta = adj[verticeExplorar]; aresta != NULL; aresta = aresta->proximaAresta) {
        if(cor[aresta->vizinho] != 0 && aresta->vizinho != aresta->pai) { // Temos uma aresta de retorno e portanto um ciclo
            (*compConexas)++;
        } else {
            dfs(adj, cor, aresta->vizinho, compConexas);
        }
    }

    cor[verticeExplorar] = 2;
}

int alguemNaoAlcancado(int* cor, int n) {
    int alguem = -1;
    for(int i = 0; i < n; i++) {
        if(cor[i] == 0) {
            alguem = i;
        }
    }

    return alguem;

}

int main() {
    int n;
    int m;
    int* compConexas = malloc(sizeof(int));
    *compConexas = 0;
    scanf("%d %d", &n, &m);
    no** adj = malloc(n * sizeof(no*));
    int* cor = malloc(n * sizeof(int));
    inicializarGrafo(adj, cor, n);

    int v = 0;
    int w = 0;
    for(int i = 0; i < m; i++) {
        scanf("%d %d", &v, &w);
        v--;
        w--;
        adicionarAresta(v, w, adj);
    }

    while(alguemNaoAlcancado(cor, n) != -1) {
        dfs(adj, cor, alguemNaoAlcancado(cor, n), compConexas);
    }

    printf("%d\n", (*compConexas));
}
