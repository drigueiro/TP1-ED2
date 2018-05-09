#ifndef ARVOREBIN_H
#define ARVOREBIN_H

#include <iostream>

typedef struct titem{
	int chave;
	long int dado1;
	char dado2[1000];
}Titem;
typedef struct arvore_bin Arvore_bin;
void insere(FILE *arquivo, Titem info, int &cont, int &trasnferencia);
int atualiza_pai(FILE *arquivo, int posicao, Titem num, int &cont, int &trasnferencia);
int pesquisa(FILE *arquivo, int posicao, int procu, int *aux, int &comp);
void imprime(FILE *arq);

#endif