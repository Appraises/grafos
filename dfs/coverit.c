#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    struct no* proximaAresta;
    struct no* arestaAnterior;
} no;

typedef struct aresta {
    int v;
    int w;
} aresta;

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    n1->arestaAnterior = NULL;
    if (adj[v] != NULL) {
        adj[v]->arestaAnterior = n1;
    }
    adj[v] = n1;

    no* n2 = malloc(sizeof(no));
    n2->vizinho = v;
    n2->proximaAresta = adj[w];
    n2->arestaAnterior = NULL;
    if (adj[w] != NULL) {
        adj[w]->arestaAnterior = n2;
    }
    adj[w] = n2;
}

void inicializarGrafo(no** adj, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
    }
}

int semArestas(no** adj, int n) {
    for(int i = 0; i < n; i++) {
        if(adj[i] != NULL) {
            return i; // Tem arestas
        }
    }

    return -1; // tá sem arestas
}

void limparSolucao(int* solucao, int n) {
    for(int i = 0; i < (n/2); i++) {
        solucao[i] = -1;
    }
}

void removerTodosVertices(int v, no** adj) {
    no* atual = adj[v];
    while(atual != NULL) {
        int removerArestasVizinho = atual->vizinho;
        no* aresta = adj[removerArestasVizinho];
        
        while(aresta != NULL) {
            no* proximo = aresta->proximaAresta;

            if(aresta->vizinho == v) {
                if(aresta->arestaAnterior != NULL) {
                    aresta->arestaAnterior->proximaAresta = aresta->proximaAresta;
                } else {
                    adj[removerArestasVizinho] = aresta->proximaAresta;
                }
                if(aresta->proximaAresta != NULL) {
                    aresta->proximaAresta->arestaAnterior = aresta->arestaAnterior;
                }
                free(aresta); 
                break;
            }    
            aresta = proximo; 
        }

        no* temp = atual;
        atual = atual->proximaAresta;
        free(temp);
    }

    adj[v] = NULL;
}


int main() {
    int t;
    scanf("%d", &t);

    for(int j = 0; j < t; j++) {
        int n, m;
        scanf("%d %d", &n, &m);
    
        no** adj = malloc(n * sizeof(no*));
        no** adjCopia = malloc(n * sizeof(no*));

        inicializarGrafo(adj, n);
        inicializarGrafo(adjCopia, n);
    
        for(int i = 0; i < m; i++) {
            int v, w;
            scanf("%d %d", &v, &w);
    
            v--;
            w--;
    
            adicionarAresta(v, w, adj);
            adicionarAresta(v, w, adjCopia);
        }

        int* solucao = malloc((n/2) * sizeof(int));
        int tamanhoSolucao = 0;

        int v = semArestas(adjCopia, n);
        while(v != -1) {
            int w = adjCopia[v]->vizinho;

            removerTodosVertices(v, adjCopia);
            removerTodosVertices(w, adjCopia);

            solucao[tamanhoSolucao++] = v;
            solucao[tamanhoSolucao++] = w;
            v = semArestas(adjCopia, n);
        }

        printf("%d\n", tamanhoSolucao);
        for(int i = 0; i < (n/2); i++) {
            printf("%d ", solucao[i] + 1);
        }
        printf("\n");

        tamanhoSolucao = 0;
        limparSolucao(solucao, n);
    }

}