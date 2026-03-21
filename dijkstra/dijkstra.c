#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 10

typedef struct no {
    int vizinho; // Com qual vértice ele se liga
    int peso;
    struct no *proximaAresta; // Ir pra próxima aresta que ele tem
} no;

typedef struct aresta {
    int v;
    int w;
} aresta;

no* adj[N];
int explorado[N];
int distancia[N]; // A distância pra cada vértice

void inicializarGrafo() { 
    for(int i = 0; i < N; i++) {
        adj[i] = NULL; // Lista de adjacência de cada vértice começa zerada
        distancia[i] = INT_MAX; // A distância pra chegar em cada vértice começa como infinita
        explorado[i] = 0; // Nenhum vértice foi explorado ainda
    }
}

void adicionarAresta(int v, int w, int peso) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w; // Adicionamos nossa aresta
    n1->peso = peso;
    n1->proximaAresta = adj[v]; // Ligamos a nossa nova aresta a primeira aresta que já tinhamos antes
    adj[v] = n1; // Nossa nova aresta se torna a primeira aresta da lista de adjacência

    // Por estarmos em um grafo não direcionado, temos que fazer o oposto também

    no* n2 = malloc(sizeof(no));
    n2->vizinho = v;
    n2->peso = peso;
    n2->proximaAresta = adj[w];
    adj[w] = n2;
}

int pegarMenor(int dist[], int explorado[]) {
    int menorDist = INT_MAX;
    int u = -1;

    for(int i = 0; i < N; i++) { // Vai rodar v vezes
        if(!explorado[i] && dist[i] < menorDist) {
            menorDist = dist[i];
            u = i;
        }
    }

    return u;
}


void dijkstra(int verticeComecar) {
    distancia[verticeComecar] = 0; // A distância do vértice que vamos começar pra ele mesmo é zero

    for(int i = 0; i < N; i++) {
        int u = pegarMenor(distancia, explorado);
        if (u == -1) break; // Não há vértice alcançável a partir da origem, não dá pra ver a distância até todos os pontos e pegar o caminho mínimo
        explorado[u] = 1;

        no *arestaExplorar = adj[u];

        while(arestaExplorar != NULL) {
            int verticeDestino = arestaExplorar->vizinho;
            int pesoParaDestino = arestaExplorar->peso;
    
            if(!explorado[verticeDestino] && distancia[u] + pesoParaDestino < distancia[verticeDestino]) {
                // Se o vértice não foi explorado e a distância do vértice que estamos + o deslocamento para esse novo vértice
                // for menor do que a distância que a gente tinha pra chegar a esse vértice antes, então
                // trocamos para essa nova distância (achamos um atalho)
    
                distancia[verticeDestino] = distancia[u] + pesoParaDestino;
            }
    
            arestaExplorar = arestaExplorar->proximaAresta;
        }
    }
}


int main() {
    inicializarGrafo();

// Componente principal (bem denso)
adicionarAresta(0, 1, 3);
adicionarAresta(0, 2, 9);
adicionarAresta(1, 3, 7);
adicionarAresta(1, 4, 11);
adicionarAresta(2, 4, 2);
adicionarAresta(2, 5, 5);
adicionarAresta(3, 6, 4);
adicionarAresta(4, 6, 9);
adicionarAresta(4, 7, 10);
adicionarAresta(5, 7, 1);
adicionarAresta(6, 8, 4);
adicionarAresta(7, 8, 5);

// Ciclos explícitos
adicionarAresta(3, 4, 1);
adicionarAresta(6, 7, 2);

// Segundo componente conectado
adicionarAresta(9, 5, 3);
    // Temos nossa estrutura de adjacência agora montada
    // Vamos então fazer a busca em profundidade nela

    int verticeComeçar = 3; // Queremos saber a caminho mínimo de 3 para todos os outros vertices

    dijkstra(verticeComeçar); // Começamos pelo primeiro vértice

}