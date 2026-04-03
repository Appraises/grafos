#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int vizinho;
    struct no* proximaAresta;
} no;

typedef struct posicaoIJ {
    int i;
    int j;
} posicaoIJ;

typedef struct node {
    posicaoIJ vertice;
    struct node *proximo;
} node;

typedef struct vertice {
    int id;
    char tipo; // Prateleira, espaço, chuva
} vertice;

typedef struct fila {
    node* cabeca;
    node* fim;
} fila;


void inicializarGrafo(no** adj, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
    }
}

void inicializarMatriz(int** cor, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cor[i][j] = 0;
        } 
    }
}

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;


}

int estaVazia(fila* f) {
    return (f->cabeca->proximo == NULL);
}

void inicializarFila(fila* f) {
    f->cabeca = (node*)malloc(sizeof(node));
    f->cabeca->proximo = NULL;
    f->fim = f->cabeca;
}

void push(fila *f, posicaoIJ vertice) {
    if(f->cabeca == NULL || f->fim == NULL) {
        printf("faltou inicializar pai");
    }

    node* novo = malloc(sizeof(node));
    novo->vertice = vertice;
    novo->proximo = NULL;

    f->fim->proximo = novo;
    f->fim = novo;
}

posicaoIJ pop(fila *f) {
    node* verticeRemover = f->cabeca->proximo;
    posicaoIJ verticeRemovido = verticeRemover->vertice;
    f->cabeca->proximo = verticeRemover->proximo;

    if(f->cabeca->proximo == NULL) {
        f->fim = f->cabeca;
    }

    free(verticeRemover);
    return verticeRemovido;  
}

int valido(int i, int j, int n, int m) {
    return i >= 0 && i < n && j >= 0 && j < m;
}



void bfs(posicaoIJ goteira, int** cor, fila *f, vertice** matriz, int n, int m) {
    cor[goteira.i][goteira.j] = 1;
    push(f, goteira);

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while(!estaVazia(f)) {
        posicaoIJ verticeComecoFila = pop(f);

        for(int d = 0; d < 4; d++) {
            int ni = verticeComecoFila.i + dx[d];
            int nj = verticeComecoFila.j + dy[d];

            posicaoIJ novo;
            novo.i = ni;
            novo.j = nj;

            if(!valido(ni, nj, n, m)) continue;

            if(matriz[ni][nj].tipo != '.') continue;

            if(
                (valido(ni - 1, nj, n, m) && matriz[ni - 1][nj].tipo == 'o') ||

                (valido(ni, nj - 1, n, m) &&
                valido(ni + 1, nj - 1, n, m) &&
                matriz[ni][nj - 1].tipo == 'o' &&
                matriz[ni + 1][nj - 1].tipo == '#') ||

                (valido(ni, nj + 1, n, m) &&
                valido(ni + 1, nj + 1, n, m) &&
                matriz[ni][nj + 1].tipo == 'o' &&
                matriz[ni + 1][nj + 1].tipo == '#')
            ) {
                matriz[ni][nj].tipo = 'o';
                push(f, (posicaoIJ){ni, nj});
            }
        }
    }
}


int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int** cor = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        cor[i] = malloc(m * sizeof(int));
    }

    inicializarMatriz(cor, n, m);

    fila f;
    inicializarFila(&f);

    vertice** matriz = malloc(n * sizeof(vertice*));
    for(int i = 0; i < n; i++) {
        matriz[i] = malloc(m * sizeof(vertice));
    }

    posicaoIJ goteira;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);
            matriz[i][j].tipo = c;

            if(matriz[i][j].tipo == 'o') {
                goteira.i = i;
                goteira.j = j;
            }
        }
    }

    bfs(goteira, cor, &f, matriz, n, m);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%c", matriz[i][j].tipo);
        }
        printf("\n");
    }
}