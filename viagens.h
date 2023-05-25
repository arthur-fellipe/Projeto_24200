/*****************************************************************//**
 * \file   viagens.h
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
#pragma region Viagem
typedef struct Viagem
{
	int id;
	int cliente_id;
	int veiculo_id;
	float precoViagem;
	float distanciaViagem;
}Viagem;

typedef struct ListaViagem
{
	Viagem viagem;
	struct ListaViagem* proxima;
}ListaViagem;
#pragma endregion

#pragma region Funções Viagem
ListaViagem* RegistarViagem(ListaViagem* listaViagem, int id, int cliente_id, int veiculo_id, float precoViagem, float distanciaViagem);
bool VerificarExisteViagem(ListaViagem* listaViagem, Viagem* novaViagem);
ListaViagem* CriarListaViagem(ListaViagem* listaViagem, Viagem* novaViagem);
ListaViagem* InserirViagem(ListaViagem* listaViagem, Viagem* novaViagem);
#pragma endregion