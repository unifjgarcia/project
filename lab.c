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
