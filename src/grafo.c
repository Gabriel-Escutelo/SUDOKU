#include "sudoku.h"

int grafo_linha(int id)
{
    return id / TAMANHO;
}

int grafo_coluna(int id)
{
    return id % TAMANHO;
}

int grafo_bloco(int id)
{
    int l = grafo_linha(id);
    int c = grafo_coluna(id);
    return(l / 3) * 3 + (c / 3);
}

bool grafo_sao_vizinhos(int id1, int id2) {
    if (id1 == id2) return false;
    return (grafo_linha(id1)  == grafo_linha(id2))  ||
           (grafo_coluna(id1) == grafo_coluna(id2)) ||
           (grafo_bloco(id1)  == grafo_bloco(id2));
}

void grafo_inicializar(Grafo *g) {
    int i, j;
    for (i = 0; i < TOTAL_NOS; i++) {
        g->nos[i].id = i;
        g->nos[i].valor = 0;
        g->nos[i].fixo = false;
        g->nos[i].num_vizinhos = 0;
    }
    for (i = 0; i < TOTAL_NOS; i++) {
        for (j = 0; j < TOTAL_NOS; j++) {
            if (grafo_sao_vizinhos(i, j)) {
                g->nos[i].vizinhos[g->nos[i].num_vizinhos] = &g->nos[j];
                g->nos[i].num_vizinhos++;
            }
        }
    }
}   