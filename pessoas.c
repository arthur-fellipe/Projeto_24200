﻿/*****************************************************************//**
 * \file   pessoas.c
 * \brief
 *
 * \author Arthur Fellipe
 * \date   March 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dados.h"
#include "pessoas.h"

 /*void lerDados(FILE* fp, Pessoa* leituraPessoa)
 {
	 while (!feof(fp))
	 {
		 fscanf(fp, "%d;%d;%50[^;];%f;\n", &(leituraPessoa->id), &(leituraPessoa->admin), leituraPessoa->nome, &(leituraPessoa->saldo));
	 }
 }*/


ListaPessoa* LerFicheiroPessoaTxt()
{

	// Abre o ficheiro com os dados
	FILE* fp = fopen("pessoas.txt", "r");

	// Verifica se o ficheiro foi aberto com sucesso
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}
	// L� os dados do ficheiro
	Pessoa* novaPessoa = malloc(sizeof(Pessoa));
	ListaPessoa* listaPessoa = NULL;
	//int count = 0;
	while (!feof(fp) != NULL)
	{
		if (fscanf(fp, "%d;%d;%50[^;];%f\n", &(novaPessoa->id), &(novaPessoa->admin), novaPessoa->nome, &(novaPessoa->saldo)))
		{
			if (listaPessoa == NULL)
			{
				listaPessoa = CriarListaPessoa(listaPessoa, novaPessoa);
				CriarListaPessoaBin(listaPessoa);
			}
			else
			{
				if (VerificarExistePessoa(listaPessoa, novaPessoa) == false)
				{
					listaPessoa = InserirPessoa(listaPessoa, novaPessoa);
				}
			}
		}
		//count++;
	}

	// Fecha o ficheiro
	fclose(fp);

	return listaPessoa;
}

bool VerificarExistePessoa(ListaPessoa* listaPessoa, Pessoa* novaPessoa)
{
	ListaPessoa* aux = malloc(sizeof(ListaPessoa));
	aux = listaPessoa;
	while (aux != NULL)
	{
		if (aux->p.id == novaPessoa->id)
		{
			return true;
		}
		else
		{
			aux = aux->proxima;
		}
	}
	return false;
}

ListaPessoa* CriarListaPessoa(ListaPessoa* listaPessoa, Pessoa* novaPessoa)
{
	ListaPessoa* novoNo = malloc(sizeof(ListaPessoa));

	novoNo->p = *novaPessoa;
	novoNo->proxima = NULL;

	return novoNo;
}

ListaPessoa* InserirPessoa(ListaPessoa* listaPessoa, Pessoa* novaPessoa)
{
	ListaPessoa* novoNo = malloc(sizeof(ListaPessoa)), * aux;

	novoNo->p = *novaPessoa;
	novoNo->proxima = NULL;

	aux = listaPessoa;
	while (aux->proxima)
	{
		aux = aux->proxima;
	}
	aux->proxima = novoNo;

	//Insere a pessoa no ficheiro binario
	InserirListaPessoaBin(novoNo);

	return listaPessoa;
}

/**
 * Cria ficheiro bin�rio e guarda os dados armazenados na lista de Pessoas
 *
 * \param listaPessoa
 * \return
 */
