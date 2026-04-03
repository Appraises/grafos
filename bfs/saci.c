#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    struct no* proximaAresta;
} no;

typedef struct node {
    int vertice;
    struct node* proximo;
} node;

typedef struct fila {
    struct node* cabeca;
    struct node* fim;
} fila;

typedef struct vertice {
    int id;
    char caminho;
} vertice;

void inicializarGrafo(no** adj, int* cor, int* caminho, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
        cor[i] = 0;
        caminho[i] = -1;
    }
}

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;

    no* n2 = malloc(sizeof(no));
    n2->vizinho = v;
    n2->proximaAresta = adj[w];
    adj[w] = n2;
}

void inicializarFila(fila *f) {
    f->cabeca = (node*)malloc(sizeof(node));
    f->cabeca->proximo = NULL;
    f->fim = f->cabeca;
}

int estaVazia(fila *f) {
    return (f->cabeca->proximo == NULL);
}

void push(fila *f, int vertice) {
    if(f->cabeca == NULL || f->fim == NULL) {
        printf("Fila nÃ£o inicializada.\n");
        exit(1);
    }

    node* novo = (node*)malloc(sizeof(node));
    novo->vertice = vertice;
    novo->proximo = NULL;
    f->fim->proximo = novo;
    f->fim = novo;
}

int pop(fila *f) {
    if(f->cabeca->proximo == NULL) {
        printf("Fila tÃ¡ vazia pai");
        exit(1);
    }

    node* verticeRemover = f->cabeca->proximo;
    int verticeRemovido = verticeRemover->vertice;

    f->cabeca->proximo = verticeRemover->proximo;

    if(f->cabeca->proximo == NULL) {
        f->fim = f->cabeca;
    }

    free(verticeRemover);
    return verticeRemovido;
}

void bfs(int inicio, int* cor, int* caminho, no** adj, fila *f) {
    cor[inicio] = 1;
    push(f, inicio);

    while(!estaVazia(f)) {
        int verticeInicioFila = pop(f);

        for(no* aresta = adj[verticeInicioFila]; aresta != NULL; aresta = aresta->proximaAresta) {
            if(cor[aresta->vizinho] == 0) {
                cor[aresta->vizinho] = 1;
                caminho[aresta->vizinho] = verticeInicioFila;
                push(f, aresta->vizinho);
            }
        }

        cor[verticeInicioFila] = 2;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    no** adj = malloc(n * m * sizeof(no*));
    int *cor = malloc(n * m * sizeof(int));
    int *caminho = malloc(n * m * sizeof(int));

    fila f;
    inicializarFila(&f);
    inicializarGrafo(adj, cor, caminho, n * m);


    vertice **matriz; 
    matriz = malloc(n * sizeof(vertice*));
    for (int i = 0; i < n; i++) {
        matriz[i] = malloc(m * sizeof(vertice));
    }

    int qtd_vertices = 0;
    int indiceInicial = -1;
    int indiceFinal = -1;

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);
            matriz[i][j].caminho = c;
            matriz[i][j].id = qtd_vertices++;
            if(c == '2') {
                indiceInicial = qtd_vertices - 1;
            } 

            if(c == '3') {
                indiceFinal = qtd_vertices - 1;
            } 
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];

                if(ni >= 0 && ni < n && nj >= 0 && nj < m) {
                    if((matriz[i][j].caminho == '2' || matriz[i][j].caminho == '3' || matriz[i][j].caminho == '1') && matriz[ni][nj].caminho != '0') adicionarAresta(matriz[i][j].id, matriz[ni][nj].id, adj);
                }
            }
        }
    }

    bfs(indiceInicial, cor, caminho, adj, &f);

    int idVerticeChegada = indiceFinal;
    int idVerticeInicio = indiceInicial;
    int contador = 0;

    while(idVerticeInicio != idVerticeChegada) {
        contador++;
        idVerticeChegada = caminho[idVerticeChegada];
    }

    contador++;

    printf("%d", contador);
    
}