#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BRANCO 0
#define CINZA  1
#define PRETO  2

typedef struct no {
    int vizinho; // Com qual vÃ©rtice ele se liga
    int fluxo;
    int capacidade;
    int tipo;

    struct no* original; // Cada aresta vai apontar pra sua respectiva aresta original
    struct no* reversa; // E cada aresta normal pode apontar tambÃ©m pra sua reversa

    struct no *proximaAresta; // Ir pra prÃ³xima aresta que ele tem
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
    int pai;          // vÃ©rtice anterior no caminho
    no* arestaResidual;       // aresta residual usada pra chegar aqui
} Caminho;


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

void inicializarGrafo(no** adj, int* cor, int n) { 
    for(int i = 0; i < n; i++) {
        adj[i] = NULL; // Lista de adjacÃªncia de cada vÃ©rtice comeÃ§a com todo mundo apontando pra null
        cor[i] = BRANCO;
    }
}

no* adicionarAresta(no** adj, int v, int w, int c, int tipo) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w; // Adicionamos nossa aresta
    n1->proximaAresta = adj[v]; // Ligamos a nossa nova aresta a primeira aresta que jÃ¡ tinhamos antes
    n1->capacidade = c;
    n1->tipo = tipo;
    n1->fluxo = 0; // Fluxo que passa pela aresta inicia zerado
    adj[v] = n1; // Nossa nova aresta se torna a primeira aresta da lista de adjacÃªncia

    return n1;
}

no* adicionarArestaResidual(no** adj, int v, int w, int c, int tipo) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w; // Adicionamos nossa aresta
    n1->proximaAresta = adj[v]; // Ligamos a nossa nova aresta a primeira aresta que jÃ¡ tinhamos antes
    n1->capacidade = c;
    n1->tipo = tipo;
    n1->fluxo = 0; // Fluxo que passa pela aresta inicia zerado
    adj[v] = n1; // Nossa nova aresta se torna a primeira aresta da lista de adjacÃªncia

    no* n2 = malloc(sizeof(no));
    n2->vizinho = v; // Adicionamos nossa aresta
    n2->proximaAresta = adj[w]; // Ligamos a nossa nova aresta a primeira aresta que jÃ¡ tinhamos antes
    n2->capacidade = 0; // Capacidade da aresta reversa comeÃ§a zerada 
    n2->tipo = 1;
    n2->fluxo = 0; // Fluxo que passa pela aresta inicia zerado
    adj[w] = n2; // Nossa nova aresta se torna a primeira aresta da lista de adjacÃªncia

    n1->reversa = n2;
    n2->reversa = n1;

    return n1;
}

no* buscarAresta(no** adj, int v, int w) {
    for (no* aresta = adj[v]; aresta != NULL; aresta = aresta->proximaAresta) {
        if (aresta->vizinho == w) {
            return aresta; // Já existe
        }
    }
    return NULL; // Não existe
}

void criarGrafoResidual(no** adj, no** adjResidual, int n) {
    for (int i = 0; i < n; i++) {
        for (no* aresta = adj[i]; aresta != NULL; aresta = aresta->proximaAresta) {

            int v = i;
            int w = aresta->vizinho;
            int capDireta = aresta->capacidade - aresta->fluxo; 

            no* existente = buscarAresta(adjResidual, v, w);

            if(existente != NULL) {
                existente->capacidade += capDireta;
            } else {
                no* par = adicionarArestaResidual(adjResidual, i, aresta->vizinho, capDireta, 0);
    
                par->original = aresta;
                par->reversa->tipo = 1;
                par->reversa->original = aresta;
    
                par->reversa->capacidade = aresta->fluxo;
            }

        }
    }
}


