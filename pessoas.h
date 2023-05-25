/*****************************************************************//**
 * \file   pessoas.h
 * \brief
 *
 * \author Arthur Fellipe
 * \date   March 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#pragma once

#pragma region Pessoa
typedef struct Pessoa
{
	int id;
	int admin;
	char nome[50];
	//char nif[9];
	//char morada[100];
	char localizacao[40];
	float saldo;
}Pessoa;

typedef struct ListaPessoa
{
	Pessoa p;
	struct ListaPessoa* proxima;
}ListaPessoa;
#pragma endregion

#pragma region Funções Pessoa
ListaPessoa* LerFicheiroPessoaTxt();
bool VerificarExistePessoa(ListaPessoa* listaPessoa, Pessoa* novaPessoa);
ListaPessoa* CriarListaPessoa(ListaPessoa* listaPessoa, Pessoa* nPessoa);
ListaPessoa* InserirPessoa(ListaPessoa* listaPessoa, Pessoa* nPessoa);
bool CriarListaPessoaBin(ListaPessoa* listaPessoa);
bool InserirListaPessoaBin(ListaPessoa* listaPessoa);
ListaPessoa* LerListaPessoaBin();
bool AlterarListaPessoaBin(Pessoa novosDados);
bool RemoverDadosListaPessoaBin(int id);
bool ListarPessoaBin();
#pragma endregion

/*#pragma region Grafo_Pessoas
typedef struct Aresta {
    char vertice_destino[40];
    int peso;
    struct Aresta* proxima;
} Aresta;

typedef struct Vertice {
    Aresta* head;
} Vertice;

typedef struct Grafo {
    int num_vertices;
    int num_arestas;
    Vertice* lista_adj;
} Grafo;

Grafo* criaGrafo(int N, int M) {
    Grafo* gr = malloc(sizeof(Grafo));
    gr->num_vertices = N;
    gr->num_arestas = M * 2;
    gr->lista_adj = malloc(N * sizeof(Vertice));

    for (int i = 1; i <= N; i++) {
        gr->lista_adj[i].head = NULL;
    }
    return(gr);
}

Aresta* criaAresta(int V, int W) {
    Aresta* novaAresta = malloc(sizeof(Aresta));
    novaAresta->vertice_destino = V;
    novaAresta->peso = W;
    novaAresta->proxima = NULL;

    return novaAresta;
}

bool existeAresta(Grafo* gr, int vertice_inicial, int vertice_final) {
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
