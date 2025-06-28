#include <stdio.h> // Biblioteca padrão para entrada e saída de dados
#include <string.h> // Biblioteca para manipulação de strings

// Estrutura que representa um cliente
struct Cliente {
    int id; // Identificador único do cliente
    char nome[50]; // Nome do cliente
    char cpf[15]; // CPF do cliente
};

// Estrutura que representa um produto
struct Produto {
    int id; // Identificador único do produto
    char nome[50]; // Nome do produto
    float preco; // Preço unitário do produto
    int estoque; // Quantidade disponível em estoque
};

// Estrutura que representa um item dentro de uma venda
struct ItemVenda {
    int id_produto; // ID do produto vendido
    int quantidade; // Quantidade vendida
    float valor_unitario; // Valor unitário do produto no momento da venda
};

// Estrutura que representa uma venda
struct Venda {
    int id_venda; // Identificador único da venda
    int id_cliente; // ID do cliente que realizou a compra
    struct ItemVenda itens[10]; // Itens incluídos na venda (máximo de 10)
    int total_itens; // Quantidade total de itens vendidos
    float total; // Valor total da venda
    char data[11]; // Data da venda no formato dd/mm/aaaa
    int forma_pagamento; // Forma de pagamento: 1-Dinheiro, 2-Cartao, 3-Pix
};

// Vetores globais para armazenar dados
struct Cliente clientes[50]; // Vetor de clientes cadastrados
int total_clientes = 0; // Contador de clientes

struct Produto produtos[50]; // Vetor de produtos cadastrados
int total_produtos = 0; // Contador de produtos

struct Venda vendas[50]; // Vetor de vendas registradas
int total_vendas = 0; // Contador de vendas

// Função para cadastrar um novo cliente
void cadastrar_cliente() {
    struct Cliente c;
    c.id = total_clientes + 1;
    printf("Digite o nome do cliente: ");
    scanf("%s", c.nome);
    printf("Digite o CPF do cliente:(xxx.xxx.xxx-xx) ");
    scanf("%s", c.cpf);
    clientes[total_clientes] = c;
    total_clientes++;
    printf("Cliente cadastrado com sucesso! ID: %d\n", c.id);
}

// Função para listar todos os clientes
void listar_clientes() {
    printf("\nLista de clientes:\n");
    for (int i = 0; i < total_clientes; i++) {
        printf("ID: %d | Nome: %s | CPF: %s\n", clientes[i].id, clientes[i].nome, clientes[i].cpf);
    }
}

