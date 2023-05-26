/*****************************************************************//**
 * \file   veiculos.h
 * \brief  
 * 
 * \author Arthur Fellipe
 * \date   March 2023
 *********************************************************************/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#pragma once
#pragma region Veiculo
typedef struct Veiculo
{
	int id;
	char tipoVeiculo[20];
	int bateria;
	char localizacao[40];
	float custo;
	int disponibilidade;
	//int totalViagens;
}Veiculo;

typedef struct ListaVeiculo
{
	Veiculo v;
	struct ListaVeiculo* proxima;
}ListaVeiculo;
#pragma endregion

#pragma region Funções Veículo
ListaVeiculo* LerFicheiroVeiculoTxt();
bool VerificarExisteVeiculo(ListaVeiculo* listaVeiculo, Veiculo* novoVeiculo);
ListaVeiculo* CriarListaVeiculo();
ListaVeiculo* InserirVeiculo(ListaVeiculo* listaVeiculo, Veiculo* novoVeiculo);
bool CriarListaVeiculoBin(ListaVeiculo* listaVeiculo);
bool InserirListaVeiculoBin(ListaVeiculo* listaVeiculo);
ListaVeiculo* LerListaVeiculoBin();
bool AlterarListaVeiculoBin(Veiculo novosDados);
bool RemoverDadosListaVeiculoBin(int id);
bool ListarVeiculoOrdemDecrescente();
bool ListarVeiculoLocalizacao(char localizacao[]);
#pragma endregion

#pragma region Grafo_Veículos
typedef struct Adj {
    int id;
    int peso;
    struct Adj* proxima;
} Adj;

typedef struct Vertice {
    int id;
    char localizacao[40];
    bool visitado;
    struct Vertice* proxima;
    struct Adj* lista_adjacentes;
} Vertice;

typedef struct Localizacao {
    int id;
    char localizacao[40];
    struct Localizacao* proxima;
} Localizacao;


Localizacao* ListarLocaisVeiculos();
Vertice* CriarGrafo();
Vertice* CriarVertice();
Vertice* InserirVertice(Vertice* gr, Vertice* novoVertice, bool* res);
void MostrarGrafo(Vertice* gr);

Vertice* ProcurarVerticeLocal(Vertice* gr, char* localizacao);
Vertice* ProcuraVerticeId(Vertice* gr, int id);
int ProcurarIdVertice(Vertice* gr, char* localizacao);
Adj* CriarAdj(int id, int peso);
Vertice* InserirAdjacenteVertice(Vertice* gr, char* origem, char* dest, int peso, bool* res);
Adj* InserirAdj(Adj* h, Adj* novoAdj, bool* res);
bool ExisteAdjacentes(Adj* h, int id);
void MostrarAdjacencias(Adj* h);

ListaVeiculo* SelecionarVeiculosTipo(char tipoVeiculo[]);
Localizacao* DefinirArea(char* localizacaoPessoa, Vertice* gr, int raio);
bool ListarVeiculosArea(Vertice* gr);

#pragma endregion