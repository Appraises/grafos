#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BRANCO 0
#define CINZA  1
#define PRETO  2

#define N 10

typedef struct no {
    int vizinho; // Com qual vértice ele se liga
    struct no *proximaAresta; // Ir pra próxima aresta que ele tem
} no;

typedef struct noPilha {
    int vertice;
    int pai;
    no* ondeEuParei;
    struct noPilha* prox;
} noPilha;

typedef struct aresta {
    int v;
    int w;
} aresta;

typedef struct noPilhaAresta {
    struct aresta vw;
    struct noPilhaAresta* prox;
} noPilhaAresta;

noPilha* topo = NULL; // Topo da nossa pilha, inicialmente aponta pra NULL

no* adj[N];
int cor[N];
int profundidadeEntrada[N];
int profundidadeSaida[N];
int saida = 0;
int descoberta = 0;

int high[N];

noPilhaAresta *topoPilhaAresta = NULL;

void pushVertices(noPilha **topo, noPilha *node) {
    node->ondeEuParei = adj[node->vertice];
    node->prox = *topo; // O próximo da pilha é o que era o antigo topo
    *topo = node; // O topo da minha pilha vira o que foi empilhado
}

int popVertices(noPilha **topo) {
    if (*topo == NULL) return -1; // Não há mais vértices pra desempilhar 

    noPilha* aux = *topo;
    int verticeRemovido = aux->vertice;
    *topo = aux->prox;
    free(aux);
    return verticeRemovido;
}

void pushAresta(noPilhaAresta **topo, noPilhaAresta *aresta) {
    aresta->prox = *topo;
    *topo = aresta;
}

aresta popAresta(noPilhaAresta **topo) {
    aresta arestaNula = {-1, -1};
    if (*topo == NULL) return arestaNula; // Não há mais vértices pra desempilhar 

    noPilhaAresta* aux = *topo;
    aresta aresta = aux->vw;
    *topo = aux->prox;
    free(aux);
    return aresta;
}


void inicializarGrafo() { 
    for(int i = 0; i < N; i++) {
        adj[i] = NULL; // Lista de adjacência de cada vértice começa zerada
        cor[i] = 0;
    }
}

void adicionarAresta(int v, int w) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w; // Adicionamos nossa aresta
    n1->proximaAresta = adj[v]; // Ligamos a nossa nova aresta a primeira aresta que já tinhamos antes
    adj[v] = n1; // Nossa nova aresta se torna a primeira aresta da lista de adjacência

    // Por estarmos em um grafo não direcionado, temos que fazer o oposto também

    no* n2 = malloc(sizeof(no));
    n2->vizinho = v;
    n2->proximaAresta = adj[w];
    adj[w] = n2;
}


