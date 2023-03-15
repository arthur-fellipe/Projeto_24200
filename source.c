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

/*Pessoa* CriaPessoa()
{
	Pessoa* novaPessoa = malloc(sizeof(Pessoa));

	novaPessoa = leituraFicheiro();
	novaPessoa->id = id;
	novaPessoa->admin = admin;
	strcpy(novaPessoa->nome, nome);
	//strcpy(novaPessoa->nif, nif);
	//strcpy(novaPessoa->morada, morada);
	novaPessoa->saldo = saldo;

	return (novaPessoa);
}*/

void lerDados(FILE *fp, Pessoa *leituraPessoa)
{
	while (!feof(fp))
	{
		fscanf(fp, "%d;%d;%50[^;];%f;\n", &(leituraPessoa->id), &(leituraPessoa->admin), leituraPessoa->nome, &(leituraPessoa->saldo));
	}
}

Pessoa* leituraFicheiro(Pessoa *ptr)
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
	Pessoa *novaPessoa = (Pessoa*) malloc(sizeof(Pessoa));

	lerDados(fp, novaPessoa);
	//novo = ptr;
	/*while (!feof(fp))
	{
		fscanf(fp, "%d;%d;%50[^;];%f;\n", &(novaPessoa->id), &(novaPessoa->admin), novaPessoa->nome, &(novaPessoa->saldo));
	}*/

	// Fecha o ficheiro
	fclose(fp);
	return novaPessoa;
}


NoPessoa* criaNoPessoa(Pessoa* nPessoa)
{
	NoPessoa* novo = malloc(sizeof(NoPessoa));
	novo->p = *nPessoa;
	novo->proxima = NULL;

	return novo;
}

bool InserePessoa(NoPessoa **lista, Pessoa* nPessoa)
{
	//NoPessoa *novo = malloc(sizeof(NoPessoa));
	
	if (*lista == NULL) 
	{
		*lista = nPessoa;
		return false;
	}
	else 
	{
		NoPessoa* atual = *lista;
		while (atual->proxima != NULL)
		{
			atual = atual->proxima;
		}
		atual->proxima = nPessoa;
	}

	return true;
}