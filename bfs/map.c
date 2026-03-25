#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    int iIndo;
    int jIndo;
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

void adicionarAresta(int v, int w, int i, int j, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->iIndo = i;
    n1->jIndo = j;
    n1->proximaAresta = adj[v];
    adj[v] = n1;
}

void dfs(int inicio, int* cor, no** adj, int* flag) {
    if(flag) return;
    cor[inicio] = 1;

    for(no* aresta = adj[inicio]; aresta != NULL; aresta = aresta->proximaAresta) {
        if(cor[aresta->vizinho] == 0) dfs(aresta->vizinho, cor, adj, flag);
    }

    cor[inicio] = 2;
    flag = 1;
    return;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    vertice **matriz; 
    matriz = malloc(n * sizeof(vertice*));
    for (int i = 0; i < n; i++) {
        matriz[i] = malloc(m * sizeof(vertice));
    }

    no** adj = malloc(n * sizeof(no*));
    int* cor = malloc(n * sizeof(int));
    
    int qtd_vertices = 1;
    int indiceInicial = -1;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for(int i = 0; i < n; i++) {
        char* linha = malloc(m * sizeof(char));
        for(int j = 0; j < m; j++) {
            matriz[i][j].caminho = linha[j];
            matriz[i][j].id = qtd_vertices++;
            if(linha[j] == 'o') {
                indiceInicial = qtd_vertices - 1;
            } 
        }
    }

    int posicaoInicialI = -1;
    int posicaoInicialJ = -1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {

            if(matriz[i][j].caminho == 'o') {
                posicaoInicialI = i;
                posicaoInicialJ = j;
            }

            for(int d = 0; i < d; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];

                if(ni >= 0 && ni < n && nj >= 0 && nj < m) {
                    if(matriz[i][j].caminho != '.') adicionarAresta(matriz[i][j].id, matriz[ni][nj].id, ni, nj, adj);
                }
            }
        }
    }

    dfs(indiceInicial, cor, adj);

}