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

typedef struct quadrado {
    int id;
    char peca;
} quadrado;

void inicializarGrafo(no** adj, int n, int *cor) {
    for(int i = 0; i < n; i++) {
         adj[i] = NULL;
         cor[i] = 0;
    }
}

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;
}

void inicializarFila(fila* f) {
    f->cabeca = (node*)malloc(sizeof(node));
    f->cabeca->proximo = NULL;
    f->fim = f->cabeca;
}

int estaVazia(fila *f) {
    return (f->cabeca->proximo == NULL);
}

void push(fila *f, int vertice) {
    if(f->cabeca == NULL || f->fim == NULL) {
        exit(1);
    }

    node* novo = malloc(sizeof(node));
    novo->vertice = vertice;
    novo->proximo = NULL;
    f->fim->proximo = novo;
    f->fim = novo;
}

int pop(fila* f) {
    node* verticeRemover = f->cabeca->proximo;
    int verticeRemovido = verticeRemover->vertice;

    f->cabeca->proximo = verticeRemover->proximo; 

    if(f->cabeca->proximo == NULL) {
        f->fim = f->cabeca;
    }

    free(verticeRemover);
    return verticeRemovido;
}

int alfabetoParaIndice(char letra) {
    if(letra == 'a') return 0;
    if(letra == 'b') return 1;
    if(letra == 'c') return 2;
    if(letra == 'd') return 3;
    if(letra == 'e') return 4;
    if(letra == 'f') return 5;
    if(letra == 'g') return 6;
    if(letra == 'h') return 7;

    return -1;
}

void bfs(int comeco, int fim, no** adj, int* cor, fila *f, int* niveis) {
    int contador = 0;
    niveis[comeco] = 0;
    cor[comeco] = 1;
    push(f, comeco);

    while(!estaVazia(f)) {
        int verticeInicioFila = pop(f);
        // printf("Vertices empilhados a partir de %d:\n", verticeInicioFila);

        for(no* aresta = adj[verticeInicioFila]; aresta != NULL; aresta = aresta->proximaAresta) {
            if(cor[aresta->vizinho] == 0) {
                // printf("%d ", aresta->vizinho);
                cor[aresta->vizinho] = 1;
                niveis[aresta->vizinho] = niveis[verticeInicioFila] + 1;
                push(f, aresta->vizinho);

                if(aresta->vizinho == fim) {
                    return;
                }
            }
        }

        contador++;
        // printf("Contador: %d \n", contador);
        cor[verticeInicioFila] = 2;
    }
}


int main() {
    int q;
    scanf("%d", &q);

    no** adj = malloc(64 * sizeof(no*));
    int* cor = malloc(64 * sizeof(int));
    int* niveis = malloc(64 * sizeof(int));
    inicializarGrafo(adj, 64, cor);
    
    quadrado tabuleiro[8][8];
    fila f;
    inicializarFila(&f);

    int id = 0;
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            tabuleiro[i][j].id = id++;
        }
    }
    
    // Variações do movimento do cavalo para eu poder criar as arestas
    int dx[8] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[8] = {1, -1, 1, -1, 2, -2, 2, -2};
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            for(int d = 0; d < 8; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                
                if(ni >= 0 && ni < 8 && nj >= 0 && nj < 8) {
                    // printf("Aresta: %d -> %d\n", tabuleiro[i][j].id, tabuleiro[ni][nj].id);
                    adicionarAresta(tabuleiro[i][j].id, tabuleiro[ni][nj].id, adj);
                }
            }
        }
    }

    for(int i = 0; i < q; i++) {
        for(int j = 0; j < 64; j++) {
            cor[j] = 0;
            niveis[j] = 0;
        }

        while(!estaVazia(&f)) {
            pop(&f);
        }


        char* posicaoInicial = malloc(3 * sizeof(char));
        char* posicaoFinal = malloc(3 * sizeof(char));
        scanf("%s %s", posicaoInicial, posicaoFinal);

        int colunaInicial = alfabetoParaIndice(posicaoInicial[0]);
        int linhaInicial = posicaoInicial[1] - '0' - 1;

        int colunaFinal = alfabetoParaIndice(posicaoFinal[0]);
        int linhaFinal = posicaoFinal[1] - '0' - 1;

        // printf("%d %d\n", linhaInicial, colunaInicial);
        // printf("%d %d\n", linhaFinal, colunaFinal);

        // printf("%d %d\n", linhaInicial * 8 + colunaInicial, linhaFinal * 8 + colunaFinal);
        int inicio = linhaInicial * 8 + colunaInicial;
        int fim = linhaFinal * 8 + colunaFinal;
        if(inicio == fim) printf("0\n");
        else {
            bfs(inicio, fim, adj, cor, &f, niveis);
            printf("%d\n", niveis[fim]);
        }
    }
}