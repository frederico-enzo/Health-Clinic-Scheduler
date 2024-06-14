#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições para limpar a tela, dependendo do sistema operacional
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// Definindo constantes para o número máximo de procedimentos e horários
#define MAX_PROCEDIMENTOS 5
#define MAX_HORARIOS 9

// Nomes dos procedimentos
char* procedimentoNomes[MAX_PROCEDIMENTOS] = {
    "Clinico Geral",
    "Fisioterapia",
    "Nutricao",
    "Psicologia",
    "Avaliacao Fisica"
};

// Valores dos procedimentos
float procedimentoValores[MAX_PROCEDIMENTOS] = {
    250.00,
    110.00,
    160.00,
    210.00,
    89.00
};

// Matrizes para armazenar os horários das agendas dos procedimentos
char agendas[MAX_PROCEDIMENTOS][MAX_HORARIOS][12]; // Agenda específica para cada procedimento

// Estrutura para armazenar um procedimento agendado
typedef struct {
    int procedimentoIndex;
    int horario;
} Agendamento;

// Lista de agendamentos
Agendamento agendamentos[MAX_PROCEDIMENTOS * MAX_HORARIOS];
int totalAgendamentos = 0;

// Declaração de funções
void exibirMenuPrincipal();
void exibirProcedimentos();
void agendarHorario(int procedimentoIndex);
void visualizarAgendas();
void exibirAgenda(int procedimentoIndex);
void inicializarAgenda();
void realizarPagamento();
float calcularTotal(float* totalPorProcedimento);
void exibirConsolidadoPagamento(float* totalPorProcedimento, float total, float desconto);
void removerAgendamento(int procedimentoIndex, int horario);

int main() {
    int opcao;

    // Inicializar as agendas de todos os procedimentos
    inicializarAgenda();

    // Loop principal 
    while (1) {
        exibirMenuPrincipal(); // Exibe o menu principal
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirProcedimentos(); // Exibe os procedimentos disponíveis
                break;
            case 2:
                visualizarAgendas(); // Permite visualizar as agendas dos procedimentos
                break;
            case 3:
                realizarPagamento(); // Realiza o pagamento
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
                printf("Opcao invalida. Tente novamente.\n"); // Mensagem de erro para opção inválida
        }
    }

    return 0;
}

// Função para exibir o menu principal
void exibirMenuPrincipal() {
    system(CLEAR); // Limpa a tela
    printf("\n========================================\n");
    printf("              Menu Principal            \n");
    printf("========================================\n");
    printf("1. Procedimento de saude\n");
    printf("2. Visualizar Agendas\n");
    printf("3. Pagamento\n");
    printf("5. Relatorio de Procedimentos Contratados\n");
    printf("6. Faturamento Diario\n");
    printf("7. Sair\n");
    printf("========================================\n");
}

// Função para exibir os procedimentos e permitir agendamento de horário
void exibirProcedimentos() {
    system(CLEAR); // Limpa a tela
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
        agendarHorario(opcao - 1); // Agendar horário para o procedimento escolhido
    } else {
        printf("Opcao invalida. Tente novamente.\n");
        exibirProcedimentos(); // Reexibe os procedimentos em caso de opção inválida
    }
}

// Função para agendar um horário para um procedimento específico
void agendarHorario(int procedimentoIndex) {
    int horario;
    exibirAgenda(procedimentoIndex); // Exibe a agenda do procedimento selecionado
    printf("\nEscolha um horario para agendar (1-9): ");
    scanf("%d", &horario);

    // Verifica se o horário é válido
    if (horario >= 1 && horario <= MAX_HORARIOS) {
        // Verifica se o horário está livre
        if (strcmp(agendas[procedimentoIndex][horario - 1], "L (livre)") == 0) {
            snprintf(agendas[procedimentoIndex][horario - 1], 12, "A (agendado)"); // Marca o horário como agendado
            printf("Horario agendado com sucesso!\n");
            
            // Adiciona o agendamento à lista de agendamentos
            agendamentos[totalAgendamentos].procedimentoIndex = procedimentoIndex;
            agendamentos[totalAgendamentos].horario = horario - 1;
            totalAgendamentos++;
        } else {
            printf("Horario ja esta ocupado. Tente outro.\n"); // Mensagem de erro para horário ocupado
        }
    } else {
        printf("Horario invalido.\n"); // Mensagem de erro para horário inválido
    }

    printf("\nPressione Enter para continuar...");
    getchar();
    getchar(); // Aguardar o Enter
}

// Função para visualizar as agendas dos procedimentos
void visualizarAgendas() {
    int opcao;

    do {
        system(CLEAR); // Limpa a tela
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
            exibirAgenda(opcao - 1); // Exibe a agenda do procedimento escolhido
        } else {
            printf("Opcao invalida. Tente novamente.\n"); // Mensagem de erro para opção inválida
        }

        printf("\nPressione Enter para continuar...");
        getchar();
        getchar();
    } while (1);
}

