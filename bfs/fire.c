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

void push(fila *f, posicaoIJ posicao) {
    if(f->cabeca == NULL || f->fim == NULL) {
        exit(1);
    }

    node* novo = malloc(sizeof(node));
    novo->vertice = posicao;
    novo->proximo = NULL;

    f->tamanho++;
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
    f->tamanho--;
    return verticeExcluido;
}

int valido(int i, int j, int n, int m) {
    return(i >= 0 && i < n && j >= 0 && j < m);
}

int bfs(posicaoIJ start, char** matriz, int** cor, int** niveis, fila *f, fila *filaFogo, int n, int m) {
    int segundos = 0;
    cor[start.i][start.j] = 1;
    push(f, start);
    niveis[start.i][start.j] = 1;
    
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    
    while(!estaVazia(f)) {
        // Tenho que propagar o fogo após cada troca de nível da BFS
        int tamanhoListaFogo = filaFogo->tamanho;
        for(int i = 0; i < tamanhoListaFogo; i++)  {
            posicaoIJ atual = pop(filaFogo);

            for(int d = 0; d < 4; d++) {
                int ni = atual.i + dx[d];
                int nj = atual.j + dy[d];
    
                if(valido(ni, nj, n, m) && matriz[ni][nj] != '#' && matriz[ni][nj] != '*') {
                    matriz[ni][nj] = '*';
                    push(filaFogo, (posicaoIJ){ni, nj});
                }
            }            
        }
        int qtdFila = f->tamanho;
        for(int i = 0; i < qtdFila; i++) {
            posicaoIJ posicao = pop(f);

            if(posicao.i == 0 || posicao.i == n - 1 || posicao.j == 0 || posicao.j == m - 1) {
                return segundos + 1;
            }

            for(int d = 0; d < 4; d++) {
                int ni = posicao.i + dx[d];
                int nj = posicao.j + dy[d];

                if(valido(ni, nj, n, m) && cor[ni][nj] == 0) {
                    if(matriz[ni][nj] != '*' && matriz[ni][nj] != '#') {
                        cor[ni][nj] = 1;
                        // Chegamos em uma borda, então conseguimos sair 
                        push(f, (posicaoIJ){ni, nj});
                        matriz[ni][nj] = '-';
                    }
                }
            }
        }
        

        
        segundos++;
    }

    return -1;
}

int main() {
    int q;
    scanf("%d", &q);

    for(int i = 0; i < q; i++) {

        int w, h;
        scanf("%d %d", &w, &h);
        
        fila f;
        inicializarFila(&f);
        fila filaFogo;
        inicializarFila(&filaFogo);
        posicaoIJ escapist;
        
        char** matriz = malloc(h * sizeof(char*));
        for(int j = 0; j < h; j++) {
            matriz[j] = malloc(w * sizeof(char));
        }
        
        int** cor = malloc(h * sizeof(int*));
        for(int j = 0; j < h; j++) {
            cor[j] = malloc(w * sizeof(int));
        }

        int** niveis = malloc(h * sizeof(int*));
        for(int j = 0; j < h; j++) {
            niveis[j] = malloc(w * sizeof(int));
        }
        
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                cor[i][j] = 0;
                niveis[i][j] = 0;
            }
        }
        
        // printf("cheguei aqui");
        for(int k = 0; k < h; k++) {
            for(int l = 0; l < w; l++) {
                char c;
                scanf(" %c", &c);
                matriz[k][l] = c;

                if(c == '@') {
                    escapist.i = k;
                    escapist.j = l;
                }

                if(c == '*') {
                    push(&filaFogo, (posicaoIJ){k, l});
                }
            }
        }


        int resultado = bfs(escapist, matriz, cor, niveis, &f, &filaFogo, h, w);
        if(resultado == -1) printf("IMPOSSIBLE\n");
        else printf("%d\n", resultado);

    }

}