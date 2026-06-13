#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

typedef struct no
{
    int id_vizinho;
    struct no *prox;
}no;

typedef struct vertice
{
    int id, valor;
    no *lista_vizinhos;
}vertice;

typedef struct  grafo
{
    vertice celulas[82];
}grafo;