#include <stdio.h>
#include "pessoa.h"

#include <stdlib.h>

#include "../validadores/validadores.h"
#include <string.h>

int gerar_id_valido(FILE* arquivo) {
    int id = 0;

    char linha[256];

    while (fgets(linha, 256, arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        char* token = strtok(linha, ",");
        int temp = atoi(token);
        id = temp;
    }

    return id + 1;
}

int nome_ja_cadastrado(FILE* arquivo, char* nome) {
    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        char* token = strtok(linha, ",");

        token = strtok(NULL, ","); // Pegar o valor do nome
        if (strcmp(nome, token) == 0) return 1;
    }

    return 0;
}

void cadastrar_pessoa() {
    FILE* arquivo = fopen("../dados/pessoas.csv", "a+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo pessoas.csv\n");
        return;
    }

    pessoa p;

    printf("==========Cadastrar Pessoa==========\n");

    int nome_cadastrado;
    
    do {
        printf("Digite o nome do pessoa: \n");
        scanf("%s", p.nome);

        rewind(arquivo);

	nome_cadastrado = nome_ja_cadastrado(arquivo, p.nome);

        if (nome_cadastrado) {
            printf("Nome ja cadastrado! Insira outro nome...\n");
        } else if (!valida_nome(p.nome)) {
            printf("Nome invalido...\n");
        }
    } while (nome_cadastrado || !valida_nome(p.nome));

    do {
        printf("Digite o email do pessoa: \n");
        scanf("%s", p.email);

        if (!valida_email(p.email)) {
            printf("Email invalido! Insira um email valido...\n");
        }
    } while (!valida_email(p.email));

    do {
        printf("Digite o CPF da pessoa: \n");
        scanf("%s", p.cpf);

        if (!valida_cpf(p.cpf)) {
            printf("CPF invalido! Insira um CPF valido...\n");
        }
    } while (!valida_cpf(p.cpf));

    do {
        printf("Digite a data de nascimento da pessoa: \n");
        scanf("%s", p.data_nascimento);

        if (!valida_data_nascimento(p.data_nascimento)) {
            printf("Data de nascimento invalida! Insira uma data de nascimento valida...\n");
        }
    } while (!valida_data_nascimento(p.data_nascimento));
    
    rewind(arquivo);
    p.id = gerar_id_valido(arquivo);
    
    char linha[200];
    snprintf(linha, sizeof(linha), "%d,%s,%s,%s,%s\n", p.id, p.nome, p.email, p.cpf, p.data_nascimento);

    if (fputs(linha, arquivo) == EOF) {
	printf("Erro ao escrever no arquivo...\n");
    }
    fclose(arquivo);
    printf("Pessoa cadastrada com sucesso!\n");
}

pessoa consultar_pessoa(char* nome) {
    FILE* arquivo = fopen("../dados/pessoas.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir pessoas.csv\n");
    }

    char linha[256];

    pessoa p;

    int id = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        // id
        char* token = strtok(linha, ",");
        id = atoi(token);

        token = strtok(NULL, ",");
        if (strcmp(nome, token) == 0) {
            p.id = id;

            // Nome
            strncpy(p.nome, token, sizeof(p.nome));
            p.nome[sizeof(p.nome) - 1] = '\0';

            // Email
            token = strtok(NULL, ",");
            strncpy(p.email, token, sizeof(p.email));
            p.email[sizeof(p.email) - 1] = '\0';

            // CPF
            token = strtok(NULL, ",");
            strncpy(p.cpf, token, sizeof(p.cpf));
            p.cpf[sizeof(p.cpf) - 1] = '\0';

            // Data de nascimento
            token = strtok(NULL, ",");
            strncpy(p.data_nascimento, token, sizeof(p.data_nascimento));
            p.data_nascimento[sizeof(p.data_nascimento) - 1] = '\0';
        }
    }

    fclose(arquivo);
    return p;
}

pessoa consultar_pessoa_por_id(int id_pessoa) {
    FILE* arquivo = fopen("../dados/pessoas.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir pessoas.csv\n");
    }

    char linha[256];

    pessoa p;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        char* token = strtok(linha, ",");
        int id = atoi(token);

        if (id == id_pessoa) {
            p.id = id;

            token = strtok(NULL, ",");
            strncpy(p.nome, token, sizeof(p.nome));
            p.nome[sizeof(p.nome) - 1] = '\0';

            // Email
            token = strtok(NULL, ",");
            strncpy(p.email, token, sizeof(p.email));
            p.email[sizeof(p.email) - 1] = '\0';

            // CPF
            token = strtok(NULL, ",");
            strncpy(p.cpf, token, sizeof(p.cpf));
            p.cpf[sizeof(p.cpf) - 1] = '\0';

            // Data de nascimento
            token = strtok(NULL, ",");
            strncpy(p.data_nascimento, token, sizeof(p.data_nascimento));
            p.data_nascimento[sizeof(p.data_nascimento) - 1] = '\0';
        }
    }

    fclose(arquivo);
    return p;
}

