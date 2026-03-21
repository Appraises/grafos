#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    struct no* proximaAresta;
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
    n1->proximaAresta = adj[v];
    adj[v] = n1;

    no* n2 = malloc(sizeof(no));
    n2->vizinho = v;
    n2->proximaAresta = adj[w];
    adj[w] = n2;
}

void dfs(int inicio, no** adj, int* cor, int caminhoAtual, int* caminhoMaximo, int* ultimoVertice) {
    cor[inicio] = 1;

    for(no* aresta = adj[inicio]; aresta != NULL; aresta = aresta->proximaAresta) {
        if(cor[aresta->vizinho] == 0) dfs(aresta->vizinho, adj, cor, caminhoAtual + 1, caminhoMaximo, ultimoVertice);
    }

    if(caminhoAtual > (*caminhoMaximo)) {
        (*caminhoMaximo) = caminhoAtual;
        *ultimoVertice = inicio;
    }
    cor[inicio] = 2;
}

int main() {
    int n;
    scanf("%d", &n);
    no** adj = malloc(n * sizeof(no*));
    int* cor = malloc(n * sizeof(int));
    int* caminhoMaximo = malloc(sizeof(int));
    int* ultimoVertice = malloc(sizeof(int));

    *caminhoMaximo = 0;
    *ultimoVertice = -1;

    inicializarGrafo(adj, cor, n);

    for(int i = 0; i < n - 1; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        v--;
        w--;

        adicionarAresta(v, w, adj);
    }

    *ultimoVertice = 0;

    dfs(0, adj, cor, 0, caminhoMaximo, ultimoVertice);
    
    resetarCor(cor, n);
    *caminhoMaximo = 0;

    dfs((*ultimoVertice), adj, cor, 0, caminhoMaximo, ultimoVertice);

    printf("%d\n", (*caminhoMaximo));

}