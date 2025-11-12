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

    // Coordenadas iniciais (definidas no código)
    int linhaH = 2, colunaH = 4; // Navio horizontal começa na linha 2, coluna 4
    int linhaV = 5, colunaV = 7; // Navio vertical começa na linha 5, coluna 7

    // ===== 3. Validar e posicionar o navio horizontal =====
    if (colunaH + TAM_NAVIO <= TAM) { // Cabe no tabuleiro?
        for (j = 0; j < TAM_NAVIO; j++) {
            tabuleiro[linhaH][colunaH + j] = navioHorizontal[j];
        }
    } else {
        printf("Erro: navio horizontal fora dos limites!\n");
        return 1; // Encerra o programa
    }

    // ===== Validar e posicionar o navio vertical ===== //
    if (linhaV + TAM_NAVIO <= TAM) { // Cabe no tabuleiro?
        int sobreposicao = 0;
        for (i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaV + i][colunaV] == NAVIO) {
                sobreposicao = 1;
            }
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

    // ===== Exibição do tabuleiro ===== //
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

    return 0;
}


