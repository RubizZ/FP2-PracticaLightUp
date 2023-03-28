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


int getNumFilas(const tTablero& tab);
int getNumCols(const tTablero& tab);
tCelda celdaEnPos(const tTablero& tab, int x, int y);
void ponCeldaEnPos(tTablero& tab, int x, int y, const tCelda& c);
bool leerTablero(ifstream& archivo, tTablero& tab, const string nombre);
void mostrarTablero(const tTablero& tab);
int charAInt(char c);