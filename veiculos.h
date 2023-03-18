#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "dados.h"

#pragma once
ListaVeiculo* LerFicheiroVeiculoTxt();
bool VerificarExisteVeiculo(ListaVeiculo* listaVeiculo, Veiculo* novoVeiculo);
ListaVeiculo* CriarListaVeiculo(ListaVeiculo* listaVeiculo, Veiculo* novoVeiculo);
ListaVeiculo* InserirVeiculo(ListaVeiculo* listaVeiculo, Veiculo* novoVeiculo);
bool CriarListaVeiculoBin(ListaVeiculo* listaVeiculo);
bool InserirListaVeiculoBin(ListaVeiculo* listaVeiculo);
ListaVeiculo* LerListaVeiculoBin();
bool AlterarListaVeiculoBin(Veiculo novosDados);
bool RemoverDadosListaVeiculoBin(int id);
bool ListarVeiculoBin();
