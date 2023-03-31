#pragma once
#define TABLERO_H
#include "celda.h"
#include <iostream>
#include <fstream> 
#include <iomanip>

const int MAX_FILS = 10;
const int MAX_COLS = 10;
typedef struct {
    int nFils, nCols;
    tCelda tablero[MAX_FILS][MAX_COLS];
} tTablero;

typedef enum tDir { NORTE, SUR, ESTE, OESTE, NADA };


int getNumFilas(const tTablero& tab);
int getNumCols(const tTablero& tab);
tCelda celdaEnPos(const tTablero& tab, int x, int y);
void ponCeldaEnPos(tTablero& tab, int x, int y, const tCelda& c);
bool leerTablero(ifstream& archivo, tTablero& tab);
void mostrarTablero(const tTablero& tab);
bool comprobarParedRestringida(const tTablero tab, const int x, const int y);
void colocarBombillas(ifstream& archivo, tTablero& tab);
void iluminarAlrededor(tTablero& tab, int x, int y, bool iluminar);
