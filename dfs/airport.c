#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho; 
    struct no* proximaAresta;
} no;

int inicializarGrafo(no** adj, int* grauEntrada, int* grauSaida, int* fluxo, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL; // Lista de adjacência de cada vértice começa zerada
        grauEntrada[i] = 0;
        grauSaida[i] = 0;
        fluxo[i] = 0;
    }
}

int adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;
}



int main() {
    int n, m;
    int teste = 1;
    scanf("%d %d", &n, &m); // Aeroportos e vôos
    while(n != 0 && m != 0) {
        no **adj = malloc(n * sizeof(no)); // Array de nos
        int grauEntrada[n + 1];
        int grauSaida[n + 1];
        int fluxo[n + 1];
        inicializarGrafo(adj, grauEntrada, grauSaida, fluxo, n + 1);

        int v = 0; int w = 0;
        for(int i = 0; i < m; i++) {
            scanf("%d %d", &v, &w);
            adicionarAresta(v, w, adj);
        }

        for(int i = 1; i <= n; i++) {
            for(no* aresta = adj[i]; aresta != NULL; aresta = aresta->proximaAresta) {
                grauSaida[i]++;
                grauEntrada[aresta->vizinho]++;
            }
        }

        int maior = 0;
        int aeroportoDoMaior = 0;
        for(int i = 0; i < n + 1; i++) {
            fluxo[i] = grauEntrada[i] + grauSaida[i];
            if(grauEntrada[i] + grauSaida[i] > maior) {
                maior = grauEntrada[i] + grauSaida[i];
                aeroportoDoMaior = i;
            }
        }

        printf("TESTE %d\n", teste);
        teste++;

        for(int i = 0; i < n + 1; i++) {
            // printf("%d ", grauSaida[i]);
            if(fluxo[i] == maior) {
                printf("%d ", i);
            }
        }

        printf("\n");
        printf("\n");

        
        maior = 0;
    }


}