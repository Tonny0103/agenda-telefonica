#include "telefone.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pessoa.h"

int gerar_id_valido_telefone() {
    int id = 0;

    char linha[256];

    while (fgets(linha, sizeof(linha), stdin)) {
        linha[strcspn(linha, "\n")] = '\0';

        char* token = strtok(linha, ",");
        int temp = atoi(token);
        id = temp;
    }

    return id + 1;
}

void cadastrar_telefone() {
    FILE* arquivo = fopen("dados/telefones.csv", "a+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo telefones.csv");
        return;
    }

    telefone t;
    pessoa p;
    int opcao = 0;

    printf("==========Cadastrar Telefone==========\n");
    printf("1 - Buscar por nome\n");
    printf("2 - Buscar por id\n");
    printf("3 - Retornar\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            char nome[31];
            printf("Digite o nome:\n");
            scanf("%s", nome);

            p = consultar_pessoa(nome);

            if (p.id == 0) {
                printf("Pessoa não encontrada!\n");
                fclose(arquivo);
                return;
            }

            break;
        }

        case 2: {
            int id;
            printf("Digite o id:\n");
            scanf("%d", &id);

            p = consultar_pessoa_por_id(id);

            if (p.id == 0) {
                printf("Pessoa não encontrada!\n");
                fclose(arquivo);
                return;
            }

            break;
        }

        case 3:
            fclose(arquivo);
            return;

        default:
            printf("Opção inválida!\n");
            fclose(arquivo);
            return;
    }

    t.id = gerar_id_valido_telefone();
    t.id_pessoa = p.id;

    printf("Digite o número de telefone:\n");
    scanf("%s", t.telefone);

    fprintf(arquivo, "%d,%d,%s\n", t.id, t.id_pessoa, t.telefone);

    fclose(arquivo);
    printf("Telefone cadastrado com sucesso!\n");
}


telefone consultar_telefone(char* nome) {
    telefone t;

    t.id = 0;
    t.id_pessoa = 0;
    t.telefone[0] = '\0';

    pessoa p = consultar_pessoa(nome);
    if (p.id == 0) {
        printf("Pessoa não encontrada.\n");
        return t;
    }

    FILE* arquivo = fopen("dados/telefones.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir telefones.csv\n");
        return t;
    }

    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        char* token = strtok(linha, ",");

        t.id = atoi(token);

        token = strtok(NULL, ",");
        t.id_pessoa = atoi(token);
        if (t.id_pessoa == p.id) {

            token = strtok(NULL, ",");
            strncpy(t.telefone, token, sizeof(t.telefone));
            t.telefone[sizeof(t.telefone) - 1] = '\0';

            fclose(arquivo);
            return t;
        }
    }

    fclose(arquivo);

    t.id = 0;
    t.id_pessoa = p.id;
    t.telefone[0] = '\0';
    return t;
}

telefone consultar_telefone_id(int id_pessoa) {
    telefone t;

    t.id = 0;
    t.id_pessoa = 0;
    t.telefone[0] = '\0';

    FILE* arquivo = fopen("dados/telefones.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir telefones.csv\n");
        return t;
    }

    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        char* token = strtok(linha, ",");

        t.id = atoi(token);

        token = strtok(NULL, ",");
        t.id_pessoa = atoi(token);

        if (t.id_pessoa == id_pessoa) {

            token = strtok(NULL, ",");
            strncpy(t.telefone, token, sizeof(t.telefone));
            t.telefone[sizeof(t.telefone) - 1] = '\0';

            fclose(arquivo);
            return t;
        }
    }

    fclose(arquivo);

    t.id = 0;
    t.id_pessoa = id_pessoa;
    t.telefone[0] = '\0';

    return t;
}

