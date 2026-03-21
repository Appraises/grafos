#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BRANCO 0
#define CINZA  1
#define PRETO  2

typedef struct no {
    int vizinho; // Com qual vértice ele se liga
    int fluxo;
    int capacidade;
    int tipo;

    struct no* original; // Cada aresta vai apontar pra sua respectiva aresta original
    struct no* reversa; // E cada aresta normal pode apontar também pra sua reversa

    struct no *proximaAresta; // Ir pra próxima aresta que ele tem
} no;


typedef struct node {
    int vertice;
    struct node* prox;
} node;

typedef struct fila {
    struct node* cabeca;
    struct node* fim;
} fila;

typedef struct Caminho {
    int pai;          // vértice anterior no caminho
    no* arestaResidual;       // aresta residual usada pra chegar aqui
} Caminho;


void push(fila* fila, int vertice) {
    if (fila->cabeca == NULL || fila->fim == NULL) {
        printf("Fila não inicializada\n");
        exit(1);
    }

    node* novo = (node*)malloc(sizeof(node));
    novo->vertice = vertice; // Vértice que acabamos de colocar na fila
    novo->prox = NULL; // Não tem ninguém atrás do vértice que acabamos de adicionar
    fila->fim->prox = novo; // O vertice que estava no fim agora aponta pra nosso novo vértice
    fila->fim = novo; // Fim agora é o nosso novo vertice
}

int estaVazia(fila* fila) {
    return (fila->cabeca->prox == NULL);
}

int pop(fila* fila) {
    if(fila->cabeca->prox == NULL) {
        printf("Fila está vazia já.\n");
        return -1;
    }

    node* verticeRemover = fila->cabeca->prox;
    int verticeRemovido = verticeRemover->vertice;

    fila->cabeca->prox = verticeRemover->prox; // O próximo no início da fila é quem vinha depois

    if(fila->cabeca->prox == NULL) { // Se a fila estiver vazia o fim precisa voltar a apontar pra NULL
        fila->fim = fila->cabeca; 
    }

    free(verticeRemover);
    return verticeRemovido;
}

void iniciarFila(fila *f) {
    f->cabeca = (node*)malloc(sizeof(node)); // Nó cabeça
    f->cabeca->prox = NULL;
    f->fim = f->cabeca; // Fila vazia, fim aponta para cabeça
}

void inicializarGrafo(no** adj, int* cor, int n) { 
    for(int i = 0; i < n; i++) {
        adj[i] = NULL; // Lista de adjacência de cada vértice começa com todo mundo apontando pra null
        cor[i] = BRANCO;
    }
}

no* adicionarAresta(no** adj, int v, int w, int c, int tipo) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w; // Adicionamos nossa aresta
    n1->proximaAresta = adj[v]; // Ligamos a nossa nova aresta a primeira aresta que já tinhamos antes
    n1->capacidade = c;
    n1->tipo = tipo;
    n1->fluxo = 0; // Fluxo que passa pela aresta inicia zerado
    adj[v] = n1; // Nossa nova aresta se torna a primeira aresta da lista de adjacência

    return n1;
}

no* adicionarArestaResidual(no** adj, int v, int w, int c, int tipo) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w; // Adicionamos nossa aresta
    n1->proximaAresta = adj[v]; // Ligamos a nossa nova aresta a primeira aresta que já tinhamos antes
    n1->capacidade = c;
    n1->tipo = tipo;
    n1->fluxo = 0; // Fluxo que passa pela aresta inicia zerado
    adj[v] = n1; // Nossa nova aresta se torna a primeira aresta da lista de adjacência

    no* n2 = malloc(sizeof(no));
    n2->vizinho = v; // Adicionamos nossa aresta
    n2->proximaAresta = adj[w]; // Ligamos a nossa nova aresta a primeira aresta que já tinhamos antes
    n2->capacidade = 0; // Capacidade da aresta reversa começa zerada 
    n2->tipo = 1;
    n2->fluxo = 0; // Fluxo que passa pela aresta inicia zerado
    adj[w] = n2; // Nossa nova aresta se torna a primeira aresta da lista de adjacência

    n1->reversa = n2;
    n2->reversa = n1;

    return n1;
}

