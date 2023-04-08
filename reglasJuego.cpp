#include "reglasJuego.h"

bool estaTerminado(const tTablero& tab) {
	bool condicion = true;
	int i = 0;
	while (i < getNumFilas(tab) && condicion) {
		int j = 0;
		while (j < getNumCols(tab) && condicion) {
			tCelda c = celdaEnPos(tab, i, j);
			if (estaIluminada(c) || esBombilla(c) || (esPared(c) && (!esParedRestringida(c) || comprobarParedRestringida(tab, i, j)))) {
				j++;
			} else condicion = false;
		}
		i++;
	}
	return condicion;
}

bool esPosQuit(int x, int y){
	return (x == -1 && y == 0);
}

bool esPosReset(int x, int y) {
	return (x == -1 && y == -1);
}

bool ejecutarPos(tTablero& tab, int x, int y) {
	bool valida = true;
	if (esPared(celdaEnPos(tab, x, y)) || estaIluminada(celdaEnPos(tab, x, y)) || x > getNumFilas(tab) - 1 || y > getNumCols(tab) - 1) {
		valida = false;
	}
	else if (esPosReset(x, y)) {
		cout << "Reseteando el tablero...\n\n";
		for (int i = 0; i < getNumFilas(tab); i++) {
			for (int j = 0; j < getNumCols(tab); j++) {
				tCelda c = celdaEnPos(tab, i, j);
				if (esBombilla(c)) {
					apagaCelda(c);
					ponCeldaEnPos(tab, i, j, c);
					iluminarAlrededor(tab, i, j, false);
				}
			}
		}
	}
	else {
		bool iluminar;
		tCelda c = celdaEnPos(tab, x, y);
		if (esBombilla(c)) {
			apagaCelda(c);
			iluminar = false;
		}
		else {
			ponBombilla(c);
			iluminar = true;
		}
		ponCeldaEnPos(tab, x, y, c);
		iluminarAlrededor(tab, x, y, iluminar);
	}
	return valida;
}

bool comprobarParedRestringida(const tTablero tab, int x, int y) {
	int num = 0;
	int xI = x, yI = y;
	for (tDir dir = NORTE; dir <= OESTE; dir++) {
		avanzarPosDir(x, y, dir);
		if (x >= 0 && x < getNumFilas(tab) && y >= 0 && y < getNumCols(tab) && esBombilla(celdaEnPos(tab, x, y))) num++;
		x = xI;
		y = yI;
	}
	return numParedRestringida(celdaEnPos(tab, xI, yI)) == num;
}