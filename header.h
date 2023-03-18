/*****************************************************************//**
 * \file   header.h
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
typedef struct Pessoa
{
	int id;
	int admin;
	char nome[50];
	//char nif[9];
	//char morada[100];
	float saldo;
}Pessoa;

typedef struct ListaPessoa
{
	Pessoa p;
	struct ListaPessoa *proxima;
}ListaPessoa;

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

typedef struct Veiculo
{
	int id;
	char tipoVeiculo[20];
	int bateria;
	char localizacao[40];
	float custo;
	int disponibilidade;
	//int totalViagens;
}Veiculo;

typedef struct ListaVeiculo
{
	Veiculo v;
	struct ListaVeiculo* proxima;
}ListaVeiculo;

/*typedef struct Viagem
{
	int id;
	Pessoa cliente;
	Veiculo veiculo;
	float precoViagem;
}Viagem, *ViagemPtr;

typedef struct ViagensOrdemCrescente
{
	Viagem OrdemCrescente[100];
}ViagensOrdemCrescente, *ViagensOrdemCrescente;*/

