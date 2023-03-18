/*****************************************************************//**
 * \file   main.c
 * \brief  Função principal da aplicação que gerencia o aluguer de meios de mobilidade
 * 
 * \author Arthur Fellipe
 * \date   March 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "dados.h"
#include "pessoas.h"
#include "veiculos.h"
#include "viagens.h"
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
	RemoverDadosListaPessoaBin(2);
	ListarPessoaBin();
	ListaPessoa* listaPessoaAtual = LerListaPessoaBin();
#pragma endregion

#pragma region Veiculo
	ListaVeiculo* listaVeiculo = LerFicheiroVeiculoTxt();

	Veiculo novosDadosVeiculo;
	novosDadosVeiculo.id = 3;
	strcpy(novosDadosVeiculo.tipoVeiculo, "trotineta");
	novosDadosVeiculo.bateria = 38;
	strcpy(novosDadosVeiculo.localizacao, "braga");
	novosDadosVeiculo.custo = 2.00;
	novosDadosVeiculo.disponibilidade = 1;

	AlterarListaVeiculoBin(novosDadosVeiculo);
	RemoverDadosListaVeiculoBin(2);
	ListaVeiculo* listaVeiculoAtual = LerListaVeiculoBin();
	ListarVeiculoOrdemDecrescente();
	ListarVeiculoLocalizacao("braga");

#pragma endregion

#pragma region Viagem
	ListaViagem* listaViagem = malloc(sizeof(ListaViagem));
	listaViagem = NULL;
	
	listaViagem = RegistarViagem(listaViagem, 1, novosDadosPessoa, novosDadosVeiculo, 5, 3);
	listaViagem = RegistarViagem(listaViagem, 2, novosDadosPessoa, novosDadosVeiculo, 7.50, 1.5);
#pragma endregion


	return (1);
}
