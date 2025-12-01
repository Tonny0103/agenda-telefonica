#ifndef AGENDA_TELEFONICA_PESSOA_H
#define AGENDA_TELEFONICA_PESSOA_H

typedef struct {
    int id;
    char nome[31];
    char email[31];
    char cpf[12];
    char data_nascimento[11];
} pessoa;

int gerar_id_valido(FILE* arquivo);
int nome_ja_cadastrado(FILE* arquivo, char* nome);
void cadastrar_pessoa();
pessoa consultar_pessoa(char* nome);
pessoa consultar_pessoa_por_id(int id_pessoa);
void editar_pessoa(char* nome);
void editar_pessoa_por_id(int id_pessoa);
void excluir_pessoa(char* nome);
void excluir_pessoa_por_id(int id_pessoa);

#endif //AGENDA_TELEFONICA_PESSOA_H