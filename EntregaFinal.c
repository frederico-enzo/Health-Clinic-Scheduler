#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#define MAX_PROCEDIMENTOS 5
#define MAX_HORARIOS 9

char* procedimentoNomes[MAX_PROCEDIMENTOS] = {
    "Clinico Geral",
    "Fisioterapia",
    "Nutricao",
    "Psicologia",
    "Avaliacao Fisica"
};

float procedimentoValores[MAX_PROCEDIMENTOS] = {
    250.00,
    110.00,
    160.00,
    210.00,
    89.00
};

char agendas[MAX_PROCEDIMENTOS][MAX_HORARIOS][8]; // Agenda específica para cada procedimento

void exibirMenuPrincipal();
void exibirProcedimentos();
void agendarHorario();
void exibirAgenda(int procedimentoIndex);
void inicializarAgenda();

int main() {
    int opcao;

    // Inicializar agendas de todos os procedimentos
    inicializarAgenda();

    while (1) {
        exibirMenuPrincipal();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirProcedimentos();
                break;
            case 2:
                agendarHorario();
                break;
            case 3:
                printf("Funcionalidade em desenvolvimento.\n");
                break;
            case 5:
                printf("Funcionalidade em desenvolvimento.\n");
                break;
            case 6:
                printf("Funcionalidade em desenvolvimento.\n");
                break;
            case 7:
                printf("Saindo...\n");
                exit(0);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}

void exibirMenuPrincipal() {
    system(CLEAR);
    printf("\n========================================\n");
    printf("              Menu Principal            \n");
    printf("========================================\n");
    printf("1. Procedimento de saude\n");
    printf("2. Agendar Horario\n");
    printf("3. Pagamento\n");
    printf("5. Relatorio de Procedimentos Contratados\n");
    printf("6. Faturamento Diario\n");
    printf("7. Sair\n");
    printf("========================================\n");
}

void exibirProcedimentos() {
    system(CLEAR);
    printf("\n========================================\n");
    printf("         Procedimentos de saude         \n");
    printf("========================================\n");
    printf("Item (codigo)       Nome do Item                  Valor\n");
    for (int i = 0; i < MAX_PROCEDIMENTOS; i++) {
        printf("%d                   %-25s R$ %.2f\n", i + 1, procedimentoNomes[i], procedimentoValores[i]);
    }
    printf("0. Voltar ao Menu Principal\n");
    printf("========================================\n");

    int opcao;
    printf("Escolha um procedimento: ");
    scanf("%d", &opcao);

    if (opcao == 0) {
        return; // Voltar ao menu principal
    } else if (opcao >= 1 && opcao <= MAX_PROCEDIMENTOS) {
        agendarHorario();
    } else {
        printf("Opcao invalida. Tente novamente.\n");
        exibirProcedimentos();
    }
}

void agendarHorario() {
    int opcao;

    do {
        system(CLEAR);
        printf("\n========================================\n");
        printf("         Procedimentos de saude         \n");
        printf("========================================\n");
        printf("Item (codigo)       Nome do Item                  Valor\n");
        for (int i = 0; i < MAX_PROCEDIMENTOS; i++) {
            printf("%d                   %-25s R$ %.2f\n", i + 1, procedimentoNomes[i], procedimentoValores[i]);
        }
        printf("0. Voltar ao Menu Principal\n");
        printf("========================================\n");

        printf("Escolha um procedimento para visualizar a agenda (ou 0 para voltar): ");
        scanf("%d", &opcao);

        if (opcao == 0) {
            return; // Voltar ao menu principal
        } else if (opcao >= 1 && opcao <= MAX_PROCEDIMENTOS) {
            exibirAgenda(opcao - 1);
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar(); // Aguardar a entrada do usuário para continuar
        getchar(); // Aguardar o Enter
    } while (1);
}

void exibirAgenda(int procedimentoIndex) {
    printf("\n========================================\n");
    printf("               Agenda %s              \n", procedimentoNomes[procedimentoIndex]);
    printf("========================================\n");
    printf("ID    Horario   Status\n");
    for (int i = 0; i < MAX_HORARIOS; i++) {
        printf("%02d    %02d:00     %s\n", i + 1, i + 9, agendas[procedimentoIndex][i]);
    }
    printf("========================================\n");
}


void inicializarAgenda() {
    for (int i = 0; i < MAX_PROCEDIMENTOS; i++) {
        for (int j = 0; j < MAX_HORARIOS; j++) {
            snprintf(agendas[i][j], 8, "L (livre)");
        }
    }
}
