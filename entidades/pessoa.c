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
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo pessoas.csv\n");
        fclose(arquivo);
        return;
    }

    pessoa p;

    printf("==========Cadastrar Pessoa==========\n");

    do {
        printf("Digite o nome do pessoa: \n");
        scanf("%s", p.nome);

        rewind(arquivo);

        if (nome_ja_cadastrado(arquivo, p.nome)) {
            printf("Nome ja cadastrado! Insira outro nome...\n");
        } else if (!valida_nome(p.nome)) {
            printf("Nome invalido...\n");
        }
    } while (nome_ja_cadastrado(arquivo, p.nome) || !valida_nome(p.nome));

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

    p.id = gerar_id_valido(arquivo);
}