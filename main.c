#include "lab.h"
#include <stdio.h>

int main() {
    // Declara um array de clientes.
    Cliente clientes[MAX_CLIENTES];
    // Inicializa o número de clientes como zero.
    int numClientes = 0;
    // Carrega os clientes a partir de um arquivo.
    carregarClientes(clientes, &numClientes);
    
    //Declara uma variável para armazenar a opção do menu.
    int opcao;

    do {
        // Apresenta o menu de opções para o usuário.
        printf("\nMenu de Opcoes:\n");
        printf("1. Novo cliente\n");
        printf("2. Apaga cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Debito\n");
        printf("5. Deposito\n");
        printf("6. Extrato\n");
        printf("7. Transferencia\n");
        printf("0. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
         // Utiliza um switch para executar a função correspondente à opção escolhida.
        switch (opcao) {
            case 1:
                novoCliente(clientes, &numClientes);
                break;
            case 2:
                apagaCliente(clientes, &numClientes);
                break;
            case 3:
                listarClientes(clientes, numClientes);
                break;
            case 4:
                debito(clientes, numClientes);
                break;
            case 5:
                deposito(clientes, numClientes);
                break;
            case 6:
                extrato(clientes, numClientes);
                break;
            case 7:
                transferencia(clientes, numClientes);
                break;
            case 0:
                printf("Saindo do programa. Salvando dados...\n");
                // Salva os dados dos clientes em um arquivo.
                salvarClientes(clientes, numClientes);
                break;
            default:
                // Mensagem para opções inválidas.
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);  // Continua o loop até o usuário escolher sair.

    return 0;
}
