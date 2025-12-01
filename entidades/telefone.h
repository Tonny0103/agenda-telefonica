#ifndef AGENDA_TELEFONICA_TELEFONE_H
#define AGENDA_TELEFONICA_TELEFONE_H

typedef struct {
    int id;
    int id_pessoa;
    char telefone[12];
} telefone;

int gerar_id_valido_telefone();
void cadastrar_telefone();
telefone consultar_telefone(char* nome);
telefone consultar_telefone_id(int id_pessoa);
void editar_telefone(char* nome);
void editar_telefone_id(int id_pessoa);
void excluir_telefone(char* nome);
void excluir_telefone_id(int id_pessoa);

#endif //AGENDA_TELEFONICA_TELEFONE_H