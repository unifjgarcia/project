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
void debito(Cliente clientes[], int numClientes) {
    if (numClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    char cpfDebito[12];
    printf("Informe o CPF do cliente: ");
    scanf("%s", cpfDebito);

    int indiceCliente = -1;
    for (int i = 0; i < numClientes; ++i) {
        if (my_strcmp(clientes[i].cpf, cpfDebito) == 0) {
            char senhaDebito[20];
            printf("Informe a senha do cliente: ");
            scanf("%s", senhaDebito);

            // Verifica se a senha está correta
            if (my_strcmp(clientes[i].senha, senhaDebito) == 0) {
                float valorDebito;
                printf("Informe o valor do debito: ");
                scanf("%f", &valorDebito);

                // Verifica o tipo de conta
                if (clientes[i].tipoConta == comum) {
                    // Debito na conta comum
                    valorDebito = 1.05; // Aplica taxa de 5%
                    if (clientes[i].saldo - valorDebito < -1000.00) {
                        printf("Debito nao autorizado. Saldo negativo limite atingido.\n");
                        return;
                    }
                } else {
                    // Debito na conta plus
                    valorDebito= 1.03; // Aplica taxa de 3%
                    if (clientes[i].saldo - valorDebito < -5000.00) {
                        printf("Debito nao autorizado. Saldo negativo limite atingido.\n");
                        return;
                    }
                }

                // Realiza o débito
                clientes[i].saldo -= valorDebito;
                printf("Debito de %.2f realizado com sucesso. Novo saldo: %.2f\n", valorDebito, clientes[i].saldo);
                return;
            } else {
                printf("Senha incorreta. Operacao cancelada.\n");
                return;
            }
        }
    }

    printf("Cliente com CPF %s nao encontrado.\n", cpfDebito);
}
void deposito(Cliente clientes[], int numClientes) {
    // Verifica se não há clientes cadastrados.
    if (numClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    char cpfDeposito[12];
    printf("Informe o CPF do cliente: ");
    scanf("%s", cpfDeposito);

    int indiceCliente = -1;
    // Procura pelo cliente com o CPF informado.
    for (int i = 0; i < numClientes; ++i) {
        // Compara o CPF digitado com o CPF do cliente atual.
        if (my_strcmp(clientes[i].cpf, cpfDeposito) == 0) {
            float valorDeposito;
            printf("Informe o valor do depósito: ");
            scanf("%f", &valorDeposito);

            // Realiza o depósito, atualiza o saldo e informa o sucesso.
            clientes[i].saldo += valorDeposito;
            printf("Deposito de %.2f realizado com sucesso. Novo saldo: %.2f\n", valorDeposito, clientes[i].saldo);
            return;
        }
    }

    printf("Cliente com CPF %s nao encontrado.\n", cpfDeposito);
}
void extrato(Cliente clientes[], int numClientes) {
    // Verifica se não há clientes cadastrados.
    if (numClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    char cpfExtrato[12];
    printf("Informe o CPF do cliente: ");
    scanf("%s", cpfExtrato);

    int indiceCliente = -1;
    // Procura pelo cliente com o CPF informado.
    for (int i = 0; i < numClientes; ++i) {
        // Compara o CPF digitado com o CPF do cliente atual.
        if (my_strcmp(clientes[i].cpf, cpfExtrato) == 0) {
            char senhaExtrato[20];
            printf("Informe a senha do cliente: ");
            scanf("%s", senhaExtrato);

            // Verifica se a senha está correta
            if (my_strcmp(clientes[i].senha, senhaExtrato) == 0) {
                FILE *arquivoExtrato;
                char nomeArquivo[50];
                // Gera o nome do arquivo com base no CPF do cliente.
                sprintf(nomeArquivo, "extrato_%s.txt", cpfExtrato);

                // Cria um arquivo para o extrato.
                arquivoExtrato = fopen(nomeArquivo, "w");
                if (arquivoExtrato == NULL) {
                    // Verifica se foi possível criar.
                    printf("Erro ao criar o arquivo de extrato.\n");
                    return;
                }

                // Escreve informações no arquivo
                fprintf(arquivoExtrato, "Extrato de operacoes para o cliente %s:\n", clientes[i].nome);
                fprintf(arquivoExtrato, "CPF: %s\n", clientes[i].cpf);
                fprintf(arquivoExtrato, "Tipo de Conta: %s\n", (clientes[i].tipoConta == comum) ? "Comum" : "Plus");
                fprintf(arquivoExtrato, "Saldo Inicial: %.2f\n", clientes[i].saldo);
                fprintf(arquivoExtrato, "\n");

                // Itera sobre as operações e escreve no arquivo.
                for (int j = 0; j < MAX_OPERACOES && clientes[i].operacoes[j] != 0; ++j) {
                    float valorOperacao = *(float *)&clientes[i].operacoes[j];
                    fprintf(arquivoExtrato, "Operacao %d: %.2f\n", j + 1, valorOperacao);
                }

                // Fecha o arquivo
                fclose(arquivoExtrato);

                printf("Extrato gerado com sucesso. Consulte o arquivo %s\n", nomeArquivo);
                return;
            } else {
                printf("Senha incorreta. Operacao cancelada.\n");
                return;
            }
        }
    }
    // Se nenhum cliente com o CPF informado for encontrado.
    printf("Cliente com CPF %s nao encontrado.\n", cpfExtrato);
}
// Verifica se existem clientes cadastrados
void transferencia(Cliente clientes[], int numClientes) {
    if (numClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    char cpfOrigem[12];
    printf("Informe o CPF da conta de origem: ");
    scanf("%s", cpfOrigem);

    int indiceOrigem = -1;
     // Procura o índice da conta de origem pelo CPF
    for (int i = 0; i < numClientes; ++i) {
        if (my_strcmp(clientes[i].cpf, cpfOrigem) == 0) {
            char senhaOrigem[20];
            printf("Informe a senha da conta de origem: ");
            scanf("%s", senhaOrigem);

            // Verificação da senha
            if (my_strcmp(clientes[i].senha, senhaOrigem) == 0) {
                char cpfDestino[12];
                printf("Informe o CPF da conta de destino: ");
                scanf("%s", cpfDestino);

                int indiceDestino = -1;
                // Procura o índice da conta através do CPF 
                for (int j = 0; j < numClientes; ++j) {
                    if (my_strcmp(clientes[j].cpf, cpfDestino) == 0) {
                        indiceDestino = j;
                        break;
                    }
                }
                // Verifica a existência da conta de destino, caso não seja encontrada, aparece uma mensagem
                if (indiceDestino == -1) {
                    printf("Conta de destino com CPF %s nao encontrada.\n", cpfDestino);
                    return;
                }

                float valorTransferencia;
                // Pede o valor da transferência
                printf("Informe o valor da transferencia: ");
                scanf("%f", &valorTransferencia);

                // Verifica se a conta de origem tem saldo suficiente
                if (clientes[i].saldo < valorTransferencia) {
                    printf("Transferencia nao autorizada. Saldo insuficiente.\n");
                    return;
                }

                // Realiza a transferência
                clientes[i].saldo -= valorTransferencia;
                clientes[indiceDestino].saldo += valorTransferencia;
                  // Exibe mensagens de sucesso e os novos saldos das contas
                printf("Transferencia de %.2f realizada com sucesso. Novo saldo da conta de origem: %.2f\n", valorTransferencia, clientes[i].saldo);
                printf("Novo saldo da conta de destino: %.2f\n", clientes[indiceDestino].saldo);
                return;
            } else {
                printf("Senha incorreta. Operacao cancelada.\n");
                return;
            }
        }
    }
      // Mostra caso a conta de origem não for encontrada
    printf("Conta de origem com CPF %s nao encontrada.\n", cpfOrigem);
}

void salvarClientes(Cliente clientes[], int numClientes) {
    // Abre o arquivo "clientes.dat" em modo de escrita binária ("wb").
    FILE *arquivo = fopen("clientes.dat", "wb");
    if (arquivo == NULL) {
        // Verifica se o arquivo foi aberto corretamente. Se não, exibe uma mensagem de erro e retorna.
        printf("Erro ao abrir o arquivo para escrita.\n");
        return; 
    }
     // Função fwrite para escrever os dados dos clientes no arquivo.
    fwrite(clientes, sizeof(Cliente), numClientes, arquivo);
    // Fecha o arquivo.
    fclose(arquivo);
}
void carregarClientes(Cliente clientes[], int *numClientes) {
     // Abre o arquivo "clientes.dat" em modo de leitura binária ("rb").
    FILE *arquivo = fopen("clientes.dat", "rb");
    // Verifica se o arquivo foi aberto corretamente. Se não for possível abrir, exibe uma mensagem de aviso e retorna.
    if (arquivo == NULL) {
        printf("Arquivo de dados nao encontrado. Iniciando com lista vazia.\n");
        return;
    }
    // Usa a função fread para ler os dados do arquivo e carregá-los no array de clientes.
    *numClientes = fread(clientes, sizeof(Cliente), MAX_CLIENTES, arquivo);
    // Fecha o arquivo após a leitura.
    fclose(arquivo);
}
