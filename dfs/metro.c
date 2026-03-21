#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vizinho;
    struct no* proximaAresta;
    struct no* arestaAnterior;
} no;

typedef struct node {
    int vertice;
    struct node* prox;
} node;

typedef struct fila {
    struct node* cabeca;
    struct node* fim;
} fila;


void inicializarGrafo(no** adj, int* cor, int* graus, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
        graus[i] = 0;
        cor[i] = 0;
    }
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

void adicionarAresta(int v, int w, int* graus, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    n1->arestaAnterior = NULL;
    if (adj[v] != NULL) {
        adj[v]->arestaAnterior = n1;
    }
    adj[v] = n1;

    no* n2 = malloc(sizeof(no));
    n2->vizinho = v;
    n2->proximaAresta = adj[w];
    n2->arestaAnterior = NULL;
    if (adj[w] != NULL) {
        adj[w]->arestaAnterior = n2;
    }
    adj[w] = n2;

    graus[v]++;
    graus[w]++;
}

void enfileirarGrau1(int* grau, fila* f, int n) {
    for(int i = 0; i < n; i++) {
        if(grau[i] == 1) {
            push(f, i);
        }
    }
}

int dfs(int inicio, no** adj, int* graus, int *cor) {
    cor[inicio] = 1;

    for(no* aresta = adj[inicio]; aresta != NULL; aresta = aresta->proximaAresta) {
        if(cor[aresta->vizinho] == 0 && graus[aresta->vizinho] < 3) {
            dfs(aresta->vizinho, adj, graus, cor);
        }
    }

    cor[inicio] = 2;
    return 0;
}

void dfsPontas(int inicio, no** adj, int* graus, int *cor, int *qtdVertices) {
    (*qtdVertices)++;
    cor[inicio] = 1;

    for(no* aresta = adj[inicio]; aresta != NULL; aresta = aresta->proximaAresta) {
        if(cor[aresta->vizinho] == 0) {
            dfsPontas(aresta->vizinho, adj, graus, cor, qtdVertices);
        }
    }

    cor[inicio] = 2;
}



int main() {
    
    
    int n, m;
    scanf("%d %d", &n, &m);
    
    fila f;
    iniciarFila(&f);

    no** adj = malloc(n * sizeof(no*));
    int* graus = malloc(n * sizeof(int));
    int* cor = malloc(n *sizeof(int));
    
    inicializarGrafo(adj, cor, graus, n);
    for(int i = 0; i < m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        v--;
        w--; 

        adicionarAresta(v, w, graus, adj);
    }

    enfileirarGrau1(graus, &f, n);
    
    while(!estaVazia(&f)) {
        int v0 = pop(&f);

        no* atual = adj[v0];
        
        while(atual != NULL) {
            int vizinhoV0 = atual->vizinho;
            no* aresta = adj[vizinhoV0];
            
            while(aresta != NULL) {
                no* proximo = aresta->proximaAresta;
    
                if(aresta->vizinho == v0) {
                    if(aresta->arestaAnterior != NULL) {
                        aresta->arestaAnterior->proximaAresta = aresta->proximaAresta;
                    } else {
                        adj[vizinhoV0] = aresta->proximaAresta;
                    }
                    if(aresta->proximaAresta != NULL) {
                        aresta->proximaAresta->arestaAnterior = aresta->arestaAnterior;
                    }
                    graus[vizinhoV0]--;
                    if(graus[vizinhoV0] == 1) push(&f, vizinhoV0);
                    free(aresta); 
                }    
                aresta = proximo; 
            }

            no* temp = atual;
            atual = atual->proximaAresta;
            free(temp);
        }

        adj[v0] = NULL;
        graus[v0] = 0;
    }

    int maiorGrau = 0;
    int indiceMaiorGrau = 0;
    for(int k = 0; k < n; k++) {
        if(graus[k] > maiorGrau) {
            maiorGrau = graus[k];
            indiceMaiorGrau = k;
        }
    }

    dfs(indiceMaiorGrau, adj, graus, cor);

    int *qtdVertices = malloc(sizeof(int));
    *qtdVertices = 0;


    int verticeBorda = -1;
    for(int i = 0; i < n; i++) {
        if(cor[i] == 0 && graus[i] > 0) {
            verticeBorda = i; 
            break;
        }
    }

    if(verticeBorda != -1) dfsPontas(verticeBorda, adj, graus, cor, qtdVertices);

    printf("%d", (*qtdVertices));
}