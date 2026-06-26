#include "sudoku.h"

#ifdef _WIN32
  #define LIMPAR "cls"
#else
  #define LIMPAR "clear"
#endif

static void limpar_ecra(void) 
{ 
    system(LIMPAR); 
}

static void pausar(void) {
    printf("\nPrime ENTER para continuar...");
    while (getchar() != '\n');
    getchar();
}

static int escolher_dificuldade(void) {
    int op;
    printf("  Dificuldade:\n");
    printf("  [1] Facil   (30 celulas removidas)\n");
    printf("  [2] Medio   (40 celulas removidas)\n");
    printf("  [3] Dificil (50 celulas removidas)\n");
    printf("  Opcao: ");
    if (scanf("%d", &op) != 1) op = 2;
    switch (op) {
        case 1: return 30;
        case 3: return 50;
        default: return 40;
    }
}

void interface_jogar(Jogo *j) {
    int rem = escolher_dificuldade();
    limpar_ecra();

    printf("A gerar puzzle...\n");
    solver_gerar_jogo(j, rem);

    while (true) {
        limpar_ecra();
        printf("========== SUDOKU ==========\n");
        jogo_imprimir(j);
        printf("  [L C V] Colocar valor  (ex: 3 5 7)\n");
        printf("  [0 0 0] Desfazer (Undo)\n");
        printf("  [9 9 9] Sair para o menu\n\n");
        printf("  Jogada: ");

        int l, c, v;
        if (scanf("%d %d %d", &l, &c, &v) != 3) continue;

        if (l == 9 && c == 9 && v == 9) break;

        if (l == 0 && c == 0 && v == 0) {
            if (!hist_undo(&j->historico, j))
                printf("  Nao ha jogadas para desfazer!\n");
            pausar();
            continue;
        }

        if (l < 1 || l > 9 || c < 1 || c > 9 || v < 1 || v > 9) {
            printf("  Valores invalidos! Usa linhas/colunas de 1 a 9.\n");
            pausar();
            continue;
        }

        if (!jogo_colocar(j, l - 1, c - 1, v)) {
            printf("  Jogada invalida! O numero %d ja existe nessa linha,"
                   " coluna ou bloco.\n", v);
            pausar();
            continue;
        }

        if (jogo_terminado(j)) {
            limpar_ecra();
            printf("========== SUDOKU ==========\n");
            jogo_imprimir(j);
            printf("  ** PARABENS! Puzzle resolvido! **\n\n");
            pausar();
            break;
        }
    }
}

void interface_ver_solucao(Jogo *j) {
    int rem = escolher_dificuldade();
    limpar_ecra();

    printf("A gerar puzzle...\n");
    solver_gerar_jogo(j, rem);

    printf("\nPuzzle gerado:\n");
    jogo_imprimir(j);

    printf("A resolver automaticamente (MRV + Backtracking)...\n\n");

    clock_t inicio = clock();
    bool resolvido = solver_resolver(j);
    clock_t fim    = clock();

    double ms = 1000.0 * (double)(fim - inicio) / CLOCKS_PER_SEC;

    if (resolvido) {
        printf("Solucao encontrada:\n");
        jogo_imprimir(j);
        printf("  Tempo de resolucao: %.3f ms\n\n", ms);
    } else {
        printf("  Nao foi possivel resolver o puzzle!\n\n");
    }

    pausar();
}

void interface_menu_principal(void) {
    Jogo j;
    jogo_inicializar(&j);
    srand((unsigned int)time(NULL));

    int op;
    do {
        limpar_ecra();
        printf("====================================\n");
        printf("       SUDOKU — Estruturas de Dados \n");
        printf("====================================\n\n");
        printf("  [1] Jogar\n");
        printf("  [2] Ver Resolucao Automatica (Solver)\n");
        printf("  [3] Sair\n\n");
        printf("  Opcao: ");
        if (scanf("%d", &op) != 1) op = -1;

        switch (op) {
            case 1:
                jogo_inicializar(&j);
                interface_jogar(&j);
                /* Liberta memória do histórico */
                hist_libertar(j.historico.raiz);
                break;
            case 2:
                jogo_inicializar(&j);
                interface_ver_solucao(&j);
                hist_libertar(j.historico.raiz);
                break;
            case 3:
                printf("\n  Ate logo!\n\n");
                break;
            default:
                printf("  Opcao invalida.\n");
        }
    } while (op != 3);
}