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
		CriarListaViagemBin(listaViagem);
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

	
	InserirListaViagemBin(novoNo); //Insere a pessoa no ficheiro binario

	return listaViagem;
}

/**
 * Cria ficheiro binário e guarda os dados armazenados na lista de Viagens
 *
 * \param listaViagem
 * \return
 */
bool CriarListaViagemBin(ListaViagem* listaViagem)
{
	FILE* fp = fopen("listaViagem.bin", "wb"); // Escreve ficheiro binário
	if (fp == NULL)
	{
		return (false);
	}

	ListaViagem* aux = listaViagem;
	while (aux != NULL)
	{
		Viagem buffer = aux->viagem;
		fwrite(&buffer, sizeof(Viagem), 1, fp);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}

/**
 * Insere viagens no fichiro binário.
 *
 * \param listaViagem
 * \return
 */
bool InserirListaViagemBin(ListaViagem* listaViagem)
{
	FILE* fp = fopen("listaViagem.bin", "ab"); // Insere no ficheiro binário
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return (false);
	}

	ListaViagem* aux = listaViagem;
	while (aux != NULL)
	{
		Viagem buffer = aux->viagem;
		fwrite(&buffer, sizeof(Viagem), 1, fp);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}

/**
 * Lê o ficheiro binário que armazena as viagens e retorna uma lista atualizada.
 *
 * \return listaAtual
 */
ListaViagem* LerListaViagemBin()
{
	FILE* fp = fopen("listaViagem.bin", "rb"); // Lê ficheiro binário
	if (fp == NULL)
	{
		return NULL;
	}

	ListaViagem* listaAtual = malloc(sizeof(ListaViagem)), * aux = malloc(sizeof(ListaViagem));
	listaAtual = NULL;

	while (!feof(fp) != NULL)
	{
		Viagem* viagem = malloc(sizeof(Viagem));
		if (fread(viagem, sizeof(Viagem), 1, fp))
		{
			ListaViagem* proximoNo = malloc(sizeof(ListaViagem));
			proximoNo->viagem = *viagem;
			proximoNo->proxima = NULL;

			if (listaAtual == NULL)
			{
				listaAtual = proximoNo;
			}
			else
			{
				aux = listaAtual;
				while (aux->proxima)
				{
					aux = aux->proxima;
				}
				aux->proxima = proximoNo;
			}
		}
	}
	fclose(fp);

	return listaAtual;
}

/**
 * Altera dados dentro do ficheiro binário.
 *
 * \param novosDados
 * \return
 */
bool AlterarListaViagemBin(Viagem novosDados)
{
	FILE* fp = fopen("listaViagem.bin", "rb+"); // Lê e altera ficheiro binário
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return(false);
	}

	Viagem* aux = malloc(sizeof(Viagem));
	long int cursor = ftell(fp);

	while (fread(aux, sizeof(Viagem), 1, fp))
	{
		if (aux->id == novosDados.id)
		{
			break;
		}
		cursor = ftell(fp);
	}

	fseek(fp, cursor, SEEK_SET);
	fwrite(&novosDados, sizeof(Viagem), 1, fp);

	fclose(fp);

	return true;
}

/**
 * Remove o registo de um veículo do ficheiro binário.
 *
 * \param id
 * \return
 */
bool RemoverDadosListaViagemBin(int id)
{
	FILE* fp = fopen("listaViagem.bin", "rb"); // Lê ficheiro binário
	if (fp == NULL)
	{
		return false;
	}

	FILE* fp2 = fopen("copiaListaViagem.bin", "wb"); // Escreve ficheiro binário
	if (fp2 == NULL)
	{
		return false;
	}

	Viagem* aux = malloc(sizeof(Viagem));

	while (fread(aux, sizeof(Viagem), 1, fp))
	{
		if (aux->id != id)
		{
			fwrite(aux, sizeof(Viagem), 1, fp2);
		}
	}

	fclose(fp);
	fclose(fp2);

	remove("listaViagem.bin");

	if (rename("copiaListaViagem.bin", "listaViagem.bin") != 0)
	{
		return(false);
	}

	return true;
}