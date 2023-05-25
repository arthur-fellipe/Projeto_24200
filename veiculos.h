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
ListaVeiculo* CriarListaVeiculo(ListaVeiculo* listaVeiculo, Veiculo* novoVeiculo);
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


Localizacao* ListarLocais();
Vertice* CriarGrafo();
Vertice* CriarVertice();
//Vertice* CriarVertice(char* localizacao, int id);
Vertice* InserirVertice(Vertice* gr, Vertice* novoVertice, bool* res);
void MostrarGrafo(Vertice* gr);
void MostrarAdjacencias(Adj* h);

/*bool existeAresta(Grafo* gr, int vertice_inicial, int vertice_final) {
    Aresta* arestaTeste = gr->lista_adj[vertice_inicial].head;
    while (arestaTeste != NULL) {
        if (arestaTeste->vertice_destino == vertice_final) {
            return true;
        }
        arestaTeste = arestaTeste->proxima;
    }
    return false;
}

bool insereAresta(Grafo* gr, int vertice_inicial, int vertice_final, int peso) {
    if (!gr) return (false);
    if ((vertice_final < 1) || (vertice_final > gr->num_vertices))return(false);
    if ((vertice_inicial < 1) || (vertice_inicial > gr->num_vertices))return(false);

    Aresta* novaAresta1 = criaAresta(vertice_final, peso);
    novaAresta1->proxima = gr->lista_adj[vertice_inicial].head;
    gr->lista_adj[vertice_inicial].head = novaAresta1;

    Aresta* novaAresta2 = criaAresta(vertice_inicial, peso);
    novaAresta2->proxima = gr->lista_adj[vertice_final].head;
    gr->lista_adj[vertice_final].head = novaAresta2;

    return (true);
}*/
#pragma endregion