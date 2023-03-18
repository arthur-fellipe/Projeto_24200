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
#include "dados.h"

#pragma once
ListaPessoa* LerFicheiroPessoaTxt();
bool VerificarExistePessoa(ListaPessoa* listaPessoa, Pessoa* novaPessoa);
ListaPessoa* CriarListaPessoa(ListaPessoa* listaPessoa, Pessoa* nPessoa);
ListaPessoa* InserirPessoa(ListaPessoa* listaPessoa, Pessoa* nPessoa);
bool CriarListaPessoaBin(ListaPessoa* listaPessoa);
bool InserirListaPessoaBin(ListaPessoa* listaPessoa);
ListaPessoa* LerListaPessoaBin();
bool AlterarListaPessoaBin(Pessoa novosDados);
bool RemoverDadosListaPessoaBin(int id);
bool ListarPessoaBin();
