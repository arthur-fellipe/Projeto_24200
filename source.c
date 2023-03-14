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

Pessoa* CriaPessoa(int id, bool admin, char nome[], float saldo)
{
	Pessoa* novaPessoa = (Pessoa*) malloc(sizeof(Pessoa));

	novaPessoa->id = id;
	novaPessoa->admin = admin;
	strcpy(novaPessoa->nome, nome);
	//strcpy(novaPessoa->nif, nif);
	//strcpy(novaPessoa->morada, morada);
	novaPessoa->saldo = saldo;

	return (novaPessoa);
}

bool InserePessoa(NoPessoa **lista, Pessoa* novaPessoa)
{
	NoPessoa *novo = malloc(sizeof(NoPessoa));
	
	if (novo) {
		novo->p = *novaPessoa;
		novo->proxima = *lista;
		*lista = novo;
		return true;
	}
	else {
		printf("Erro ao alocar memória\n");
	}
	return false;
}