// Função para exibir a agenda de um procedimento específico
void exibirAgenda(int procedimentoIndex) {
    system(CLEAR); // Limpa a tela
    printf("\n========================================\n");
    printf("               Agenda %s              \n", procedimentoNomes[procedimentoIndex]);
    printf("========================================\n");
    printf("ID    Horario   Status\n");
    for (int i = 0; i < MAX_HORARIOS; i++) {
        printf("%02d    %02d:00     %s\n", i + 1, i + 9, agendas[procedimentoIndex][i]); // Exibe cada horário e seu status
    }
    printf("========================================\n");
}

// Função para inicializar todas as agendas como "L (livre)"
void inicializarAgenda() {
    for (int i = 0; i < MAX_PROCEDIMENTOS; i++) {
        for (int j = 0; j < MAX_HORARIOS; j++) {
            snprintf(agendas[i][j], 12, "L (livre)"); // Inicializa todos os horários como livres
        }
    }
}

// Função para realizar o pagamento
void realizarPagamento() {
    if (totalAgendamentos == 0) {
        printf("Nenhum procedimento agendado.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        getchar();
        return;
    }

    printf("Escolha um procedimento para pagamento:\n");
    for (int i = 0; i < totalAgendamentos; i++) {
        printf("%d. %s (Horario: %02d:00)\n", i + 1, procedimentoNomes[agendamentos[i].procedimentoIndex], agendamentos[i].horario + 9);
    }
    printf("0. Voltar ao Menu Principal\n");
    int escolha;
    printf("Opcao: ");
    scanf("%d", &escolha);

    if (escolha == 0) {
        return;
    } else if (escolha < 1 || escolha > totalAgendamentos) {
        printf("Opcao invalida. Tente novamente.\n");
        realizarPagamento();
        return;
    }

    int index = escolha - 1;
    int procedimentoIndex = agendamentos[index].procedimentoIndex;
    int horario = agendamentos[index].horario;
    float total = procedimentoValores[procedimentoIndex];
    float desconto;

    printf("Escolha a forma de pagamento:\n");
    printf("1. Dinheiro (Desconto de 5%% a 10%%)\n");
    printf("2. Cartao (Desconto fixo de 5%%)\n");
    int opcao;
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("Informe o percentual de desconto (5%% a 10%%): ");
        scanf("%f", &desconto);
        if (desconto < 5 || desconto > 10) {
            printf("Desconto invalido. Aplicando desconto padrao de 5%%.\n");
            desconto = 5;
        }
    } else if (opcao == 2) {
        desconto = 5;
    } else {
        printf("Opcao invalida. Tente novamente.\n");
        realizarPagamento();
        return;
    }

    total -= total * (desconto / 100);
    exibirConsolidadoPagamento(&total, total, desconto);

    if (opcao == 1) {
        float valorRecebido, troco;
        printf("Informe o valor recebido: R$ ");
        scanf("%f", &valorRecebido);
        troco = valorRecebido - total;
        if (troco < 0) {
            printf("Valor insuficiente. Operacao cancelada.\n");
        } else {
            printf("Troco: R$ %.2f\n", troco);
            printf("Pagamento realizado com sucesso.\n");
            removerAgendamento(procedimentoIndex, horario);
        }
    } else if (opcao == 2) {
        int pagamentoOk;
        printf("Pagamento na maquina (1 - OK, 0 - Falhou): ");
        scanf("%d", &pagamentoOk);
        if (pagamentoOk) {
            printf("Pagamento realizado com sucesso.\n");
            removerAgendamento(procedimentoIndex, horario);
        } else {
            printf("Pagamento falhou. Tente novamente.\n");
            realizarPagamento();
        }
    }

    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
}

// Função para calcular o total dos procedimentos agendados
float calcularTotal(float* totalPorProcedimento) {
    float total = 0;
    for (int i = 0; i < totalAgendamentos; i++) {
        int index = agendamentos[i].procedimentoIndex;
        totalPorProcedimento[index] += procedimentoValores[index];
        total += procedimentoValores[index];
    }
    return total;
}



// Função para exibir o consolidado do pagamento
void exibirConsolidadoPagamento(float* totalPorProcedimento, float total, float desconto) {
    system(CLEAR); // Limpa a tela
    printf("\n========================================\n");
    printf("            Consolidado de Pagamento            \n");
    printf("========================================\n");
    for (int i = 0; i < MAX_PROCEDIMENTOS; i++) {
        if (totalPorProcedimento[i] > 0) {
            printf("%-25s R$ %.2f\n", procedimentoNomes[i], totalPorProcedimento[i]);
        }
    }
    printf("========================================\n");
    printf("Desconto: %.2f%%\n", desconto);
    printf("Total: R$ %.2f\n", total);
    printf("========================================\n");
}

// Função para remover um agendamento após o pagamento
void removerAgendamento(int procedimentoIndex, int horario) {
    // Marca o horário como livre novamente
    snprintf(agendas[procedimentoIndex][horario], 12, "L (livre)");

    // Remove o agendamento da lista
    for (int i = 0; i < totalAgendamentos; i++) {
        if (agendamentos[i].procedimentoIndex == procedimentoIndex && agendamentos[i].horario == horario) {
            for (int j = i; j < totalAgendamentos - 1; j++) {
                agendamentos[j] = agendamentos[j + 1];
            }
            totalAgendamentos--;
            break;
        }
    }
}
// comentario 