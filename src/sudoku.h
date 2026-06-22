#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define TAMANHO       9
#define TOTAL_NOS     81
#define MAX_VIZINHOS  20

typedef struct Vertice {
    int  id, valor, num_vizinhos;                                       
    bool fixo;                 
    struct Vertice *vizinhos[MAX_VIZINHOS];
} Vertice;

typedef struct Grafo{
    Vertice nos[TOTAL_NOS];
} Grafo;

typedef struct {
    bool used_linha  [TAMANHO][TAMANHO + 1];
    bool used_coluna [TAMANHO][TAMANHO + 1];
    bool used_bloco  [TAMANHO][TAMANHO + 1];
} TabelasHash;

typedef struct {
    Vertice *dados[TOTAL_NOS];
    int tamanho;
} MinHeap;

typedef struct NoBST {
    int id_vertice, valor_antigo, valor_novo, chave;     
    struct NoBST *esq, *dir;
} NoBST;

typedef struct {
    NoBST *raiz;
    int    proxima_chave, chave_atual;         
} HistBST;

typedef struct {
    Grafo       grafo;
    TabelasHash hash;
    MinHeap     heap;
    HistBST     historico;
    int dificuldade;
} Jogo;

void grafo_inicializar(Grafo *g);
int  grafo_linha  (int id);
int  grafo_coluna (int id);
int  grafo_bloco  (int id);
bool grafo_sao_vizinhos(int id1, int id2);

void hash_inicializar  (TabelasHash *h);
void hash_inserir      (TabelasHash *h, int linha, int coluna, int bloco, int valor);
void hash_remover      (TabelasHash *h, int linha, int coluna, int bloco, int valor);
bool hash_valido       (TabelasHash *h, int linha, int coluna, int bloco, int valor);

void heap_inicializar  (MinHeap *h);
void heap_inserir      (MinHeap *h, Vertice *v, TabelasHash *hash);
Vertice *heap_extrair_min(MinHeap *h, TabelasHash *hash);
void heap_atualizar    (MinHeap *h, TabelasHash *hash);
int  heap_contar_opcoes(Vertice *v, TabelasHash *hash);

bool solver_resolver   (Jogo *j);
void solver_gerar_jogo (Jogo *j, int celulas_remover);

void hist_inicializar  (HistBST *h);
void hist_inserir      (HistBST *h, int id, int val_ant, int val_novo);
bool hist_undo         (HistBST *h, Jogo *j);
void hist_libertar     (NoBST *no);

void jogo_inicializar  (Jogo *j);
bool jogo_colocar      (Jogo *j, int linha, int coluna, int valor);
void jogo_imprimir     (Jogo *j);
bool jogo_terminado    (Jogo *j);

void interface_menu_principal(void);
void interface_jogar         (Jogo *j);
void interface_ver_solucao   (Jogo *j);

#endif