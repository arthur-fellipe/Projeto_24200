#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "dados.h"

#pragma once
ListaViagem* RegistarViagem(ListaViagem* listaViagem, int id, Pessoa cliente, Veiculo veiculo, float precoViagem, float distanciaViagem);
bool VerificarExisteViagem(ListaViagem* listaViagem, Viagem* novaViagem);
ListaViagem* CriarListaViagem(ListaViagem* listaViagem, Viagem* novaViagem);
ListaViagem* InserirViagem(ListaViagem* listaViagem, Viagem* novaViagem);
