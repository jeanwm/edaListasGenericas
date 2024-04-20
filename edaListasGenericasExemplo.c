#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define any_t void*

typedef struct no {
    struct no* anterior;
    struct no* proximo;
    any_t valor;
} No;

typedef struct {
    No* cabeca;
    No* cauda;
} Lista;

No* novo_no(any_t valor, size_t tamanho) {
    No* no = (No*) malloc(sizeof(No));
    no->valor = malloc(tamanho);
    memcpy(no->valor, valor, tamanho);
    
    no->anterior = no->proximo = NULL;

    return no;
}

Lista* nova_lista() {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->cabeca = l->cauda = NULL;

    return l;
}

bool lista_vazia(Lista* l) {
    return l->cabeca == NULL && l->cauda == NULL;
}

void lista_push(Lista* l, any_t valor, size_t tamanho) {
    No* no = novo_no(valor, tamanho);
    
    no->anterior = l->cauda;
    
    if (lista_vazia(l)) {
        l->cabeca = no;
    } else {
        l->cauda->proximo = no;
    }
    
    l->cauda = no;
}

void lista_unshift(Lista* l, any_t valor, size_t tamanho) {
    No* no = novo_no(valor, tamanho);
    
    no->proximo = l->cabeca;
    
    if (lista_vazia(l)) {
        l->cauda = no;
    } else {
        l->cabeca->anterior = no;
    }
    
    l->cabeca = no;
}

any_t lista_pop(Lista* l) {
    if (lista_vazia(l)) {
        return NULL;
    }    

    any_t valor = l->cauda->valor;
    free(l->cauda->valor);
    
    No* anterior = l->cauda->anterior;
    
    if (anterior != NULL) {
        anterior->proximo = NULL;
    }
    
    free(l->cauda);
    l->cauda = anterior;
    
    if (anterior == NULL) {
        l->cabeca = NULL;
    }
    
    return valor;
}

any_t lista_shift(Lista* l) {
    if (lista_vazia(l)) {
        return NULL;
    }
    
    any_t valor = l->cabeca->valor;
    free(l->cabeca->valor);
    
    No* proximo = l->cabeca->proximo;
    
    if (proximo != NULL) {
        proximo->anterior = NULL;
    }
    
    free(l->cabeca);
    l->cabeca = proximo;
    
    if (proximo == NULL) {
        l->cauda = NULL;
    }
    
    return valor;
}

int main(void) {
    Lista* l = nova_lista();

    for (int i = 0; i < 10; i++) {
        if (i < 5) {
            lista_unshift(l, &i, sizeof(int));
        } else {
            lista_push(l, &i, sizeof(int));
        }
    }

    while (!lista_vazia(l)) {
        int* valor = (int*) lista_pop(l);
        printf("%d ", *valor);
    }

    return 0;
}