#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct no {
    int vizinho; 
    struct no* proximaAresta;
} no;

typedef struct node {
    int vertice;
    struct node* proximo;
} node;

typedef struct fila {
    node* cabeca;
    node* fim;
    int tamanho;
} fila;

int estaVazia(fila *f) {
    return (f->cabeca->proximo == NULL);
}

void push(int vertice, fila *f) {
    if(f->cabeca == NULL || f->fim == NULL) {
        exit(1);
    }

    node* novo = malloc(sizeof(node));
    novo->vertice = vertice;
    novo->proximo = NULL;

    f->fim->proximo = novo;
    f->fim = novo;
    f->tamanho++;
}

int pop(fila *f) {
    node* verticeExcluir = f->cabeca->proximo;
    int verticeExcluido = verticeExcluir->vertice;

    f->cabeca->proximo = verticeExcluir->proximo;

    if(f->cabeca->proximo == NULL) {
        f->fim = f->cabeca;
    }

    free(verticeExcluir);
    f->tamanho--;
    return verticeExcluido;
}

void inicializarFila(fila *f) {
    f->cabeca = malloc(sizeof(node));
    f->cabeca->proximo = NULL;
    f->fim = f->cabeca;
    f->tamanho = 0;
}

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;
}

void inicializarGrafo(no** adj, int* cor, int* distancia1, int* distancia2, int* distancia3, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
        cor[i] = 0;
        distancia1[i] = 1e9;
        distancia2[i] = 1e9;
        distancia3[i] = 1e9;
    }
}

void limpaCor(int* cor, int n) {
    for(int i = 0; i <= n; i++) {
        cor[i] = 0;
    }
}

int bfs(int verticeInicial, no** adj, int* cor, int* distancia, fila *f) {
    push(verticeInicial, f);
    cor[verticeInicial] = 1;
    distancia[verticeInicial] = 0;
    
    while(!estaVazia(f)) {
        int verticeInicioFila = pop(f);

        for(no* aresta = adj[verticeInicioFila]; aresta != NULL; aresta = aresta->proximaAresta) {
            if(cor[aresta->vizinho] == 0) {
                push(aresta->vizinho, f);
                cor[aresta->vizinho] = 1;
                distancia[aresta->vizinho] = distancia[verticeInicioFila] + 1;
            } 
        }
    }

    return 0;
}

int main() {
    int n, m;
    scanf("%d %d %d %d", &n, &m);

    no** adj = malloc((n) * sizeof(no*));
    int* cor = malloc((n) * sizeof(int));
    
    int* distanciaParaU = malloc((n + 1) * sizeof(int));
    int* distanciaUParaA = malloc((n + 1) * sizeof(int));
    int* distanciaUParaB = malloc((n + 1) * sizeof(int));
    inicializarGrafo(adj, cor, distanciaParaU, distanciaUParaA, distanciaUParaB, n + 1);
    inicializarGrafo(adj2, cor, distanciaParaU, distanciaUParaA, distanciaUParaB, n + 1);
    

    fila f;
    inicializarFila(&f);
    
    for(int i = 0; i < m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        // printf("%d %d", v, w);
        
        adicionarAresta(v, w, adj);
        adicionarAresta(w, v, adj2);
    }

    bfs(0, adj, cor, distanciaParaU, &f); // Distância de 0 para todos os vértices possivelmente intermediários

    limpaCor(cor, n);
    bfs(a, adj2, cor, distanciaUParaA, &f); // Distancia de todo vértice intermediário (u) pra a (que é a mesma de a para u)
    limpaCor(cor, n);
    bfs(b, adj2, cor, distanciaUParaB, &f); // Distância de todo u para b

    long long menorDeTodos = 2000000000000LL;

    for(int k = 0; k <= n; k++) {
        // printf("DIST DE 0 PARA %d: %d\n", k, distanciaParaU[k]);
        // printf("DIST %d PARA A: %d\n", k, distanciaUParaA[k]);
        // printf("DIST %d PARA B: %d\n", k, distanciaUParaB[k]);

        int distanciaDesseU = distanciaParaU[k] + distanciaUParaA[k] + distanciaUParaB[k]; // Pegamos a distancia para um dado vértice intermédiário
        // u, e então somamos com a distância desse u para a e a distância dele para b, o que tiver o menor
        // distância, é o custo pra pegar os talentos que queremos
        if(distanciaDesseU < menorDeTodos) menorDeTodos = distanciaDesseU;
    }

    for(int k = 0; k < n; k++) {
        long long distanciaDesseU = (long long)distanciaParaU[k] + distanciaUParaA[k] + distanciaUParaB[k];
        if(distanciaDesseU < menorDeTodos) menorDeTodos = distanciaDesseU;
    }

    printf("%lld", menorDeTodos);

    return 0;
}