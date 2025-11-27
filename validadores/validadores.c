#include "validadores.h"
#include <stdio.h>
#include "cpf.h"
#include <time.h>

int valida_nome(char* nome) {
    for (int i = 0; i < 30; i++) {
        if (i <= 2 && nome[i] == '\0') {
            return 0;
        }
    }
    return 1;
}

int valida_telefone(char* telefone) {
    for (int i = 0; i < 11; i++) {
        if (i < 9 && telefone[i] == '\0') {
            return 0;
        }
    }

    return 1;
}

int valida_email(char* email) {
    int pos_arroba = -1;
    int pos_ponto = -1;
    int qtd_arrobas = 0;

    for (int i = 0; i < 30; i++) {
        if (i < 10 && email[i] == '\0') return 0;

        if (email[i] == '@') {
            qtd_arrobas++;
            pos_arroba = i;
        }

        if (email[i] == '.') pos_ponto = i;

        if (email[i] == ' ') return 0;
    }

    if (qtd_arrobas != 1) return 0;
    if (pos_arroba == 0) return 0;
    if (pos_ponto == -1) return 0;
    if (pos_ponto < pos_arroba) return 0;
    if (pos_ponto == pos_arroba + 1) return 0;
    if (pos_ponto == 29) return 0;

    return 1;
}

int valida_cpf(char* cpf) {
    return !verifica_todos_algarismos_iguais(cpf) && verifica_digitos_verificadores(cpf);
}

int valida_data_nascimento(char* data_nascimento) {
    int dia, mes, ano;

    if (sscanf(data_nascimento, "%2d/%2d/%4d", &dia, &mes, &ano) != 3) {
        return 0;
    }

    if (dia < 1 || dia > 31) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (ano < 1900) return 0;

    int dias_no_mes[] = {31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31};

    int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);

    if (bissexto && mes == 2) {
        dias_no_mes[1] = 29;
    }

    if (dia > dias_no_mes[mes - 1]) return 0;

    time_t agora = time(NULL);
    struct tm *data_atual = localtime(&agora);

    int dia_atual = data_atual->tm_mday;
    int mes_atual = data_atual->tm_mon + 1;
    int ano_atual = data_atual->tm_year + 1900;

    if (ano > ano_atual) return 0;

    if (ano == ano_atual && mes > mes_atual) return 0;

    if (ano == ano_atual && mes == mes_atual && dia > dia_atual) return 0;

    return 1;
}