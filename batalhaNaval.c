#include <stdio.h>
#include <windows.h>

// Configurações de tamanho
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // Enchendo o tabuleiro de água
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Inserindo três vezes o número 3 para representar os navios e seu tamanho
    int navio[TAM_NAVIO] = {3, 3, 3};

    // Navio horizontal
    int linha_horiz = 2;
    int col_horiz_ini = 1;

    // Navio vertical
    int linha_vert_ini = 5;
    int col_vert = 7;

    // Verifica se o navio cabe no tabuleiro horizontalmente
    if (col_horiz_ini + TAM_NAVIO <= TAM_TABULEIRO) {
        
        // Coloca o navio no tabuleiro
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha_horiz][col_horiz_ini + i] = navio[i];
        }
        printf("-> Navio horizontal posicionado! ✅\n");
        
    } else {
        printf("-> O navio ultrapassa os limites do tabuleiro! ⚠️\n");
    }

    // Verifica se o navio cabe no tabuleiro verticalmente
    int posicao_valida = 1; 
    if (linha_vert_ini + TAM_NAVIO <= TAM_TABULEIRO) {
        
        // Antes de posicionar, verifica se já existe um navio no local
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha_vert_ini + i][col_vert] != 0) {
                posicao_valida = 0;
                break;
            }
        }
        // Colocando o navio vertical se a posição for válida
        if (posicao_valida == 1) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linha_vert_ini + i][col_vert] = navio[i];
            }
            printf("-> Navio vertical posicionado! ✅\n");
        } else {
            printf("-> O navio sobrepoe outro navio! ⚠️\n");
        }
        
    } else {
        printf("-> O navio ultrapassa os limites do tabuleiro! ⚠️\n");
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
