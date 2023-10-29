#ifndef PROJETO_LAB_H
#define PROJETO_LAB_H

//Definindo número máximo de clientes e operações
#define MAX_CLIENTES 1000
#define MAX_OPERACOES 100

//Representação para os tipos de conta do banco
typedef enum {
    comum,
    plus
} TipoConta;

//Representação dos dados de um cliente
typedef struct {
    char nome[50];
    char cpf[12];
    TipoConta tipoConta;
    float saldo;
    char senha[20];
    int operacoes[MAX_OPERACOES];
} Cliente;

int my_strcmp(const char *str1, const char *str2);
void novoCliente(Cliente clientes[], int *numClientes);
void apagaCliente(Cliente clientes[], int *numClientes);
void listarClientes(Cliente clientes[], int numClientes);
void debito(Cliente clientes[], int numClientes);
void deposito(Cliente clientes[], int numClientes);
void extrato(Cliente clientes[], int numClientes);
void transferencia(Cliente clientes[], int numClientes);
void salvarClientes(Cliente clientes[], int numClientes); 
void carregarClientes(Cliente clientes[], int *numClientes);

#endif
