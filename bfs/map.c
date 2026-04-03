#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    struct no* proximaAresta;
} no;

typedef struct vertice {
    int id;
    char caminho;
} vertice;

void inicializarGrafo(no** adj, int* cor, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = 0;
        cor[i] = 0;
    }
}

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;
}

int dfs(int inicio, int* cor, no** adj, int* flag, int m) {
    cor[inicio] = 1;
    // printf("%d %d %d\n", inicio, (inicio / m) + 1, (inicio % m) + 1);
    if(*flag) return inicio;

    for(no* aresta = adj[inicio]; aresta != NULL; aresta = aresta->proximaAresta) {
        if(cor[aresta->vizinho] == 0) {
            int resultado = dfs(aresta->vizinho, cor, adj, flag, m);
            if(*flag) return resultado;
        }
    }

    cor[inicio] = 2;
    *flag = 1;
    return inicio;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    vertice **matriz; 
    matriz = malloc(n * sizeof(vertice*));
    for (int i = 0; i < n; i++) {
        matriz[i] = malloc(m * sizeof(vertice));
    }

    no** adj = malloc(n * m * sizeof(no*));
    int* cor = malloc(n * m * sizeof(int));
    
    int* flag = malloc(sizeof(int));
    *flag = 0;

    inicializarGrafo(adj, cor, n * m);

    int indiceInicial = -1;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for(int i = 0; i < n; i++) {
        char* linha = malloc(m * sizeof(char));
        scanf("%s", linha);
        for(int j = 0; j < m; j++) {
            matriz[i][j].caminho = linha[j];
            matriz[i][j].id = i * m + j; 
            if(linha[j] == 'o') {
                indiceInicial = i * m + j;
                // printf("%d %d %d %d", indiceInicial, i + 1, m, j + 1);
            } 
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {

            for(int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];

                if(ni >= 0 && ni < n && nj >= 0 && nj < m) {
                    if(matriz[i][j].caminho != '.' && matriz[ni][nj].caminho != '.') adicionarAresta(matriz[i][j].id, matriz[ni][nj].id, adj);
                }
            }
        }
    }

    int idVerticeFinal = dfs(indiceInicial, cor, adj, flag, m);

    int i = idVerticeFinal/m;
    int j = idVerticeFinal % m;

    printf("%d %d", i + 1, j + 1);

}