void buscaProfundidade(int vertice) {
    int verticeQueVamosExplorar = vertice;
    noPilha* noEmpilhar = malloc(sizeof(noPilha));
    noEmpilhar->vertice = vertice;
    noEmpilhar->pai = -1;
    
    cor[verticeQueVamosExplorar] = CINZA;

    pushVertices(&topo, noEmpilhar); // Empilhamos o vértice, foi alcançado (primeiro)
    high[vertice] = descoberta;
    profundidadeEntrada[vertice] = descoberta++; // Colocamos a profundidade de entrada do nosso vértice

    while(topo != NULL) {
        int verticeQueVamosExplorar = topo->vertice;

        if(topo->ondeEuParei == NULL) {
            cor[verticeQueVamosExplorar] = PRETO;
            profundidadeSaida[verticeQueVamosExplorar] = saida++;
            int w = popVertices(&topo);

            if (topo != NULL) { // Se o topo não for null quando a gente removeu esse vértice
                int v = topo->vertice;

                if(high[w] >= profundidadeEntrada[v]) { // Isso indica que não temos pra onde voltar pra v ou pra cima de v
                    printf("Componente biconexo encontrado.\n");
                    aresta e;

                    do {
                        e = popAresta(&topoPilhaAresta);
                        printf("  (%d, %d)", e.v, e.w);
                    } while(!(e.v == v && e.w == w));
                    printf("\n");
                }

                if(high[w] < high[v]) {
                    high[v] = high[w]; // Relatório pro pai dele
                }
            }

            printf("%d\n", w);
            continue;
        }
        
        int paraOndeVamos = topo->ondeEuParei->vizinho;
        int pai = topo->vertice; // Definimos quem é o pai do vértice, que é o antes do vértice para onde vamos
        topo->ondeEuParei = topo->ondeEuParei->proximaAresta;

        if(paraOndeVamos == topo->pai) continue; // Se for a aresta que eu volto pro meu pai, fodase

        // Definimos nossa aresta
        aresta arestaAtual;
        arestaAtual.v = topo->vertice;
        arestaAtual.w = paraOndeVamos;

        // Vamos explorar então esse novo vértice
        verticeQueVamosExplorar = paraOndeVamos;
        
        // Checamos se esse vértice é cinza ou preto, ou seja, se está marcado
        if(cor[verticeQueVamosExplorar] == CINZA || cor[verticeQueVamosExplorar] == PRETO) {

            // Evitar duplicatas de arestas de retorno, caso contrário teriamos as arestas que sobem e que descem
            if(profundidadeEntrada[topo->vertice] > profundidadeEntrada[verticeQueVamosExplorar]) {
                noPilhaAresta* arestaEmpilhar = malloc(sizeof(noPilhaAresta));
                arestaEmpilhar->vw = arestaAtual;
                pushAresta(&topoPilhaAresta, arestaEmpilhar); // Empilhamos a aresta, sempre que foi de baixo pra cima

                // Se a PE desse novo vértice de retorno que conseguimos usar for menor do que o nosso high, trocamos
                if(high[topo->vertice] > profundidadeEntrada[verticeQueVamosExplorar]) {
                    high[topo->vertice] = profundidadeEntrada[verticeQueVamosExplorar]; 
                }

            }

            continue; // Simplesmente pulamos esse vértice, podemos ir pro próximo
        } else {

            // Se o vértice que vamos explorar não foi visitado ainda, empilhamos ele, pra explorar ele
            noPilha* noEmpilhar = malloc(sizeof(noPilha));
            noEmpilhar->vertice = verticeQueVamosExplorar;
            noEmpilhar->pai = pai; // Definimos o pai de onde ele veio que foi salvo antes

            // Empilhamos nossa aresta, sem restrições aqui, já que já pulamos a aresta do pai lá emcima
            noPilhaAresta* arestaEmpilhar = malloc(sizeof(noPilhaAresta));
            arestaEmpilhar->vw = arestaAtual;
            pushAresta(&topoPilhaAresta, arestaEmpilhar);

            high[noEmpilhar->vertice] = descoberta; // High inicialmente começa com a profundidade de entrada
            profundidadeEntrada[noEmpilhar->vertice] = descoberta++; // Definimos a profundidade de entrada, já que colocamos ele na pilha
            pushVertices(&topo, noEmpilhar); // Empilho o vértice
            cor[verticeQueVamosExplorar] = CINZA; // Marco ele como visitado
        }
    }
}


int main() {
    inicializarGrafo();

// Componente principal (bem denso)
adicionarAresta(0, 1);
adicionarAresta(0, 2);
adicionarAresta(1, 3);
adicionarAresta(1, 4);
adicionarAresta(2, 4);
adicionarAresta(2, 5);
adicionarAresta(3, 6);
adicionarAresta(4, 6);
adicionarAresta(4, 7);
adicionarAresta(5, 7);
adicionarAresta(6, 8);
adicionarAresta(7, 8);

// Ciclos explícitos
adicionarAresta(3, 4);
adicionarAresta(6, 7);

// Segundo componente conectado
adicionarAresta(9, 5);
    // Temos nossa estrutura de adjacência agora montada
    // Vamos então fazer a busca em profundidade nela

    int verticeComeçar = 1;

    buscaProfundidade(verticeComeçar); // Começamos pelo primeiro vértice

}