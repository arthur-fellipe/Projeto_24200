/*****************************************************************//**
 * \file   main.c
 * \brief  
 * 
 * \author Arthur Fellipe
 * \date   March 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "dados.h"
#include "pessoas.h"
#include "veiculos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int main()
{
	#pragma region Pessoa
	ListaPessoa* listaPessoa = LerFicheiroPessoaTxt();

	Pessoa novosDadosPessoa;
	novosDadosPessoa.id = 3;
	novosDadosPessoa.admin = 0;
	strcpy(novosDadosPessoa.nome, "Joao");
	novosDadosPessoa.saldo = 57.50;

	AlterarListaPessoaBin(novosDadosPessoa);
	LerListaPessoaBin();
	RemoverDadosListaPessoaBin(3);
	ListarPessoaBin();
	#pragma endregion

#pragma region Veiculo
	ListaVeiculo* listaVeiculo = LerFicheiroVeiculoTxt();

	Veiculo novosDadosVeiculo;
	novosDadosVeiculo.id = 3;
	strcpy(novosDadosVeiculo.tipoVeiculo, "trotineta");
	novosDadosVeiculo.bateria = 38;
	strcpy(novosDadosVeiculo.localizacao, "barco-mar-peixe");
	novosDadosVeiculo.custo = 2.00;
	novosDadosVeiculo.disponibilidade = 1;

	AlterarListaVeiculoBin(novosDadosVeiculo);
	LerListaVeiculoBin();
	RemoverDadosListaVeiculoBin(2);
	ListarVeiculoBin();
#pragma endregion


	return (1);
}
