# Compilador (SCC0605 - Teoria da Computação e Compiladores: Trabalho 1)

Esta fase do projeto (versão 0.2) implementa o analisador **léxico** do
compilador.

## Requerimentos de Compilação

Programas necessários:
- Gnu make (versão utilizada: GNU Make 4.2.1)
- Gnu C Compiler (versão utilizada: gcc (Debian 9.3.0-10) 9.3.0)

Sistema de teste utilizado:
- Linux debian-testing-note 5.7.0-rc1-local-1 #10 SMP x86\_64 GNU/Linux
- Distributor ID:	Debian
	- Description:	Debian GNU/Linux bullseye/sid
	- Release:	testing
	- Codename:	bullseye

## Instruções de Compilação

Na pasta com os arquivos fonte (*.c e *.h), utilizar `make all` para compilar
o executável `lexico`. Execute `make clean` para excluir os arquivos objeto (*.o)
e o arquivo executável.

## Instruções de uso

Para rodar o programa, execute `/path/to/file/lexico` ou `./lexico` se estiver no
mesmo diretório que o executável. Se não houver argumentos, o analisador léxico
irá tomar `meu_programa.txt` como entrada.

Utilizando `./main /path/to/file.txt`, o analisador léxico irá utilizar o
arquivo fornecido como código fonte para análise. Há também vários casos de
teste em `tests/`.

Para gerar um arquivo de saída com os pares string-token, redirecione a saída
do comando como o seguinte exemplo:

```
./main /path/to/file.txt > analise_lexica.txt
```

