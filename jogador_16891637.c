#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../carta.h" 
#include "jogador_16891637.h" 

// --- Variáveis Globais ---
static int id_global;
static int num_jogadores_global;
static int num_cartas_mao_global;
static Carta mao_global[6]; 
static Valor manilha_global;
static int cartas_jogadas[6] = {0};
static int numero_rodada_atual;

// --- Funções Auxiliares ---

static void marcar_carta_como_jogada(int indice_carta) {
    if (indice_carta >= 0 && indice_carta < num_cartas_mao_global) {
        cartas_jogadas[indice_carta] = 1;
    }
}

static int contar_manilhas_na_mao() {
    int contador = 0;
    for (int i = 0; i < num_cartas_mao_global; i++) {
        if (cartas_jogadas[i] == 0 && mao_global[i].valor == manilha_global) {
            contador++;
        }
    }
    return contador;
}

// Funções para contar cartas específicas
static int contar_A_na_mao() {
    int contador = 0;
    for (int i = 0; i < num_cartas_mao_global; i++) {
        if (cartas_jogadas[i] == 0 && mao_global[i].valor == AS) {
            contador++;
        }
    }
    return contador;
}

static int contar_2_na_mao() {
    int contador = 0;
    for (int i = 0; i < num_cartas_mao_global; i++) {
        if (cartas_jogadas[i] == 0 && mao_global[i].valor == DOIS) {
            contador++;
        }
    }
    return contador;
}

static int contar_3_na_mao() {
    int contador = 0;
    for (int i = 0; i < num_cartas_mao_global; i++) {
        if (cartas_jogadas[i] == 0 && mao_global[i].valor == TRES) {
            contador++;
        }
    }
    return contador;
}

static int menor_carta_jogador() {
    int idx = -1;
    for (int i = 0; i < num_cartas_mao_global; i++) {
        if (cartas_jogadas[i]) continue;
        if (mao_global[i].valor == manilha_global) continue;
        if (idx == -1 || mao_global[i].valor < mao_global[idx].valor) {
            idx = i;
        }
    }
    return idx;
}

static int maior_carta_nao_manilha_jogador() {
    int idx = -1;
    for (int i = 0; i < num_cartas_mao_global; i++) {
        if (cartas_jogadas[i]) continue;
        if (mao_global[i].valor == manilha_global) continue;
        if (idx == -1 || mao_global[i].valor > mao_global[idx].valor) {
            idx = i;
        }
    }
    return idx;
}

// Retorna o índice da carta mais forte na mesa.
static int maior_carta_na_mesa(const Carta* mesa, int num_na_mesa) {
    if (num_na_mesa == 0) return -1;
    
    int idx_vencedor = 0;
    for (int i = 1; i < num_na_mesa; i++) {
        // Lógica de comparação de cartas (manilha vs não-manilha)
        int a_eh_manilha = (mesa[i].valor == manilha_global);
        int b_eh_manilha = (mesa[idx_vencedor].valor == manilha_global);

        if (a_eh_manilha && !b_eh_manilha) {
            idx_vencedor = i;
        } else if (a_eh_manilha && b_eh_manilha) {
            // Desempate de manilhas por naipe 
            if (mesa[i].naipe > mesa[idx_vencedor].naipe) {
                idx_vencedor = i;
            }
        } else if (!a_eh_manilha && !b_eh_manilha) {
            if (mesa[i].valor > mesa[idx_vencedor].valor) {
                idx_vencedor = i;
            }
        }
    }
    return idx_vencedor;
}

// --- Implementação da Interface do Jogador ---

const char* nome_jogador_16891637() {
    return "Mateus Nunes";
}

void iniciar_jogador_16891637(int meu_id, int total_jogadores) {
    id_global = meu_id;
    num_jogadores_global = total_jogadores;
}

