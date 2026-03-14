#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BRANCO 0
#define CINZA  1
#define PRETO  2

typedef struct no {
    int vizinho; // Com qual vértice ele se liga
    int fluxo;
    int capacidade;
    struct no *proximaAresta; // Ir pra próxima aresta que ele tem
} no;

typedef struct {
    int pai;          // vértice anterior no caminho
    no* aresta;       // aresta residual usada pra chegar aqui
} Caminho;


void inicializarGrafo(no** adj, int* cor, int n) { 
    for(int i = 0; i < n; i++) {
        adj[i] = NULL; // Lista de adjacência de cada vértice começa com todo mundo apontando pra null
        cor[i] = BRANCO;
    }
}

void adicionarAresta(no** adj, int v, int w, int c) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w; // Adicionamos nossa aresta
    n1->proximaAresta = adj[v]; // Ligamos a nossa nova aresta a primeira aresta que já tinhamos antes
    n1->capacidade = c;
    n1->fluxo = 0; // Fluxo que passa pela aresta inicia zerado
    adj[v] = n1; // Nossa nova aresta se torna a primeira aresta da lista de adjacência
}


// Usamos uma busca em profundidade pra criar o grafo residual
void criarGrafoResidual(int verticeExplorar, no** adj, int* cor, int n) {
    no **adjResidual = malloc(n * sizeof(no*));
    no* atual = adj[verticeExplorar];
    cor[verticeExplorar] = CINZA; // Acabamos de alcançar esse vértice aqui

    while(atual != NULL) {
        if(cor[atual->vizinho] != BRANCO) {
            if(atual->fluxo < atual->capacidade) {
                adicionarAresta(adjResidual, verticeExplorar, atual->vizinho, atual->capacidade - atual->fluxo);
            } else if (atual->fluxo != 0){
                adicionarAresta(adjResidual, atual->vizinho, verticeExplorar, atual->fluxo);
            }
            atual = atual->proximaAresta;
            continue;
        }

        if(atual->fluxo < atual->capacidade) {
            adicionarAresta(adjResidual, verticeExplorar, atual->vizinho, atual->capacidade - atual->fluxo);
        } else if (atual->fluxo != 0){
            adicionarAresta(adjResidual, atual->vizinho, verticeExplorar, atual->fluxo);
        }


        criarGrafoResidual(atual->vizinho, adj, cor, n);
        atual = atual->proximaAresta;
    }

    cor[verticeExplorar] = PRETO;
}

int acharCaminho(int x, int y, no** adj, Caminho* caminho, int* cor, int n) {
    no **adjResidual = malloc(n * sizeof(no*));
    no* atual = adj[x];
    cor[x] = CINZA; // Acabamos de alcançar esse vértice aqui

    if(x == y) return 1;

    while(atual != NULL) {
        if(cor[atual->vizinho] != BRANCO) {
            if(x == y) return 1;
            atual = atual->proximaAresta;
            continue;
        }

        acharCaminho(atual->vizinho, y, adj, caminho, cor, n);
        atual = atual->proximaAresta;
    }

    cor[x] = PRETO;
}

void flow(no** adj, int* cor, int n) {
    int source = 0; // Vertice 1 que é o equivalente ao zero já que estamos usando uma estrutura de adjacência
    int sinkhole = n - 1;

    criarGrafoResidual(source, adj, cor, n);
}


int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    no **adj = malloc(n * sizeof(no*));
    int* cor = malloc(n * sizeof(int));
    Caminho* caminho = malloc(n * sizeof(Caminho));
    inicializarGrafo(adj, cor, n);

    for(int i = 0; i < m; i++) {
        int v, w, c;
        if(c > 1e9) {
            return -1;
        }
        scanf("%d %d %d", &v, &w, &c);
        adicionarAresta(adj, v, w, c);
    }

    flow(adj, cor, n);
}