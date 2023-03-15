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
}Pessoa, * PessoaPtr;

typedef struct NoPessoa
{
	Pessoa p;
	struct NoPessoa *proxima;
}NoPessoa, * NoPessoaPtr;

//Pessoa* CriaPessoa();
//void lerDados(FILE *fp, Pessoa *leituraPessoa);
Pessoa* leituraFicheiro(Pessoa *ptr);
NoPessoa* criaNoPessoa(Pessoa* nPessoa);
bool InserePessoa(NoPessoa **lista, Pessoa* nPessoa);
/*typedef struct Veiculo
{
	int id;
	char tipoVeiculo[20];
	int bateria;
	char localizacao[40];
	float custo;
	int disponibilidade;
	int totalViagens;
}Veiculo, *VeiculoPtr;

typedef struct Viagem
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

