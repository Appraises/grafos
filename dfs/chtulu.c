#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    struct no* proximaAresta;
} no;

void adicionarAresta(int v, int w, no** adj, int n, int* grau) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;

    no* n2 = malloc(sizeof(no));
    n2->vizinho = v;
    n2->proximaAresta = adj[w];
    adj[w] = n2;

    // Aumentamos o grau daquele vértice em específico
    grau[v]++;
    grau[w]++;
}

void inicializarGrafo(no** adj, int* cor, int* grau, int* caminho, int n) {
    for(int i = 0; i < n; i++) {
        cor[i] = 0;
        grau[i] = 0;
        caminho[i] = -1;
        adj[i] = NULL;
    }
}

void dfs(int inicio, int* cor, int* caminho, int* verticesDoCiclo, int* arestasRetorno, int* grau, no** adj) {
    cor[inicio] = 1;

    for(no* aresta = adj[inicio]; aresta != NULL; aresta = aresta->proximaAresta) {
        if(cor[aresta->vizinho] == 0) {
            caminho[aresta->vizinho] = inicio; // Da onde ele veio
            dfs(aresta->vizinho, cor, caminho, verticesDoCiclo, arestasRetorno, grau, adj); // E daí eu exploro ele
        } else if(aresta->vizinho != caminho[inicio] && cor[aresta->vizinho] == 1) { // Encontramos uma aresta de retorno, então encontramos um ciclo
            (*arestasRetorno)++;
            int verticeAntesAcharCiclo = inicio;
            int verticeFechaCiclo = aresta->vizinho;
            
            while(verticeAntesAcharCiclo != verticeFechaCiclo) {
                (*verticesDoCiclo)++;
                verticeAntesAcharCiclo = caminho[verticeAntesAcharCiclo];
            }

            (*verticesDoCiclo)++;
        }
    }

    cor[inicio] = 2;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    no** adj = malloc(n * sizeof(no*));
    int* cor = malloc(n * sizeof(int));
    int* caminho = malloc(n * sizeof(int));
    int* grau = malloc(n * sizeof(int));
    int* verticesDoCiclo = malloc(sizeof(int));
    int* arestasRetorno = malloc(sizeof(int));

    *verticesDoCiclo = 0;
    *arestasRetorno = 0;

    inicializarGrafo(adj, cor, grau, caminho, n);

    for(int i = 0; i < m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        v--;
        w--;

        adicionarAresta(v, w, adj, n, grau);
    }

    dfs(0, cor, caminho, verticesDoCiclo, arestasRetorno, grau, adj);


    int flag = 0;
    for(int i = 0; i < n; i++) {
        if(cor[i] == 0) {
            flag = 1;
        }
    }

    // printf("%d %d", (*verticesDoCiclo), (*arestasRetorno));

    if((*arestasRetorno) == 1 && ((*verticesDoCiclo) >= 3) && !flag) {
        printf("FHTAGN!\n");
    } else {
        printf("NO\n");
    }
}