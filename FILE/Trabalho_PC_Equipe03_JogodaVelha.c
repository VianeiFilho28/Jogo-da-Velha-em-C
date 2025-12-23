/*
TRABALHO FINAL - PROGRAMAÇÃO COMPUTACIONAL
EQUIPE 03 - JOGO DA VELHA
FRANCISCO JONATHAN LIMA PAULA -581253
GABRIEL FARIAS MAGALHAES - 581758
JOSE VIANEI CASTRO E SILVA FILHO - 580381
*/

#include <stdio.h>    /* Inclui a biblioteca padrão de entrada e saída (para printf, scanf, etc.) */
#include <stdlib.h>   /* Inclui a biblioteca padrão (para funções como system, exit, etc.) */
#include <string.h>   /* Inclui a biblioteca de manipulação de strings (para funções como strlen, strcspn, etc.) */
#include <locale.h>   /* Inclui a biblioteca para configurações de localização (para setlocale) */
#include <ctype.h>    /* Inclui a biblioteca para manipulação de caracteres (para toupper) */

/* Declaração de variáveis globais */

char tabuleiro[3][3];         /* Matriz que representa o tabuleiro do jogo da velha (3x3) */
char jogador1[50], jogador2[50]; /* Arrays para armazenar os nomes dos jogadores */
char simbolo1, simbolo2;     /* Variáveis para armazenar os símbolos ('X' ou 'O') de cada jogador */

/* Função para limpar o buffer de entrada de forma portátil */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Função para inicializar ou "limpar" o tabuleiro com números de 1 a 9 */
void limparTabuleiro() {
    int pos = '1'; /* 'pos' é inicializado com o caractere '1' para preencher as células */
    int i, j;      /* Variáveis de loop declaradas no início do bloco */
    for(i = 0; i < 3; i++) { /* Percorre as linhas do tabuleiro */
        for(j = 0; j < 3; j++) { /* Percorre as colunas do tabuleiro */
            tabuleiro[i][j] = pos++; /* Atribui o caractere da posição e incrementa 'pos' para o próximo número */
        }
    }
}

/* Função para imprimir o estado atual do tabuleiro na tela */
void imprimirTabuleiro() {
    int i, j; /* Variáveis de loop declaradas no início do bloco */
    printf("\n"); /* Adiciona uma linha em branco para melhor formatação */
    for(i = 0; i < 3; i++) { /* Percorre as linhas */
        for(j = 0; j < 3; j++) { /* Percorre as colunas */
            printf("%c", tabuleiro[i][j]); /* Imprime o conteúdo da célula atual */
            if(j < 2) printf("|"); /* Imprime um separador vertical entre as colunas, exceto na última */
        }
        printf("\n"); /* Pula para a próxima linha após imprimir todas as colunas de uma linha */
    }
    printf("\n"); /* Adiciona uma linha em branco para melhor formatação */
}

/* Função para verificar se um jogador venceu */
/* Retorna 1 se o símbolo fornecido venceu, 0 caso contrário */
int verificarVencedor(char simbolo) {
    int i; /* Variável de loop declarada no início do bloco */
    /* Verifica linhas */
    for(i = 0; i < 3; i++) {
        if(tabuleiro[i][0] == simbolo && tabuleiro[i][1] == simbolo && tabuleiro[i][2] == simbolo) {
            return 1; /* Retorna 1 se uma linha completa tem o mesmo símbolo */
        }
    }

    /* Verifica colunas */
    for(i = 0; i < 3; i++) {
        if(tabuleiro[0][i] == simbolo && tabuleiro[1][i] == simbolo && tabuleiro[2][i] == simbolo) {
            return 1; /* Retorna 1 se uma coluna completa tem o mesmo símbolo */
        }
    }

    /* Verifica diagonal principal (superior esquerda para inferior direita) */
    if(tabuleiro[0][0] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][2] == simbolo) {
        return 1; /* Retorna 1 se a diagonal principal tem o mesmo símbolo */
    }

    /* Verifica diagonal secundária (superior direita para inferior esquerda) */
    if(tabuleiro[0][2] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][0] == simbolo) {
        return 1; /* Retorna 1 se a diagonal secundária tem o mesmo símbolo */
    }

    return 0; /* Retorna 0 se nenhum vencedor for encontrado */
}

