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
        int numero = cpf[i] - '0';
        soma = soma + (numero * multiplicador);
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
        int numero = cpf[i] - '0';
        soma = soma + (numero * multiplicador);
        multiplicador--;
    }

    int resto = soma % 11;

    if (resto == 0 || resto == 1) return 0;

    return 11 - resto;
}

int verifica_digitos_verificadores(char* cpf) {
    int primeiro_digito = calcula_primeiro_digito_verificador(cpf);
    int segundo_digito = calcula_segundo_digito_verificador(cpf);

    int valido = 1;

    if (primeiro_digito != cpf[9] - '0') valido = 0;
    if (segundo_digito != cpf[10] - '0') valido = 0;

    return valido;
}