void editar_pessoa(char* nome) {
    FILE* arquivo = fopen("../dados/pessoas.csv", "r+");
    if (!arquivo) {
        printf("Erro ao abrir pessoas.csv\n");
        return;
    }

    FILE* temp = fopen("../dados/temp.csv", "w+");
    if (!temp) {
        printf("Erro ao criar temp.csv\n");
        fclose(arquivo);
        return;
    }

    int opcao = 0;
    printf("Digite o que deseja editar: \n");
    printf("1 - Nome\n");
    printf("2 - Data de nascimento\n");
    printf("3 - CPF\n");
    printf("4 - E-mail\n");
    scanf("%d", &opcao);

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        pessoa p;

        char* token = strtok(linha, ",");

        p.id = atoi(token);

        token = strtok(NULL, ",");
        strncpy(p.nome, token, sizeof(p.nome));

        token = strtok(NULL, ",");
        strncpy(p.email, token, sizeof(p.email));

        token = strtok(NULL, ",");
        strncpy(p.cpf, token, sizeof(p.cpf));

        token = strtok(NULL, ",");
        strncpy(p.data_nascimento, token, sizeof(p.data_nascimento));

        if (strcmp(p.nome, nome) == 0) {
            encontrado = 1;

            switch (opcao) {
                case 1:
                    printf("Novo nome: \n");
                    scanf("%s", p.nome);
                    break;
                case 2:
                    printf("Novo data de nascimento: \n");
                    scanf("%s", p.data_nascimento);
                    break;
                case 3:
                    printf("Novo CPF: \n");
                    scanf("%s", p.cpf);
                    break;
                case 4:
                    printf("Novo E-mail: \n");
                    scanf("%s", p.email);
                    break;
                default:
                    printf("Opcao invalida! \n");
            }
        }

        fprintf(temp, "%d,%s,%s,%s,%s\n",
                p.id, p.nome, p.email, p.cpf, p.data_nascimento);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("../dados/pessoas.csv");
        rename("../dados/temp.csv", "../dados/pessoas.csv");
        printf("Pessoa editada com sucesso!\n");
    } else {
        remove("../dados/temp.csv");
        printf("Pessoa não encontrada.\n");
    }
}

void editar_pessoa_por_id(int id_pessoa) {
    FILE* arquivo = fopen("../dados/pessoas.csv", "r+");
    if (!arquivo) {
        printf("Erro ao abrir pessoas.csv\n");
        return;
    }

    FILE* temp = fopen("../dados/temp.csv", "w+");
    if (!temp) {
        printf("Erro ao criar temp.csv\n");
        fclose(arquivo);
        return;
    }

    int opcao = 0;
    printf("Digite o que deseja editar: \n");
    printf("1 - Nome\n");
    printf("2 - Data de nascimento\n");
    printf("3 - CPF\n");
    printf("4 - E-mail\n");
    scanf("%d", &opcao);

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        pessoa p;

        char* token = strtok(linha, ",");

        p.id = atoi(token);

        token = strtok(NULL, ",");
        strncpy(p.nome, token, sizeof(p.nome));

        token = strtok(NULL, ",");
        strncpy(p.email, token, sizeof(p.email));

        token = strtok(NULL, ",");
        strncpy(p.cpf, token, sizeof(p.cpf));

        token = strtok(NULL, ",");
        strncpy(p.data_nascimento, token, sizeof(p.data_nascimento));

        if (p.id == id_pessoa) {
            encontrado = 1;

            switch (opcao) {
                case 1:
                    printf("Novo nome: \n");
                    scanf("%s", p.nome);
                    break;
                case 2:
                    printf("Novo data de nascimento: \n");
                    scanf("%s", p.data_nascimento);
                    break;
                case 3:
                    printf("Novo CPF: \n");
                    scanf("%s", p.cpf);
                    break;
                case 4:
                    printf("Novo E-mail: \n");
                    scanf("%s", p.email);
                    break;
                default:
                    printf("Opcao invalida! \n");
            }
        }

        fprintf(temp, "%d,%s,%s,%s,%s\n",
                p.id, p.nome, p.email, p.cpf, p.data_nascimento);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("../dados/pessoas.csv");
        rename("../dados/temp.csv", "../dados/pessoas.csv");
        printf("Pessoa editada com sucesso!\n");
    } else {
        remove("../dados/temp.csv");
        printf("Pessoa não encontrada.\n");
    }
}