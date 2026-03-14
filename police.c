#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct no {
    int vizinho;
    struct no* proximaAresta;
} no;

typedef struct node {
    int vertice;
    struct node* prox;
} node;


typedef struct fila {
    struct node* cabeca;
    struct node* fim;
} fila;

void push(fila* fila, int vertice) {
    if (fila->cabeca == NULL || fila->fim == NULL) {
        printf("Fila nÃ£o inicializada\n");
        exit(1);
    }

    node* novo = (node*)malloc(sizeof(node));
    novo->vertice = vertice; // VÃ©rtice que acabamos de colocar na fila
    novo->prox = NULL; // NÃ£o tem ninguÃ©m atrÃ¡s do vÃ©rtice que acabamos de adicionar
    fila->fim->prox = novo; // O vertice que estava no fim agora aponta pra nosso novo vÃ©rtice
    fila->fim = novo; // Fim agora Ã© o nosso novo vertice
}

int estaVazia(fila* fila) {
    return (fila->cabeca->prox == NULL);
}

int pop(fila* fila) {
    if(fila->cabeca->prox == NULL) {
        printf("Fila estÃ¡ vazia jÃ¡.\n");
        return -1;
    }

    node* verticeRemover = fila->cabeca->prox;
    int verticeRemovido = verticeRemover->vertice;

    fila->cabeca->prox = verticeRemover->prox; // O prÃ³ximo no inÃ­cio da fila Ã© quem vinha depois

    if(fila->cabeca->prox == NULL) { // Se a fila estiver vazia o fim precisa voltar a apontar pra NULL
        fila->fim = fila->cabeca; 
    }

    free(verticeRemover);
    return verticeRemovido;
}

void iniciarFila(fila *f) {
    f->cabeca = (node*)malloc(sizeof(node)); // NÃ³ cabeÃ§a
    f->cabeca->prox = NULL;
    f->fim = f->cabeca; // Fila vazia, fim aponta para cabeÃ§a
}

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;

    no *n2 = malloc(sizeof(no));
    n2->vizinho = v;
    n2->proximaAresta = adj[w];
    adj[w] = n2;
}

void inicializarGrafo(no** adj, int* visitado, int* niveis, int* escolhas, int n) {
    for(int i = 0; i < n; i++) {
        escolhas[i] = 0;
        niveis[i] = 0;
        visitado[i] = 0;
        adj[i] = NULL;
    }
}

void bfs(int iniciar, no** adj, int *visitado, int *niveis) {

    fila f;
    iniciarFila(&f); // Fila começa zerada
    niveis[iniciar] = 0;
    push(&f, iniciar);

    while(!estaVazia(&f)) {
        int verticeExplorar = pop(&f);
        for(no* aresta = adj[verticeExplorar]; aresta != NULL; aresta = aresta->proximaAresta) {
            if(visitado[verticeExplorar] == 0) {
                visitado[verticeExplorar] = 1;
                niveis[aresta->vizinho] = niveis[verticeExplorar] + 1;
                push(&f, aresta->vizinho);
            }
        }
    }

}



int main() {
    int n;
    int m;
    scanf("%d %d", &n, &m); // n = bairros  m = ruas
    no** adj = malloc(n * sizeof(no*));
    int* visitado = malloc(n * sizeof(int));
    int* proibidos = malloc(n * sizeof(int));
    int* grau = malloc(n * sizeof(int));
    inicializarGrafo(adj, visitado, grau, proibidos, n);

    int v = 0;
    int w = 0;
    for(int i = 0; i < m; i++) {
        scanf("%d %d", &v, &w);
        v--;
        w--;
        adicionarAresta(v, w, adj);
    }

    for(int i = 0; i < n; i++) {
        for(no* aresta = adj[i]; aresta != NULL; aresta = aresta->proximaAresta)  {
            grau[i]++;
        }
    }


    int menor = INT_MAX;
    int indiceDoMenor;
    for(int i = 0; i < n; i++) {
        if(grau[i] < menor) {
            menor = grau[i];
            indiceDoMenor = i;
        }
    }

    proibidos[indiceDoMenor] = 1;

    for(no* aresta = adj[indiceDoMenor]; aresta != NULL; aresta = aresta->proximaAresta) {
        proibidos[aresta->vizinho] = 1; // Para cada vizinho u de v 
    } 

    for(int i = 0; i < n; i++) {
        if(proibidos[i]) printf("0 ");
        else printf("1 ");
    }
    

    
}