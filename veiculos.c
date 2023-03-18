/*****************************************************************//**
 * \file   veiculos.c
 * \brief  Fun��es que modularizam o tratamento dos ve�culos a serem alugados
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
#include "veiculos.h"

/**
 *  L� o ficheiro que contem as informa��es dos ve�culos e armazena esses dados em uma lista.
 * 
 * \return
 */
ListaVeiculo* LerFicheiroVeiculoTxt()
{

	// Abre o ficheiro com os dados
	FILE* fp = fopen("veiculos.txt", "r");

	// Verifica se o ficheiro foi aberto com sucesso
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}
	// L� os dados do ficheiro
	Veiculo* novoVeiculo = malloc(sizeof(Veiculo));
	ListaVeiculo* listaVeiculo = NULL;
	while (!feof(fp) != NULL)
	{
		if (fscanf(fp, "%d;%20[^;];%d;%40[^;];%f;%d\n", &(novoVeiculo->id), novoVeiculo->tipoVeiculo, &(novoVeiculo->bateria), novoVeiculo->localizacao, &(novoVeiculo->custo), &(novoVeiculo->disponibilidade)))
		{
			if (listaVeiculo == NULL)
			{
				listaVeiculo = CriarListaVeiculo(listaVeiculo, novoVeiculo); //Chama fun��o para criar a lista de ve�culos
				CriarListaVeiculoBin(listaVeiculo); //Cria ficheiro bin�rio para armazenar a lista de ve�culos
			}
			else
			{
				if (VerificarExisteVeiculo(listaVeiculo, novoVeiculo) == false) //Verifica se j� existe o ve�culo dentro da lista
				{
					listaVeiculo = InserirVeiculo(listaVeiculo, novoVeiculo); //Insere novo ve�culo em lista j� existente
				}
			}
		}
	}

	// Fecha o ficheiro
	fclose(fp);

	return listaVeiculo;
}

/**
 * Verifica se j� existe o ve�culo dentro da lista.
 * 
 * \param listaVeiculo
 * \param novoVeiculo
 * \return 
 */
