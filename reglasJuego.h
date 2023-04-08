#pragma once
#define REGLASJUEGO_H
#include "tablero.h"

bool estaTerminado(const tTablero& tab);
bool esPosQuit(int x, int y);
bool esPosReset(int x, int y);
bool ejecutarPos(tTablero& tab, int x, int y);
bool comprobarParedRestringida(const tTablero tab, const int x, const int y);