bool CriarListaPessoaBin(ListaPessoa* listaPessoa)
{
	FILE* fp = fopen("listaPessoa.bin", "wb"); // Escreve ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return (false);
	}

	ListaPessoa* aux = listaPessoa;
	while (aux != NULL)
	{
		Pessoa buffer = aux->p;
		fwrite(&buffer, sizeof(Pessoa), 1, fp);
		//printf("%d;%d;%s;%f\n", buffer.id, buffer.admin, buffer.nome, buffer.saldo);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}

bool InserirListaPessoaBin(ListaPessoa* listaPessoa)
{
	FILE* fp = fopen("listaPessoa.bin", "ab"); // Insere no ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return (false);
	}

	ListaPessoa* aux = listaPessoa;
	while (aux != NULL)
	{
		Pessoa buffer = aux->p;
		fwrite(&buffer, sizeof(Pessoa), 1, fp);
		//printf("%d;%d;%s;%f\n", buffer.id, buffer.admin, buffer.nome, buffer.saldo);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}

ListaPessoa* LerListaPessoaBin()
{
	FILE* fp = fopen("listaPessoa.bin", "rb"); // L� ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}

	ListaPessoa* listaAtual = malloc(sizeof(ListaPessoa)), * aux = malloc(sizeof(ListaPessoa));
	listaAtual = NULL;

	while (!feof(fp) != NULL)
	{
		Pessoa* p = malloc(sizeof(Pessoa));
		if (fread(p, sizeof(Pessoa), 1, fp))
		{
			ListaPessoa* proximoNo = malloc(sizeof(ListaPessoa));
			proximoNo->p = *p;
			proximoNo->proxima = NULL;

			if (listaAtual == NULL)
			{
				listaAtual = proximoNo;
			}
			else
			{
				aux = listaAtual;
				while (aux->proxima)
				{
					aux = aux->proxima;
				}
				aux->proxima = proximoNo;
			}
		}
	}
	fclose(fp);

	return listaAtual;
}

bool AlterarListaPessoaBin(Pessoa novosDados)
{
	FILE* fp = fopen("listaPessoa.bin", "rb+"); // L� e altera ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return(false);
	}

	Pessoa* aux = malloc(sizeof(Pessoa));
	long int cursor = ftell(fp);

	while (fread(aux, sizeof(Pessoa), 1, fp))
	{
		if (aux->id == novosDados.id)
		{
			break;
		}
		cursor = ftell(fp);
	}

	fseek(fp, cursor, SEEK_SET);
	fwrite(&novosDados, sizeof(Pessoa), 1, fp);

	fclose(fp);
	//free(aux);

	return true;
}

bool RemoverDadosListaPessoaBin(int id)
{
	FILE* fp = fopen("listaPessoa.bin", "rb"); // L� ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}

	FILE* fp2 = fopen("copiaListaPessoa.bin", "wb"); // Escreve ficheiro bin�rio
	if (fp2 == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}

	Pessoa* aux = malloc(sizeof(Pessoa));
	//long int cursor;

	while (fread(aux, sizeof(Pessoa), 1, fp))
	{
		if (aux->id != id)
		{
			fwrite(aux, sizeof(Pessoa), 1, fp2);
			//printf("%d;%d;%s;%f\n", aux->id, aux->admin, aux->nome, aux->saldo);
		}
		//cursor = ftell(fp);
	}

	fclose(fp);
	fclose(fp2);

	//free(aux);

	remove("listaPessoa.bin");

	if (rename("copiaListaPessoa.bin", "listaPessoa.bin") != 0)
	{
		printf("Erro ao renomear arquivo de sa�da");
		return(false);
	}

	return true;
}

bool ListarPessoaBin()
{
	int tamanho = 1, i = 0;
	Pessoa* vetorPessoa = malloc(tamanho * sizeof(Pessoa));
	ListaPessoa* listaAtual = LerListaPessoaBin();

	if (vetorPessoa != NULL) {
		//printf("Mem�ria alocada com sucesso.\n");
		while (listaAtual != NULL)
		{
			if (i >= tamanho)
			{
				int novoTamanho = i + 1;
				vetorPessoa = (Pessoa*)realloc(vetorPessoa, novoTamanho * sizeof(Pessoa));
				if (vetorPessoa == NULL) {
					printf("Erro: n�o foi poss�vel realocar mem�ria.\n");
					exit(1);
				}
				tamanho = novoTamanho;
			}
			vetorPessoa[i] = listaAtual->p;
			listaAtual = listaAtual->proxima;
			i++;
		}
	}
	else
	{
		printf("Erro: n�o foi poss�vel alocar mem�ria.\n");
		return false;
	}

	for (int j = 0; j < tamanho; j++)
	{
		printf("%d;%d;%s;%f;\n", vetorPessoa[j].id, vetorPessoa[j].admin, vetorPessoa[j].nome, vetorPessoa[j].saldo);
	}

	return true;
}