#include <stdio.h>

#include "menu.h"

int main(void) {
    int opcao = 0;

    do {
        printf("\n========= MENU PRINCIPAL =========\n");
        printf("1 - Cadastrar\n");
        printf("2 - Editar\n");
        printf("3 - Excluir\n");
        printf("4 - Consultar\n");
        printf("5 - Sair\n");
        printf("==================================\n");
        printf("Selecione uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: menu_cadastrar(); break;
            case 2: menu_editar(); break;
            case 3: menu_excluir(); break;
            case 4: menu_consultar(); break;
            case 5:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 5);

    return 0;
}
