#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    struct no *proximaAresta;
} no;

void adicionarAresta(int v, int w, no** adj, int* graus) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;

    no* n2 = malloc(sizeof(no));
    n2->vizinho = v;
    n2->proximaAresta = adj[w];
    adj[w] = n2;

    graus[v]++;
    graus[w]++;
}

void inicializarGrafo(no** adj, int* cor, int* graus, int n) {
    for(int i  = 0; i < n; i++) {
        adj[i] = NULL;
        cor[i] = 0;
        graus[i] = 0;
    }
}

void dfs(int inicio, no** adj, int* cor, int* graus, int* temGato, int consecutivos, int maiorConsecutivos, int m, int* qtdRestaurantes) {
    cor[inicio] = 1;

    for(no* aresta = adj[inicio]; aresta != NULL; aresta = aresta->proximaAresta) {
        if(cor[aresta->vizinho] == 0) { 
            int novoConsecutivos = consecutivos;
            int novoMaiorConsecutivos = maiorConsecutivos;

            if(temGato[aresta->vizinho]) novoConsecutivos++;
            if(novoConsecutivos > novoMaiorConsecutivos) novoMaiorConsecutivos = novoConsecutivos;
            if(!temGato[aresta->vizinho]) novoConsecutivos = 0;
            dfs(aresta->vizinho, adj, cor, graus, temGato, novoConsecutivos, novoMaiorConsecutivos, m, qtdRestaurantes);
        }
    }

    cor[inicio] = 2;
    if(graus[inicio] == 1 && inicio != 0) { // Se o grau desse que ficou preto for igual a 1, chegamos em uma folha
        if(!(maiorConsecutivos > m)) {
            // printf("%d\n", inicio);
            (*qtdRestaurantes)++;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    no** adj = malloc(n * sizeof(no*));
    int *cor = malloc(n * sizeof(int));
    int *graus = malloc(n * sizeof(int));
    int *temGato = malloc(n * sizeof(int));

    inicializarGrafo(adj, cor, graus, n);

    int *qtdRestaurantes = malloc(sizeof(int));
    *qtdRestaurantes = 0;

    int gato;
    for(int i = 0; i < n; i++) {
        scanf("%d", &gato);
        temGato[i] = gato;
    }

    int v, w;
    for(int j = 0; j < n - 1; j++) {
        scanf("%d %d", &v, &w);
        v--;
        w--;
        adicionarAresta(v, w, adj, graus);
    }

    int consecutivos = 0;
    if(temGato[0]) consecutivos++;

    dfs(0, adj, cor, graus, temGato, consecutivos, consecutivos, m, qtdRestaurantes);
    printf("%d", (*qtdRestaurantes));
}