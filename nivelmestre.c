#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5
#define MAX_MISSAO 2

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

typedef enum {
    MISSAO_CONQUISTAR_TRES,
    MISSAO_DESTRUIR_VERDE
} TipoMissao;

typedef struct {
    TipoMissao tipo;
    int conquistados;
} Missao;

// ---------- Funções ----------

void inicializarTerritorios(Territorio *Territorios);
void mostrarMapa(const Territorio *Territorios);
void menuPrincipal(Territorio *territorios, Missao *missao);
void atacar(Territorio *territorios, Missao *missao);
void verificarMissao(const Territorio *Territorios, const Missao *missao);
void sortearMissao(Missao *missao);
int contarTerritorios(const Territorio *territorios, const char *cor);
void exibirDescricaoMissao(const Missao *missao);

// ---------- Função Principal ----------

int main() {
    srand(time (NULL));

    Territorio *territorios = (Territorio *)calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (!territorios) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    Missao missao;
    inicializarTerritorios(territorios);
    sortearMissao(&missao);
    exibirDescricaoMissao(&missao);
    menuPrincipal(territorios, &missao);

    printf("\nMapa final:\n");
    mostrarMapa(territorios);
    free(territorios);

    return 0;
}

// ---------- Implementações ----------

void inicializarTerritorios(Territorio *territorios) {
    printf("====================================\n");
    printf(" WAR ESTRUTURADO - NIVEL MESTRE \n");
    printf("====================================\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", territorios[i].nome);
        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        printf("\n");
    }
}

void mostrarMapa(const Territorio *territorios) {
    printf("======================================\n");
    printf("   MAPA DO MUNDO - ESTADO ATUAL       \n");
    printf("======================================\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%d. %s (Exército %s, Tropas: %d)\n",
               i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

void sortearMissao(Missao *missao) {
    missao->tipo = rand() % MAX_MISSAO;
    missao->conquistados = 0;
}

void exibirDescricaoMissao(const Missao *missao) {
    printf("======================================\n");
    printf("          MISSÃO ATRIBUIDA            \n");
    printf("======================================\n");
    switch (missao->tipo) {
        case MISSAO_CONQUISTAR_TRES:
            printf("Missão: Conquistar 3 territórios!\n");
            break;
        case MISSAO_DESTRUIR_VERDE:
            printf("Missão: Destruir todos os territórios do exército Verde!\n");
            break;
    }
}

void menuPrincipal(Territorio *territorios, Missao *missao) {
    int opcao;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atacar(territorios, missao);
                break;
            case 2:
                verificarMissao(territorios, missao);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void atacar(Territorio *territorios, Missao *missao) {
    int atacante, defensor;
    mostrarMapa(territorios);

    printf("Digite o número do território ATACANTE (1 a 5, 0 para cancelar): ");
    scanf("%d", &atacante);
    if (atacante == 0) return;

    printf("Digite o número do território DEFENSOR (1 a 5): ");
    scanf("%d", &defensor);

    if (atacante < 1 || atacante > NUM_TERRITORIOS ||
        defensor < 1 || defensor > NUM_TERRITORIOS ||
        atacante == defensor) {
        printf("Entrada inválida!\n");
        return;
    }

    Territorio *att = &territorios[atacante - 1];
    Territorio *def = &territorios[defensor - 1];

    if (att->tropas <= 1) {
        printf("O território atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    int dado_ataque = rand() % 6 + 1;
    int dado_defesa = rand() % 6 + 1;

    printf("\n%s (ATACANTE) tirou: %d\n", att->nome, dado_ataque);
    printf("%s (DEFENSOR) tirou: %d\n", def->nome, dado_defesa);

    if (dado_ataque >= dado_defesa) {
        def->tropas--;
        printf("O defensor perdeu 1 tropa!\n");

        if (def->tropas <= 0) {
            printf("%s foi conquistado por %s!\n", def->nome, att->nome);
            strcpy(def->cor, att->cor);
            def->tropas = 1;
            att->tropas--;

            if (missao->tipo == MISSAO_CONQUISTAR_TRES)
                missao->conquistados++;
        }
    } else {
        att->tropas--;
        printf("O atacante perdeu 1 tropa!\n");
    }
}

int contarTerritorios(const Territorio *territorios, const char *cor) {
    int count = 0;
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(territorios[i].cor, cor) == 0) {
            count++;
        }
    }
    return count;
}

void verificarMissao(const Territorio *territorios, const Missao *missao) {
    int vitoria = 0;

    switch (missao->tipo) {
        case MISSAO_CONQUISTAR_TRES:
            printf("Territórios conquistados: %d/3\n", missao->conquistados);
            if (missao->conquistados >= 3) vitoria = 1;
            break;
        case MISSAO_DESTRUIR_VERDE:
            if (contarTerritorios(territorios, "Verde") == 0) {
                vitoria = 1;
                printf("Todos os territórios verdes foram destruídos!\n");
            } else {
                printf("Ainda existem territórios do exército Verde.\n");
            }
            break;
    }

    if (vitoria) {
        printf("\n🎉 PARABÉNS! Você concluiu sua missão! 🎉\n");
        exit(0);
    }
}
