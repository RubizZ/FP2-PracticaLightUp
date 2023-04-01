#include "reglasJuego.h"

bool estaTerminado(const tTablero& tab) {
	bool condicion = true;
	int i = 0;
	while (i < tab.nFils && condicion) {
		int j = 0;
		while (j < tab.nCols && condicion) {
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
			iluminar = false;
			apagaCelda(c);
			ponCeldaEnPos(tab, x, y, c);
		}
		else {
			iluminar = true;
			ponBombilla(c);
			ponCeldaEnPos(tab, x, y, c);
		}
		iluminarAlrededor(tab, x, y, iluminar);
	}
	return valida;
}

/* ILUMINAR ALREDEDOR SIN tDir
	bool terminarIz = false, terminarDe = false, terminarAr = false, terminarAb = false;
	int i = 1;
	while (!terminarIz || !terminarDe || !terminarAr || !terminarAb) {

		if (esPared(tab.tablero[x][y + i]) && y + i < tab.nFils) terminarAb = true;
		else actualizaIluminaciónCelda(tab.tablero[x][y + i], iluminar);

		if (esPared(tab.tablero[x][y - i]) && y - i >= 0) terminarAr = true;
		else actualizaIluminaciónCelda(tab.tablero[x][y - i], iluminar);

		if (esPared(tab.tablero[x - i][y]) && x - i >= 0) terminarIz = true;
		else actualizaIluminaciónCelda(tab.tablero[x - i][y], iluminar);

		if (esPared(tab.tablero[x + i][y]) && x + i < tab.nCols) terminarDe = true;
		else actualizaIluminaciónCelda(tab.tablero[x + i][y], iluminar);

		i++;
	}
*/

/* ILUMINAR ALREDEDOR CON tDir PERO SIN SWITCH INUTIL
	while (dir < NADA) {
		if (dir == NORTE) {
			if (esPared(celdaEnPos(tab, x, y - i)) || y - i == 0) {
				dir = ESTE;
				i = 1;
			}
			else {
				c = celdaEnPos(tab, x, y - i);
				actualizaIluminacionCelda(c, iluminar);
				ponCeldaEnPos(tab, x, y - i, c);
			}
		}
		else if (dir == ESTE) {
			if (esPared(celdaEnPos(tab, x + i, y)) || x + i == tab.nCols) {
				dir = SUR;
				i = 1;
			}
			else {
				c = celdaEnPos(tab, x + i, y);
				actualizaIluminacionCelda(c, iluminar);
				ponCeldaEnPos(tab, x + i, y, c);
			}
		}
		else if (dir == SUR) {
			if (esPared(celdaEnPos(tab, x, y + i)) || y + i == tab.nFils) {
				dir = OESTE;
				i = 1;
			}
			else {
				c = celdaEnPos(tab, x, y + i);
				actualizaIluminacionCelda(c, iluminar);
				ponCeldaEnPos(tab, x, y + i, c);
			}
		}
		else if (dir == OESTE) {
			if (esPared(celdaEnPos(tab, x - i, y)) || x - i == 0) {
				dir = NADA;
			}
			else {
				c = celdaEnPos(tab, x - i, y);
				actualizaIluminacionCelda(c, iluminar);
				ponCeldaEnPos(tab, x - i, y, c);
			}
		}
		i++;
	}
*/

/* ILUMINAR ALREDEDOR CON tDir y switch useless
	int i = 1;
	switch (dir) {
	NORTE:
		while (!esPared(celdaEnPos(tab, x + i, y)) && y - i != 0) {
			c = celdaEnPos(tab, x, y - i);
			actualizaIluminacionCelda(c, iluminar);
			ponCeldaEnPos(tab, x, y - i, c);
			i++;
		}
		dir = ESTE;
		break;
	ESTE:
		while (!esPared(celdaEnPos(tab, x + i, y)) && x + i != tab.nCols) {
			c = celdaEnPos(tab, x + i, y);
			actualizaIluminacionCelda(c, iluminar);
			ponCeldaEnPos(tab, x + i, y, c);
			i++;
		}
		dir = SUR;
		break;
	SUR:
		while (!esPared(celdaEnPos(tab, x, y + i)) && y + i != tab.nFils) {
			c = celdaEnPos(tab, x, y + i);
			actualizaIluminacionCelda(c, iluminar);
			ponCeldaEnPos(tab, x, y + i, c);
			i++;
		}
		dir = OESTE;
		break;
	OESTE:
		while (!esPared(celdaEnPos(tab, x - i, y)) && x - i != 0) {
			c = celdaEnPos(tab, x - i, y);
			actualizaIluminacionCelda(c, iluminar);
			ponCeldaEnPos(tab, x - i, y, c);
			i++;
		}
		break;
	}
	*/