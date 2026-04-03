#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    struct no* proximaAresta;
} no;

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
} fila;


void inicializarFila(fila *f) {
    f->cabeca = malloc(sizeof(node));
    f->cabeca->proximo = NULL;
    f->fim = f->cabeca;
}

int estaVazia(fila *f) {
    return (f->cabeca->proximo == NULL);
}

void push(fila *f, posicaoIJ posicao) {
    if(f->cabeca == NULL || f->fim == NULL) {
        exit(1);
    }

    node* novo = malloc(sizeof(node));
    novo->vertice = posicao;
    novo->proximo = NULL;

    f->fim->proximo = novo;
    f->fim = novo;
}

posicaoIJ pop(fila *f) {
    node* verticeExcluir = f->cabeca->proximo;
    posicaoIJ verticeExcluido = verticeExcluir->vertice;

    f->cabeca->proximo = verticeExcluir->proximo;

    if(f->cabeca->proximo == NULL) {
        f->fim = f->cabeca;
    }

    free(verticeExcluir);
    return verticeExcluido;
}

int valido(int i, int j, int n, int m) {
    return(i >= 0 && i < n && j >= 0 && j < m);
}

int bfs(posicaoIJ start, char** matriz, int** cor, int** corFogo, fila *f, fila *filaFogo, int n, int m) {
    int segundos = 0;
    cor[start.i][start.j] = 1;
    push(f, start);
    
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    
    while(!estaVazia(f)) {
        segundos++;
        posicaoIJ posicao = pop(f);

        // Chegamos em uma borda, então conseguimos sair 
        if(posicao.i == 0 || posicao.i == n - 1 || posicao.j == 0 || posicao.j == m) {
            return segundos + 1;
        }

        for(int d = 0; d < 4; d++) {
            int ni = posicao.i + dx[d];
            int nj = posicao.j + dy[d];

            if(valido(ni, nj, n, m) && cor[ni][nj] == 0) {
                cor[ni][nj] = 1;
                if(matriz[ni][nj] != '*' && matriz[ni][nj] != '#') push(f, (posicaoIJ){ni, nj});
            }
        }

        // Tenho que propagar o fogo após toda iteração da BFS

        node* lista = filaFogo->cabeca->proximo;
        while(lista != NULL && corFogo[lista->vertice.i][lista->vertice.j] == 0) {
            for(int d = 0; d < 4; d++) {
                int ni = lista->vertice.i + dx[d];
                int nj = lista->vertice.j + dy[d];
    
                if(valido(ni, nj, n, m) && matriz[ni][nj] != '#' && matriz[ni][nj] != '*') {
                    matriz[ni][nj] = '*';
                    push(filaFogo, (posicaoIJ){ni, nj});
                }
            }            

            lista = lista->proximo;
        }        

        
    }

    return -1;
}

int main() {
    int q;
    scanf("%d", &q);

    for(int i = 0; i < q; i++) {

        int n, m;
        scanf("%d %d", &n, &m);
        
        fila f;
        inicializarFila(&f);
        fila filaFogo;
        inicializarFila(&filaFogo);

        posicaoIJ escapist;

        char** matriz = malloc(n * sizeof(char*));
        for(int j = 0; j < n; j++) {
            matriz[i] = malloc(m * sizeof(char));
        }

        int** cor = malloc(n * sizeof(int*));
        for(int j = 0; j < n; j++) {
            cor[i] = malloc(m * sizeof(int));
        }

        int** corFogo = malloc(n * sizeof(int*));
        for(int j = 0; j < n; j++) {
            corFogo[i] = malloc(m * sizeof(int));
        }

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cor[i][j] = 0;
                corFogo[i][j] = 0;
            }
        }

        for(int k = 0; k < n; k++) {
            for(int l = 0; l < m; l++) {
                char c;
                scanf("%c", &c);
                matriz[k][l] = c;

                if(c == '@') {
                    escapist.i = k;
                    escapist.j = l;
                }
            }
        }

        int resultado = bfs(escapist, matriz, cor, corFogo, &f, &filaFogo, n, m);
        if(resultado == -1) printf("IMPOSSIBLE\n");
        else printf("%d", resultado);

    }

}