void criarGrafoResidual(no** adj, no** adjResidual, int n) {
    for (int i = 0; i < n; i++) {
        for (no* aresta = adj[i]; aresta != NULL; aresta = aresta->proximaAresta) {

            int capDireta = aresta->capacidade - aresta->fluxo; 
            no* par = adicionarArestaResidual(adjResidual, i, aresta->vizinho, capDireta, 0);

            par->original = aresta;
            par->reversa->tipo = 1;
            par->reversa->original = aresta;

            par->reversa->capacidade = aresta->fluxo;
        }
    }
}


// Função que CRIA o grafo de nível definindo os níveis dos vértices
int criarGrafoNivel(int source, int sink, no** adjResidual, int *niveis, int n) {
    for (int i = 0; i < n; i++) niveis[i] = -1;

    // Sempre colocamos o primeiro vertice do grafo residual na fila primeiro pra ser explorado
    fila f;
    iniciarFila(&f); // Fila começa zerada

    niveis[source] = 0;
    push(&f, source);

    while(!estaVazia(&f)) { // Enquanto a fila não estiver vazia nós continuamos nossa busca em profundidade
        int v = pop(&f);

        for(no* arestasExplorar = adjResidual[v]; arestasExplorar != NULL; arestasExplorar = arestasExplorar->proximaAresta) {
            if(arestasExplorar->capacidade > 0 && niveis[arestasExplorar->vizinho] == -1) {
                niveis[arestasExplorar->vizinho] = niveis[v] + 1;
                push(&f, arestasExplorar->vizinho);
            }
        }
    }

    return niveis[sink] != -1;


}

// Busca em profundidade
long long dfs(int v, int t, int fluxo, no** adjResidual, int* nivel, no** next) {
    if (v == t)
        return fluxo; // sumidouro encontrado

    for (; next[v] != NULL; next[v] = next[v]->proximaAresta) {
        no* e = next[v];

        if(e->capacidade > 0 && nivel[e->vizinho] == nivel[v] + 1) {

            long long empurrado = dfs(e->vizinho, t, fluxo < e->capacidade ? fluxo : e->capacidade, adjResidual, nivel, next);

            if (empurrado > 0) {
                e->capacidade -= empurrado;
                e->reversa->capacidade += empurrado;
                if (e->tipo == 0)
                    e->original->fluxo += empurrado;
                else
                    e->original->fluxo -= empurrado;

                return empurrado;
            }
        }
    }
    return 0;
}

long long maxFlow(no** adj, no** adjResidual, Caminho* caminho, int* cor, int* niveis, no** next, int n) {
    int source = 0;
    int sinkhole = n - 1;
    long long fluxoMax = 0;

    criarGrafoResidual(adj, adjResidual, n);
    while(criarGrafoNivel(source, sinkhole, adjResidual, niveis, n)) {
        for (int i = 0; i < n; i++)
            next[i] = adjResidual[i];

        long long f;
        while ((f = dfs(source, sinkhole, INT_MAX, adjResidual, niveis, next)) > 0) {
            fluxoMax += f;
        }   
    }

    return fluxoMax;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m); 
    no **adj = malloc(n * sizeof(no*));
    no **adjResidual = malloc(n * sizeof(no*));
    no **next = malloc(n * sizeof(no*));
    int* cor = malloc(n * sizeof(int));
    int* niveis = malloc(n * sizeof(int));
    Caminho* caminho = malloc(n * sizeof(Caminho));
    inicializarGrafo(adj, cor, n);
    inicializarGrafo(adjResidual, cor, n);
    no* ponteiroPrasArestas[m];
    
    for(int i = 0; i < m; i++) {
        int v, w, c;
        scanf("%d %d %d", &v, &w, &c);
        
        if(c > 1e9) {
            return -1;
        }
        v--;
        w--;
        ponteiroPrasArestas[i] = adicionarAresta(adj, v, w, c, 0);
    }
    
    long long flowMaximo = maxFlow(adj, adjResidual, caminho, cor, niveis, next, n);
    printf("%lld\n", flowMaximo);
    for (int i = 0; i < m; i++) {
        printf("%d\n", ponteiroPrasArestas[i]->fluxo);
    }
}