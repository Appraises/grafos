#include <stdio.h>
#include <stdlib.h>


typedef struct vertice {
    char tipo; 
    int id;
} vertice;

typedef struct no {
    int vizinho; 
    int tipo;
    struct no* proximaAresta;
} no;


int inicializarGrafo(no** adj, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL; // Lista de adjacência de cada vértice começa zerada
    }
}

int adicionarAresta(int v, int w, int tipo, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->tipo = tipo;
    n1->proximaAresta = adj[v];
    adj[v] = n1;
}



int main() {
    int qtdVertices = 0;
    int costa = 0;
    int n, m;
    scanf("%d %d", &n, &m); // Linhas e colunas

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};  

    vertice **matriz; 
    matriz = malloc(n * sizeof(vertice*));
    for (int i = 0; i < n; i++) {
        matriz[i] = malloc(m * sizeof(vertice));
    }

    no **adj = malloc(n * m * sizeof(no)); // Array de nos
    inicializarGrafo(adj, n * m);

    for(int i = 0; i < n; i++) {
        char* linha = malloc(m * sizeof(char));
        scanf("%s", linha);
        for(int j = 0; j < m; j++) {        
            matriz[i][j].tipo = linha[j];
            matriz[i][j].id = qtdVertices++;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];

                if(ni < 0 || ni >= n || nj < 0 || nj >= m) {
                    adicionarAresta(matriz[i][j].id, -1, 2, adj);
                } else {
                    if(matriz[ni][nj].tipo == '#')
                        adicionarAresta(matriz[i][j].id, matriz[ni][nj].id, 1, adj);

                    if(matriz[ni][nj].tipo == '.')
                        adicionarAresta(matriz[i][j].id, matriz[ni][nj].id, 2, adj);
                }
            }
        }
    }

    int temMar = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(no* aresta = adj[matriz[i][j].id]; aresta != NULL; aresta = aresta->proximaAresta) {
                if(matriz[i][j].tipo == '#' && aresta->tipo == 2) {
                    if(!temMar) costa++;
                    temMar = 1;
                }
            }
            temMar = 0;
        }
    }

    printf("%d", costa);




}