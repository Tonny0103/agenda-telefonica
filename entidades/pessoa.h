#ifndef AGENDA_TELEFONICA_PESSOA_H
#define AGENDA_TELEFONICA_PESSOA_H

typedef struct {
    int id;
    char nome[30];
    char email[30];
    char cpf[11];
    char data_nascimento[10];
} pessoa;

int gerar_id_valido(FILE* arquivo);
int nome_ja_cadastrado(FILE* arquivo, char* nome);
void cadastrar_pessoa();
pessoa* consultar_pessoa();
pessoa* consultar_pessoa_por_id(int id);
void editar_pessoa();
void excluir_pessoa();

#endif //AGENDA_TELEFONICA_PESSOA_H