/*****************************************************************//**
 * \file   pessoas.c
 * \brief  Funções que modularizam o tratamento dos utilizadores da aplicação 
 * 
 * \author Arthur Fellipe
 * \date   March 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pessoas.h"

/**
 * Lê o ficheiro que contem as informações dos utilizadores e armazena esses dados em uma lista.
 * 
 * \return
 */
ListaPessoa* LerFicheiroPessoaTxt()
{

	// Abre o ficheiro com os dados
	FILE* fp = fopen("pessoas.txt", "r");

	// Verifica se o ficheiro foi aberto com sucesso
	if (fp == NULL)
	{
		 printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}
	// Lê os dados do ficheiro
	Pessoa* novaPessoa = malloc(sizeof(Pessoa));
	ListaPessoa* listaPessoa = CriarListaPessoa(); //Chama função para criar a lista de pessoas
	CriarListaPessoaBin(listaPessoa); //Cria ficheiro binário para armazenar a lista de pessoas
	while (!feof(fp) != NULL)
	{
		if (fscanf(fp, "%d;%d;%50[^;];%40[^;];%f\n", &(novaPessoa->id), &(novaPessoa->admin), novaPessoa->nome, novaPessoa->localizacao, &(novaPessoa->saldo)))
		{
			if (VerificarExistePessoa(listaPessoa, novaPessoa) == false) //Verifica se já existe a pessoa dentro da lista
			{
				listaPessoa = InserirPessoa(listaPessoa, novaPessoa); //Insere nova pessoa em lista já existente
			}
		}
	}
	InserirListaPessoaBin(listaPessoa); //Insere a lista no ficheiro binario

	// Fecha o ficheiro
	fclose(fp);

	return listaPessoa;
}

/**
 * Verifica se já existe a pessoa dentro da lista.
 * 
 * \param listaPessoa
 * \param novaPessoa
 * \return 
 */
