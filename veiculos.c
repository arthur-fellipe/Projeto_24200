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
#include <limits.h>
#include "pessoas.h"
#include "veiculos.h"

#pragma region Fase1
/**
 *  Lê o ficheiro que contem as informações dos veículos e armazena esses dados em uma lista.
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
	// Lê os dados do ficheiro
	Veiculo* novoVeiculo = malloc(sizeof(Veiculo));
	ListaVeiculo* listaVeiculo = CriarListaVeiculo(); //Chama função para criar a lista de veículos
	CriarListaVeiculoBin(listaVeiculo); //Cria ficheiro binário para armazenar a lista de veículos

	while (!feof(fp) != NULL)
	{
		if (fscanf(fp, "%d;%20[^;];%d;%40[^;];%f;%d\n", &(novoVeiculo->id), novoVeiculo->tipoVeiculo, &(novoVeiculo->bateria), novoVeiculo->localizacao, &(novoVeiculo->custo), &(novoVeiculo->disponibilidade)))
		{

			if (VerificarExisteVeiculo(listaVeiculo, novoVeiculo) == false) //Verifica se já existe o veículo dentro da lista
			{
				listaVeiculo = InserirVeiculo(listaVeiculo, novoVeiculo); //Insere novo veículo em lista já existente
			}
			
		}
	}
	InserirListaVeiculoBin(listaVeiculo);	//Insere a lista no ficheiro binario
	
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
 * \return listaVeiculo
 */
ListaVeiculo* CriarListaVeiculo()
{
	ListaVeiculo* listaVeiculo = NULL;
	return listaVeiculo;
}

/**
 * Insere veículos na lista.
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
 * \return listaAtual
 */
ListaVeiculo* LerListaVeiculoBin()
{
	FILE* fp = fopen("listaVeiculo.bin", "rb"); // Lê ficheiro binário
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
		return false;
	}

	FILE* fp2 = fopen("copiaListaVeiculo.bin", "wb"); // Escreve ficheiro binário
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

	for (int j = 0; j < i; j++)
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

	for (int j = 0; j < i; j++)
	{
		printf("%d;%s;%d;%s;%f;%d\n", vetorVeiculo[j].id, vetorVeiculo[j].tipoVeiculo, vetorVeiculo[j].bateria, vetorVeiculo[j].localizacao, vetorVeiculo[j].custo, vetorVeiculo[j].disponibilidade);
	}

	return true;
}
#pragma endregion

#pragma region Grafo_Veículos
Aresta* LerFicheiroAdjacentesTxt()
{
	// Abre o ficheiro com os dados
	FILE* fp = fopen("adjacentes.txt", "r");

	// Verifica se o ficheiro foi aberto com sucesso
	if (fp == NULL)
	{
		return NULL;
	}
	// Lê os dados do ficheiro
	Aresta* novaAresta = malloc(sizeof(Aresta));
	ListaAresta* listaAresta = CriarListaAresta(); //Chama função para criar a lista de arestas

	while (!feof(fp) != NULL)
	{
		if (fscanf(fp, "%40[^;];%40[^;];%d\n", novaAresta->origem, novaAresta->destino, &(novaAresta->peso)))
		{
			if (VerificarExisteAresta(listaAresta, novaAresta) == false) //Verifica se já existe a aresta dentro da lista
			{
				listaAresta = InserirAresta(listaAresta, novaAresta); //Insere nova aresta em lista já existente
			}
		}
	}

	// Fecha o ficheiro
	fclose(fp);

	return listaAresta;
}

/**
 * Verifica se já existe a aresta dentro da lista.
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
 * Recebe a lista atualizada de veículos e cria uma lista com todas as localizações.
 * 
 * \param listaVeiculo
 * \return listaLocalVeiculo
 */
