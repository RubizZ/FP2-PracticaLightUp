//#include <iostream>
#include <fstream> 
#include <iomanip>
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
int charAInt(char c){
	int n = 0;
	if (c == '0') n = 0;
	else if (c == '1') n = 1;
	else if (c == '2') n = 2;
	else if (c == '3') n = 3;
	else if (c == '4') n = 4;
	return n;
}
bool leerTablero(ifstream& archivo, tTablero& tab){
	bool condicion = false;
	archivo.open("tablero.txt");
	if (archivo.is_open()) {
		condicion = true;
		archivo >> tab.nFils;
		archivo >> tab.nCols;
		for (int i = 0; i < tab.nFils; i++) {
			for (int j = 0; j < tab.nCols; j++) {
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
	return condicion;
	
}

void mostrarTablero(const tTablero& tab){
	//cout << BG_YELLOW << RED << " * " << RESET;
	cout << setw(4) << right << "|";
	for (int i = 0; i < tab.nCols; i++) {
		cout << BLUE << " " << i << " " << RESET << "|";
	}
	cout << endl;
	cout << "---+---+---+---+---+---+" << endl;
	for (int i = 0; i < tab.nFils; i++) { 
		
		cout << BLUE << " " << i << " " << RESET << "|";
		for(int j = 0; j < tab.nCols; j++){
			
			if (estaIluminada(tab.tablero[i][j])) {
				if (esBombilla(tab.tablero[i][j])) cout << BG_YELLOW << ORANGE << " * " << RESET;
				else cout << setw(3) << BG_YELLOW << "   " << RESET;
			}
			else if (estaApagada(tab.tablero[i][j])) cout << BG_WHITE << "   " << RESET;
			else if (esParedRestringida(tab.tablero[i][j])) cout << BG_BLACK << WHITE << " " << numParedRestringida(tab.tablero[i][j]) << " " << RESET;
			else if (esPared(tab.tablero[i][j])) cout << BG_BLACK<< "   " << RESET;
			cout << "|";
		}
		cout << endl << "---+---+---+---+---+---+" << endl;
	}
}
int main() {
	tTablero tablero;
	ifstream archivo;
	
	if (leerTablero(archivo, tablero)) {
		mostrarTablero(tablero);
	}
	else cout << "Ha habido un error";
}