bool VerificarExistePessoa(ListaPessoa* listaPessoa, Pessoa* novaPessoa)
{
	ListaPessoa* aux = malloc(sizeof(ListaPessoa));
	aux = listaPessoa;
	while (aux != NULL)
	{
		if (aux->p.id == novaPessoa->id)
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
 * Cria lista de pessoas.
 * 
 * \param listaPessoa
 * \param novaPessoa
 * \return listaPessoa
 */
ListaPessoa* CriarListaPessoa()
{
	ListaPessoa* listaPessoa = NULL;
	return listaPessoa;
}

/**
 * Insere pessoas na lista.
 * 
 * \param listaPessoa
 * \param novaPessoa
 * \return listaPessoa
 */
ListaPessoa* InserirPessoa(ListaPessoa* listaPessoa, Pessoa* novaPessoa)
{
	ListaPessoa* novoNo = malloc(sizeof(ListaPessoa)), * aux;

	novoNo->p = *novaPessoa;
	novoNo->proxima = NULL;

	if (listaPessoa == NULL)
	{
		listaPessoa = novoNo;
	}
	else
	{
		aux = listaPessoa;
		while (aux->proxima)
		{
			aux = aux->proxima;
		}
		aux->proxima = novoNo;
	}
	
	return listaPessoa;
}

/**
 * Cria ficheiro binário e guarda os dados armazenados na lista de Pessoas
 *
 * \param listaPessoa
 * \return
 */
bool CriarListaPessoaBin(ListaPessoa* listaPessoa)
{
	FILE* fp = fopen("listaPessoa.bin", "wb"); // Escreve ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return (false);
	}

	ListaPessoa* aux = listaPessoa;
	while (aux != NULL)
	{
		Pessoa buffer = aux->p;
		fwrite(&buffer, sizeof(Pessoa), 1, fp);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}

/**
 * Insere pessoas no ficheiro binário.
 * 
 * \param listaPessoa
 * \return 
 */
bool InserirListaPessoaBin(ListaPessoa* listaPessoa)
{
	FILE* fp = fopen("listaPessoa.bin", "ab"); // Insere no ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return (false);
	}

	ListaPessoa* aux = listaPessoa;
	while (aux != NULL)
	{
		Pessoa buffer = aux->p;
		fwrite(&buffer, sizeof(Pessoa), 1, fp);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}

/**
 * Lê o ficheiro binário que armazena as pessoas e retorna uma lista atualizada.
 * 
 * \return listaAtual
 */
ListaPessoa* LerListaPessoaBin()
{
	FILE* fp = fopen("listaPessoa.bin", "rb"); // Lê ficheiro binário
	if (fp == NULL)
	{
		return NULL;
	}

	ListaPessoa* listaAtual = malloc(sizeof(ListaPessoa)), * aux = malloc(sizeof(ListaPessoa));
	listaAtual = NULL;

	while (!feof(fp) != NULL)
	{
		Pessoa* p = malloc(sizeof(Pessoa));
		if (fread(p, sizeof(Pessoa), 1, fp))
		{
			ListaPessoa* proximoNo = malloc(sizeof(ListaPessoa));
			proximoNo->p = *p;
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
bool AlterarListaPessoaBin(Pessoa novosDados)
{
	FILE* fp = fopen("listaPessoa.bin", "rb+"); // Lê e altera ficheiro binário
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return(false);
	}

	Pessoa* aux = malloc(sizeof(Pessoa));
	long int cursor = ftell(fp);

	while (fread(aux, sizeof(Pessoa), 1, fp))
	{
		if (aux->id == novosDados.id)
		{
			break;
		}
		cursor = ftell(fp);
	}

	fseek(fp, cursor, SEEK_SET);
	fwrite(&novosDados, sizeof(Pessoa), 1, fp);

	fclose(fp);

	return true;
}

/**
 * Remove o registo de uma pessoa do ficheiro binário.
 * 
 * \param id
 * \return 
 */
bool RemoverDadosListaPessoaBin(int id)
{
	FILE* fp = fopen("listaPessoa.bin", "rb"); // Lê ficheiro binário
	if (fp == NULL)
	{
		return false;
	}

	FILE* fp2 = fopen("copiaListaPessoa.bin", "wb"); // Escreve ficheiro bin�rio
	if (fp2 == NULL)
	{
		return false;
	}

	Pessoa* aux = malloc(sizeof(Pessoa));

	while (fread(aux, sizeof(Pessoa), 1, fp))
	{
		if (aux->id != id)
		{
			fwrite(aux, sizeof(Pessoa), 1, fp2);
		}
	}

	fclose(fp);
	fclose(fp2);

	remove("listaPessoa.bin");

	if (rename("copiaListaPessoa.bin", "listaPessoa.bin") != 0)
	{
		return(false);
	}
	return true;
}

/**
 * Lista as pessoas registadas no ficheiro binário.
 * 
 * \return 
 */
bool ListarPessoaBin()
{
	int tamanho = 1, i = 0;
	Pessoa* vetorPessoa = malloc(tamanho * sizeof(Pessoa));
	ListaPessoa* listaAtual = LerListaPessoaBin(); //Armazena as pessoas do ficheiro binário em uma lista

	if (vetorPessoa != NULL) {
		while (listaAtual != NULL)
		{
			if (i >= tamanho)
			{
				int novoTamanho = i + 1;
				vetorPessoa = (Pessoa*)realloc(vetorPessoa, novoTamanho * sizeof(Pessoa));
				if (vetorPessoa == NULL) {
					return false;
				}
				tamanho = novoTamanho;
			}
			vetorPessoa[i] = listaAtual->p;
			listaAtual = listaAtual->proxima;
			i++;
		}
	}
	else
	{
		printf("Erro: não foi possível alocar memória.\n");
		return false;
	}

	for (int j = 0; j < tamanho; j++)
	{
		printf("%d;%d;%s;%s;%f;\n", vetorPessoa[j].id, vetorPessoa[j].admin, vetorPessoa[j].nome, vetorPessoa[j].localizacao, vetorPessoa[j].saldo);
	}

	return true;
}
