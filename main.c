#include <stdio.h>      // Biblioteca para funções de entrada e saída (printf, scanf)
#include <string.h>     // Biblioteca para manipulação de strings

// Estrutura que representa um cliente
struct Cliente {
    int id;             // Identificador do cliente
    char nome[50];      // Nome do cliente
    char cpf[15];       // CPF do cliente
};

// Estrutura que representa um produto
struct Produto {
    int id;             // Identificador do produto
    char nome[50];      // Nome do produto
    float preco;        // Preço do produto
    int estoque;        // Quantidade em estoque
};

// Estrutura que representa um item dentro de uma venda
struct ItemVenda {
    int id_produto;         // ID do produto vendido
    int quantidade;         // Quantidade vendida
    float valor_unitario;   // Valor unitário do produto na venda
};

// Estrutura que representa uma venda
struct Venda {
    int id_venda;               // Identificador da venda
    int id_cliente;             // ID do cliente que fez a compra
    struct ItemVenda itens[10]; // Vetor de itens da venda (até 10 itens)
    int total_itens;            // Quantidade de itens na venda
    float total;                // Valor total da venda
};

// Vetores globais para armazenar clientes, produtos e vendas
struct Cliente clientes[50];    // Vetor para até 50 clientes
int total_clientes = 0;         // Contador de clientes cadastrados

struct Produto produtos[50];    // Vetor para até 50 produtos
int total_produtos = 0;         // Contador de produtos cadastrados

struct Venda vendas[50];        // Vetor para até 50 vendas
int total_vendas = 0;           // Contador de vendas realizadas

// Função para cadastrar um novo cliente
void cadastrar_cliente() {
    struct Cliente c;
    c.id = total_clientes + 1;  // Gera um novo ID para o cliente
    printf("Digite o nome do cliente: ");
    scanf("%s", c.nome);        // Lê o nome do cliente
    printf("Digite o CPF do cliente: ");
    scanf("%s", c.cpf);         // Lê o CPF do cliente
    clientes[total_clientes] = c;   // Adiciona o cliente ao vetor
    total_clientes++;               // Incrementa o contador de clientes
    printf("Cliente cadastrado com sucesso! ID: %d\n", c.id);
}

// Função para listar todos os clientes cadastrados
void listar_clientes() {
    printf("\nLista de clientes:\n");
    for (int i = 0; i < total_clientes; i++) {
        printf("ID: %d | Nome: %s | CPF: %s\n", clientes[i].id, clientes[i].nome, clientes[i].cpf);
    }
}

// Função para cadastrar um novo produto
void cadastrar_produto() {
    struct Produto p;
    p.id = total_produtos + 1;      // Gera um novo ID para o produto
    printf("Digite o nome do produto: ");
    scanf("%s", p.nome);            // Lê o nome do produto
    printf("Digite o preco do produto: ");
    scanf("%f", &p.preco);          // Lê o preço do produto
    printf("Digite o estoque disponível: ");
    scanf("%d", &p.estoque);        // Lê a quantidade em estoque
    produtos[total_produtos] = p;   // Adiciona o produto ao vetor
    total_produtos++;               // Incrementa o contador de produtos
    printf("Produto cadastrado com sucesso! ID: %d\n", p.id);
}

// Função para listar todos os produtos cadastrados
void listar_produtos() {
    printf("\nLista de produtos:\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("ID: %d | Nome: %s | Preco: R$ %.2f | Estoque: %d\n", produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
}

// Função para cadastrar uma nova venda
void cadastrar_venda() {
    struct Venda v;
    v.id_venda = total_vendas + 1;  // Gera um novo ID para a venda
    v.total_itens = 0;              // Inicializa o total de itens
    v.total = 0;                    // Inicializa o valor total da venda

    printf("Digite o ID do cliente: ");
    scanf("%d", &v.id_cliente);     // Lê o ID do cliente que está comprando

    int continuar;
    do {
        struct ItemVenda item;
        printf("Digite o ID do produto: ");
        scanf("%d", &item.id_produto);      // Lê o ID do produto
        printf("Digite a quantidade: ");
        scanf("%d", &item.quantidade);      // Lê a quantidade desejada

        int encontrado = 0;
        // Procura o produto no vetor de produtos
        for (int i = 0; i < total_produtos; i++) {
            if (produtos[i].id == item.id_produto) {
                if (produtos[i].estoque >= item.quantidade) {
                    item.valor_unitario = produtos[i].preco;      // Define o valor unitário
                    produtos[i].estoque -= item.quantidade;       // Atualiza o estoque
                    v.itens[v.total_itens] = item;                // Adiciona o item à venda
                    v.total_itens++;                              // Incrementa o total de itens
                    v.total += item.valor_unitario * item.quantidade; // Soma ao total da venda
                    encontrado = 1;
                    break;
                } else {
                    printf("Estoque insuficiente!\n");
                    return;
                }
            }
        }
        if (!encontrado) {
            printf("Produto nao encontrado.\n");
            return;
        }

        printf("Deseja adicionar outro item? (1-Sim, 0-Nao): ");
        scanf("%d", &continuar);    // Pergunta se quer adicionar mais itens à venda
    } while (continuar);

    vendas[total_vendas] = v;       // Adiciona a venda ao vetor de vendas
    total_vendas++;                 // Incrementa o contador de vendas
    printf("Venda registrada com sucesso! Total: R$ %.2f\n", v.total);
}

// Função para listar todas as vendas realizadas
void listar_vendas() {
    printf("\nLista de Vendas:\n");
    for (int i = 0; i < total_vendas; i++) {
        struct Venda v = vendas[i];
        printf("\nID Venda: %d | Cliente ID: %d | Total: R$ %.2f\n", v.id_venda, v.id_cliente, v.total);
        for (int j = 0; j < v.total_itens; j++) {
            printf("   Produto ID: %d | Qtde: %d | Unit: R$ %.2f\n",
                   v.itens[j].id_produto,
                   v.itens[j].quantidade,
                   v.itens[j].valor_unitario);
        }
    }
}

// Função principal do programa: mostra o menu e chama as funções conforme a escolha do usuário
int main() {
    int opcao = -1;
    do {
        printf("\nMENU PRINCIPAL\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Cadastrar Produto\n");
        printf("4. Listar Produtos\n");
        printf("5. Cadastrar Venda\n");
        printf("6. Listar Vendas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            cadastrar_cliente();    // Chama a função para cadastrar cliente
        } else if (opcao == 2) {
            listar_clientes();      // Chama a função para listar clientes
        } else if (opcao == 3) {
            cadastrar_produto();    // Chama a função para cadastrar produto
        } else if (opcao == 4) {
            listar_produtos();      // Chama a função para listar produtos
        } else if (opcao == 5) {
            cadastrar_venda();      // Chama a função para cadastrar venda
        } else if (opcao == 6) {
            listar_vendas();        // Chama a função para listar vendas
        } else if (opcao == 0) {
            printf("Saindo do programa...\n");
        } else {
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);          // Repete até o usuário escolher sair
    return 0;
}