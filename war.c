#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[30]; // Nome do território
    char cor[10];  // Cor do exército que domina o território
    int tropas;    // Quantidade de tropas presentes
} Territorio;

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Protótipo das funções
void inicializarTerritorios(Territorio *Territ);
void exibirMapa(Territorio *Territ);
void faseDeAtaque(Territorio *Territ);
void simularAtaque(Territorio *atacante, Territorio *defensor);

int main()
{
    // --- Declaração do vetor de structs ---
    // Vetor com capacidade para armazenar 5 territórios.
    Territorio Territ[5];

    printf("==================================\n");
    printf("WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("==================================\n");

    inicializarTerritorios(Territ);
    exibirMapa(Territ);

    return 0;
}

// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
// 1. Configuração Inicial (Setup):
// - Define o locale para português.
// - Inicializa a semente para geração de números aleatórios com base no tempo atual.
// - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
// - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
// - Define a cor do jogador e sorteia sua missão secreta.

// 2. Laço Principal do Jogo (Game Loop):
// - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
// - A cada iteração, exibe o mapa, a missão e o menu de ações.
// - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
//   - Opção 1: Inicia a fase de ataque.
//   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
//   - Opção 0: Encerra o jogo.
// - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

// 3. Limpeza:
// - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

void inicializarTerritorios(Territorio *Territ)
{
    // --- Entrada dos dados ---
    // Laço for para cadastrar os 5 territórios.
    for (int i = 0; i < 5; i++)
    {
        printf("\n--> Cadastrando Territorio %d:\n", i + 1);
        // Leitura do nome do território
        printf("Nome do território: ");
        scanf("%29s", Territ[i].nome); // lê no máximo 29 caracteres + '\0'

        // Leitura da cor do exército
        printf("Cor do exército (ex: Azul, Verde...): ");
        scanf("%s", Territ[i].cor);

        // Leitura da quantidade de tropas
        printf("Número de tropas: ");
        scanf("%d", &Territ[i].tropas);
    }
}
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

void exibirMapa(Territorio *Territ)
{
    // --- Exibição dos dados ---
    // Após o cadastro, percorremos o vetor e mostramos os dados.
    printf("\n=====================================\n");
    printf("   MAPA DO MUNDO ESTADO ATUAL\n");
    printf("=====================================\n");

    for (int i = 0; i < 5; i++)
    {
        printf("%d. ", i + 1);
        printf("%s ", Territ[i].nome);
        printf("(Exército: %s, ", Territ[i].cor);
        printf("Tropas: %d)\n", Territ[i].tropas);
    }

    faseDeAtaque(Territ);
}
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

void faseDeAtaque(Territorio *Territ)
{
    int ataque;
    int defensor;

    printf("\n--- FASE DE ATAQUE ---\n");

    printf("Escolha o território atacante ( 1 a 5, ou 0 para sair): ");
    scanf("%d", &ataque);

    if (ataque == 0)
    {
        printf("Obrigado! até mais...");
        return;
    }

    printf("Escolha o território defensor ( 1 a 5, ou 0 para sair): ");
    scanf("%d", &defensor);

    simularAtaque(&Territ[ataque - 1], &Territ[defensor - 1]);

    exibirMapa(Territ);
}
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

void simularAtaque(Territorio *atacante, Territorio *defensor)
{
    if (strcmp(atacante->cor, defensor->cor) == 0)
    {
        printf("Você não pode atacar um território da mesma cor!\n");
        return;
    }
    if (atacante->tropas < 1)
    {
        printf("O território atacante precisa ter pelo menos 1 tropas!\n");
        return;
    }

    // Rolagem de dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nRolagem de dados:\n");
    printf("Atacante (%s) rolou os dados e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) rolou os dados e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor)
    {
        defensor->tropas--;
        atacante->tropas++;
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        if (defensor->tropas == 0)
        {
            strcpy(defensor->cor, atacante->cor);
            printf("CONQUISTA! O território %s foi dominado pelo Excercito %s!", defensor->nome, defensor->cor);
        }
    }
    else
    {
        defensor->tropas++;
        atacante->tropas--;
        printf("VITORIA DO DEFENSOR! O atacante perdeu 1 tropa.\n");
        if (atacante->tropas == 0)
        {
            strcpy(atacante->cor, defensor->cor);
            printf("CONQUISTA! O território %s foi dominado pelo Excercito %s!", atacante->nome, atacante->cor);
        }
    }
}
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
