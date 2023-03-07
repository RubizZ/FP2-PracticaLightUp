#include <iostream>
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
bool leerTablero(ifstream& archivo, tTablero& tab){
	archivo.open("tablero.txt");
	archivo >> tab.nFils;
	archivo >> tab.nCols;
	for (int i; i < tab.nFils; i++){
		for (int j; j < tab.nCols; j++){
			char tipo;
			archivo >> tipo;
			if (tipo == '.') tab.tablero[i][j].tipo = LIBRE;
			else if (tipo == 'X') {
				tab.tablero[i][j].tipo = PARED;
				tab.tablero[i][j].numBombillas = 0;
			}
			else {
				tab.tablero[i][j].tipo = PARED;
				tab.tablero[i][j].tipo = //hacer char a int;
			}
		}
	}
}
void mostrarTablero(const tTablero& tab){
	//cout << BG_YELLOW << RED << " * " << RESET;
	for (int i = 0; i < MAX_FILS; i++) {

		for (int j = 0; j< )


	}

}