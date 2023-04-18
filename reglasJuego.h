#pragma once
#define REGLASJUEGO_H
#include "tablero.h"

typedef enum tDir { NORTE, SUR, ESTE, OESTE };

bool estaTerminado(const tTablero& tab);
bool esPosQuit(int x, int y);
bool ejecutarPos(tTablero& tab, int x, int y);
void iluminarAlrededor(tTablero& tab, int x, int y, bool iluminar);