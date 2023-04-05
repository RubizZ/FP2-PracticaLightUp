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

bool comprobarParedRestringida(const tTablero tab, const int x, const int y) {
	int num = 0;
	
	if (x - 1 >= 0 && esBombilla(tab.tablero[x - 1][y])) num++;
	if (y + 1 < tab.nCols && esBombilla(tab.tablero[x][y + 1])) num++;
	if (x + 1 < tab.nFils && esBombilla(tab.tablero[x + 1][y])) num++;
	if (y - 1 >= 0 && esBombilla(tab.tablero[x][y - 1])) num++;
	
	return numParedRestringida(tab.tablero[x][y]) == num;
}

void iluminarAlrededor(tTablero& tab, int x, int y, bool iluminar) {
	tDir dir = NORTE;
	do {
		int i = 1;
		switch (dir) {
		case NORTE:
			while (x - i >= 0 && !esPared(celdaEnPos(tab, x - i, y))) {
				actualizaIluminacionCelda(tab.tablero[x - i][y], iluminar);
				i++;
			}
			break;
		case ESTE:
			while (y + i < tab.nFils && !esPared(tab.tablero[x][y + i])) {
				actualizaIluminacionCelda(tab.tablero[x][y + i], iluminar);
				i++;
			}
			break;
		case SUR:
			while (x + i < tab.nCols && !esPared(tab.tablero[x + i][y])) {
				actualizaIluminacionCelda(tab.tablero[x + i][y], iluminar);
				i++;
			}
			break;
		case OESTE:
			while (y - i >= 0 && !esPared(tab.tablero[x][y - i])) {
				actualizaIluminacionCelda(tab.tablero[x][y - i], iluminar);
				i++;
			}
			break;
		}
		dir++;
	} while (dir != NORTE);
}

tDir operator ++ (tDir& dir, int) {
	tDir dirAnterior = dir;
	switch (dir) {
	case NORTE:
		dir = ESTE;
		break;
	case ESTE:
		dir = SUR;
		break;
	case SUR:
		dir = OESTE;
		break;
	case OESTE:
		dir = NORTE;
		break;
	}
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



/* iluminarAlrededor SIN tDir QUE ILUMINA UNIFORMEMENTE EN CADA DIRECCION
	bool terminarN = false, terminarE = false, terminarS = false, terminarO = false;
	int i = 1;
	while (!terminarN || !terminarE || !terminarS || !terminarO) {

		if (!terminarN && !esPared(tab.tablero[x][y - i]) && y - i >= 0) actualizaIluminaciónCelda(tab.tablero[x][y - i], iluminar);
		else terminarN = true;

		if (!terminarE && !esPared(tab.tablero[x + i][y]) && x + i < tab.nCols) actualizaIluminaciónCelda(tab.tablero[x + i][y], iluminar);
		else terminarE = true;
		
		if (!terminarS && !esPared(tab.tablero[x][y + i]) && y + i < tab.nFils) actualizaIluminaciónCelda(tab.tablero[x][y + i], iluminar); 
		else terminarS = true;

		if (!terminarO && !esPared(tab.tablero[x - i][y]) && x - i >= 0) actualizaIluminaciónCelda(tab.tablero[x - i][y], iluminar);
		else terminarO = true;

		i++;
	}
*/