// Função para editar um cliente
void editar_cliente() {
    int id, encontrado = 0;
    printf("Digite o ID do cliente que deseja editar: ");
    scanf("%d", &id);
    for (int i = 0; i < total_clientes; i++) {
        if (clientes[i].id == id) {
            encontrado = 1;
            printf("Editar cliente ID %d:\n", id);
            printf("Novo nome: ");
            scanf("%s", clientes[i].nome);
            printf("Novo CPF: ");
            scanf("%s", clientes[i].cpf);
            printf("Cliente atualizado com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

// Função para remover um cliente
void remover_cliente() {
    int id, encontrado = 0;
    printf("Digite o ID do cliente que deseja remover: ");
    scanf("%d", &id);
    for (int i = 0; i < total_clientes; i++) {
        if (clientes[i].id == id) {
            encontrado = 1;
            for (int j = i; j < total_clientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            total_clientes--;
            printf("Cliente removido com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

// Função para cadastrar um novo produto
void cadastrar_produto() {
    struct Produto p;
    p.id = total_produtos + 1;
    printf("Digite o nome do produto: ");
    scanf("%s", p.nome);
    printf("Digite o preco do produto: ");
    scanf("%f", &p.preco);
    printf("Digite o estoque disponivel: ");
    scanf("%d", &p.estoque);
    produtos[total_produtos] = p;
    total_produtos++;
    printf("Produto cadastrado com sucesso! ID: %d\n", p.id);
}

// Função para listar todos os produtos
void listar_produtos() {
    printf("\nLista de produtos:\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("ID: %d | Nome: %s | Preco: R$ %.2f | Estoque: %d\n", produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
}

// Função para editar um produto
void editar_produto() {
    int id, encontrado = 0;
    printf("Digite o ID do produto que deseja editar: ");
    scanf("%d", &id);
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].id == id) {
            encontrado = 1;
            printf("Editar produto ID %d:\n", id);
            printf("Novo nome: ");
            scanf("%s", produtos[i].nome);
            printf("Novo preco: ");
            scanf("%f", &produtos[i].preco);
            printf("Novo estoque: ");
            scanf("%d", &produtos[i].estoque);
            printf("Produto atualizado com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}

// Função para cadastrar uma nova venda
void cadastrar_venda() {
    struct Venda v;
    v.id_venda = total_vendas + 1;
    v.total_itens = 0;
    v.total = 0;
    printf("Digite o ID do cliente: ");
    scanf("%d", &v.id_cliente);
    int continuar;
    do {
        struct ItemVenda item;
        printf("Digite o ID do produto: ");
        scanf("%d", &item.id_produto);
        printf("Digite a quantidade: ");
        scanf("%d", &item.quantidade);
        int encontrado = 0;
        for (int i = 0; i < total_produtos; i++) {
            if (produtos[i].id == item.id_produto) {
                if (produtos[i].estoque >= item.quantidade) {
                    item.valor_unitario = produtos[i].preco;
                    produtos[i].estoque -= item.quantidade;
                    v.itens[v.total_itens] = item;
                    v.total_itens++;
                    v.total += item.valor_unitario * item.quantidade;
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
        scanf("%d", &continuar);
    } while (continuar);
    printf("Digite a data da venda (dd/mm/aaaa): ");
    scanf("%s", v.data);
    printf("Forma de pagamento (1-Dinheiro, 2-Cartao, 3-Pix): ");
    scanf("%d", &v.forma_pagamento);
    vendas[total_vendas] = v;
    total_vendas++;
    printf("Venda registrada com sucesso! Total: R$ %.2f\n", v.total);
}

// Função para listar todas as vendas
void listar_vendas() {
    printf("\nLista de Vendas:\n");
    for (int i = 0; i < total_vendas; i++) {
        struct Venda v = vendas[i];
        printf("\nID Venda: %d | Cliente ID: %d | Total: R$ %.2f\n", v.id_venda, v.id_cliente, v.total);
        printf("   Data: %s | Forma de Pagamento: ", v.data);
        if (v.forma_pagamento == 1) printf("Dinheiro\n");
        else if (v.forma_pagamento == 2) printf("Cartao\n");
        else if (v.forma_pagamento == 3) printf("Pix\n");
        else printf("Desconhecida\n");
        for (int j = 0; j < v.total_itens; j++) {
            printf("   Produto ID: %d | Qtde: %d | Unit: R$ %.2f\n",
                   v.itens[j].id_produto,
                   v.itens[j].quantidade,
                   v.itens[j].valor_unitario);
        }
    }
}

// Função principal com menu
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
        printf("7. Remover Cliente\n");
        printf("8. Editar Cliente\n");
        printf("9. Editar Produto\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        if (opcao == 1) cadastrar_cliente();
        else if (opcao == 2) listar_clientes();
        else if (opcao == 3) cadastrar_produto();
        else if (opcao == 4) listar_produtos();
        else if (opcao == 5) cadastrar_venda();
        else if (opcao == 6) listar_vendas();
        else if (opcao == 7) remover_cliente();
        else if (opcao == 8) editar_cliente();
        else if (opcao == 9) editar_produto();
        else if (opcao == 0) printf("Saindo do programa...\n");
        else printf("Opcao invalida!\n");
    } while (opcao != 0);
    return 0;
}