bool VerificarExisteVeiculo(ListaVeiculo* listaVeiculo, Veiculo* novoVeiculo)
{
	ListaVeiculo* aux = malloc(sizeof(ListaVeiculo));
	aux = listaVeiculo;
	while (aux != NULL)
	{
		if (aux->v.id == novoVeiculo->id)
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
 * Cria lista de ve�culos.
 * 
 * \param listaVeiculo
 * \param novoVeiculo
 * \return 
 */
ListaVeiculo* CriarListaVeiculo(ListaVeiculo* listaVeiculo, Veiculo* novoVeiculo)
{
	ListaVeiculo* novoNo = malloc(sizeof(ListaVeiculo));

	novoNo->v = *novoVeiculo;
	novoNo->proxima = NULL;

	return novoNo;
}

/**
 * Insere ve�culos na lista.
 * 
 * \param listaVeiculo
 * \param novoVeiculo
 * \return 
 */
ListaVeiculo* InserirVeiculo(ListaVeiculo* listaVeiculo, Veiculo* novoVeiculo)
{
	ListaVeiculo* novoNo = malloc(sizeof(ListaVeiculo)), * aux;

	novoNo->v = *novoVeiculo;
	novoNo->proxima = NULL;

	aux = listaVeiculo;
	while (aux->proxima)
	{
		aux = aux->proxima;
	}
	aux->proxima = novoNo;

	InserirListaVeiculoBin(novoNo);	//Insere a pessoa no ficheiro binario

	return listaVeiculo;
}

/**
 * Cria ficheiro bin�rio e guarda os dados armazenados na lista de Ve�culos
 *
 * \param listaVeiculo
 * \return
 */
bool CriarListaVeiculoBin(ListaVeiculo* listaVeiculo)
{
	FILE* fp = fopen("listaVeiculo.bin", "wb"); // Escreve ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return (false);
	}

	ListaVeiculo* aux = listaVeiculo;
	while (aux != NULL)
	{
		Veiculo buffer = aux->v;
		fwrite(&buffer, sizeof(Veiculo), 1, fp);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}

/**
 * Insere ve�culos no fichiro bin�rio.
 * 
 * \param listaVeiculo
 * \return 
 */
bool InserirListaVeiculoBin(ListaVeiculo* listaVeiculo)
{
	FILE* fp = fopen("listaVeiculo.bin", "ab"); // Insere no ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return (false);
	}

	ListaVeiculo* aux = listaVeiculo;
	while (aux != NULL)
	{
		Veiculo buffer = aux->v;
		fwrite(&buffer, sizeof(Veiculo), 1, fp);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}

/**
 * L� o ficheiro bin�rio que armazena os ve�culos e retorna uma lista atualizada.
 * 
 * \return 
 */
ListaVeiculo* LerListaVeiculoBin()
{
	FILE* fp = fopen("listaVeiculo.bin", "rb"); // L� ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}

	ListaVeiculo* listaAtual = malloc(sizeof(ListaVeiculo)), * aux = malloc(sizeof(ListaVeiculo));
	listaAtual = NULL;

	while (!feof(fp) != NULL)
	{
		Veiculo* v = malloc(sizeof(Veiculo));
		if (fread(v, sizeof(Veiculo), 1, fp))
		{
			ListaVeiculo* proximoNo = malloc(sizeof(ListaVeiculo));
			proximoNo->v = *v;
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
 * Altera dados dentro do ficheiro bin�rio.
 * 
 * \param novosDados
 * \return 
 */
bool AlterarListaVeiculoBin(Veiculo novosDados)
{
	FILE* fp = fopen("listaVeiculo.bin", "rb+"); // L� e altera ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		return(false);
	}

	Veiculo* aux = malloc(sizeof(Veiculo));
	long int cursor = ftell(fp);

	while (fread(aux, sizeof(Veiculo), 1, fp))
	{
		if (aux->id == novosDados.id)
		{
			break;
		}
		cursor = ftell(fp);
	}

	fseek(fp, cursor, SEEK_SET);
	fwrite(&novosDados, sizeof(Veiculo), 1, fp);

	fclose(fp);

	return true;
}

/**
 * Remove o registo de um ve�culo do ficheiro bin�rio.
 * 
 * \param id
 * \return 
 */
bool RemoverDadosListaVeiculoBin(int id)
{
	FILE* fp = fopen("listaVeiculo.bin", "rb"); // L� ficheiro bin�rio
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}

	FILE* fp2 = fopen("copiaListaVeiculo.bin", "wb"); // Escreve ficheiro bin�rio
	if (fp2 == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}

	Veiculo* aux = malloc(sizeof(Veiculo));

	while (fread(aux, sizeof(Veiculo), 1, fp))
	{
		if (aux->id != id)
		{
			fwrite(aux, sizeof(Veiculo), 1, fp2);
		}
	}

	fclose(fp);
	fclose(fp2);

	remove("listaVeiculo.bin");

	if (rename("copiaListaVeiculo.bin", "listaVeiculo.bin") != 0)
	{
		printf("Erro ao renomear arquivo de sa�da");
		return(false);
	}

	return true;
}

/**
 * Fun��o auxiliar que comparar os atributos de um array e os retorna em ordem decrescente.
 * 
 * \param a
 * \param b
 * \return 
 */
int comparar(const void* a, const void* b)
{
	return (&b - &a);
}

/**
 * Lista os ve�culos registados no ficheiro bin�rio em ordem decrescente.
 * 
 * \return 
 */
bool ListarVeiculoOrdemDecrescente()
{
	int tamanho = 1, i = 0;
	Veiculo* vetorVeiculo = malloc(tamanho * sizeof(Veiculo));
	ListaVeiculo* listaAtual = LerListaVeiculoBin(); //Armazena os ve�culos do ficheiro bin�rio em uma lista

	if (vetorVeiculo != NULL) {
		while (listaAtual != NULL)
		{
			if (i >= tamanho)
			{
				int novoTamanho = i + 1;
				vetorVeiculo = (Veiculo*)realloc(vetorVeiculo, novoTamanho * sizeof(Veiculo));
				if (vetorVeiculo == NULL) {
					printf("Erro: n�o foi poss�vel realocar mem�ria.\n");
					exit(1);
				}
				tamanho = novoTamanho;
			}
			vetorVeiculo[i] = listaAtual->v;
			listaAtual = listaAtual->proxima;
			i++;
		}
	}
	else
	{
		printf("Erro: n�o foi poss�vel alocar mem�ria.\n");
		return false;
	}

	qsort(vetorVeiculo, tamanho, sizeof(Veiculo), comparar);

	for (int j = 0; j < tamanho; j++)
	{
		printf("%d;%s;%d;%s;%f;%d\n", vetorVeiculo[j].id, vetorVeiculo[j].tipoVeiculo, vetorVeiculo[j].bateria, vetorVeiculo[j].localizacao, vetorVeiculo[j].custo, vetorVeiculo[j].disponibilidade);
	}

	return true;
}

/**
 * Lista os ve�culos registados no ficheiro bin�rio localizados em determinado lugar.
 * 
 * \param localizacao
 * \return 
 */
bool ListarVeiculoLocalizacao(char localizacao[])
{
	int tamanho = 1, i = 0;
	Veiculo* vetorVeiculo = malloc(tamanho * sizeof(Veiculo));
	ListaVeiculo* listaAtual = LerListaVeiculoBin(); //Armazena os ve�culos do ficheiro bin�rio em uma lista

	if (vetorVeiculo != NULL) {
		while (listaAtual != NULL)
		{
			if (i >= tamanho)
			{
				int novoTamanho = i + 1;
				vetorVeiculo = (Veiculo*)realloc(vetorVeiculo, novoTamanho * sizeof(Veiculo));
				if (vetorVeiculo == NULL) {
					printf("Erro: n�o foi poss�vel realocar mem�ria.\n");
					exit(1);
				}
				tamanho = novoTamanho;
			}
			if (strcmp(listaAtual->v.localizacao, localizacao)==0)
			{
				vetorVeiculo[i] = listaAtual->v;
				i++;
			}

			listaAtual = listaAtual->proxima;
			
		}
	}
	else
	{
		printf("Erro: n�o foi poss�vel alocar mem�ria.\n");
		return false;
	}

	for (int j = 0; j < tamanho; j++)
	{
		printf("%d;%s;%d;%s;%f;%d\n", vetorVeiculo[j].id, vetorVeiculo[j].tipoVeiculo, vetorVeiculo[j].bateria, vetorVeiculo[j].localizacao, vetorVeiculo[j].custo, vetorVeiculo[j].disponibilidade);
	}

	return true;
}
