#pragma once
#define REGLASJUEGO_H

bool estaTerminado(tTablero const& tab);
bool esPosQuit(int x, int y);
void ejecutarPos(tTablero& tab, int x, int y);