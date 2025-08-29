#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TERRITORIOS 5

//Estrutura do territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
}Territorio;

//Função para cadastrar os territórios com entrada do usuario
void cadastrarTerritorios(Territorio *territorios) {
    printf("====================================\n");
    printf(" WAR ESTRUTURADO - NIVEL AVENTUREIRO \n");
    printf("====================================\n");

    for(int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);

        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }
}

//Função para exibir o mapa
void mostrarMapa(Territorio *territorios) {
    printf("======================================\n");
    printf("   MAPA DO MUNDO - ESTADO ATUAL       \n");
    printf("======================================\n");

    for (int i = 0; i <  NUM_TERRITORIOS; i++) {
        printf("%d. %s (Exército %s, Tropas: %d)\n",
        i + 1,
        territorios[i].nome,
        territorios[i].cor,
        territorios[i].tropas);
    }
    printf("---------------------\n");
}

//Função para simular uma batalha entre territorios
void simularBatalha(Territorio *territorios) {
    int atacante, defensor;

    while(1) {
        mostrarMapa(territorios);

        printf("\nDigite o número do território ATACANTE (1 a 5, 0 para sair): ");
        scanf("%d", &atacante);
        if (atacante == 0) break;

        printf("Digite o número do territorio DEFENSOR (1 a 5): ");
        scanf("%d", &defensor);

        //Validação
        if (atacante < 1 || atacante > NUM_TERRITORIOS ||
            defensor < 1 || defensor > NUM_TERRITORIOS ||
            atacante == defensor) {
                printf("Entrada invalida! Tente novamente.\n\n");
                continue;
            }

            Territorio *att = &territorios[atacante - 1];
            Territorio *def = &territorios[defensor - 1];

            if (att->tropas <= 1) {
                printf(") territorio atacante precisa de mais uma tropa para atacar!\n\n");
                continue;
            }

            //Soteio dos dados(1 a 6)
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
            }
        } else {
            att->tropas--;
            printf("O atacante perdeu 1 tropa!\n");
        }

        printf("\n------------------------------\n");
    }
}

    int main() {
    srand(time(NULL)); // Inicializa números aleatórios

    // Aloca memória dinamicamente para os territórios
    Territorio *territorios = (Territorio *)calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(territorios);
    simularBatalha(territorios);

    printf("Fim do jogo. Mapa final:\n");
    mostrarMapa(territorios);

    free(territorios); // Libera memória

    return 0;
}

