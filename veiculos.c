/*****************************************************************//**
 * \file   veiculos.c
 * \brief  Funções que modularizam o tratamento dos veículos a serem alugados
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
 *  Lê o ficheiro que contem as informações dos veículos e armazena esses dados em uma lista.
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
	// Lê os dados do ficheiro
	Veiculo* novoVeiculo = malloc(sizeof(Veiculo));
	ListaVeiculo* listaVeiculo = NULL;
	while (!feof(fp) != NULL)
	{
		if (fscanf(fp, "%d;%20[^;];%d;%40[^;];%f;%d\n", &(novoVeiculo->id), novoVeiculo->tipoVeiculo, &(novoVeiculo->bateria), novoVeiculo->localizacao, &(novoVeiculo->custo), &(novoVeiculo->disponibilidade)))
		{
			if (listaVeiculo == NULL)
			{
				listaVeiculo = CriarListaVeiculo(listaVeiculo, novoVeiculo); //Chama função para criar a lista de veículos
				CriarListaVeiculoBin(listaVeiculo); //Cria ficheiro binário para armazenar a lista de veículos
			}
			else
			{
				if (VerificarExisteVeiculo(listaVeiculo, novoVeiculo) == false) //Verifica se já existe o veículo dentro da lista
				{
					listaVeiculo = InserirVeiculo(listaVeiculo, novoVeiculo); //Insere novo veículo em lista já existente
				}
			}
		}
	}

	// Fecha o ficheiro
	fclose(fp);

	return listaVeiculo;
}

/**
 * Verifica se já existe o veículo dentro da lista.
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
 * Cria lista de veículos.
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
 * Insere veículos na lista.
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
 * Cria ficheiro binário e guarda os dados armazenados na lista de Veículos
 *
 * \param listaVeiculo
 * \return
 */
