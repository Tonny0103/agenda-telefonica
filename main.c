#include <stdio.h>
#include "validadores/cpf.h"

int main(void) {
    char cpf[11];

    printf("Digite um cpf: \n");
    scanf("%s", cpf);

    int todos_algarismos_iguais = verifica_todos_algarismos_iguais(cpf);
    if (todos_algarismos_iguais == 1) {
        printf("Erro: todos os algarismos do CPF sao iguais.\n");
        return 0;
    }

    int primeiro_digito_verificador = calcula_primeiro_digito_verificador(cpf);
    int segundo_digito_verificador = calcula_segundo_digito_verificador(cpf);

    printf("Primeiro digito verificador: %i\n", primeiro_digito_verificador);
    printf("Segunda digito verificador: %i\n", segundo_digito_verificador);

    if (cpf[9] != primeiro_digito_verificador || cpf[10] != segundo_digito_verificador) {
        printf("Erro: CPF invalido.");
        return 0;
    }

    printf("CPF valido!");

    return 0;
}