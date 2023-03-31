//#include <iostream>

#include "tablero.h"


int getNumFilas(const tTablero& tab){
	return tab.nFils;
}
int getNumCols(const tTablero& tab){
	return tab.nCols;
}
tCelda celdaEnPos(const tTablero& tab, int x, int y){
	return tab.tablero[x][y];
}
void ponCeldaEnPos(tTablero& tab, int x, int y, const tCelda& c){
	tab.tablero[x][y] = c;
}

bool leerTablero(ifstream& archivo, tTablero& tab){
	bool condicion = false;
	archivo >> tab.nFils;
	archivo >> tab.nCols;

	if (tab.nFils < MAX_FILS && tab.nCols < MAX_COLS) {
		condicion = true;
		for (int i = 0; i < tab.nFils; i++) {
			for (int j = 0; j < tab.nCols; j++) {
				char tipo = '.';
				archivo >> tipo;

				tab.tablero[i][j] = charToCelda(tipo);
				
				/*
				if (tipo == '.') {
					tab.tablero[i][j].tipo = libre;
					tab.tablero[i][j].numbombillas = 0;
				}
				else if (tipo == 'x') {
					tab.tablero[i][j].tipo = pared;
					tab.tablero[i][j].numbombillas = -1;
				}
				else {
					tab.tablero[i][j].tipo = pared;
					tab.tablero[i][j].numbombillas = charaint(tipo);
				}
				*/
			}
		}
	}
	return condicion;
}

void mostrarTablero(const tTablero& tab){
	cout << setw(4) << right << "|";
	for (int i = 0; i < tab.nCols; i++) {
		cout << BLUE << " " << i << " " << RESET << "|";
	}
	cout << endl;
	
	for (int i = 0; i < tab.nFils; i++) { 
		for (int j = 0; j <= tab.nCols; j++) cout << "---+";
		cout << endl;
		cout << BLUE << " " << i << " " << RESET << "|";
		for (int j = 0; j < tab.nCols; j++){
			char c = celdaToChar(tab.tablero[i][j]);
			if (estaIluminada(tab.tablero[i][j])) cout << BG_YELLOW << " " << c << " " << RESET;
			else if (esBombilla(tab.tablero[i][j])) cout << BG_YELLOW << ORANGE << " " << c << " " << RESET;
			else if (estaApagada(tab.tablero[i][j])) cout << BG_WHITE << " " << c << " " << RESET;
			else if (esParedRestringida(tab.tablero[i][j])) cout << BG_BLACK << WHITE << " " << c << " " << RESET;
			else if (esPared(tab.tablero[i][j])) cout << BG_BLACK << " " << c << " " << RESET;
			cout << "|";
		}
		cout << endl;
	}
	for (int j = 0; j <= tab.nCols; j++) cout << "---+";
	cout << endl << endl;
}

bool comprobarParedRestringida(const tTablero tab, const int x, const int y) {
	int num = 0;
	if (esBombilla(tab.tablero[x][y - 1])) num++;
	if (esBombilla(tab.tablero[x + 1][y])) num++;
	if (esBombilla(tab.tablero[x][y + 1])) num++;
	if (esBombilla(tab.tablero[x - 1][y])) num++;

	return numParedRestringida(tab.tablero[x][y]) == num;
}

void iluminarAlrededor(tTablero& tab, int x, int y, bool iluminar) {
	tCelda c;
	tDir dir = NORTE;

	int i = 0;
	while (dir != NADA) {
		i++;
		if (dir == NORTE) {
			if (y - i < 0 || esPared(tab.tablero[x][y - i])) {
				dir = ESTE;
				i = 0;
			}
			else actualizaIluminacionCelda(tab.tablero[x][y - i], iluminar);
		}
		else if (dir == ESTE) {
			if (x + i > tab.nCols || esPared(tab.tablero[x + i][y])) {
				dir = SUR;
				i = 0;
			}
			else actualizaIluminacionCelda(tab.tablero[x + i][y], iluminar);
		}
		else if (dir == SUR) {
			if (y + i > tab.nFils || esPared(tab.tablero[x][y + i])) {
				dir = OESTE;
				i = 0;
			}
			else actualizaIluminacionCelda(tab.tablero[x][y + i], iluminar);
		}
		else if (dir == OESTE) {
			if (x - i < 0 || esPared(celdaEnPos(tab, x - i, y))) {
				dir = NADA;
			}
			else actualizaIluminacionCelda(tab.tablero[x - i][y], iluminar);
		}
	}
}

void colocarBombillas(ifstream& archivo, tTablero& tab) {
	int bombillas = 0;
	archivo >> bombillas;
	if (bombillas > 0) {
		for (int i = 0; i < bombillas; i++) {
			int fila, columna;
			tCelda c;
			archivo >> fila;
			archivo >> columna;

			ponBombilla(tab.tablero[fila][columna]);
			iluminarAlrededor(tab, fila, columna, true);
		}
	}
}