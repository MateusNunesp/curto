#ifndef JOGADOR_16891637_H
#define JOGADOR_16891637_H
#include "../carta.h" 
const char* nome_jogador_16891637();
void iniciar_jogador_16891637(int meu_id, int total_jogadores);
void nova_rodada_jogador_16891637(int rodada, Carta carta_virada, Valor manilha, int n_cartas, Carta* minha_mao);
int apostar_jogador_16891637(const int* apostas);
int jogar_jogador_16891637(const Carta* mesa, int num_na_mesa);
#endif 
