#include <stdio.h>
#include <stdlib.h>

typedef struct posicaoIJ {
    int i;
    int j;
} posicaoIJ;

typedef struct node {
    posicaoIJ vertice;
    struct node* proximo;
} node;

typedef struct fila {
    node* cabeca;
    node* fim;
    int tamanho;
} fila;


void inicializarFila(fila *f) {
    f->cabeca = malloc(sizeof(node));
    f->cabeca->proximo = NULL;
    f->fim = f->cabeca;
    f->tamanho = 0;
}

int estaVazia(fila *f) {
    return (f->cabeca->proximo == NULL);
}

void push(posicaoIJ posicao, fila* f) {
    if(f->cabeca == NULL || f->fim == NULL) {
        exit(1);
    }

    node* novo = malloc(sizeof(node));
    novo->vertice = posicao;
    novo->proximo = NULL;

    f->fim->proximo = novo;
    f->tamanho++;
    f->fim = novo;
}

posicaoIJ pop(fila *f) {
    node* verticeExcluir = f->cabeca->proximo;
    posicaoIJ verticeExcluido = verticeExcluir->vertice;

    f->cabeca->proximo = verticeExcluir->proximo;
    if(f->cabeca->proximo == NULL) {
        f->fim = f->cabeca;
    }

    f->tamanho--;
    free(verticeExcluir);
    return verticeExcluido;
}

int valido(int i, int j, int n, int m) {
    return (i >= 0 && i < n && j >= 0 && j < m);
}

void bfs(posicaoIJ start, fila *f, char** matriz, int** cor, int** niveis, posicaoIJ** pais, int n, int m) {
    niveis[start.i][start.j] = 0;
    cor[start.i][start.j] = 1;
    push(start, f);

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while(!estaVazia(f)) {
        posicaoIJ atual = pop(f);
        if(atual.i == n - 1 && atual.j == m - 1) return;
        
        for(int d = 0; d < 4; d++) {
            int ni = atual.i + dx[d];
            int nj = atual.j + dy[d];

            if(valido(ni, nj, n, m) && cor[ni][nj] == 0) {
                if(matriz[ni][nj] != '#') {
                    cor[ni][nj] = 1;
                    niveis[ni][nj] = niveis[atual.i][atual.j] + 1;
                    pais[ni][nj] = (posicaoIJ){atual.i, atual.j};
                    push((posicaoIJ){ni, nj}, f);
                }
            }

        }


    }
}

int bfsCustom(posicaoIJ start, fila *f, char** matriz, int** cor, int** niveis1, int** niveis2, posicaoIJ** pais, int n, int m) {
    cor[start.i][start.j] = 1;
    push(start, f);

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while(!estaVazia(f)) {
        posicaoIJ atual = pop(f);
        if(atual.i == n - 1 && atual.j == m - 1) return 1;
        
        for(int d = 0; d < 4; d++) {
            int ni = atual.i + dx[d];
            int nj = atual.j + dy[d];

            if(valido(ni, nj, n, m) && cor[ni][nj] == 0) {
                if(matriz[ni][nj] != '#' && niveis1[ni][nj] == niveis1[atual.i][atual.j] + 1 && niveis2[ni][nj] == niveis2[atual.i][atual.j] + 1) {
                    cor[ni][nj] = 1;
                    pais[ni][nj] = (posicaoIJ){atual.i, atual.j};
                    push((posicaoIJ){ni, nj}, f);
                }
            }

        }
    }

    return 0;
}


int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    fila f;
    inicializarFila(&f);

    fila f2;
    inicializarFila(&f2);

    char **matriz1 = malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++) {
        matriz1[i] = malloc(m * sizeof(char));
    }

    char **matriz2 = malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++) {
        matriz2[i] = malloc(m * sizeof(char));
    }

    int **cor = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        cor[i] = malloc(m * sizeof(int));
    }

    int **niveis1 = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        niveis1[i] = malloc(m * sizeof(int));
    }

    int **niveis2 = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        niveis2[i] = malloc(m * sizeof(int));
    }

    posicaoIJ **pais1 = malloc(n * sizeof(posicaoIJ*));
    for(int i = 0; i < n; i++) {
        pais1[i] = malloc(m * sizeof(posicaoIJ));
    }

    posicaoIJ **pais2 = malloc(n * sizeof(posicaoIJ*));
    for(int i = 0; i < n; i++) {
        pais2[i] = malloc(m * sizeof(posicaoIJ));
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cor[i][j] = 0;
            niveis1[i][j] = -1;
            niveis2[i][j] = -1;
            pais1[i][j].i = -1;
            pais1[i][j].j = -1;

            pais2[i][j].i = -1;
            pais2[i][j].j = -1;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);

            matriz1[i][j] = c;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);

            matriz2[i][j] = c;
        }
    }

    bfs((posicaoIJ){0, 0}, &f, matriz1, cor, niveis1, pais1, n, m);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cor[i][j] = 0;
        }
    }

    while(!estaVazia(&f)) {
        pop(&f);
    }

    bfs((posicaoIJ){0, 0}, &f, matriz2, cor, niveis2, pais2, n, m);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cor[i][j] = 0;
        }
    }

    while(!estaVazia(&f)) {
        pop(&f);
    }

    int resultado = bfsCustom((posicaoIJ){0, 0}, &f, matriz2, cor, niveis1, niveis2, pais2, n, m);

    if(resultado) printf("YES");
    else printf("NO");
}
