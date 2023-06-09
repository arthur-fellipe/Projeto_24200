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
#include <limits.h>
#include "pessoas.h"
#include "veiculos.h"

#pragma region Fase1
/**
 *  L� o ficheiro que contem as informa��es dos ve�culos e armazena esses dados em uma lista.
 * 
 * \return listaVeiculo
 */
ListaVeiculo* LerFicheiroVeiculoTxt()
{

	// Abre o ficheiro com os dados
	FILE* fp = fopen("veiculos.txt", "r");

	// Verifica se o ficheiro foi aberto com sucesso
	if (fp == NULL)
	{
		return NULL;
	}
	// L� os dados do ficheiro
	Veiculo* novoVeiculo = malloc(sizeof(Veiculo));
	ListaVeiculo* listaVeiculo = CriarListaVeiculo(); //Chama fun��o para criar a lista de ve�culos
	CriarListaVeiculoBin(listaVeiculo); //Cria ficheiro bin�rio para armazenar a lista de ve�culos

	while (!feof(fp) != NULL)
	{
		if (fscanf(fp, "%d;%20[^;];%d;%40[^;];%f;%d\n", &(novoVeiculo->id), novoVeiculo->tipoVeiculo, &(novoVeiculo->bateria), novoVeiculo->localizacao, &(novoVeiculo->custo), &(novoVeiculo->disponibilidade)))
		{

			if (VerificarExisteVeiculo(listaVeiculo, novoVeiculo) == false) //Verifica se j� existe o ve�culo dentro da lista
			{
				listaVeiculo = InserirVeiculo(listaVeiculo, novoVeiculo); //Insere novo ve�culo em lista j� existente
			}
			
		}
	}
	InserirListaVeiculoBin(listaVeiculo);	//Insere a lista no ficheiro binario
	
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
 * \return listaVeiculo
 */
ListaVeiculo* CriarListaVeiculo()
{
	ListaVeiculo* listaVeiculo = NULL;
	return listaVeiculo;
}

/**
 * Insere ve�culos na lista.
 * 
 * \param listaVeiculo
 * \param novoVeiculo
 * \return listaVeiculo
 */
ListaVeiculo* InserirVeiculo(ListaVeiculo* listaVeiculo, Veiculo* novoVeiculo)
{
	ListaVeiculo* novoNo = malloc(sizeof(ListaVeiculo)), * aux;

	novoNo->v = *novoVeiculo;
	novoNo->proxima = NULL;

	if (listaVeiculo == NULL)
	{
		listaVeiculo = novoNo;
	}
	else {
		aux = listaVeiculo;
		while (aux->proxima)
		{
			aux = aux->proxima;
		}
		aux->proxima = novoNo;
	}
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
 * \return listaAtual
 */
ListaVeiculo* LerListaVeiculoBin()
{
	FILE* fp = fopen("listaVeiculo.bin", "rb"); // L� ficheiro bin�rio
	if (fp == NULL)
	{
		return NULL;
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
		return false;
	}

	FILE* fp2 = fopen("copiaListaVeiculo.bin", "wb"); // Escreve ficheiro bin�rio
	if (fp2 == NULL)
	{
		return false;
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
		return(false);
	}

	return true;
}

/**
 * Fun��o auxiliar que compara os atributos de um array e os retorna em ordem decrescente.
 * 
 * \param a
 * \param b
 * \return 
 */
int comparar(const void* a, const void* b)
{
	const Veiculo* veiculoA = (const Veiculo*)a;
	const Veiculo* veiculoB = (const Veiculo*)b;

	if (veiculoA->id < veiculoB->id)
		return 1;
	else if (veiculoA->id > veiculoB->id)
		return -1;
	else
		return 0;
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
					return false;
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
		return false;
	}

	qsort(vetorVeiculo, tamanho, sizeof(Veiculo), comparar);

	for (int j = 0; j < i; j++)
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

	for (int j = 0; j < i; j++)
	{
		printf("%d;%s;%d;%s;%f;%d\n", vetorVeiculo[j].id, vetorVeiculo[j].tipoVeiculo, vetorVeiculo[j].bateria, vetorVeiculo[j].localizacao, vetorVeiculo[j].custo, vetorVeiculo[j].disponibilidade);
	}

	return true;
}
#pragma endregion

#pragma region Grafo_Ve�culos
Aresta* LerFicheiroAdjacentesTxt()
{
	// Abre o ficheiro com os dados
	FILE* fp = fopen("adjacentes.txt", "r");

	// Verifica se o ficheiro foi aberto com sucesso
	if (fp == NULL)
	{
		return NULL;
	}
	// L� os dados do ficheiro
	Aresta* novaAresta = malloc(sizeof(Aresta));
	ListaAresta* listaAresta = CriarListaAresta(); //Chama fun��o para criar a lista de arestas

	while (!feof(fp) != NULL)
	{
		if (fscanf(fp, "%40[^;];%40[^;];%d\n", novaAresta->origem, novaAresta->destino, &(novaAresta->peso)))
		{
			if (VerificarExisteAresta(listaAresta, novaAresta) == false) //Verifica se j� existe a aresta dentro da lista
			{
				listaAresta = InserirAresta(listaAresta, novaAresta); //Insere nova aresta em lista j� existente
			}
		}
	}

	// Fecha o ficheiro
	fclose(fp);

	return listaAresta;
}

/**
 * Verifica se j� existe a aresta dentro da lista.
 *
 * \param listaAresta
 * \param novaAresta
 * \return
 */
bool VerificarExisteAresta(ListaAresta* listaAresta, Aresta* novaAresta)
{
	ListaAresta* aux = malloc(sizeof(ListaAresta));
	aux = listaAresta;
	while (aux != NULL)
	{
		if ((strcmp(aux->a.origem, novaAresta->origem) == 0) || (strcmp(aux->a.origem, novaAresta->destino) == 0))
		{
			if ((strcmp(aux->a.destino, novaAresta->origem)==0) || (strcmp(aux->a.destino, novaAresta->destino) == 0))
			return true;
		}

			aux = aux->proxima;

	}
	return false;
}

/**
 * Cria lista de arestas.
 *
 * \return listaAresta
 */
ListaAresta* CriarListaAresta() 
{
	ListaAresta* listaAresta = NULL;
	return listaAresta;
}

/**
 * Insere arestas na lista.
 *
 * \param listaAresta
 * \param novaAresta
 * \return listaAresta
 */
ListaAresta* InserirAresta(ListaAresta* listaAresta, Aresta* novaAresta)
{
	ListaAresta* novoNo = malloc(sizeof(ListaAresta)), * aux;

	novoNo->a = *novaAresta;
	novoNo->proxima = NULL;

	if (listaAresta == NULL)
	{
		listaAresta = novoNo;
	}
	else {
		aux = listaAresta;
		while (aux->proxima)
		{
			aux = aux->proxima;
		}
		aux->proxima = novoNo;
	}
	return listaAresta;
}


/**
 * Recebe a lista atualizada de ve�culos e cria uma lista com todas as localiza��es.
 * 
 * \param listaVeiculo
 * \return listaLocalVeiculo
 */
Localizacao* ListarLocaisVeiculos(ListaVeiculo* listaVeiculo) {
	int i = 0;
	Localizacao* listaLocalVeiculo = NULL;

	while (listaVeiculo) {
		Localizacao* aux = listaLocalVeiculo;
		int encontrado = 0; // Vari�vel de controle para verificar se a localiza��o j� existe na lista

		while (aux) {
			if (strcmp(listaVeiculo->v.localizacao, aux->localizacao) == 0) {
				encontrado = 1;
				break; // Localiza��o j� existe na lista, interrompe o loop
			}
			aux = aux->proxima;
		}

		if (!encontrado) {
			Localizacao* novoLocal = malloc(sizeof(Localizacao));

			strcpy(novoLocal->localizacao, listaVeiculo->v.localizacao);
			novoLocal->id = i;
			novoLocal->proxima = NULL;

			if (listaLocalVeiculo == NULL) {
				listaLocalVeiculo = novoLocal;
			}
			else {
				aux = listaLocalVeiculo;
				while (aux->proxima) {
					aux = aux->proxima;
				}
				aux->proxima = novoLocal;
			}
			i++;
		}
		listaVeiculo = listaVeiculo->proxima;
	}
	return listaLocalVeiculo;
}
/**
 * Cria um grafo vazio.
 * 
 * \return 
 */
Vertice* CriarGrafo() {
	return NULL;
}

/**
 * Cria uma lista com todos os v�rtices.
 * 
 * \return listaVertices
 */
Vertice* CriarVertice() {
	Vertice* listaVertices = NULL;
	ListaVeiculo* listaVeiculo = LerListaVeiculoBin(); //Armazena os ve�culos do ficheiro bin�rio em uma lista
	Localizacao* listaLocalVeiculo = ListarLocaisVeiculos(listaVeiculo); //Chama a fun��o para criar uma lista de localiza��es

	while (listaLocalVeiculo)
	{
		Vertice* aux2 = listaVertices;
		Vertice* novoVertice = malloc(sizeof(Vertice));
		if (novoVertice == NULL)
		{
			return NULL;
		}

		novoVertice->id = listaLocalVeiculo->id;
		strcpy(novoVertice->localizacao, listaLocalVeiculo->localizacao);
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
		listaLocalVeiculo = listaLocalVeiculo->proxima;
	}

	return listaVertices;
}

/**
 * Insere os vertices no grafo.
 * 
 * \param gr
 * \param novoVertice
 * \param res
 * \return gr
 */
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

/**
 * Imprime o grafo no ecr�.
 * 
 * \param gr
 */
void MostrarGrafo(Vertice* gr) {
	if (gr == NULL) {
		return NULL;
	}

	printf("V�rtice: %d - %s\n", gr->id, gr->localizacao);
	MostrarAdjacencias(gr->lista_adjacentes);
	MostrarGrafo(gr->proxima);
}

/**
 * Procura um v�rtice a partir do nome da localiza��o.
 * 
 * \param gr
 * \param localizacao
 * \return gr
 */
Vertice* ProcurarVerticeLocal(Vertice* gr, char* localizacao) {
	if (gr == NULL) {
		return NULL;
	}
	if (strcmp(gr->localizacao, localizacao) == 0) {
		return gr;
	}
	return(ProcurarVerticeLocal(gr->proxima, localizacao));
}

/**
 * Procura um v�rtice a partir do seu id.
 * 
 * \param gr
 * \param id
 * \return gr
 */
Vertice* ProcurarVerticeId(Vertice* gr, int id) {
	if (gr == NULL) {
		return NULL;
	}
	if (gr->id == id) {
		return gr;
	}
	return(ProcurarVerticeId(gr->proxima, id));
}

/**
 * Procura o id de um v�rtice a partir do nome da localiza��o.
 * 
 * \param gr
 * \param localizacao
 * \return gr->id
 */
int ProcurarIdVertice(Vertice* gr, char* localizacao) {
	if (gr == NULL) {
		return -1;
	}
	if (gr->proxima == NULL && strcmp(gr->localizacao, localizacao) > 0) {
		return -2;
	}
	if (strcmp(gr->localizacao, localizacao) == 0) {
		return gr->id;
	}
	return(ProcurarIdVertice(gr->proxima, localizacao));
}

/**
 * Cria um adjacente.
 * 
 * \param id
 * \param peso
 * \return novoAdj
 */
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

/**
 * Insere os adjacentes nos v�rtices do grafo de forma recursiva.
 * 
 * \param gr
 * \param listaAresta
 * \param res
 * \return 
 */
Vertice* InserirAdjVertice(Vertice* gr, ListaAresta* listaAresta, bool* res) {
	*res = false;

	if (gr == NULL || listaAresta == NULL) {
		return gr; // Se o grafo ou a listaAresta est� vazia, ignora opera��o
	}

	ListaAresta* listaAtual = listaAresta;

	while (listaAtual != NULL) {
		Vertice* origem = ProcurarVerticeLocal(gr, listaAtual->a.origem);
		Vertice* destino = ProcurarVerticeLocal(gr, listaAtual->a.destino);

		if (origem != NULL && destino != NULL) {
			int idOrigem = ProcurarIdVertice(gr, listaAtual->a.origem);
			int idDestino = ProcurarIdVertice(gr, listaAtual->a.destino);

			if (!ExisteAdjacentes(origem->lista_adjacentes, idDestino)) {
				// Cria a adjac�ncia no v�rtice de origem
				Adj* novoAdjOrigem = CriarAdj(idDestino, listaAtual->a.peso);
				origem->lista_adjacentes = InserirAdj(origem->lista_adjacentes, novoAdjOrigem, res);
			}

			if (!ExisteAdjacentes(destino->lista_adjacentes, idOrigem)) {
				// Cria a adjac�ncia no v�rtice de destino
				Adj* novoAdjDestino = CriarAdj(idOrigem, listaAtual->a.peso);
				destino->lista_adjacentes = InserirAdj(destino->lista_adjacentes, novoAdjDestino, res);
			}
		}

		listaAtual = listaAtual->proxima;
	}

	return gr;
}

/**
 * Insere o adjacente na lista de adjacentes de um v�rtice.
 * 
 * \param h
 * \param novoAdj
 * \param res
 * \return listaAdjacentes
 */
Adj* InserirAdj(Adj* listaAdjacentes, Adj* novoAdj, bool* res) {

	*res = false;

	if (novoAdj == NULL) {	//Se o novo adjacente � nulo, ignora opera��o
		return listaAdjacentes;
	}

	if (ExisteAdjacentes(listaAdjacentes, novoAdj->id) == true) {
		return listaAdjacentes; // Se o novo adjacente existe, ignora a opera��o
	}

	// Inserir novo adjacente
	*res = true;
	if (listaAdjacentes == NULL) {	//Se lista de adjacencias � vazia, este � o primeiro adjacente
		listaAdjacentes = novoAdj;
		return listaAdjacentes;
	}
	//Sen�o, insere no in�cio da lista de adjac�ntes
	novoAdj->proxima = listaAdjacentes;
	listaAdjacentes = novoAdj;

	return listaAdjacentes;
}

/**
 * Verifica se o adjacente j� est� na lista.
 * 
 * \param h
 * \param id
 * \return 
 */
bool ExisteAdjacentes(Adj* listaAdjacentes, int id) {
	if (listaAdjacentes == NULL) {
		return false;
	}
	if (listaAdjacentes->id == id) {
		return true;
	}
	return ExisteAdjacentes(listaAdjacentes->proxima, id);
}

/**
 * Imprime no ecr� a lista de adjacentes de um v�rtice.
 * 
 * \param listaAdjacentes
 */
void MostrarAdjacencias(Adj* listaAdjacentes) {
	if (listaAdjacentes == NULL) {
		return NULL;
	}
	printf("\tAdj: %d - %d\n", listaAdjacentes->id, listaAdjacentes->peso);
	MostrarAdjacencias(listaAdjacentes->proxima);
}

/**
 * Calcula o n�mero de v�rtices de um grafo.
 * 
 * \param gr
 * \return 
 */
int CalcularTamanhoGrafo(Vertice* gr) {
	int tamanho = 0;
	
	Vertice* aux = gr;
	while (aux != NULL) {
		tamanho++;
		aux = aux->proxima;
	}

	return tamanho;
}
#pragma endregion

#pragma region Menor Caminho
/*// Fun��o para calcular a dist�ncia entre dois v�rtices
int CalcularDistancia(Vertice* origem, Vertice* destino) {
	if (origem == NULL || destino == NULL) {
		return NULL;
	}
		
	Adj* auxOrigem = origem->lista_adjacentes;
	Vertice* auxDest = destino;
	while (auxOrigem) {

		if (auxOrigem->id == auxDest->id) {
			return auxOrigem->peso;
		}
		auxOrigem = auxOrigem->proxima;
	}
	// Se a dist�ncia n�o estiver definida, retorne um valor inv�lido
	return 0;
}

bool TodosVerticesVisitados(bool* visitados, int tamanhoGrafo) {
	for (int i = 0; i < tamanhoGrafo; i++) {
		if (!visitados[i]) {
			return false;
		}
	}
	return true;
}

void EncontrarMenorTrajeto(Vertice* grafo) {
	int tamanho = CalcularTamanhoGrafo(grafo);
	bool* visitados = (bool*)malloc(sizeof(bool) * tamanho);
	for (int i = 0; i < tamanho; i++) {
		visitados[i] = false; // Inicializa todos os v�rtices como n�o visitados
	}
	visitados[0] = true; // Marca o v�rtice 0 como visitado
	int menorDistancia = INT_MAX; // Menor dist�ncia inicialmente definida como infinito
	Vertice* verticeAtual = NULL;

	BuscaExaustiva(grafo, visitados, tamanho, NULL, 0, &menorDistancia);
	free(visitados);
}

void BuscaExaustiva(Vertice* grafo, bool* visitados, int tamanhoGrafo, Vertice* verticeAtual, int distanciaAtual, int* menorDistancia) {
	if (TodosVerticesVisitados(visitados, tamanhoGrafo)) {
		if (distanciaAtual < *menorDistancia) {
			*menorDistancia = distanciaAtual;
		}
		return;
	}

	for (Vertice* vertice = grafo; vertice != NULL; vertice = vertice->proxima) {
		if (!visitados[vertice->id]) {
			visitados[vertice->id] = true;
			int novaDistancia = distanciaAtual + CalcularDistancia(verticeAtual, vertice);
			BuscaExaustiva(grafo, visitados, tamanhoGrafo, vertice, novaDistancia, menorDistancia);
			visitados[vertice->id] = false;
		}
	}
}


ListaVeiculo* SelecionarVeiculosBateria() {
	ListaVeiculo* listaAtual = LerListaVeiculoBin(); //Armazena os ve�culos do ficheiro bin�rio em uma lista
	ListaVeiculo* listaBateria = CriarListaVeiculo();

	while (listaAtual != NULL)
	{
		if (listaAtual->v.bateria < 50)
		{
			Veiculo* v = &listaAtual->v;
			listaBateria = InserirVeiculo(listaBateria, v);
		}
		listaAtual = listaAtual->proxima;
	}
	return listaBateria;
}

Localizacao* LocalizarBateria(ListaVeiculo* listaBateria) {
	Localizacao* locaisBateria = ListarLocaisVeiculos(listaBateria);

	return locaisBateria;
}*/
#pragma endregion

#pragma region Ve�culos_Area
/**
 * Cria uma lista com todos os ve�culos de determinado tipo.
 * 
 * \param tipoVeiculo
 * \return listaTipo
 */
ListaVeiculo* SelecionarVeiculosTipo(char* tipoVeiculo) {
	ListaVeiculo* listaAtual = LerListaVeiculoBin(); //Armazena os ve�culos do ficheiro bin�rio em uma lista
	ListaVeiculo* listaTipo = CriarListaVeiculo();

	while (listaAtual != NULL)
	{
		if (strcmp(listaAtual->v.tipoVeiculo, tipoVeiculo) == 0)
		{
			Veiculo* v = &listaAtual->v;
			listaTipo = InserirVeiculo(listaTipo, v);
		}
		listaAtual = listaAtual->proxima;

	}
	return listaTipo;
}

/**
 * Cria uma lista como todos os locais inseridos dentro de determinado raio.
 * 
 * \param localizacaoPessoa
 * \param gr
 * \param raio
 * \return listaArea
 */
Localizacao* DefinirArea(char* localizacaoPessoa, Vertice* gr, int raio) {

	Vertice* verticePessoa = ProcurarVerticeLocal(gr, localizacaoPessoa);
	if (verticePessoa == NULL)
	{
		return NULL;
	}

	Localizacao* listaArea = malloc(sizeof(Localizacao));
	listaArea->id = verticePessoa->id;
	strcpy(listaArea->localizacao, verticePessoa->localizacao);
	listaArea->proxima = NULL;

	Adj* adjacente = verticePessoa->lista_adjacentes;

	while (adjacente != NULL)
	{

		if (adjacente->peso <= raio * 2)
		{
			Vertice* adj = ProcurarVerticeId(gr, adjacente->id);
			if (adj)
			{
				Localizacao* novoLocal = malloc(sizeof(Localizacao));

				novoLocal->id = adj->id;
				strcpy(novoLocal->localizacao, adj->localizacao);
				novoLocal->proxima = NULL;

				Localizacao* aux = listaArea;
				while (aux->proxima) {
					aux = aux->proxima;
				}
				aux->proxima = novoLocal;
			}
		}
		adjacente = adjacente->proxima;
	}
	return listaArea;
}

/**
 * Compara a listaTipo e a listaArea e imprime no ecr� os ve�culos daquele tipo naquele raio.
 * 
 * \param gr
 * \return 
 */
bool ListarVeiculosArea(Vertice* gr) {
	ListaVeiculo* listaTipo = SelecionarVeiculosTipo("bicicleta");
	Localizacao* listaArea = DefinirArea("Braga", gr, 50);

	Localizacao* auxArea = listaArea;

	while (listaTipo)
	{
		while (listaArea)
		{
			if (strcmp(listaTipo->v.localizacao, listaArea->localizacao) == 0)
			{
				printf("%d;%s;%d;%s;%f;%d\n", listaTipo->v.id, listaTipo->v.tipoVeiculo, listaTipo->v.bateria, listaTipo->v.localizacao, listaTipo->v.custo, listaTipo->v.disponibilidade);
			}
			listaArea = listaArea->proxima;
		}
		listaTipo = listaTipo->proxima;
		listaArea = auxArea;
	}
	return true;
}
#pragma endregion
