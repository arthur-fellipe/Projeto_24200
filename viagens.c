/*****************************************************************//**
 * \file   viagens.c
 * \brief  Funções que modularizam o tratamento das viagens realizadas
 * 
 * \author Arthur Fellipe
 * \date   March 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "viagens.h"
#include "pessoas.h"

/**
 * Regista a viagem realizada por certo usuário, atualizando o seu saldo.
 * 
 * \param listaViagem
 * \param id
 * \param cliente
 * \param veiculo
 * \param precoViagem
 * \param distanciaViagem
 * \return 
 */
ListaViagem* RegistarViagem(ListaViagem* listaViagem, int id, int cliente_id, int veiculo_id, float precoViagem, float distanciaViagem)
{
	Viagem* novaViagem = malloc(sizeof(Viagem));
	if (novaViagem == NULL) return NULL;
	novaViagem->id = id;
	novaViagem->cliente_id = cliente_id;
	novaViagem->veiculo_id = veiculo_id;
	novaViagem->precoViagem = precoViagem;
	novaViagem->distanciaViagem = distanciaViagem;

	if (listaViagem == NULL)
	{
		listaViagem = CriarListaViagem(listaViagem, novaViagem); //Chama função para criar a lista de viagens
		//CriarListaViagemBin(listaViagem);
	}
	else
	{
		if (VerificarExisteViagem(listaViagem, novaViagem) == false) //Verifica se já existe a viagem dentro da lista
		{
			listaViagem = InserirViagem(listaViagem, novaViagem); //Insere nova viagem em lista já existente
		}
	}

	/*Pessoa clienteAtualizado = cliente;
	clienteAtualizado.saldo = clienteAtualizado.saldo - novaViagem->precoViagem;
	 
	AlterarListaPessoaBin(clienteAtualizado); //Atualiza o saldo do cliente que realizou a viagem*/

	return listaViagem;
}

/**
 * Verifica se já existe a viagem dentro da lista.
 * 
 * \param listaViagem
 * \param novaViagem
 * \return 
 */
bool VerificarExisteViagem(ListaViagem* listaViagem, Viagem* novaViagem)
{
	ListaViagem* aux = malloc(sizeof(ListaViagem));
	aux = listaViagem;
	while (aux != NULL)
	{
		if (aux->viagem.id == novaViagem->id)
		{
			return true;
		}
		else
		{
			aux = aux->proxima;
		}
	}
	return false;
}

/**
 * Cria lista de viagens.
 * 
 * \param listaViagem
 * \param novaViagem
 * \return 
 */
ListaViagem* CriarListaViagem(ListaViagem* listaViagem, Viagem* novaViagem)
{
	ListaViagem* novoNo = malloc(sizeof(ListaViagem));

	novoNo->viagem = *novaViagem;
	novoNo->proxima = NULL;

	return novoNo;
}

/**
 * Insere viagens na lista.
 * 
 * \param listaViagem
 * \param novaViagem
 * \return 
 */
ListaViagem* InserirViagem(ListaViagem* listaViagem, Viagem* novaViagem)
{
	ListaViagem* novoNo = malloc(sizeof(ListaViagem)), * aux;

	novoNo->viagem = *novaViagem;
	novoNo->proxima = NULL;

	aux = listaViagem;
	while (aux->proxima)
	{
		aux = aux->proxima;
	}
	aux->proxima = novoNo;

	
	//InserirListaViagemBin(novoNo); //Insere a pessoa no ficheiro binario

	return listaViagem;
}