#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "arvorebin.h"
#include "gerador.h"

using namespace std;

int main(int argc, char *argv[]){
	int metodo, quantidade, situacao, chave, comp, transf;
	//Variaveis usadas para receber os valores de entrada da funcao
	metodo = atoi(argv[1]);
	quantidade = atoi(argv[2]);
	situacao = atoi(argv[3]);
	chave = atoi(argv[4]);

	if(metodo == 1){
		return 0;
	}
	
	if(metodo == 2){
		comp = 0;
		transf = 0;
		clock_t inicio, fim;
		cout <<"Arvore binaria em arquivo\n";
		FILE* arqArvore;//arquivo para escrever a arvore binaria
		FILE*arquivo;//arquivo contendo as informacoes
		Titem info;//variavel para ler do arquivo

		if((arqArvore = fopen("arvore.bin", "w+b")) == NULL){//cria o arquivo para escrita
			cout << "Nao foi possivel criar o arquivo!!!\n";
		}
		gerador_arquivo(quantidade, situacao);//gera as chaves

		if((arquivo = fopen("registros.bin", "rb")) == NULL){//abre arquivo para leitura
			cout << "Nao foi possivel abrir o arquivo!!!\n";
		}
		inicio = clock();//funcao para saber o tempo gasto na execucao
		int cont = 0;//auxiliar usado para atualizar o no pai
		while(fread(&info, sizeof(info), 1, arquivo)){//le dado um por um para preencher a arvore
			insere(arqArvore, info, cont, transf);//insere no arquivo
		}
		cout << "Transferencias realizadas: " << transf << endl;
		fim = clock();//termino da funcao de tempo 
		cout << ((double)(fim - inicio)/CLOCKS_PER_SEC) << "ms\n";//calcula o tempo gasto
		int achado;//auxiliar para receber o valor da chave caso ache
		if(pesquisa(arqArvore, 0, chave, &achado, comp) == 1)//funcao booleana de pesquisa
			cout <<"Dado encontrado!\n Chave: " << achado << "-----Comparacoes: " << comp << endl;//
		else 
			cout <<"Dado nao encontrado!!\n";


		rewind(arqArvore);
		imprime(arqArvore);
		fclose(arqArvore);
	}
	
	if(metodo == 3){
		return 0;
	}

	return 0;
}