#pragma once
#define REGLASJUEGO_H
#include "tablero.h"

typedef enum tDir { NORTE, SUR, ESTE, OESTE, NADA };

bool estaTerminado(const tTablero& tab);
bool esPosQuit(int x, int y);
bool esPosReset(int x, int y);
void iluminarAlrededor(tTablero& tab, int x, int y, bool iluminar);
void ejecutarPos(tTablero& tab, int x, int y);