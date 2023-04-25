#pragma once
#define PARTIDA_H

#include "tablero.h"
#include "listaPosiciones.h"

typedef struct
{
	tTablero tablero;
	tListaPosiciones listaBombillas;
	int nivel;
} tPartida;

void iniciaPartida(tPartida& partida);
void cargarPartida(ifstream& archivo, tPartida& partida);
bool operator<(const tPartida& partida, int nivel);
bool operator<(const tPartida& partida1, const tPartida& partida2);
bool esigual(const tPartida& partida, int nivel);
bool juega(tPartida& partida, int& nIt);
void guardarPartida(ofstream& archivo, const tPartida& partida);
void destruyePartida(tPartida& partida);