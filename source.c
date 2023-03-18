/*****************************************************************//**
 * \file   source.c
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
#include "Header.h"

/*void lerDados(FILE* fp, Pessoa* leituraPessoa)
{
	while (!feof(fp))
	{
		fscanf(fp, "%d;%d;%50[^;];%f;\n", &(leituraPessoa->id), &(leituraPessoa->admin), leituraPessoa->nome, &(leituraPessoa->saldo));
	}
}*/


ListaPessoa* LerFicheiroTxt()
{

	// Abre o ficheiro com os dados
	FILE* fp = fopen("pessoas.txt", "r");

	// Verifica se o arquivo foi aberto com sucesso
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}
	// Lê os dados do ficheiro
	Pessoa* novaPessoa = malloc(sizeof(Pessoa));
	ListaPessoa *listaPessoa = NULL;
	int count = 0;
	while (!feof(fp) != NULL)
	{
		if (fscanf(fp, "%d;%d;%50[^;];%f\n", &(novaPessoa->id), &(novaPessoa->admin), novaPessoa->nome, &(novaPessoa->saldo)))
		{
			if (listaPessoa == NULL)
			{
				listaPessoa = CriarListaPessoa(listaPessoa, novaPessoa);
			}
			else
			{
				listaPessoa = InserirPessoa(listaPessoa, novaPessoa);
			}
		}
		count++;
	}

	// Fecha o ficheiro
	fclose(fp);
	
	return listaPessoa;
}

ListaPessoa* CriarListaPessoa(ListaPessoa* listaPessoa, Pessoa* novaPessoa)
{
	ListaPessoa *novoNo = malloc(sizeof(ListaPessoa));

	novoNo->p = *novaPessoa;
	novoNo->proxima = NULL;

	listaPessoa = novoNo;

	CriarListaPessoaBin(listaPessoa);
	
	return listaPessoa;
}

ListaPessoa* InserirPessoa(ListaPessoa *listaPessoa, Pessoa* novaPessoa)
{
	ListaPessoa *novoNo = malloc(sizeof(ListaPessoa)), *aux;
	
	novoNo->p = *novaPessoa;
	novoNo->proxima = NULL;

	//listaPessoa->proxima = novoNo;
	aux = listaPessoa;
	while (aux->proxima)
	{
			aux = aux->proxima;
	}
	aux->proxima = novoNo;

	//Insere a pessoa no ficheiro binario
	//InserirListaPessoaBin(listaPessoa);
	InserirListaPessoaBin(novoNo);

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
	FILE* fp = fopen("listaPessoa.bin", "wb"); // Escreve ficheiro binário
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
		printf("%d;%d;%s;%f\n", buffer.id, buffer.admin, buffer.nome, buffer.saldo);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}

bool InserirListaPessoaBin(ListaPessoa* listaPessoa)
{
	FILE* fp = fopen("listaPessoa.bin", "ab"); // Insere no ficheiro binário
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
		printf("%d;%d;%s;%f\n", buffer.id, buffer.admin, buffer.nome, buffer.saldo);
		aux = aux->proxima;
	}

	fclose(fp);

	return (true);
}

ListaPessoa* LerListaPessoaBin()
{
	FILE* fp = fopen("listaPessoa.bin", "rb"); // Lê ficheiro binário
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}

	ListaPessoa* listaAtual = malloc(sizeof(ListaPessoa)), *aux = malloc(sizeof(ListaPessoa));
	listaAtual = NULL;

	while(!feof(fp) != NULL)		
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
	//listaAtual->proxima = aux;
	fclose(fp);

	return listaAtual;
}

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
	//free(aux);

	return true;
}

bool RemoverDadosListaPessoaBin(int id)
{
	FILE* fp = fopen("listaPessoa.bin", "rb"); // Lê ficheiro binário
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}

	FILE* fp2 = fopen("copiaListaPessoa.bin", "wb"); // Escreve ficheiro binário
	if (fp2 == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}

	Pessoa* aux = malloc(sizeof(Pessoa));
	//long int cursor;

	while (fread(aux, sizeof(Pessoa), 1, fp))
	{
		if (aux->id != id)
		{
			fwrite(aux, sizeof(Pessoa), 1, fp2);
			//printf("%d;%d;%s;%f\n", aux->id, aux->admin, aux->nome, aux->saldo);
		}
		//cursor = ftell(fp);
	}

	fclose(fp);
	fclose(fp2);

	//free(aux);

	remove("listaPessoa.bin");
	
	if (rename("copiaListaPessoa.bin", "listaPessoa.bin") != 0)
	{
		printf("Erro ao renomear arquivo de saída");
		return(false);
	}
	
	return true;
}

/*bool AlterarListaPessoaBin()
{
	int tamanho = 1;
	Pessoa* vetorPessoa = malloc(tamanho * sizeof(Pessoa));
	ListaPessoa* listaAtual = LerListaPessoaBin();

	if (vetorPessoa != NULL) {
		printf("Memória alocada com sucesso.\n");
		int i = 0;

		while (listaAtual != NULL)
		{
			if (i >= tamanho)
			{
				int novoTamanho = i + 1;
				vetorPessoa = (Pessoa*) realloc(vetorPessoa, novoTamanho * sizeof(Pessoa));
				if (vetorPessoa == NULL) {
					printf("Erro: não foi possível realocar memória.\n");
					exit(1);
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
		//exit(1);
	}

	for (int j = 0; j < tamanho; j++)
	{
		printf("%d;%d;%s;%f;\n", vetorPessoa[j].id, vetorPessoa[j].admin, vetorPessoa[j].nome, vetorPessoa[j].saldo);
	}

	int idAlterar;
	printf("Digite o id do usuário que pretende alterar: ");
	scanf("%d", &idAlterar);
	printf("Digite os novos dados do usuário %d:", idAlterar);
	scanf("%d", &vetorPessoa[idAlterar - 1].admin);
	scanf("%s", vetorPessoa[idAlterar - 1].nome);
	scanf("%f", &vetorPessoa[idAlterar - 1].saldo);

	printf("%d;%s;%f;", vetorPessoa[idAlterar - 1].admin, vetorPessoa[idAlterar - 1].nome, vetorPessoa[idAlterar - 1].saldo);
	for (int k = 0; k < tamanho; k++)
	{
		printf("%d;%d;%s;%f;\n", vetorPessoa[k].id, vetorPessoa[k].admin, vetorPessoa[k].nome, vetorPessoa[k].saldo);
	}

	return true;
}*/
