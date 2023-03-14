//#include <iostream>
#include <fstream> 
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
void charAInt(char c){
	int n;
	if (c == 0) n = 0;
	else if (c == 1) n = 1;
	else if (c == 2) n = 2;
	else if (c == 3) n = 3;
	else if (c == 4) n = 4;
	return n;
}
bool leerTablero(ifstream& archivo, tTablero& tab){
	archivo.open("tablero.txt");
	archivo >> tab.nFils;
	archivo >> tab.nCols;
	for (int i; i < tab.nFils; i++){
		for (int j; j < tab.nCols; j++){
			char tipo;
			archivo >> tipo;
			if (tipo == '.') {
				tab.tablero[i][j].tipo = LIBRE;
				tab.tablero[i][j].numBombillas = 0;
			}
			else if (tipo == 'X') {
				tab.tablero[i][j].tipo = PARED;
				tab.tablero[i][j].numBombillas = -1;
			}
			else {
				tab.tablero[i][j].tipo = PARED;
				tab.tablero[i][j].numBombillas = charAInt(tipo);
			}
		}
	}
}

void mostrarTablero(const tTablero& tab){
	//cout << BG_YELLOW << RED << " * " << RESET;
	cout << setw(3) << right << "|";
	for (int i = 0; i < tab.nCols; i++) {
		cout << setw(3) << center << BLUE << i << RESET << "|";
	}

	for (int i = 0; i < tab.nFils; i++) { 
		for(int j = 0; j < tab.nCols; j++){
			cout << "-+---+---+---+---+---+" << endl;
			cout << setw(3) << center << BLUE << i << RESET << "|";
			if (estaIluminada(tab.tablero[i][j])) {
				if esBombilla(tab.tablero[i][j]) cout << setw(3) << BG_YELLOW << ORANGE << "*" << RESET; //esto tambien
				else cout << setw(3) << BG_YELLOW << "" << RESET; //esto tambien 
			}
			else if (estaApagada(tab.tablero[i][j])) cout << setw(3) << BG_WHITE << "" << RESET; // revisar si lo pinta todo de blanco sin poner espacio
			else if (esParedRestringida(tab.tablero[i][j])) cout << setw(3) << BG_BLACK << WHITE << numParedRestringida(tab.tablero[i][j]) << RESET;
			else if (esPared(tab.tablero[i][j]) cout << setw(3) << BG_WHITE << "" << RESET;
			cout << "|";
		}
	}
}
}
int main() {
	tTablero tablero;
	ifstream archivo;
	archivo.open("tablero.txt");
	
	leerTablero(archivo, tablero);
	mostrarTablero(tablero);
}
