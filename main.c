#include <stdio.h>
#include "validadores/validadores.h"

int main(void) {
    char email[30];

    printf("Digite um email: \n");
    scanf("%s", email);

    int email_valido = valida_email(email);

    if (!email_valido) printf("Email inválido \n");

    return 0;
}
