#include "menu.h"

#include <stdio.h>

#include "entidades/pessoa.h"
#include "entidades/telefone.h"

void menu_cadastrar() {
    int opcao = 0;

    do {
        printf("\n------- MENU CADASTRAR -------\n");
        printf("1 - Pessoa\n");
        printf("2 - Telefone\n");
        printf("3 - Retornar\n");
        printf("------------------------------\n");
        printf("Selecione: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_pessoa();
                break;

            case 2:
                cadastrar_telefone();
                break;

            case 3:
                return;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 3);
}

void menu_editar() {
    int opcao = 0;

    do {
        printf("\n------- MENU EDITAR -------\n");
        printf("1 - Pessoa\n");
        printf("2 - Telefone\n");
        printf("3 - Retornar\n");
        printf("---------------------------\n");
        printf("Selecione: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int op2;
                printf("\nEditar Pessoa por:\n");
                printf("1 - Nome\n");
                printf("2 - IDPessoa\n");
                printf("3 - Retornar\n");
                scanf("%d", &op2);

                if (op2 == 1) {
                    char nome[31];
                    printf("Digite o nome: ");
                    scanf("%s", nome);
                    editar_pessoa(nome);
                } else if (op2 == 2) {
                    int id;
                    printf("Digite o ID: ");
                    scanf("%d", &id);
                    editar_pessoa_por_id(id);
                }
                break;
            }

            case 2: {
                int op2;
                printf("\nEditar Telefone por:\n");
                printf("1 - Nome\n");
                printf("2 - IDPessoa\n");
                printf("3 - Retornar\n");
                scanf("%d", &op2);

                if (op2 == 1) {
                    char nome[31];
                    printf("Digite o nome: ");
                    scanf("%s", nome);
                    editar_telefone(nome);
                } else if (op2 == 2) {
                    int id;
                    printf("Digite o ID: ");
                    scanf("%d", &id);
                    editar_telefone_id(id);
                }
                break;
            }

            case 3:
                return;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 3);
}

void menu_excluir() {
    int opcao = 0;

    do {
        printf("\n------- MENU EXCLUIR -------\n");
        printf("1 - Pessoa\n");
        printf("2 - Telefone\n");
        printf("3 - Retornar\n");
        printf("----------------------------\n");
        printf("Selecione: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int op2;
                printf("\nExcluir Pessoa por:\n");
                printf("1 - Nome\n");
                printf("2 - IDPessoa\n");
                printf("3 - Retornar\n");
                scanf("%d", &op2);

                if (op2 == 1) {
                    char nome[31];
                    printf("Digite o nome: ");
                    scanf("%s", nome);
                    excluir_pessoa(nome);
                } else if (op2 == 2) {
                    int id;
                    printf("Digite o ID: ");
                    scanf("%d", &id);
                    excluir_pessoa_por_id(id);
                }
                break;
            }

            case 2: {
                int op2;
                printf("\nExcluir Telefone por:\n");
                printf("1 - Nome\n");
                printf("2 - IDPessoa\n");
                printf("3 - Retornar\n");
                scanf("%d", &op2);

                if (op2 == 1) {
                    char nome[31];
                    printf("Digite o nome: ");
                    scanf("%s", nome);
                    excluir_telefone(nome);
                } else if (op2 == 2) {
                    int id;
                    printf("Digite o ID: ");
                    scanf("%d", &id);
                    excluir_telefone_id(id);
                }
                break;
            }

            case 3:
                return;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 3);
}

void menu_consultar() {
    int opcao = 0;

    do {
        printf("\n------- MENU CONSULTAR -------\n");
        printf("1 - Pessoa\n");
        printf("2 - Telefone\n");
        printf("3 - Retornar\n");
        printf("------------------------------\n");
        printf("Selecione: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int op2;
                printf("\nConsultar Pessoa por:\n");
                printf("1 - Nome\n");
                printf("2 - IDPessoa\n");
                printf("3 - Retornar\n");
                scanf("%d", &op2);

                if (op2 == 1) {
                    char nome[31];
                    pessoa p;
                    printf("Digite o nome: ");
                    scanf("%s", nome);
                    p = consultar_pessoa(nome);
                    if (p.id != 0) {
                        printf("ID: %d\nNome: %s\nEmail: %s\nCPF: %s\nNascimento: %s\n",
                               p.id, p.nome, p.email, p.cpf, p.data_nascimento);
                    }
                } else if (op2 == 2) {
                    int id;
                    pessoa p;
                    printf("Digite o ID: ");
                    scanf("%d", &id);
                    p = consultar_pessoa_por_id(id);
                    if (p.id != 0) {
                        printf("ID: %d\nNome: %s\nEmail: %s\nCPF: %s\nNascimento: %s\n",
                               p.id, p.nome, p.email, p.cpf, p.data_nascimento);
                    }
                }
                break;
            }

            case 2: {
                int op2;
                printf("\nConsultar Telefone por:\n");
                printf("1 - Nome\n");
                printf("2 - IDPessoa\n");
                printf("3 - Retornar\n");
                scanf("%d", &op2);

                telefone t;

                if (op2 == 1) {
                    char nome[31];
                    printf("Nome: ");
                    scanf("%s", nome);
                    t = consultar_telefone(nome);
                } else if (op2 == 2) {
                    int id;
                    printf("ID: ");
                    scanf("%d", &id);
                    t = consultar_telefone_id(id);
                }

                if (t.id != 0) {
                    printf("ID: %d\nIDPessoa: %d\nTelefone: %s\n",
                           t.id, t.id_pessoa, t.telefone);
                }

                break;
            }

            case 3:
                return;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 3);
}
