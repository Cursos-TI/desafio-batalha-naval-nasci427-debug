#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3   // Cada navio ocupa 3 posições
#define AGUA 0        // Representa água
#define NAVIO 3       // Representa parte do navio

int main() {
    int tabuleiro[TAM][TAM]; // Matriz do tabuleiro
    int i, j;

    // ===== Inicializar o tabuleiro ===== //
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA; // Todas as posições começam com água (0)
        }
    }

    // ===== Definir os navios ===== //
    int navioHorizontal[TAM_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAM_NAVIO]   = {NAVIO, NAVIO, NAVIO};
    int navioDiagonal1[TAM_NAVIO]  = {NAVIO, NAVIO, NAVIO}; // ↘ diagonal
    int navioDiagonal2[TAM_NAVIO]  = {NAVIO, NAVIO, NAVIO}; // ↙ diagonal

    // ===== Coordenadas iniciais ===== //
    int linhaH = 2, colunaH = 4; // Navio horizontal
    int linhaV = 5, colunaV = 7; // Navio vertical
    int linhaD1 = 1, colunaD1 = 1; // Navio diagonal ↘
    int linhaD2 = 1, colunaD2 = 8; // Navio diagonal ↙

    // ===== Validar e posicionar o navio horizontal ===== //
    if (colunaH + TAM_NAVIO <= TAM) { 
        for (j = 0; j < TAM_NAVIO; j++) {
            tabuleiro[linhaH][colunaH + j] = navioHorizontal[j];
        }
    } else {
        printf("Erro: navio horizontal fora dos limites!\n");
        return 1;
    }

    // ===== Validar e posicionar o navio vertical ===== //
    if (linhaV + TAM_NAVIO <= TAM) { 
        int sobreposicao = 0;
        for (i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaV + i][colunaV] == NAVIO)
                sobreposicao = 1;
        }

        if (!sobreposicao) {
            for (i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = navioVertical[i];
            }
        } else {
            printf("Erro: sobreposição de navios detectada!\n");
            return 1;
        }
    } else {
        printf("Erro: navio vertical fora dos limites!\n");
        return 1;
    }

    // ===== Validar e posicionar o navio diagonal ↘ ===== //
    if (linhaD1 + TAM_NAVIO <= TAM && colunaD1 + TAM_NAVIO <= TAM) {
        int sobreposicao = 0;
        for (i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaD1 + i][colunaD1 + i] == NAVIO)
                sobreposicao = 1;
        }

        if (!sobreposicao) {
            for (i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaD1 + i][colunaD1 + i] = navioDiagonal1[i];
            }
        } else {
            printf("Erro: sobreposição de navio diagonal ↘ detectada!\n");
            return 1;
        }
    } else {
        printf("Erro: navio diagonal ↘ fora dos limites!\n");
        return 1;
    }

    // ===== Validar e posicionar o navio diagonal ↙ ===== //
    if (linhaD2 + TAM_NAVIO <= TAM && colunaD2 - (TAM_NAVIO - 1) >= 0) {
        int sobreposicao = 0;
        for (i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaD2 + i][colunaD2 - i] == NAVIO)
                sobreposicao = 1;
        }

        if (!sobreposicao) {
            for (i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaD2 + i][colunaD2 - i] = navioDiagonal2[i];
            }
        } else {
            printf("Erro: sobreposição de navio diagonal ↙ detectada!\n");
            return 1;
        }
    } else {
        printf("Erro: navio diagonal ↙ fora dos limites!\n");
        return 1;
    }

    // ===== Exibir o tabuleiro ===== //
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    // ===== Mostrar coordenadas dos navios ===== //
    printf("\nCoordenadas do Navio Horizontal:\n");
    for (j = 0; j < TAM_NAVIO; j++) {
        printf("Parte %d -> Linha: %d | Coluna: %d\n", j + 1, linhaH, colunaH + j);
    }

    printf("\nCoordenadas do Navio Vertical:\n");
    for (i = 0; i < TAM_NAVIO; i++) {
        printf("Parte %d -> Linha: %d | Coluna: %d\n", i + 1, linhaV + i, colunaV);
    }

    printf("\nCoordenadas do Navio Diagonal ↘:\n");
    for (i = 0; i < TAM_NAVIO; i++) {
        printf("Parte %d -> Linha: %d | Coluna: %d\n", i + 1, linhaD1 + i, colunaD1 + i);
    }

    printf("\nCoordenadas do Navio Diagonal ↙:\n");
    for (i = 0; i < TAM_NAVIO; i++) {
        printf("Parte %d -> Linha: %d | Coluna: %d\n", i + 1, linhaD2 + i, colunaD2 - i);
    }

    return 0;
}