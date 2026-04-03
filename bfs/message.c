#include <stdio.h>
#include <stdlib.h>

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

void inicializarGrafo(no** adj, int n, int* cor, int* quaisVertices, int* caminho) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
        cor[i] = 0;
        quaisVertices[i] = 0;
        caminho[i] = -1;
    }
}

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;
}

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

void bfs(int inicio, fila* f, int* cor, no** adj, int* caminho) {
    cor[inicio] = 1;
    push(f, inicio);

    while(!estaVazia(f)) {
        int inicioFila = pop(f);

        for(no* aresta = adj[inicioFila]; aresta != NULL; aresta = aresta->proximaAresta) {
            if(cor[aresta->vizinho] == 0) {
                cor[aresta->vizinho] = 1;
                caminho[aresta->vizinho] = inicioFila;
                push(f, aresta->vizinho);
            }
        }

        cor[inicioFila] = 2;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    no** adj = malloc(n * sizeof(no*));
    int* cor = malloc(n * sizeof(int));
    int* caminho = malloc(n * sizeof(int));
    int* quaisVertices = malloc(n * sizeof(int));
    fila f;
    iniciarFila(&f);

    inicializarGrafo(adj, n, cor, quaisVertices, caminho);

    for(int i = 0; i < m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);

        v--;
        w--;

        adicionarAresta(v, w, adj);
        adicionarAresta(w, v, adj);
    }

    
    int verticePartindoMaija = n - 1;
    int verticeInicial = 0;
    int contador = 0;
    bfs(0, &f, cor, adj, caminho);

    if(caminho[n - 1] == -1 && n > 1) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    
    while(verticePartindoMaija != verticeInicial) {
        quaisVertices[contador] = verticePartindoMaija;
        contador++;
        verticePartindoMaija = caminho[verticePartindoMaija];
    }

    quaisVertices[contador] = verticePartindoMaija;
    printf("%d\n", contador + 1);

    for(int i = contador; i >= 0; i--) {
        printf("%d ", quaisVertices[i] + 1);
    }        

    return 0;

}