#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int index;
    struct node* proximo;
} node; 

typedef struct fila {
    node* cabeca;
    node* fim;
} fila;

void inicializarFila(fila* f) {
    f->cabeca = NULL;
    f->fim = NULL;
}

int main() {

}