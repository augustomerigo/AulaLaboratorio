#include <stdio.h>
#include <string.h>

char clientes[50][50];
int total_clientes = 0;

char produtos[50][50];
float precos[50];1

int total_produtos = 0;

void cadastrar_cliente() {
    printf("Digite o nome do cliente: ");
    scanf("%s", clientes[total_clientes]);
    printf("Cliente %s cadastrado com sucesso!\n", clientes[total_clientes]);
    total_clientes++;
}
void cadastrar_produto() {
    printf("Digite o nome do produto: ");
    scanf("%s", produtos[total_produtos]);
    printf("Digite o preco do produto: ");
    scanf("%f", &precos[total_produtos]);
    printf("Produto %s cadastrado com sucesso! Preco: %.2f\n", produtos[total_produtos], precos[total_produtos]);
    total_produtos++;
}

void cadastrar_venda() {
    char cliente[50], produto[50];
    int quantidade;
    printf("Digite o nome do cliente: ");
    scanf("%s", cliente);
    printf("Digite o nome do produto: ");
    scanf("%s", produto);
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);
    printf("Venda cadastrada com sucesso! Cliente: %s, Produto: %s, Quantidade: %d\n", cliente, produto, quantidade);
}

void listar_clientes() {
    printf("Lista de clientes cadastrados:\n");
    for (int i = 0; i < total_clientes; i++) {
        printf("%d. %s\n", i + 1, clientes[i]);
    }
}
void listar_produtos() {
    printf("Lista de produtos cadastrados:\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("%d. %s - %.2f\n", i + 1, produtos[i], precos[i]);
    }
}
void remover_clientes(){
    char nome[50];
    printf("Digite o nome do cliente a ser removido: ");
    scanf("%s", nome);
    strcpy(clientes[total_clientes], nome);
    total_clientes--;
    printf("Cliente %s removido com sucesso!\n", nome);
}
int main() {
    int opcao = -1;
    do {
        printf("MENU\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Produto\n");
        printf("3. Cadastrar Venda\n");
        printf("4. Listar Clientes\n");
        printf("5. Listar Produtos\n");
        printf("6. Remover Cliente\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        if (opcao == 1) {
            cadastrar_cliente();
        } else if (opcao == 2) {
            cadastrar_produto();
        } else if (opcao == 3) {
            cadastrar_venda();
        } else if (opcao == 4) {
            listar_clientes();
        } else if (opcao == 5) {
            listar_produtos();
        } else if (opcao == 6) {
            remover_clientes();
        } else if (opcao != 0) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
    printf("Saindo do programa\n");
    return 0;
}