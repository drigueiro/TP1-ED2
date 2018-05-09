#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "gerador.h"
#include "arvorebin.h"

using namespace std;

void gerador_arquivo(int quantidade, int situacao){//quantidade de chaves e situacao, se e ordenado, decrescente ou aleatorio
	FILE* arquivo;
	Titem info;
	switch(situacao){
		case 1:{//arquivo em ordem crescente
			if((arquivo = fopen("registros.bin", "wb")) == NULL)//cria o arquivo para escrita
				cout << "Nao foi possivel criar o arquivo!!!\n";
			

			for (int i = 1; i<=quantidade; i++){//roda o for ate a quantidade passada como parametro
				info.chave = i;//chave em ordem crescente
				info.dado1 = rand()%10000;//aleatorio para o primeiro dado
				for(int j=0; j<26; j++){
					info.dado2[j] = 'a'+(char)(rand()%26);//aleatorio letras
				}
				fwrite(&info, sizeof(info), 1, arquivo);//escreve no arquivo um dado de cada vez
			}

			fclose(arquivo);//fecha o arquivo 
			break;
		}
		case 2:{//arquivo decrescente 
			if((arquivo = fopen("registros.bin", "wb")) == NULL)
				cout << "Nao foi possivel criar o arquivo!!!\n";
			

			for (int i = quantidade; i > 0; i--){
				info.chave = i;
				info.dado1 = rand()%10000;
				for(int j=0; j<26; j++){
					info.dado2[j] = 'a'+(char)(rand()%26);
				}
				fwrite(&info, sizeof(info), 1, arquivo);
			}

			fclose(arquivo);
			break;
		}
		case 3:{
			int vet[quantidade];
			if((arquivo = fopen("registros.bin", "wb")) == NULL)
				cout << "Nao foi possivel criar o arquivo!!!\n";

			srand(time(NULL));
			for(int i = 0; i<quantidade; i++)
				vet[i] = i+1;

			for(int i=0; i<quantidade; i++){
				int j = i+rand()/(RAND_MAX/(quantidade - i)+1);
				int t = vet[j];
				vet[j] = vet[i];
				vet[i] = t;
			}

			for (int i = 0; i<quantidade; i++){//roda o for ate a quantidade passada como parametro
				info.chave = vet[i];//chave em ordem crescente
				info.dado1 = rand()%10000;//aleatorio para o primeiro dado
				for(int j=0; j<26; j++){
					info.dado2[j] = 'a'+(char)(rand()%26);//aleatorio letras
				}
				fwrite(&info, sizeof(info), 1, arquivo);//escreve no arquivo um dado de cada vez
			}

			fclose(arquivo);
			break;
		}
	}

}