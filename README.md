# Agenda Telefônica - Projeto de algoritmos II

### Instruções para execução do programa
Usando o MinGW ou o powershell do windows, **na raiz do projeto**, execute o seguinte comando:
```bash
gcc main.c menu.c entidades/pessoa.c entidades/telefone.c validadores/validadores.c validadores/cpf.c -o agenda-telefonica
```
E a partir disso execute o binário:
```bash
./agenda-telefonica.exe
```
#### Alternativa (CMake)
Verifique que instalou o CMake corretamente a seguir execute:
```
cmake -G "MinGW Makefiles" -B build
cmake --build build
```
A partir disso entre na pasta ``build`` que foi gerada e copie o binário para a pasta raiz do projeto para que haja nenhum erro durante as leitruas de arquivo do programa.