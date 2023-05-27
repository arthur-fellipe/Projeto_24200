/*****************************************************************//**
 * \file   pessoas.h
 * \brief
 *
 * \author Arthur Fellipe
 * \date   March 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#pragma once

#pragma region Pessoa
typedef struct Pessoa
{
	int id;
	int admin;
	char nome[50];
	//char nif[9];
	//char morada[100];
	char localizacao[40];
	float saldo;
}Pessoa;

typedef struct ListaPessoa
{
	Pessoa p;
	struct ListaPessoa* proxima;
}ListaPessoa;
#pragma endregion

#pragma region Funções Pessoa
ListaPessoa* LerFicheiroPessoaTxt();
bool VerificarExistePessoa(ListaPessoa* listaPessoa, Pessoa* novaPessoa);
ListaPessoa* CriarListaPessoa();
ListaPessoa* InserirPessoa(ListaPessoa* listaPessoa, Pessoa* nPessoa);
bool CriarListaPessoaBin(ListaPessoa* listaPessoa);
bool InserirListaPessoaBin(ListaPessoa* listaPessoa);
ListaPessoa* LerListaPessoaBin();
bool AlterarListaPessoaBin(Pessoa novosDados);
bool RemoverDadosListaPessoaBin(int id);
bool ListarPessoaBin();
#pragma endregion