/* Função para verificar se uma posição no tabuleiro está disponível */
/* Retorna 1 se a posição estiver disponível, 0 caso contrário */
int espacoDisponivel(int posicao) {
    /* Converte a posição (1-9) para coordenadas de linha e coluna (0-2) */
    int linha = (posicao - 1) / 3;
    int coluna = (posicao - 1) % 3;
    /* Verifica se a célula na posição especificada não contém o símbolo de nenhum dos jogadores */
    return tabuleiro[linha][coluna] != simbolo1 && tabuleiro[linha][coluna] != simbolo2;
}

/* Função para marcar uma posição no tabuleiro com o símbolo do jogador */
void marcar(int posicao, char simbolo) {
    /* Converte a posição (1-9) para coordenadas de linha e coluna (0-2) */
    int linha = (posicao - 1) / 3;
    int coluna = (posicao - 1) % 3;
    tabuleiro[linha][coluna] = simbolo; /* Atribui o símbolo à célula do tabuleiro */
}

/* Função para verificar se o jogo está completo (todas as células preenchidas) */
/* Retorna 1 se o jogo estiver completo, 0 caso contrário */
int jogoCompleto() {
    int i, j; /* Variáveis de loop declaradas no início do bloco */
    for(i = 0; i < 3; i++) { /* Percorre as linhas */
        for(j = 0; j < 3; j++) { /* Percorre as colunas */
            /* Se encontrar uma célula que não foi preenchida por nenhum dos símbolos, o jogo não está completo */
            if(tabuleiro[i][j] != simbolo1 && tabuleiro[i][j] != simbolo2) {
                return 0; /* Retorna 0 (jogo não completo) */
            }
        }
    }
    return 1; /* Retorna 1 (jogo completo - deu velha) */
}