// FunÃ§Ã£o que CRIA o grafo de nÃ­vel definindo os nÃ­veis dos vÃ©rtices
int criarGrafoNivel(int source, int sink, no** adjResidual, int *niveis, int n) {
    for (int i = 0; i < n; i++) niveis[i] = -1;

    // Sempre colocamos o primeiro vertice do grafo residual na fila primeiro pra ser explorado
    fila f;
    iniciarFila(&f); // Fila comeÃ§a zerada

    niveis[source] = 0;
    push(&f, source);

    while(!estaVazia(&f)) { // Enquanto a fila nÃ£o estiver vazia nÃ³s continuamos nossa busca em profundidade
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

void bfs(int source, no** adjResidual, int* alcancavel, int n) {
    for(int i = 0; i < n; i++) alcancavel[i] = 0;
    // Sempre colocamos o primeiro vertice do grafo residual na fila primeiro pra ser explorado
    fila f;
    iniciarFila(&f); // Fila comeÃ§a zerada
    
    alcancavel[source] = 1;
    push(&f, source);

    while(!estaVazia(&f)) { // Enquanto a fila nÃ£o estiver vazia nÃ³s continuamos nossa busca em profundidade
        int v = pop(&f);

        for(no* arestasExplorar = adjResidual[v]; arestasExplorar != NULL; arestasExplorar = arestasExplorar->proximaAresta) {
            if (arestasExplorar->capacidade > 0 && alcancavel[arestasExplorar->vizinho] != 1) {
                alcancavel[arestasExplorar->vizinho] = 1;
                push(&f, arestasExplorar->vizinho);
            }
        }
    }
}


void encontrarCortes(no** adj, int n, int* alcancavel, int* qtdCorte, no** listaGargalos) {
    for(int i = 0; i < n; i++) {
        for(no* aresta = adj[i]; aresta != NULL; aresta = aresta->proximaAresta) {
            if((alcancavel[i] == 1 && alcancavel[aresta->vizinho] == 0)) {
                (*qtdCorte)++;
            }
        }
    }
}


// Busca em profundidade
long long dfs(int v, int t, int fluxo, no** adjResidual, int* nivel, no** next, int* qtdCorte, no** listaGargalos) {
    if (v == t) {
        return fluxo; // sumidouro encontrado
    }

    for (; next[v] != NULL; next[v] = next[v]->proximaAresta) {
        no* e = next[v];

        if(e->capacidade > 0 && nivel[e->vizinho] == nivel[v] + 1) {
            long long empurrado = dfs(e->vizinho, t, fluxo < e->capacidade ? fluxo : e->capacidade, adjResidual, nivel, next, qtdCorte, listaGargalos);
            
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

long long maxFlow(no** adj, no** adjResidual, int* alcancavel, int* niveis, no** next, int n, int* qtdCorte, no** listaGargalos) {
    int source = 0;
    int sinkhole = n - 1;
    long long fluxoMax = 0;

    criarGrafoResidual(adj, adjResidual, n);
    while(criarGrafoNivel(source, sinkhole, adjResidual, niveis, n)) {
        for (int i = 0; i < n; i++)
            next[i] = adjResidual[i];

        long long f;
        while ((f = dfs(source, sinkhole, INT_MAX, adjResidual, niveis, next, qtdCorte, listaGargalos)) > 0) {
            fluxoMax += f;
        }   
    }

    bfs(source, adjResidual, alcancavel, n);
    encontrarCortes(adj, n, alcancavel, qtdCorte, listaGargalos);

    return fluxoMax;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m); 
    no **adj = malloc(n * sizeof(no*));
    no **adjResidual = malloc(n * sizeof(no*));
    no **next = malloc(n * sizeof(no*));
    no **listaGargalos = malloc(n * sizeof(no*));
    int* cor = malloc(n * sizeof(int));
    int* alcancavel = malloc(n * sizeof(int));
    int* niveis = malloc(n * sizeof(int));
    int* qtdCorte = malloc(sizeof(int));
    *qtdCorte = 0;

    inicializarGrafo(adj, cor, n);
    inicializarGrafo(adjResidual, cor, n);
    int arestas_v[m], arestas_w[m];
    
    for(int i = 0; i < m; i++) {
        int v, w, c;
        scanf("%d %d %d", &v, &w, &c);
        
        if(c > 1e9) {
            return -1;
        }
        v--;
        w--;

        arestas_v[i] = v;
        arestas_w[i] = w;
        adicionarAresta(adj, v, w, c, 0);
        adicionarAresta(adj, w, v, c, 0);
    }
    
    long long flowMaximo = maxFlow(adj, adjResidual, alcancavel, niveis, next, n, qtdCorte, listaGargalos);
    printf("%d %lld\n", *qtdCorte, flowMaximo); // Printo a quantidade vezes de corte e o flow máximo
    for(int i = 0; i < m; i++) {
        if(alcancavel[arestas_v[i]] != alcancavel[arestas_w[i]]) {
            printf("%d ", i + 1);
        }
    }
}