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

	int id = 1;
	bool admin = true;
	char nome[50] = "Rui";
	//strcpy(p.nif, "11111111");
	//strcpy(p.morada, "Rua A, 25");
	float saldo = 100.00;

	Pessoa* p = CriaPessoa(id, admin, nome, saldo);
	
	NoPessoa* lista = NULL; 

	InserePessoa(&lista, p);

	return (1);
}
