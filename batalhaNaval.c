#include <stdio.h>
#include <windows.h>

// Configurações de tamanho
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HAB 5

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // Iniciando o tabuleiro e o tamanho dos navios e habilidades
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};
    int navio[TAM_NAVIO] = {3, 3, 3};
    int cone[TAM_HAB][TAM_HAB] = {0};
    int cruz[TAM_HAB][TAM_HAB] = {0};
    int octaedro[TAM_HAB][TAM_HAB] = {0};

    // Navio horizontal
    int linha_h = 2, col_h = 1; 
    
    // Navio vertical
    int linha_v = 5, col_v = 7; 
    
    // Navio diagonal 1
    int linha_d1 = 6, col_d1 = 1; 
    
    // Navio diagonal 2
    int linha_d2 = 3, col_d2 = 6;

    // Validando e colocando o navio horizontal
    int valido_h = 1;
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha_h; 
        int c = col_h + i;
        
        // Verifica limites (se a linha ou coluna passaram de 9 ou são menores que 0)
        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO) { valido_h = 0; break; }
        // Verifica sobreposição
        if (tabuleiro[l][c] != 0) { valido_h = 0; break; }
    }
    if (valido_h == 1) {
        for (int i = 0; i < TAM_NAVIO; i++) { tabuleiro[linha_h][col_h + i] = navio[i]; }
        printf("Navio 1 (Horizontal) posicionado.\n");
    }

    // Validando e colocando o navio vertical
    int valido_v = 1;
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha_v + i;
        int c = col_v;
        
        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO) { valido_v = 0; break; }
        if (tabuleiro[l][c] != 0) { valido_v = 0; break; }
    }
    if (valido_v == 1) {
        for (int i = 0; i < TAM_NAVIO; i++) { tabuleiro[linha_v + i][col_v] = navio[i]; }
        printf("Navio 2 (Vertical) posicionado.\n");
    }

    // Validando e colocando o navio diagonal 1
    int valido_d1 = 1;
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha_d1 + i;
        int c = col_d1 + i;
        
        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO) { valido_d1 = 0; break; }
        if (tabuleiro[l][c] != 0) { valido_d1 = 0; break; }
    }
    if (valido_d1 == 1) {
        for (int i = 0; i < TAM_NAVIO; i++) { tabuleiro[linha_d1 + i][col_d1 + i] = navio[i]; }
        printf("Navio 3 (Diagonal \\) posicionado.\n");
    }

    // Validando e colocando o navio diagonal 2
    int valido_d2 = 1;
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha_d2 - i;
        int c = col_d2 + i;
        
        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO) { valido_d2 = 0; break; }
        if (tabuleiro[l][c] != 0) { valido_d2 = 0; break; }
    }
    if (valido_d2 == 1) {
        for (int i = 0; i < TAM_NAVIO; i++) { tabuleiro[linha_d2 - i][col_d2 + i] = navio[i]; }
        printf("Navio 4 (Diagonal /) posicionado.\n");
    }

    // Gerando a habilidade em cone
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Desenha apenas nas 3 primeiras linhas. A cada linha, a largura aumenta.
            if (i < 3 && j >= (2 - i) && j <= (2 + i)) {
                cone[i][j] = 1;
            }
        }
    }

    // Gerando a habilidade em cruz
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Marca 1 se for a linha do meio OU a coluna do meio
            if (i == 2 || j == 2) {
                cruz[i][j] = 1;
            }
        }
    }

    // Gerando a habilidade em octaedro
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Calculamos a distância do ponto atual até o centro (2,2)
            // Como C básico não tem função abs() em stdio, usamos operador ternário para valor absoluto
            int dist_i = (i > 2) ? (i - 2) : (2 - i);
            int dist_j = (j > 2) ? (j - 2) : (2 - j);
            
            // Se a soma das distâncias for menor ou igual a 2, pertence ao octaedro
            if (dist_i + dist_j <= 2) {
                octaedro[i][j] = 1;
            }
        }
    }

    // Aplicando a habilidade em cone no tabuleiro
    int origem_cone_linha = 1, origem_cone_col = 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (cone[i][j] == 1) {
                // Calcula as coordenadas
                int l_tab = origem_cone_linha + i;
                int c_tab = origem_cone_col + (j - 2);

                // Validação se está dentro do tabuleiro
                if (l_tab >= 0 && l_tab < TAM_TABULEIRO && c_tab >= 0 && c_tab < TAM_TABULEIRO) {
                    tabuleiro[l_tab][c_tab] = 5;
                }
            }
        }
    }

    // Aplicando a habilidade em cruz no tabuleiro
    int origem_cruz_linha = 7, origem_cruz_col = 3;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (cruz[i][j] == 1) {
                int l_tab = origem_cruz_linha + (i - 2);
                int c_tab = origem_cruz_col + (j - 2);

                if (l_tab >= 0 && l_tab < TAM_TABULEIRO && c_tab >= 0 && c_tab < TAM_TABULEIRO) {
                    tabuleiro[l_tab][c_tab] = 5;
                }
            }
        }
    }

    // Aplicando a habilidade em octaedro no tabuleiro
    int origem_octa_linha = 4, origem_octa_col = 7;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (octaedro[i][j] == 1) {
                int l_tab = origem_octa_linha + (i - 2);
                int c_tab = origem_octa_col + (j - 2);

                if (l_tab >= 0 && l_tab < TAM_TABULEIRO && c_tab >= 0 && c_tab < TAM_TABULEIRO) {
                    tabuleiro[l_tab][c_tab] = 5;
                }
            }
        }
    }

    printf("\n");
    // --- EXIBIÇÃO DO TABULEIRO ---
    printf("Tabuleiro de Batalha Naval! ⚔️\n");
    printf("------------- 🔱 -------------\n");
    
    // Loop para percorrer as linhas da matriz
    for (int linha = 0; linha < TAM_TABULEIRO; linha++) {
        // Loop para percorrer as colunas da matriz
        for (int coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            // Imprime o valor daquela coordenada com um espaço para ficar organizado
            printf(" %d ", tabuleiro[linha][coluna]);
        }
        // Ao final de cada linha, pula para a linha de baixo no console
        printf("\n");
    }
    printf("------------- 🔱 -------------\n");
    return 0;
}
