#include <stdio.h>
#include <stdlib.h> // Para usar abs()

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3   // Cada navio ocupa 3 posições
#define AGUA 0        // Representa água
#define NAVIO 3       // Representa parte do navio
#define HABILIDADE 5  // Representa área afetada pela habilidade
#define TAM_HAB 5     // Tamanho das matrizes de habilidade (5x5)

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

    // ====== MATRIZES DE HABILIDADE ====== //
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // === Criar Cone (em forma triangular apontando para baixo) ===
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2) - i && j <= (TAM_HAB / 2) + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    // === Criar Cruz ===
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }

    // === Criar Octaedro (formato de losango) ===
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }

    // ====== Aplicar habilidades no tabuleiro ====== //
    int centro = TAM_HAB / 2;

    // Posição da origem de cada habilidade
    int origemConeL = 1, origemConeC = 5;
    int origemCruzL = 6, origemCruzC = 2;
    int origemOctaL = 7, origemOctaC = 8;

    // --- Cone ---
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (cone[i][j] == 1) {
                int l = origemConeL + (i - centro);
                int c = origemConeC + (j - centro);
                if (l >= 0 && l < TAM && c >= 0 && c < TAM && tabuleiro[l][c] == AGUA)
                    tabuleiro[l][c] = HABILIDADE;
            }
        }
    }

    // --- Cruz ---
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (cruz[i][j] == 1) {
                int l = origemCruzL + (i - centro);
                int c = origemCruzC + (j - centro);
                if (l >= 0 && l < TAM && c >= 0 && c < TAM && tabuleiro[l][c] == AGUA)
                    tabuleiro[l][c] = HABILIDADE;
            }
        }
    }

    // --- Octaedro ---
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (octaedro[i][j] == 1) {
                int l = origemOctaL + (i - centro);
                int c = origemOctaC + (j - centro);
                if (l >= 0 && l < TAM && c >= 0 && c < TAM && tabuleiro[l][c] == AGUA)
                    tabuleiro[l][c] = HABILIDADE;
            }
        }
    }

    // ===== Exibir o tabuleiro ===== //
    printf("\n=== TABULEIRO DE BATALHA NAVAL COM HABILIDADES ===\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf("~ ");  // água
            else if (tabuleiro[i][j] == NAVIO)
                printf("N ");  // navio
            else if (tabuleiro[i][j] == HABILIDADE)
                printf("* ");  // área de habilidade
        }
        printf("\n");
    }

    // ===== Legenda ===== //
    printf("\nLegenda:\n~ = Água\nN = Navio\n* = Área de Habilidade\n");

    return 0;
}