#include "lab.h"
#include <stdio.h>

//Função para comparar duas strings
int my_strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str1 == *str2){
        str1++;
        str2++;
    }
    return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

// Função para cadastrar um novo cliente do banco
void novoCliente(Cliente clientes[], int *numClientes) {
    // Verifica se o número de clientes atingiu o limite máximo
    if (*numClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido. Impossível adicionar novo cliente.\n");
        return;
    }

    // Solicita e armazena informações do novo cliente
    printf("Informe o nome do cliente: ");
    scanf("%s", clientes[*numClientes].nome);

    printf("Informe o CPF do cliente: ");
    scanf("%s", clientes[*numClientes].cpf);

    printf("Escolha o tipo de conta (0 para Comum, 1 para Plus): ");
    scanf("%d", (int*)&clientes[*numClientes].tipoConta);

    printf("Informe o valor inicial da conta: ");
    scanf("%f", &clientes[*numClientes].saldo);

    printf("Informe a senha do cliente: ");
    scanf("%s", clientes[*numClientes].senha);

    // Inicializa o array de operações do cliente cadastrado
    for (size_t i = 0; i < MAX_OPERACOES; ++i) {
        clientes[*numClientes].operacoes[i] = 0;
    }

    // Incrementa o número total de clientes
    (*numClientes)++;
    printf("Cliente adicionado com sucesso!\n");
}

// Função para apagar um cliente cadastrado no banco a partir do seu CPF e senha
void apagaCliente(Cliente clientes[], int *numClientes) {
    // Verifica se o cliente à ser apagado existe
    if (*numClientes == 0) {
        printf("Nenhum cliente cadastrado. Impossível apagar.\n");
        return;
    }
    // Solicita o CPF do cliente a ser apagado
    char cpfParaApagar[12];
    printf("Informe o CPF do cliente a ser apagado: ");
    scanf("%s", cpfParaApagar);

    // Variável para armazenar o índice do cliente a ser apagado
    int indiceCliente = -1;

    // Busca entre os clientes o cliente com o CPF fornecido
    for (int i = 0; i < *numClientes; ++i) {
        // Verifica se o CPF do cliente atual é igual ao fornecido
        if (my_strcmp(clientes[i].cpf, cpfParaApagar) == 0) {
            // Solicita a senha do cliente para confirmar a exclusão
            char senhaDigitada[20];
            printf("Informe a senha do cliente: ");
            scanf("%s", senhaDigitada);

            // Verifica se a senha está correta
            if (my_strcmp(clientes[i].senha, senhaDigitada) == 0) {
                indiceCliente = i;
                break;
            } else {
                printf("Senha incorreta. Operacao cancelada.\n");
                return;
            }
        }
    }

    // Verifica se o cliente com o CPF fornecido foi encontrado
    if (indiceCliente == -1) {
        printf("Cliente com CPF %s nao encontrado.\n", cpfParaApagar);
    } else {
        // Move todos os clientes à direita do cliente a ser apagado uma posição para a esquerda
        for (int i = indiceCliente; i < *numClientes - 1; ++i) {
            clientes[i] = clientes[i + 1];
        }

        (*numClientes)--;
        printf("Cliente com CPF %s apagado com sucesso!\n", cpfParaApagar);
    }
}
void listarClientes(Cliente clientes[], int numClientes){
    // Verifica se o número de clientes é zero.
    if (numClientes == 0) {
        // Se não houver clientes, imprime uma mensagem e retorna.
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    // Se houver clientes, imprime um cabeçalho.
    printf("Listagem de clientes:\n");
    // Loop para iterar sobre os clientes no array.
    for (int i = 0; i < numClientes; ++i) {
        // Imprime o número do cliente.
        printf("Cliente %d:\n", i + 1);
        // Imprime o nome do cliente.
        printf("Nome: %s\n", clientes[i].nome);
        // Imprime o CPF do cliente.
        printf("CPF: %s\n", clientes[i].cpf);
        // Imprime o Tipo de Conta do cliente e imprime "Comum" ou "Plus".
        printf("Tipo de Conta: %s\n", (clientes[i].tipoConta == comum) ? "Comum" : "Plus");
        // Imprime o Saldo do cliente.
        printf("Saldo: %.2f\n", clientes[i].saldo);
        // Adiciona uma linha em branco para separar informações de clientes.
        printf("\n");
    }
}