bool CriarListaVeiculoBin(ListaVeiculo* listaVeiculo)
{
	FILE* fp = fopen("listaVeiculo.bin", "wb"); // Escreve ficheiro binário
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
 * Insere veículos no fichiro binário.
 * 
 * \param listaVeiculo
 * \return 
 */
bool InserirListaVeiculoBin(ListaVeiculo* listaVeiculo)
{
	FILE* fp = fopen("listaVeiculo.bin", "ab"); // Insere no ficheiro binário
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
 * Lê o ficheiro binário que armazena os veículos e retorna uma lista atualizada.
 * 
 * \return 
 */
ListaVeiculo* LerListaVeiculoBin()
{
	FILE* fp = fopen("listaVeiculo.bin", "rb"); // Lê ficheiro binário
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
 * Altera dados dentro do ficheiro binário.
 * 
 * \param novosDados
 * \return 
 */
bool AlterarListaVeiculoBin(Veiculo novosDados)
{
	FILE* fp = fopen("listaVeiculo.bin", "rb+"); // Lê e altera ficheiro binário
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
 * Remove o registo de um veículo do ficheiro binário.
 * 
 * \param id
 * \return 
 */
bool RemoverDadosListaVeiculoBin(int id)
{
	FILE* fp = fopen("listaVeiculo.bin", "rb"); // Lê ficheiro binário
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro\n");
		exit(1);
	}

	FILE* fp2 = fopen("copiaListaVeiculo.bin", "wb"); // Escreve ficheiro binário
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
		printf("Erro ao renomear arquivo de saída");
		return(false);
	}

	return true;
}

/**
 * Função auxiliar que comparar os atributos de um array e os retorna em ordem decrescente.
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
 * Lista os veículos registados no ficheiro binário em ordem decrescente.
 * 
 * \return 
 */
bool ListarVeiculoOrdemDecrescente()
{
	int tamanho = 1, i = 0;
	Veiculo* vetorVeiculo = malloc(tamanho * sizeof(Veiculo));
	ListaVeiculo* listaAtual = LerListaVeiculoBin(); //Armazena os veículos do ficheiro binário em uma lista

	if (vetorVeiculo != NULL) {
		while (listaAtual != NULL)
		{
			if (i >= tamanho)
			{
				int novoTamanho = i + 1;
				vetorVeiculo = (Veiculo*)realloc(vetorVeiculo, novoTamanho * sizeof(Veiculo));
				if (vetorVeiculo == NULL) {
					printf("Erro: não foi possível realocar memória.\n");
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
		printf("Erro: não foi possível alocar memória.\n");
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
 * Lista os veículos registados no ficheiro binário localizados em determinado lugar.
 * 
 * \param localizacao
 * \return 
 */
bool ListarVeiculoLocalizacao(char localizacao[])
{
	int tamanho = 1, i = 0;
	Veiculo* vetorVeiculo = malloc(tamanho * sizeof(Veiculo));
	ListaVeiculo* listaAtual = LerListaVeiculoBin(); //Armazena os veículos do ficheiro binário em uma lista

	if (vetorVeiculo != NULL) {
		while (listaAtual != NULL)
		{
			if (i >= tamanho)
			{
				int novoTamanho = i + 1;
				vetorVeiculo = (Veiculo*)realloc(vetorVeiculo, novoTamanho * sizeof(Veiculo));
				if (vetorVeiculo == NULL) {
					return false;
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
		return false;
	}

	for (int j = 0; j < tamanho; j++)
	{
		printf("%d;%s;%d;%s;%f;%d\n", vetorVeiculo[j].id, vetorVeiculo[j].tipoVeiculo, vetorVeiculo[j].bateria, vetorVeiculo[j].localizacao, vetorVeiculo[j].custo, vetorVeiculo[j].disponibilidade);
	}

	return true;
}

#pragma region Grafo_Veículos
Localizacao* ListarLocais() {
	int i = 0;
	ListaVeiculo* listaVeiculo = LerListaVeiculoBin();
	Localizacao* listaLocal = NULL; // Inicializa com NULL

	while (listaVeiculo) {
		Localizacao* aux = listaLocal;
		int encontrado = 0; // Variável de controle para verificar se a localização já existe na lista

		while (aux) {
			if (strcmp(listaVeiculo->v.localizacao, aux->localizacao) == 0) {
				encontrado = 1;
				break; // Localização já existe na lista, interrompe o loop
			}
			aux = aux->proxima;
		}

		if (!encontrado) {
			Localizacao* novoLocal = malloc(sizeof(Localizacao));

			novoLocal->id = i;
			strcpy(novoLocal->localizacao, listaVeiculo->v.localizacao);
			novoLocal->proxima = NULL;

			if (listaLocal == NULL) {
				listaLocal = novoLocal;
			}
			else {
				aux = listaLocal;
				while (aux->proxima) {
					aux = aux->proxima;
				}
				aux->proxima = novoLocal;
			}
			i++;
		}
		listaVeiculo = listaVeiculo->proxima;
	}
	return listaLocal;
}

Vertice* CriarGrafo() {
	return NULL;
}

Vertice* CriarVertice() {
	Vertice* listaVertices = NULL;
	Localizacao* listaLocais = ListarLocais();

	while (listaLocais)
	{
		Vertice* aux2 = listaVertices;
		Vertice* novoVertice = malloc(sizeof(Vertice));
		if (novoVertice == NULL)
		{
			return NULL;
		}

		novoVertice->id = listaLocais->id;
		strcpy(novoVertice->localizacao, listaLocais->localizacao);
		novoVertice->proxima = NULL;
		novoVertice->lista_adjacentes = NULL;

		if (listaVertices == NULL) {
			listaVertices = novoVertice;
		}
		else {
			while (aux2->proxima) {
				aux2 = aux2->proxima;
			}
			aux2->proxima = novoVertice;
		}
		listaLocais = listaLocais->proxima;
	}

	return listaVertices;
}

Vertice* InserirVertice(Vertice* gr, Vertice* novoVertice, bool* res) {
	if (gr == NULL) {
		gr = novoVertice;
		*res = true;
		return gr;
	}
	else
	{
		Vertice* aux = gr;
		Vertice* ant = aux;
		while (aux && strcmp(aux->localizacao, novoVertice->localizacao) < 0) {
			ant = aux;
			aux = aux->proxima;
		}
		if (aux == gr) {
			novoVertice->proxima = gr;
			gr = novoVertice;
		}
		else
		{
			novoVertice->proxima = aux;
			ant->proxima = novoVertice;
		}
		*res = true;
	}
	return gr;
}

void MostrarGrafo(Vertice* gr) {
	if (gr == NULL) {
		return NULL;
	}

	printf("Vértice: %d - %s\n", gr->id, gr->localizacao);
	MostrarAdjacencias(gr->lista_adjacentes);
	MostrarGrafo(gr->proxima);
}

Vertice* ProcurarVertice(Vertice* gr, char* localizacao) {
	if (gr == NULL) {
		return NULL;
	}
	if (strcmp(gr->localizacao, localizacao) == 0) {
		return gr;
	}
	return(ProcurarVertice(gr->proxima, localizacao));
}

int ProcurarVerticeId(Vertice* gr, char* localizacao) {
	if (gr == NULL) {
		return -1;
	}
	if (gr->proxima == NULL && strcmp(gr->localizacao, localizacao) > 0) {
		return -2;
	}
	if (strcmp(gr->localizacao, localizacao) == 0) {
		return gr->id;
	}
	return(ProcurarVerticeId(gr->proxima, localizacao));
}


Adj* CriarAdj(int id, int peso) {
	Adj* novoAdj = (Adj*)calloc(1, sizeof(Adj));
	if (novoAdj == NULL) {
		return NULL;
	}
	novoAdj->id = id;
	novoAdj->peso = peso;
	novoAdj->proxima = NULL;
	return novoAdj;
}

Vertice* InserirAdjacenteVertice(Vertice* gr, char* origem, char* dest, int peso, bool* res) {
#pragma region Validações
	*res = false;				//por defeito é falso

	if (gr == NULL) {
		return gr;	//<! se grafo está vazio, ignora operação
	}

	Vertice* aux = ProcurarVertice(gr, origem);	//<! procura vertice origem
	int idDest = ProcurarVerticeId(gr, dest);	//<! procura vertice destino

	if (aux == NULL || idDest < 0) {
		return gr;			//<! Se não encontrou vertice origem e destino, ignora operação
	}

	if (ExisteAdjacentes(aux->lista_adjacentes, idDest) == true) {
		return gr; //Se já foi registado esta adjacencia, ignorar a operação
	}

#pragma endregion

#pragma region Ação
	//Insere nova adjacencia no vertice "Origem"
	Adj* novoAdj = CriarAdj(idDest, peso);
	aux->lista_adjacentes = InserirAdj(aux->lista_adjacentes, novoAdj, res);
	return (InserirAdjacenteVertice(gr, dest, origem, peso, res));
#pragma endregion

}

Adj* InserirAdj(Adj* h, Adj* novoAdj, bool* res) {

	*res = false;		//por defeito é falso

	if (novoAdj == NULL) {	//Se novo adjacente é nulo, ignora operação
		return h;
	}

	if (ExisteAdjacentes(h, novoAdj->id) == true) {
		return h; // Se novo adj existe, ignorar operação
	}

	// Inserir nova adjacencia!
	*res = true;
	if (h == NULL) {	//Se lista de adjacencias é vazia, esta é a primeira adjacencia
		h = novoAdj;
		return h;
	}
	//senão insere no início das adjacências!
	novoAdj->proxima = h;
	h = novoAdj;

	return h;
}

bool ExisteAdjacentes(Adj* h, int id) {
	if (h == NULL) {
		return false;
	}
	if (h->id == id) {
		return true;
	}
	return ExisteAdjacentes(h->proxima, id);
}


void MostrarAdjacencias(Adj* h) {
	if (h == NULL) {
		return NULL;
	}
	printf("\tAdj: %d - %d\n", h->id, h->peso);
	MostrarAdjacencias(h->proxima);
}

#pragma endregion
