/*****************************************************************//**
 * \file   main.c
 * \brief  
 * 
 * \author Arthur Fellipe
 * \date   March 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int main()
{

	ListaPessoa* listaPessoa = LerFicheiroTxt();

	Pessoa novosDados;
	novosDados.id = 3;
	novosDados.admin = 0;
	strcpy(novosDados.nome, "Joao");
	novosDados.saldo = 57.50;

	AlterarListaPessoaBin(novosDados);
	LerListaPessoaBin();
	RemoverDadosListaPessoaBin(3);
	ListarPessoaBin();

	return (1);
}