void editar_telefone(char* nome) {
    pessoa p = consultar_pessoa(nome);
    if (p.id == 0) {
        printf("Pessoa não encontrada!\n");
        return;
    }

    FILE* arquivo = fopen("dados/telefones.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir telefones.csv\n");
        return;
    }

    FILE* temp = fopen("dados/temp.csv", "w+");
    if (!temp) {
        printf("Erro ao criar temp.csv\n");
        fclose(arquivo);
        return;
    }

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        telefone t;
        char* token = strtok(linha, ",");

        t.id = atoi(token);

        token = strtok(NULL, ",");
        t.id_pessoa = atoi(token);

        token = strtok(NULL, ",");
        strncpy(t.telefone, token, sizeof(t.telefone));
        t.telefone[sizeof(t.telefone) - 1] = '\0';

        if (t.id_pessoa == p.id) {
            encontrado = 1;

            printf("Novo telefone: \n");
            scanf("%s", t.telefone);
        }

        fprintf(temp, "%d,%d,%s\n", t.id, t.id_pessoa, t.telefone);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("dados/telefones.csv");
        rename("dados/temp.csv", "dados/telefones.csv");
        printf("Telefone editado com sucesso!\n");
    } else {
        remove("dados/temp.csv");
        printf("Telefone não encontrado para este nome.\n");
    }
}

void editar_telefone_id(int id_pessoa) {
    FILE* arquivo = fopen("dados/telefones.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir telefones.csv\n");
        return;
    }

    FILE* temp = fopen("dados/temp.csv", "w+");
    if (!temp) {
        printf("Erro ao criar temp.csv\n");
        fclose(arquivo);
        return;
    }

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        telefone t;
        char* token = strtok(linha, ",");

        t.id = atoi(token);

        token = strtok(NULL, ",");
        t.id_pessoa = atoi(token);

        token = strtok(NULL, ",");
        strncpy(t.telefone, token, sizeof(t.telefone));
        t.telefone[sizeof(t.telefone) - 1] = '\0';

        if (t.id_pessoa == id_pessoa) {
            encontrado = 1;

            printf("Novo telefone: \n");
            scanf("%s", t.telefone);
        }

        fprintf(temp, "%d,%d,%s\n", t.id, t.id_pessoa, t.telefone);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("dados/telefones.csv");
        rename("dados/temp.csv", "dados/telefones.csv");
        printf("Telefone editado com sucesso!\n");
    } else {
        remove("dados/temp.csv");
        printf("Telefone não encontrado para este ID.\n");
    }
}

void excluir_telefone(char* nome) {
    pessoa p = consultar_pessoa(nome);
    if (p.id == 0) {
        printf("Pessoa nao encontrada \n");
        return;
    }

    FILE* arquivo = fopen("dados/telefones.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir telefones.csv\n");
        return;
    }

    FILE* temp = fopen("dados/temp.csv", "w+");
    if (!temp) {
        printf("Erro ao criar temp.csv\n");
        fclose(arquivo);
        return;
    }

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        telefone t;
        char* token = strtok(linha, ",");

        t.id = atoi(token);

        token = strtok(NULL, ",");
        t.id_pessoa = atoi(token);

        token = strtok(NULL, ",");
        strncpy(t.telefone, token, sizeof(t.telefone));

        if (t.id_pessoa != p.id) {
            fprintf(arquivo, "%d,%d,%s", t.id, t.id_pessoa, t.telefone);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("dados/telefones.csv");
        rename("dados/temp.csv", "dados/telefones.csv");
        printf("Telefone excluido com sucesso!\n");
    } else {
        remove("dados/temp.csv");
        printf("Telefone não encontrado para este ID.\n");
    }
}

void excluir_telefone_id(int id_pessoa) {
    FILE* arquivo = fopen("dados/telefones.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir telefones.csv\n");
        return;
    }

    FILE* temp = fopen("dados/temp.csv", "w+");
    if (!temp) {
        printf("Erro ao criar temp.csv\n");
        fclose(arquivo);
        return;
    }

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        telefone t;
        char* token = strtok(linha, ",");

        t.id = atoi(token);

        token = strtok(NULL, ",");
        t.id_pessoa = atoi(token);

        token = strtok(NULL, ",");
        strncpy(t.telefone, token, sizeof(t.telefone));

        if (t.id_pessoa != id_pessoa) {
            fprintf(arquivo, "%d,%d,%s", t.id, t.id_pessoa, t.telefone);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("dados/telefones.csv");
        rename("dados/temp.csv", "dados/telefones.csv");
        printf("Telefone excluido com sucesso!\n");
    } else {
        remove("dados/temp.csv");
        printf("Telefone não encontrado para este ID.\n");
    }
}