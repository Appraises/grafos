#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no {
    int vizinho;
    struct no* proximaAresta;
} no;

typedef struct node {
    int vertice;
    int distancia;
    struct node* prox;
} node;

typedef struct fila {
    struct node* cabeca;
    struct node* fim;
} fila;

void inicializarGrafo(no** adj, int n, int* cor, int* protegidoPor) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
        cor[i] = 0;
        protegidoPor[i] = -1;
    }
}

void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;
}

void push(fila* fila, int vertice, int d) {
    if (fila->cabeca == NULL || fila->fim == NULL) {
        printf("Fila nÃ£o inicializada\n");
        exit(1);
    }

    node* novo = (node*)malloc(sizeof(node));
    novo->vertice = vertice; // VÃ©rtice que acabamos de colocar na fila
    novo->prox = NULL; // NÃ£o tem ninguÃ©m atrÃ¡s do vÃ©rtice que acabamos de adicionar
    novo->distancia = d;
    fila->fim->prox = novo; // O vertice que estava no fim agora aponta pra nosso novo vÃ©rtice
    fila->fim = novo; // Fim agora Ã© o nosso novo vertice
}

int estaVazia(fila* fila) {
    return (fila->cabeca->prox == NULL);
}

node pop(fila* fila) {
    if(fila->cabeca->prox == NULL) {
        printf("Fila estÃ¡ vazia jÃ¡.\n");
        exit(1);
    }

    node* verticeRemover = fila->cabeca->prox;
    node dados = *verticeRemover;

    fila->cabeca->prox = verticeRemover->prox; // O prÃ³ximo no inÃ­cio da fila Ã© quem vinha depois

    if(fila->cabeca->prox == NULL) { // Se a fila estiver vazia o fim precisa voltar a apontar pra NULL
        fila->fim = fila->cabeca; 
    }

    free(verticeRemover);
    return dados;
}

void iniciarFila(fila *f) {
    f->cabeca = (node*)malloc(sizeof(node)); // NÃ³ cabeÃ§a
    f->cabeca->prox = NULL;
    f->fim = f->cabeca; // Fila vazia, fim aponta para cabeÃ§a
}

int bfs(int inicio, fila* f, int* cor, no** adj, int* protegidoPor, int s) {
    if(cor[inicio] == 1) return 0;
    cor[inicio] = 1;
    protegidoPor[inicio] = inicio;
    push(f, inicio, 0);
    int conflito = 0;

    // bfs normal até aqui
    while(!estaVazia(f)) {
        node atual = pop(f);
        if(conflito) continue; // limpar a lista pro próximo caso se tiver dado conflito

        if(atual.distancia < s) { // enquanto a distância, que tá indo junto com o node, for menor do que a força, podemos ir seguindo
            for(no* aresta = adj[atual.vertice]; aresta != NULL; aresta = aresta->proximaAresta) {
                if(cor[aresta->vizinho] == 0) { // Se não foi colorido até agora, pinto ele, e dou push
                    cor[aresta->vizinho] = 1;
                    push(f, aresta->vizinho, atual.distancia + 1); // Incremento a distância
                    protegidoPor[aresta->vizinho] = inicio; // Marco que ele foi protegido por aquele que iniciou a bfs, já que estamos construindo as camadas a partir dele
                } else {
                    if(protegidoPor[aresta->vizinho] != inicio) conflito = 1; // Verificamos se ele tá sendo protegido por 
                    // por algum soldado diferente, se tiver, aqui daria um conflito
                }
            }
        }
    }

    return (conflito == 0); // Se não deu nenhum conflito, retorno 1, tudo certo
    // caso contrário 0
}

int main() {
    int q;
    scanf("%d", &q);

    for(int i = 0; i < q; i++) {
        int n, r, m;
        scanf("%d %d %d", &n, &r, &m);
    
        no** adj = malloc(n * sizeof(no*));
        int* cor = malloc(n * sizeof(int));
        int* protegidoPor = malloc(n * sizeof(int));
    
        fila f;
        iniciarFila(&f);
    
        inicializarGrafo(adj, n, cor, protegidoPor);
    
        for(int j = 0; j < r; j++) {
            int v, w;
            scanf("%d %d", &v, &w);
    
            v--;
            w--;
    
            adicionarAresta(v, w, adj);
            adicionarAresta(w, v, adj);
        }

        int possivel = 1;
        for(int l = 0; l < m; l++) {
            int k, s;
            scanf("%d %d", &k, &s);
            k--;


            if(possivel) { // Se não for possível nem precisa verificar o resto dos casos
                if(!bfs(k, &f, cor, adj, protegidoPor, s)) {
                    // Se retornar 0 então deu algum conflito, e se temos conflito, então
                    // não é possível a solução ser ótima
                    possivel = 0;
                }
            } 
        }


        // Verificamos se tem alguma cidade que não foi protegida, se tiver alguma, nossa solução também não é ótima
        if(possivel) {
            for(int d = 0; d < n; d++) {
                if(cor[d] == 0) {
                    possivel = 0;
                    break;
                }
                // printf("%d ", coberto[d]);
            }
        }

        // Se possivel continua como 1, printamos que sim, é possível, caso contrário não
        if(possivel) printf("Yes\n");
        else printf("No\n");
    }

    return 0;

}