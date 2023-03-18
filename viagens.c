/*****************************************************************//**
 * \file   viagens.c
 * \brief  
 * 
 * \author Arthur Fellipe
 * \date   March 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dados.h"
#include "viagens.h"
#include "pessoas.h"


ListaViagem* RegistarViagem(ListaViagem* listaViagem, int id, Pessoa cliente, Veiculo veiculo, float precoViagem, float distanciaViagem)
{
	Viagem* novaViagem = malloc(sizeof(Viagem));

	novaViagem->id = id;
	novaViagem->cliente = cliente;
	novaViagem->veiculo = veiculo;
	novaViagem->precoViagem = precoViagem;
	novaViagem->distanciaViagem = distanciaViagem;

	//ListaViagem* listaViagem = malloc(sizeof(ListaViagem));
	//listaViagem = NULL;

	if (listaViagem == NULL)
	{
		listaViagem = CriarListaViagem(listaViagem, novaViagem);
		//CriarListaViagemBin(listaViagem);
	}
	else
	{
		if (VerificarExisteViagem(listaViagem, novaViagem) == false)
		{
			listaViagem = InserirViagem(listaViagem, novaViagem);
		}
	}

	Pessoa clienteAtualizado = cliente;
	clienteAtualizado.saldo = clienteAtualizado.saldo - novaViagem->precoViagem;
	 
	AlterarListaPessoaBin(clienteAtualizado);

	return listaViagem;
}

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

ListaViagem* CriarListaViagem(ListaViagem* listaViagem, Viagem* novaViagem)
{
	ListaViagem* novoNo = malloc(sizeof(ListaViagem));

	novoNo->viagem = *novaViagem;
	novoNo->proxima = NULL;

	return novoNo;
}

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

	//Insere a pessoa no ficheiro binario
	//InserirListaPessoaBin(novoNo);

	return listaViagem;
}


/*Aluguer* criarAluguer(Cliente* inicioC, Aluguer* inicioA, int id, int idMeio, int idCliente, float custo)
{
	Aluguer* novoAluguer = (Aluguer*)malloc(sizeof(Aluguer));

	if (novoAluguer == NULL) return NULL;
	novoAluguer->proximo = NULL;

	novoAluguer->id = id;
	novoAluguer->idMeio = idMeio;
	novoAluguer->idCliente = idCliente;
	novoAluguer->custo = custo;

	if (inicioA == NULL) {
		inicioA = novoAluguer;
	}
	else {
		novoAluguer->proximo = inicioA;
		inicioA = novoAluguer;
	}

	Cliente* clienteUtente = buscarCliente(inicioC, idCliente);
	int identificador = clienteUtente->id;
	float novoSaldo = clienteUtente->saldo - novoAluguer->custo;

	alterarCliente(inicioC, identificador, clienteUtente->id, clienteUtente->nome, clienteUtente->nif, clienteUtente->morada, novoSaldo);

	return novoAluguer;
}*/