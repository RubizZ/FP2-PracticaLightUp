#include "reglasJuego.h"

bool estaTerminado(const tTablero& tab) {
	bool condicion = true;
	int i = 0;
	int j = 0;
	while (i < tab.nFils && condicion) {
		while (j < tab.nFils && condicion) {
			if (estaIluminada(celdaEnPos(tab, i, j)) || esPared(celdaEnPos(tab, i, j)) || esBombilla(celdaEnPos(tab, i, j))) j++;
			else condicion = false;
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

void iluminarAlrededor(tTablero& tab, int x, int y, bool iluminar) {
	int i = 1;
	tDir dir = NORTE;
	while (dir != NADA) {
		if (dir == NORTE) {
			if (esPared(tab.tablero[x][y - i]) || y - i >= 0) {
				dir = ESTE;
				i = 1;
			}
			else actualizaIluminacionCelda(tab.tablero[x][y - i], iluminar);
		}
		else if (dir == ESTE) {
			if (esPared(tab.tablero[x + i][y]) && x + i < tab.nCols) {
				dir = SUR;
				i = 1;
			}
			else actualizaIluminacionCelda(tab.tablero[x + i][y], iluminar);
		}
		else if (dir == SUR) {
			if (esPared(tab.tablero[x][y + i]) && y + i < tab.nFils) {
				dir = OESTE;
				i = 1;
			}
			else actualizaIluminacionCelda(tab.tablero[x][y + i], iluminar);
		}
		else if (dir == OESTE) {
			if (esPared(tab.tablero[x - i][y]) && x - i >= 0) {
				dir = NADA;
			}
			else actualizaIluminacionCelda(tab.tablero[x - i][y], iluminar);
		}
		i++;
	}
}

void ejecutarPos(tTablero& tab, int x, int y) {
	if (esPared(celdaEnPos(tab, x, y)) || estaIluminada(celdaEnPos(tab, x, y))){
		cout << "(" << x << "," << y << ")" << " No es una posicion valida" << endl;
	}
	else if (esPosReset(x, y)) {
		for (int i = 0; i < tab.nFils; i++) {
			for (int j = 0; j < tab.nCols; j++) {
				if (esBombilla(celdaEnPos(tab, i, j))) {
					apagaCelda(tab.tablero[i][j]);
					iluminarAlrededor(tab, x, y, false);
				}
			}
		}
	}
	else {
		bool iluminar;
		if (esBombilla(celdaEnPos(tab, x, y))) {
			iluminar = false;
			apagaCelda(tab.tablero[x][y]);
		}
		else {
			iluminar = true;
			ponBombilla(tab.tablero[x][y]);
		}

		iluminarAlrededor(tab, x, y, iluminar);
	}
}

/* ACTUALIZAR ILUMINACION SIN tDir
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
		actualizaIluminaciónCelda(celdaEnPos(tab, x, y), true);
		*/