#include <stdio.h>
#include <string.h>

#define NUM_TERRITORIOS 5

//Definindo a struct do territorio
//Aramazenando as informações de um territorio: nome, cor do exercito é quantidade de tropas
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
}Territorio;

int main() {
    printf("====================================\n");
    printf(" WAR ESTRUTURADO - NIVEL NOVATO \n");
    printf("====================================\n");

    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");

    Territorio territorios[NUM_TERRITORIOS]; //Vetor que armazena 5 territorios

    //Loop para entrada dos dados dos territorios
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);

        //Solicita e lê o nome do territorio
        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);

        //Solicita e lê a cor do exercito
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);

        //Solicita e lê o numero de tropas
        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    //Exibição dos dados cadastrados
    printf("====================================\n");
    printf(" MAPA DO MUNDO - ESTADO ATUAL \n");
    printf("====================================\n");

    for(int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("-Nome: %s\n", territorios[i].nome);
        printf("-Cor do exercito: %s\n", territorios[i].cor);
        printf("-Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("-------------------------\n");
    }

    return 0;

}