void nova_rodada_jogador_16891637(int rodada, Carta carta_virada, Valor manilha, int n_cartas, Carta* minha_mao) {
    num_cartas_mao_global = n_cartas;
    numero_rodada_atual = rodada;
    manilha_global = manilha; 

    for (int i = 0; i < num_cartas_mao_global; i++) {
        mao_global[i] = minha_mao[i];
        cartas_jogadas[i] = 0;
    }
}

int apostar_jogador_16891637(const int* apostas) {
    if (numero_rodada_atual == 1) {
        int contador_aposta = 0;
        contador_aposta += contar_A_na_mao();
        contador_aposta += contar_manilhas_na_mao();
        contador_aposta += contar_2_na_mao();
        contador_aposta += contar_3_na_mao();
        return contador_aposta;
    }

    if (numero_rodada_atual == 2) {
        int contador_aposta = 0;
        contador_aposta += contar_manilhas_na_mao();
        contador_aposta += contar_2_na_mao();
        contador_aposta += contar_3_na_mao();
        return contador_aposta;
    }

    if (numero_rodada_atual == 3) {
        int contador_aposta = 0;
        contador_aposta += contar_2_na_mao();
        contador_aposta += contar_manilhas_na_mao();
        contador_aposta += contar_3_na_mao();
        return contador_aposta;
    }

    if (numero_rodada_atual == 4) {
        int contador_aposta = 0;
        contador_aposta += contar_manilhas_na_mao();
        contador_aposta += contar_3_na_mao();
        return contador_aposta;
    }
    
    if (numero_rodada_atual == 5) {
        int contador_aposta = 0;
        contador_aposta += contar_manilhas_na_mao();
        contador_aposta += contar_3_na_mao();
        return contador_aposta;
    }
    
    return 0;
}

int jogar_jogador_16891637(const Carta* mesa, int num_na_mesa) {
    int idx_maior_na_mesa = maior_carta_na_mesa(mesa, num_na_mesa);
    
    // Se a mesa estiver vazia, joga a menor carta.
    if (idx_maior_na_mesa == -1) {
        int idx_menor_na_mao1 = menor_carta_jogador();
        if (idx_menor_na_mao1 != -1) {
            marcar_carta_como_jogada(idx_menor_na_mao1);
            return idx_menor_na_mao1;
        }
    } else { // Se a mesa não está vazia
        Carta carta_mais_forte_mesa = mesa[idx_maior_na_mesa];
        
        // Tenta vencer com uma carta não-manilha mais forte, se a da mesa não for manilha
        if (carta_mais_forte_mesa.valor != manilha_global) {
            int idx_maior_na_mao = maior_carta_nao_manilha_jogador();
            if (idx_maior_na_mao != -1 && mao_global[idx_maior_na_mao].valor > carta_mais_forte_mesa.valor) {
                marcar_carta_como_jogada(idx_maior_na_mao);
                return idx_maior_na_mao;
            }
        }
        
        // Se não pode vencer com não-manilha, tenta vencer com uma manilha
        if (contar_manilhas_na_mao() > 0) {
            for (int i = 0; i < num_cartas_mao_global; i++) {
                if (cartas_jogadas[i] == 0 && mao_global[i].valor == manilha_global) {
                     // Lógica para jogar a manilha apenas se ela for mais forte que a da mesa
                     if (carta_mais_forte_mesa.valor != manilha_global || mao_global[i].naipe > carta_mais_forte_mesa.naipe) {
                        marcar_carta_como_jogada(i);
                        return i;
                     }
                }
            }
        }
    }
    
    // Se não pode vencer, joga a menor carta disponível.
    int idx_menor_na_mao = menor_carta_jogador();
    if (idx_menor_na_mao != -1) {
        marcar_carta_como_jogada(idx_menor_na_mao);
        return idx_menor_na_mao;
    }

    // Se só sobraram manilhas (e não pode vencer com elas) ou em último caso, joga a primeira válida.
    for (int i = 0; i < num_cartas_mao_global; i++) {
        if (cartas_jogadas[i] == 0) {
            marcar_carta_como_jogada(i);
            return i;
        }
    }

    return -1; // Erro
}
