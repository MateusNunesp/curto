# Bot Jogador para Curto (Fodinha)

Este projeto contém uma implementação de jogador automatizado (bot) para o jogo **Curto** (também conhecido como **Fodinha**), compatível com a simulação de jogo [`@marciomoretto/curto`](https://github.com/marciomoretto/curto).

---

## Regras do Jogo

- **Objetivo:**
  [cite_start]Terminar com a menor penalidade possível, apostando corretamente e jogando cartas estrategicamente.

- **Manilha:**
  [cite_start]A cada rodada, uma carta é virada para definir a manilha. [cite_start]A manilha é a carta imediatamente superior à carta virada, seguindo a ordem dos valores.

- **Rodadas:**
    - [cite_start]Cada jogador recebe um conjunto de cartas no início da rodada.
    - [cite_start]Os jogadores fazem suas apostas, indicando quantas mãos acreditam que podem vencer.
    - [cite_start]Os jogadores jogam uma carta por vez, seguindo a ordem da mesa.
    - [cite_start]A carta mais forte, considerando o valor e a manilha, vence a mão.

- **Pontuação:**
    - [cite_start]Um jogador recebe penalidades se vencer mais ou menos rodadas do que apostou. [cite_start]A penalidade é calculada como `|Aposta - Vitórias|`.
    - [cite_start]Se vencer exatamente o número de rodadas apostadas, o jogador não recebe penalidades.

- **Fim do Jogo:**
  [cite_start]O jogo termina após 5 rodadas. [cite_start]O jogador com a menor penalidade total é declarado vencedor.

Para mais detalhes, consulte a documentação oficial da simulação de jogo.

---

## Funções do Arquivo

### Funções Auxiliares

Estas funções dão suporte à lógica principal do bot, realizando operações sobre o estado das cartas e ajudando na decisão das jogadas:

- **`void marcar_carta_como_jogada(int indice_carta)`**
  Marca uma carta como já utilizada nesta rodada.

- **`int contar_manilhas_na_mao()`**
  Conta quantas manilhas (não jogadas) o jogador possui na mão.

- **`int contar_A_na_mao()`**, **`int contar_2_na_mao()`**, **`int contar_3_na_mao()`**
  Funções específicas para contar cartas de alto valor na mão, usadas na estratégia de aposta.

- **`int menor_carta_jogador()`**
  Retorna o índice da menor carta comum (não manilha) na mão do jogador.

- **`int maior_carta_nao_manilha_jogador()`**
  Retorna o índice da maior carta comum (não manilha) na mão do jogador.

- **`int maior_carta_na_mesa(const Carta* mesa, int num_na_mesa)`**
  Analisa as cartas na mesa e retorna o índice daquela que está vencendo a mão no momento.

---

### Funções Principais do Jogador

Estas funções constituem a interface principal do bot e são chamadas diretamente pela simulação durante o jogo:

- **`const char* nome_jogador_16891637()`**
  Retorna o nome do jogador ("Mateus Nunes").

- **`void iniciar_16891637(int meu_id, int total_jogadores)`**
  [cite_start]Inicializa variáveis globais e prepara o jogador para o início da partida.

- **`void nova_rodada_16891637(int rodada, Carta carta_virada, Valor manilha, int n_cartas, Carta* minha_mao)`**
  [cite_start]Prepara o estado do jogador para uma nova rodada, atualizando a mão, a manilha e o número da rodada.

- **`int apostar_16891637(const int* apostas)`**
  [cite_start]Decide quantas mãos o bot pretende ganhar na rodada atual, de acordo com a estratégia de aposta.

- **`int jogar_16891637(const Carta* mesa, int num_na_mesa)`**
  [cite_start]Decide qual carta jogar na mão atual, de acordo com a estratégia de jogo.

---

## Estratégia do Bot

A lógica do bot foi desenhada para ser agressiva no início e adaptar-se conforme o jogo avança.

### 1. Aposta

A estratégia de aposta é variável e depende da rodada, refletindo o número de cartas na mão e a importância de cartas altas:
- **Rodada 1:** Aposta a soma total de Manilhas, Ases, 2 e 3 na mão.
- **Rodadas 2 e 3:** Aposta a soma de Manilhas, 2 e 3.
- **Rodadas 4 e 5:** Aposta a soma de Manilhas e 3, focando nas cartas mais decisivas.

### 2. Jogada

A lógica de jogo busca vencer a mão da forma mais eficiente possível e descartar cartas fracas quando a vitória é improvável:
1.  **Iniciar a mão:** Se for o primeiro a jogar, joga a maior carta comum (não manilha) para tentar estabelecer controle.
2.  **Tentar vencer com carta comum:** Se a carta mais forte na mesa não for manilha, o bot tenta jogar uma carta comum de valor superior para vencer a mão.
3.  **Tentar vencer com manilha:** Se não for possível vencer com uma carta comum, o bot verifica se possui uma manilha capaz de superar a carta mais forte da mesa e a joga.
4.  **Descartar:** Se a vitória não for possível com as opções acima, o bot joga a sua menor carta comum, guardando cartas mais fortes para outras mãos.
5.  **Último Recurso:** Se nenhuma das lógicas acima se aplicar (por exemplo, se só restarem manilhas fracas), o bot joga a primeira carta válida que encontrar.

---

## Licença

Este projeto é livre para fins acadêmicos e de estudo.
Consulte a simulação de jogo principal para detalhes de licença e uso.