#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "arvorebin.h"

using namespace std;

struct arvore_bin{
	Titem indice;
	int esq;
	int dir;
};

void insere(FILE *arquivo, Titem info, int &cont, int &transferencia){//funcao para inserir um elemento no arquivo de acordo com sua implementacao
	Arvore_bin arvore;//arvore para guardar dados do arquivo
	fseek(arquivo, 0, SEEK_END);//manda o ponteiro para o final do arquivo para o if verificar seu tamanho
	if(ftell(arquivo) == 0){//verifica o tamanho do arquivo
		arvore.indice = info;
		arvore.esq = -1;//folha a esquerda
		arvore.dir = -1;//folha a direita
		fwrite(&arvore, sizeof(arvore), 1, arquivo);
		cont++;//contador para guardar posicao do filho
		return;
	}
	rewind(arquivo);//ponteiro no inicio do arquivo
	if((atualiza_pai(arquivo, 0, info, cont, transferencia)) == 1){
		fseek(arquivo, 0, SEEK_END);//ponteiro vai para o final do arquivo 
		arvore.indice = info;
		arvore.esq = -1;
		arvore.dir = -1;
		fwrite(&arvore, sizeof(arvore), 1, arquivo);//escreve no final do arquivo 
		cont++; //contador para atualizar o paireturn;
	}
	else
		return;
}

int atualiza_pai(FILE *arquivo, int posicao, Titem num, int &cont, int &transferencia){
	Arvore_bin arvore;//auxiliar para percorrer o arquivo
	long int bytes;
	bytes = posicao*sizeof(arvore);//quantidade a ser pulada do arquivo 
	fseek(arquivo, bytes, SEEK_SET);//pula o ponteiro para o pai

	if(fread(&arvore, sizeof(arvore), 1, arquivo) == 0)//le o arquivo um por um
		return 0;
	transferencia++;
	if(num.chave > arvore.indice.chave){//item maior q chave

		if(arvore.dir < 0){//no folha a direita, para atualizar o pai
			fseek(arquivo, bytes, SEEK_SET);//volta para posicao anterior onde se encontra o pai
			arvore.dir = cont;
			fwrite(&arvore, sizeof(arvore), 1, arquivo);//escreve na arvore
			return 1;//caso base
		}
		else//arvore a direita
			atualiza_pai(arquivo, arvore.dir, num, cont, transferencia);//caminha para a direita com essa quantidade de leitura: arvore.dir
	}
	else if(num.chave < arvore.indice.chave){//faz o mesmo q o if acima porem para a esquerda com elementos menores que a chave

		if(arvore.esq < 0){//no folha a esquerda
			fseek(arquivo, bytes, SEEK_SET);
			arvore.esq = cont;
			fwrite(&arvore, sizeof(arvore), 1, arquivo);
			return 1;
		}
		else//arvore a esquerda
			atualiza_pai(arquivo, arvore.esq, num, cont, transferencia);
	}
	else 
		return 0;
}

int pesquisa(FILE *arquivo, int posicao, int procu, int *aux, int &comp){
	Arvore_bin arvore;//auxiliar para percorrer o arquivo
	long int bytes;
	bytes = posicao*sizeof(arvore);

	fseek(arquivo, bytes, SEEK_SET);
	if(fread(&arvore, sizeof(arvore), 1, arquivo) == 0)//le o arquivo um por um
		return 0;
	comp++;
	if(procu > arvore.indice.chave){//item maior q chave
		if(arvore.dir < 0)//no folha a direita
			return 0;//caso base
		
		else //caminhar a direita
			pesquisa(arquivo, arvore.dir, procu, aux, comp);//caminha para a direita com essa quantidade de leitura: arvore.dir
		
	}
	else if(procu < arvore.indice.chave){//arvore a esquerda
		if(arvore.esq < 0)//no folha a esquerda
			return 0;
		
		else//caminhar a esquerda
			pesquisa(arquivo, arvore.esq, procu, aux, comp);
		
	}
	else if(procu == arvore.indice.chave){//encontrou item desejado
		*aux = arvore.indice.chave;//atribuiu valor ao vetor
		return 1;
	}
}

void imprime(FILE *arq){
	Arvore_bin arvore;
	while(fread(&arvore, sizeof(arvore), 1, arq) == 1){//le um item por vez
		cout << arvore.esq << " | " << arvore.indice.chave << " | " << arvore.dir << endl;//mostra na tela
	}
}