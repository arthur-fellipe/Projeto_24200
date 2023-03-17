/*****************************************************************//**
 * \file   source.c
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
#include "Header.h"

/*void lerDados(FILE* fp, Pessoa* leituraPessoa)
{
	while (!feof(fp))
	{
		fscanf(fp, "%d;%d;%50[^;];%f;\n", &(leituraPessoa->id), &(leituraPessoa->admin), leituraPessoa->nome, &(leituraPessoa->saldo));
	}
}*/

/**
 * Cria ficheiro binário e guarda os dados armazenados na lista de Pessoas
 * 
 * \param listaPessoa
 * \return 
 */
/*bool guardaListaPessoaBin(NoPessoa* listaPessoa)
{
	FILE* fp = fopen("listaPessoa.bin", "wb"); // Escreve ficheiro binário
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return (false);
	}

	NoPessoa* aux = listaPessoa;
	char buffer[1024];
	while (aux != NULL)
	{
		sprintf(buffer, "%d;%d;%s;%f;\n", aux->p.id, aux->p.admin, aux->p.nome, aux->p.saldo);
		fwrite(buffer, sizeof(strlen(buffer)), 1, fp);
		printf("%s", buffer);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}*/

NoPessoa* leituraFicheiro()
{

	// Abre o ficheiro com os dados
	FILE* fp = fopen("pessoas.txt", "r");

	// Verifica se o arquivo foi aberto com sucesso
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}
	// Lê os dados do ficheiro
	Pessoa* ptr = malloc(sizeof(Pessoa));
	NoPessoa *listaPessoa = NULL;
	int count = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%d;%d;%50[^;];%f;\n", &(ptr->id), &(ptr->admin), ptr->nome, &(ptr->saldo));
		listaPessoa = InserePessoa(listaPessoa, ptr);
		count++;
	}

	// Fecha o ficheiro
	fclose(fp);
	
	return listaPessoa;
}

NoPessoa* InserePessoa(NoPessoa *listaPessoa, Pessoa* nPessoa)
{
	NoPessoa *novoNo = malloc(sizeof(NoPessoa)), *aux;
	
	novoNo->p = *nPessoa;
	novoNo->proxima = NULL;

	if (listaPessoa == NULL)
	{
		listaPessoa = novoNo;
	}
	else
	{
		aux = listaPessoa;
		while (aux->proxima)
		{
			aux = aux->proxima;
		}
		aux->proxima = novoNo;
	}


	return listaPessoa;
}

bool guardaListaPessoaBin(NoPessoa* listaPessoa)
{
	FILE* fp = fopen("listaPessoa.bin", "wb"); // Escreve ficheiro binário
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return (false);
	}

	NoPessoa* aux = listaPessoa;
	while (aux != NULL)
	{
		Pessoa buffer = aux->p;
		fwrite(&buffer, sizeof(Pessoa), 1, fp);
		//printf("%d;%d;%s;%f;\n", buffer.id, buffer.admin, buffer.nome, buffer.saldo);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}

NoPessoa* lerListaPessoaBin()
{
	FILE* fp = fopen("listaPessoa.bin", "rb"); // Lê ficheiro binário
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}

	NoPessoa* listaAtual = malloc(sizeof(NoPessoa));
	listaAtual = NULL;

	while(!feof(fp))		
	{	
		Pessoa* p = malloc(sizeof(Pessoa));
		fread(p, sizeof(Pessoa), 1, fp);

		NoPessoa* primeiroNo = malloc(sizeof(NoPessoa)), *proximoNo;
		primeiroNo->p = *p;
		primeiroNo->proxima = NULL;
		if (listaAtual == NULL)
		{
			listaAtual = primeiroNo;
		}
		else
		{
			proximoNo = listaAtual;
			while (proximoNo->proxima)
			{
				proximoNo = proximoNo->proxima;
			}
			proximoNo->proxima = primeiroNo;
		}

	}
	return listaAtual;
}