Localizacao* ListarLocaisVeiculos(ListaVeiculo* listaVeiculo) {
	int i = 0;
	Localizacao* listaLocalVeiculo = NULL;

	while (listaVeiculo) {
		Localizacao* aux = listaLocalVeiculo;
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
 * Cria uma lista com todos os vértices.
 * 
 * \return listaVertices
 */
Vertice* CriarVertice() {
	Vertice* listaVertices = NULL;
	ListaVeiculo* listaVeiculo = LerListaVeiculoBin(); //Armazena os veículos do ficheiro binário em uma lista
	Localizacao* listaLocalVeiculo = ListarLocaisVeiculos(listaVeiculo); //Chama a função para criar uma lista de localizações

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
 * Imprime o grafo no ecrã.
 * 
 * \param gr
 */
void MostrarGrafo(Vertice* gr) {
	if (gr == NULL) {
		return NULL;
	}

	printf("Vértice: %d - %s\n", gr->id, gr->localizacao);
	MostrarAdjacencias(gr->lista_adjacentes);
	MostrarGrafo(gr->proxima);
}

/**
 * Procura um vértice a partir do nome da localização.
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
 * Procura um vértice a partir do seu id.
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
 * Procura o id de um vértice a partir do nome da localização.
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
 * Insere os adjacentes nos vértices do grafo de forma recursiva.
 * 
 * \param gr
 * \param listaAresta
 * \param res
 * \return 
 */
Vertice* InserirAdjVertice(Vertice* gr, ListaAresta* listaAresta, bool* res) {
	*res = false;

	if (gr == NULL || listaAresta == NULL) {
		return gr; // Se o grafo ou a listaAresta está vazia, ignora operação
	}

	ListaAresta* listaAtual = listaAresta;

	while (listaAtual != NULL) {
		Vertice* origem = ProcurarVerticeLocal(gr, listaAtual->a.origem);
		Vertice* destino = ProcurarVerticeLocal(gr, listaAtual->a.destino);

		if (origem != NULL && destino != NULL) {
			int idOrigem = ProcurarIdVertice(gr, listaAtual->a.origem);
			int idDestino = ProcurarIdVertice(gr, listaAtual->a.destino);

			if (!ExisteAdjacentes(origem->lista_adjacentes, idDestino)) {
				// Cria a adjacência no vértice de origem
				Adj* novoAdjOrigem = CriarAdj(idDestino, listaAtual->a.peso);
				origem->lista_adjacentes = InserirAdj(origem->lista_adjacentes, novoAdjOrigem, res);
			}

			if (!ExisteAdjacentes(destino->lista_adjacentes, idOrigem)) {
				// Cria a adjacência no vértice de destino
				Adj* novoAdjDestino = CriarAdj(idOrigem, listaAtual->a.peso);
				destino->lista_adjacentes = InserirAdj(destino->lista_adjacentes, novoAdjDestino, res);
			}
		}

		listaAtual = listaAtual->proxima;
	}

	return gr;
}






/**
 * Insere o adjacente na lista de adjacentes de um vértice.
 * 
 * \param h
 * \param novoAdj
 * \param res
 * \return listaAdjacentes
 */
Adj* InserirAdj(Adj* listaAdjacentes, Adj* novoAdj, bool* res) {

	*res = false;

	if (novoAdj == NULL) {	//Se o novo adjacente é nulo, ignora operação
		return listaAdjacentes;
	}

	if (ExisteAdjacentes(listaAdjacentes, novoAdj->id) == true) {
		return listaAdjacentes; // Se o novo adjacente existe, ignora a operação
	}

	// Inserir novo adjacente
	*res = true;
	if (listaAdjacentes == NULL) {	//Se lista de adjacencias é vazia, este é o primeiro adjacente
		listaAdjacentes = novoAdj;
		return listaAdjacentes;
	}
	//Senão, insere no início da lista de adjacêntes
	novoAdj->proxima = listaAdjacentes;
	listaAdjacentes = novoAdj;

	return listaAdjacentes;
}

/**
 * Verifica se o adjacente já está na lista.
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
 * Imprime no ecrã a lista de adjacentes de um vértice.
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
 * Calcula o número de vértices de um grafo.
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
/*ListaVeiculo* SelecionarVeiculosBateria() {
	ListaVeiculo* listaAtual = LerListaVeiculoBin(); //Armazena os veículos do ficheiro binário em uma lista
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
}




Vertice* EncontrarCaminhoMinimo(Vertice* gr, int src, int dst, int CalcularTamanhoGrafo) {
	// Crie e inicialize as estruturas de dados necessárias para o algoritmo de Dijkstra
	int* distancias = (int*)malloc(CalcularTamanhoGrafo * sizeof(int));
	int* predecessores = (int*)malloc(CalcularTamanhoGrafo * sizeof(int));
	bool* visitados = (bool*)malloc(CalcularTamanhoGrafo * sizeof(bool));

	for (int i = 0; i < CalcularTamanhoGrafo; i++) {
		distancias[i] = INT_MAX; // Distância inicialmente infinita para todos os vértices
		predecessores[i] = -1; // Predecessor desconhecido inicialmente para todos os vértices
		visitados[i] = false; // Nenhum vértice foi visitado inicialmente
	}

	distancias[src] = 0; // Distância do vértice de origem para si mesmo é zero

	// Executar o algoritmo de Dijkstra
	for (int count = 0; count < CalcularTamanhoGrafo - 1; count++) {
		int u = -1;
		int menorDistancia = INT_MAX;

		// Encontre o vértice não visitado com a menor distância
		for (int v = 0; v < CalcularTamanhoGrafo; v++) {
			if (!visitados[v] && distancias[v] < menorDistancia) {
				u = v;
				menorDistancia = distancias[v];
			}
		}

		// Marque o vértice atual como visitado
		visitados[u] = true;

		// Atualize as distâncias dos vértices adjacentes ao vértice atual
		Adj* adjacente = gr[u].lista_adjacentes;
		while (adjacente != NULL) {
			int v = adjacente->id;
			int pesoAresta = adjacente->peso;

			if (!visitados[v] && distancias[u] + pesoAresta < distancias[v]) {
				distancias[v] = distancias[u] + pesoAresta;
				predecessores[v] = u;
			}

			adjacente = adjacente->proxima;
		}
	}

	// Construa o caminho mínimo a partir dos predecessores
	Vertice* caminho = NULL;
	int atual = dst;
	bool res;

	while (atual != -1) {
		Vertice* vertice = ProcurarVerticeId(gr, atual);
		caminho = InserirVertice(caminho, vertice, &res);
		atual = predecessores[atual];
	}

	// Libere a memória alocada para as estruturas de dados do algoritmo de Dijkstra
	free(distancias);
	free(predecessores);
	free(visitados);

	// Retorne o caminho mínimo encontrado
	return caminho;
}

int CalcularDistancia(Vertice* gr, int src, int dst) {
	Vertice* verticeSrc = ProcurarVerticeId(gr, src);

	// Procurar a aresta que conecta src e dst na lista de adjacências do vértice src
	Adj* adjacente = verticeSrc->lista_adjacentes;
	while (adjacente) {
		if (adjacente->id == dst) {
			// O peso da aresta é a distância entre os vértices src e dst
			return adjacente->peso;
		}
		adjacente = adjacente->proxima;
	}

	// Caso a aresta entre src e dst não seja encontrada, retorna um valor inválido
	return -1;
}

int CalcularDistanciaTotal(Vertice* gr, Vertice* caminho) {
	int distanciaTotal = 0;
	Vertice* atual = caminho;
	while (atual && atual->proxima) {
		distanciaTotal += CalcularDistancia(gr, atual->id, atual->proxima->id);
		atual = atual->proxima;
	}
	return distanciaTotal;
}

int CalcularMenorDistancia(Vertice* gr, Localizacao* locaisBateria, int CalcularTamanhoGrafo) {
	char* central = gr->localizacao;
	char* src = central;
	int menorDistancia = 0;

	Localizacao* auxLocaisBateria = locaisBateria;

	while (auxLocaisBateria) {
		char* dest = auxLocaisBateria->localizacao;
		int s = ProcurarIdVertice(gr, src);
		int d = ProcurarIdVertice(gr, dest);

		Vertice* caminho = EncontrarCaminhoMinimo(gr, s, d, CalcularTamanhoGrafo);
		if (caminho) {
			menorDistancia += CalcularDistanciaTotal(gr, caminho);
			//LiberarListaVertice(caminho); // Liberar a memória alocada para o caminho
		}
		else {
			// Tratar caso em que não há caminho possível entre os vértices
			// Pode lançar uma exceção, retornar um valor especial ou tomar alguma outra ação adequada ao seu problema
			return -1;
		}

		// Atualizar src e passar para o próximo destino
		src = dest;
		auxLocaisBateria = auxLocaisBateria->proxima;
	}

	// Incluir a distância do último destino de volta à central
	int s = ProcurarIdVertice(gr, src);
	int d = ProcurarIdVertice(gr, central);

	Vertice* caminho = EncontrarCaminhoMinimo(gr, s, d, CalcularTamanhoGrafo);
	if (caminho) {
		menorDistancia += CalcularDistanciaTotal(gr, caminho);
		//LiberarListaVertice(caminho); // Liberar a memória alocada para o caminho
	}

	return menorDistancia;
}

int CountPaths(Vertice* gr, int src, int dst, int pathCount, bool* visited) {
	if (gr == NULL)
		return 0;

	// If listaAtual vertex is same as destination, then increment count
	if (src == dst)
		return (++pathCount);

	else {
		// Mark the listaAtual vertex as visited
		visited[src] = true;

		// Recur for all the vertices adjacent to this vertex
		Vertice* aux = ProcurarVerticeId(gr, src);
		Adj* hAdj = aux->lista_adjacentes;
		while (hAdj) {
			Vertice* v = ProcurarVerticeId(gr, hAdj->id);
			if (!visited[v->id])
				pathCount = CountPaths(gr, v->id, dst, pathCount, visited);
			hAdj = hAdj->proxima;
		}
	}

	// Mark the listaAtual vertex as unvisited before returning
	visited[src] = false;

	return pathCount;
}

int CountPathsVerticesName(Vertice* gr, Localizacao* locaisBateria, int CalcularTamanhoGrafo) {
	char* central = gr->localizacao;
	char* src = central;
	int countPaths = 0;

	Localizacao* auxLocaisBateria = locaisBateria;

	while (auxLocaisBateria) {
		char* dest = auxLocaisBateria->localizacao;
		int s = ProcurarIdVertice(gr, src);
		int d = ProcurarIdVertice(gr, dest);

		// Create and initialize the visited array
		bool* visited = (bool*)malloc(CalcularTamanhoGrafo * sizeof(bool));
		for (int i = 0; i < CalcularTamanhoGrafo; i++)
			visited[i] = false;

		countPaths += CountPaths(gr, s, d, 0, visited);

		// Free the visited array
		free(visited);

		// Update src and move to the next destination
		src = dest;
		auxLocaisBateria = auxLocaisBateria->proxima;
	}

	// Include the path from the last destination back to the central vertex
	int s = ProcurarIdVertice(gr, src);
	int d = ProcurarIdVertice(gr, central);

	// Create and initialize the visited array
	bool* visited = (bool*)malloc(CalcularTamanhoGrafo * sizeof(bool));
	for (int i = 0; i < CalcularTamanhoGrafo; i++)
		visited[i] = false;

	countPaths += CountPaths(gr, s, d, 0, visited);

	// Free the visited array
	free(visited);

	return countPaths;
}*/

#pragma endregion

#pragma region Veículos_Area
/**
 * Cria uma lista com todos os veículos de determinado tipo.
 * 
 * \param tipoVeiculo
 * \return listaTipo
 */
ListaVeiculo* SelecionarVeiculosTipo(char* tipoVeiculo) {
	ListaVeiculo* listaAtual = LerListaVeiculoBin(); //Armazena os veículos do ficheiro binário em uma lista
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
 * Compara a listaTipo e a listaArea e imprime no ecrã os veículos daquele tipo naquele raio.
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
