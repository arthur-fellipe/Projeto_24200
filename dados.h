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
	float saldo;
}Pessoa;

typedef struct ListaPessoa
{
	Pessoa p;
	struct ListaPessoa* proxima;
}ListaPessoa;
#pragma endregion

#pragma region Veiculo
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
#pragma endregion

#pragma region Viagem
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
#pragma endregion

