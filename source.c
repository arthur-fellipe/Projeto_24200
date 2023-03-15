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

/*void lerDados(FILE* fp, Pessoa* leituraPessoa)
{
	while (!feof(fp))
	{
		fscanf(fp, "%d;%d;%50[^;];%f;\n", &(leituraPessoa->id), &(leituraPessoa->admin), leituraPessoa->nome, &(leituraPessoa->saldo));
	}
}*/

NoPessoa* leituraFicheiro(Pessoa *ptr)
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
	NoPessoa *listaPessoa = (NoPessoa*)malloc(sizeof(NoPessoa));

	//lerDados(fp, novaPessoa);
	//novo = ptr;
	while (!feof(fp))
	{
		fscanf(fp, "%d;%d;%50[^;];%f;\n", &(ptr->id), &(ptr->admin), ptr->nome, &(ptr->saldo));
		listaPessoa = InserePessoa(&listaPessoa, ptr);
	}

	// Fecha o ficheiro
	fclose(fp);
	return listaPessoa;
}


/*NoPessoa* criaNoPessoa(Pessoa* nPessoa)
{
	NoPessoa* novo = malloc(sizeof(NoPessoa));
	novo->p = *nPessoa;
	novo->proxima = NULL;

	return novo;
}*/

NoPessoa* InserePessoa(NoPessoa **lista, Pessoa* nPessoa)
{
	NoPessoa *novoNo = malloc(sizeof(NoPessoa));
	
	if (novoNo != NULL)
	{
		novoNo->p = *nPessoa;
		novoNo->proxima = *lista;
		return novoNo;
	}
	else return(lista);
	/* {
		NoPessoa* listaAtual = *lista;
		while (listaAtual->proxima != NULL)
		{
			listaAtual = listaAtual->proxima;
		}
		listaAtual->proxima = nPessoa;
	}*/
}

/*bool InserePessoaLista(NoPessoa** lista, Pessoa* novaPessoa)
{
	//Pessoa *novaPessoa;
	bool aux = false;
	NoPessoa* auxLista = *lista;
	/*while (fscanf(fp, "%d;%d;%50[^;];%f;\n", &(novaPessoa->id), &(novaPessoa->admin), novaPessoa->nome, &(novaPessoa->saldo) == 4)) {
		NoPessoa* novoNo = create_node(novaPessoa);
		aux = InserePessoa(&lista, novoNo);
	}
	NoPessoa* novoNo = criaNoPessoa(novaPessoa);
	aux = InserePessoa(auxLista, novoNo);
	
	return aux;
}*/