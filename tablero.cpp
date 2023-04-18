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



