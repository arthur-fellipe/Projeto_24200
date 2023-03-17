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

	NoPessoa* listaPessoa = leituraFicheiro();
	// Cria ficheiro binário e guarda os dados obtidos no ficheiro .txt
	guardaListaPessoaBin(listaPessoa);
	lerListaPessoaBin();
	return (1);
}
