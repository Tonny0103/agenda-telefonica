#include <stdio.h>
#include "validadores/validadores.h"

int main(void) {
    char cpf[11];

    printf("Digite um cpf: \n");
    scanf("%s", cpf);

    int cpf_valido = valida_cpf(cpf);

    if (!cpf_valido) printf("CPF invalido\n");

    return 0;
}
