#include "cpf.h"

int verifica_todos_algarismos_iguais(char* cpf) {
    int todos_algarismos_iguais = 1;
    for (int i = 0; i < 11; i++) {
        if (i != 10) {
            if (cpf[i] != cpf[i + 1]) todos_algarismos_iguais = 0;
        }
    }
    return todos_algarismos_iguais;
}

int calcula_primeiro_digito_verificador(char* cpf) {
    int soma = 0;
    int multiplicador = 10;

    for (int i = 0; i < 9; i++) {
        soma = soma + (cpf[i] * multiplicador);
        multiplicador--;
    }

    int resto = soma % 11;

    if (resto == 0 || resto == 1) return 0;

    return 11 - resto;
}

int calcula_segundo_digito_verificador(char* cpf) {
    int soma = 0;
    int multiplicador = 11;

    for (int i = 0; i < 10; i++) {
        soma = soma + (cpf[i] * multiplicador);
        multiplicador--;
    }

    int resto = soma % 11;

    if (resto == 0 || resto == 1) return 0;

    return 11 - resto;
}