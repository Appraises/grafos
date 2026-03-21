#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    struct no* proximaAresta;
} no;

void inicializarGrafo(no** adj, int *cor, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
        cor[i] = 0;
    }
}

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;

    no* n2 = malloc(sizeof(no));
    n2->vizinho = v;
    n2->proximaAresta = adj[w];
    adj[w] = n2;
}

void dfs(int inicio, no** adj, int* cor) {
    cor[inicio] = 1;

    for(no* aresta = adj[inicio]; aresta != NULL; aresta = aresta->proximaAresta) {
        if(cor[aresta->vizinho] == 0) dfs(aresta->vizinho, adj, cor);
    }

    cor[inicio] = 2;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *cor = malloc(n * sizeof(int));
    no** adj = malloc(n * sizeof(no*));
    int grupos = 0;

    inicializarGrafo(adj, cor, n);

    for(int i = 0; i < m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);

        v--;
        w--;

        adicionarAresta(v, w, adj);
    }
    
    for(int j = 0; j < n; j++) {
        if(cor[j] == 0) {
            dfs(j, adj, cor);
            grupos++;
        }
    }

    printf("%d", grupos);
}