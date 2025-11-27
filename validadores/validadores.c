#include "validadores.h"
#include "cpf.h"

int valida_cpf(char* cpf) {
    return !verifica_todos_algarismos_iguais(cpf) && verifica_digitos_verificadores(cpf);
}
