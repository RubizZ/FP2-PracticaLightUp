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
			if (estaIluminada(tab.tablero[i][j])) cout << BG_YELLOW << "   " << RESET;
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

void avanzarPosDir(int& x, int& y, const tDir dir) {
	switch (dir) {
	case NORTE: x--; break;
	case ESTE: y++; break;
	case SUR: x++; break;
	case OESTE: y--; break;
	}
}

void iluminarAlrededor(tTablero& tab, int x, int y, bool iluminar) {
	int xI = x, yI = y;
	for (tDir dir = NORTE; dir <= OESTE; dir++) {
		x = xI;
		y = yI;
		avanzarPosDir(x, y, dir);
		while (x >= 0 && x < tab.nFils && y >= 0 && y < tab.nCols && !esPared(tab.tablero[x][y])) {
			actualizaIluminacionCelda(tab.tablero[x][y], iluminar);
			avanzarPosDir(x, y, dir);
		}
	}
}

tDir operator ++ (tDir& dir, int) {
	tDir dirAnterior = dir;
	dir = tDir(dir + 1);
	return dirAnterior;
}

void colocarBombillas(ifstream& archivo, tTablero& tab) {
	int bombillas = 0;
	archivo >> bombillas;
	if (bombillas > 0) {
		for (int i = 0; i < bombillas; i++) {
			int fila, columna;
			archivo >> fila;
			archivo >> columna;

			ponBombilla(tab.tablero[fila][columna]);
			iluminarAlrededor(tab, fila, columna, true);
		}
	}
}