/* Função principal do programa */
int main() {

    int opcao, vez, posicao; /* Variáveis para opções, controle de turno e posição jogada */
    int erro = 0; /* Variável para controlar erros na entrada */
    
    setlocale(LC_ALL, "ptb"); /* Define a localização para português do Brasil (para acentuação, etc.) */
    
    /* Solicita e lê o nome do Jogador 1 */
    printf("Digite o nome do Jogador 1: ");
    fgets(jogador1, sizeof(jogador1), stdin); /* Lê a linha completa, incluindo o '\n' */
    jogador1[strcspn(jogador1, "\n")] = '\0'; /* Remove o '\n' do final da string */

    /* Solicita e lê o nome do Jogador 2 */
    printf("Digite o nome do Jogador 2: ");
    fgets(jogador2, sizeof(jogador2), stdin); /* Lê a linha completa, incluindo o '\n' */
    jogador2[strcspn(jogador2, "\n")] = '\0'; /* Remove o '\n' do final da string */

    /* Loop para garantir que os símbolos escolhidos sejam 'X' ou 'O' */
    do{
        printf("%s, escolha seu símbolo (ex: X): ", jogador1);
        scanf(" %c", &simbolo1); /* Lê o símbolo do Jogador 1 (o espaço antes de %c consome o '\n' pendente) */
        simbolo1 = toupper(simbolo1); /* Converte o símbolo para maiúscula */
        if(simbolo1 != 'X' && simbolo1 != 'O'){ /* Verifica se o símbolo é inválido */
            printf("Símbolo inválido! Escolha entre X ou O.\n");
            limparBufferEntrada(); /* Limpa o buffer após leitura de caractere inválido */
        } else{
            /* Atribui o símbolo oposto para o Jogador 2 */
            if(simbolo1 == 'X'){
                simbolo2 = 'O';
                printf("%s, seu símbolo será: O\n", jogador2); /* Informa o símbolo do Jogador 2 */
            } else{
                simbolo2 = 'X';
                printf("%s, seu símbolo será: X\n", jogador2); /* Informa o símbolo do Jogador 2 */
            }   
        }
        
    } while(simbolo1 != 'X' && simbolo1 != 'O'); /* Continua o loop até um símbolo válido ser escolhido */
    
    limparBufferEntrada(); /* Limpa o buffer após a leitura do símbolo, antes de iniciar o jogo */

    /* Loop principal do jogo, permite jogar múltiplas rodadas */
    do {
        limparTabuleiro(); /* Limpa o tabuleiro para uma nova rodada */
        vez = 0;           /* Inicializa o contador de turnos (0 para Jogador 1, 1 para Jogador 2, etc.) */

        /* Loop de uma única rodada do jogo */
        while(1) {
            imprimirTabuleiro(); /* Imprime o estado atual do tabuleiro */
            /* Informa de quem é a vez de jogar */
            printf("Informe a próxima posição %s: ", (vez % 2 == 0) ? jogador1 : jogador2);
            /* Verifica se a entrada da posição é um número válido */
            if(scanf("%d", &posicao) != 1){
                printf("Posição inválida. Tente novamente.\n");
                limparBufferEntrada(); /* Limpa o buffer de entrada para evitar loops infinitos com entradas inválidas */
                continue;   /* Volta para o início do loop */
            }

            /* Verifica se a posição é válida (entre 1 e 9) e se está disponível */
            if(posicao < 1 || posicao > 9 || !espacoDisponivel(posicao)) {
                printf("Posição inválida ou ocupada. Tente novamente.\n");
                limparBufferEntrada(); /* Limpa o buffer após uma posição inválida */
                continue; /* Volta para o início do loop */
            }
            limparBufferEntrada(); /* Limpa o buffer após a leitura da posição válida */

            /* Marca a posição escolhida com o símbolo do jogador atual */
            marcar(posicao, (vez % 2 == 0) ? simbolo1 : simbolo2);

            /* Verifica se o jogador atual venceu */
            if(verificarVencedor((vez % 2 == 0) ? simbolo1 : simbolo2)) {
                imprimirTabuleiro(); /* Imprime o tabuleiro final */
                printf("Parabéns, %s venceu!\n", (vez % 2 == 0) ? jogador1 : jogador2); /* Anuncia o vencedor */
                break; /* Sai do loop da rodada atual */
            }

            /* Verifica se o jogo está completo (deu velha) */
            if(jogoCompleto()) {
                imprimirTabuleiro(); /* Imprime o tabuleiro final */
                printf("Deu velha! Ninguém venceu.\n"); /* Anuncia o empate */
                break; /* Sai do loop da rodada atual */
            }

            vez++; /* Passa a vez para o próximo jogador */
        }
        
        /* Loop para perguntar se deseja jogar novamente e validar a entrada */
        do{
            erro = 0;
            printf("Deseja jogar novamente?\n1. S\n2. N\nDigite o número correspondente a opção: ");
            /* Verifica se a entrada da opção é um número válido */
            if(scanf("%d", &opcao) != 1){
                printf("Valor inválido.\n");
                limparBufferEntrada(); /* Limpa o buffer de entrada */
                erro = 1; /* Indica que houve um erro */
                continue;
            }   
            /* Verifica se a opção está entre 1 e 2 */
            if(opcao != 1 && opcao != 2){
                printf("Valor Inválido.\n");
                erro = 1; /* Indica que houve um erro */
            }
            limparBufferEntrada(); /* Limpa o buffer após a leitura da opção */
        } while(erro); /* Continua o loop enquanto houver erro na entrada */
        
    } while(opcao == 1); /* Continua o loop principal do jogo se a opção for '1' (Sim) */

    printf("Obrigado por jogar!\n"); /* Mensagem de despedida */
    return 0; /* Retorna 0 para indicar que o programa foi executado com sucesso */
}
