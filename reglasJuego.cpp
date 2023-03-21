#include "reglasJuego.h"
#include "celda.h"
#include "tablero.h"

bool estaTerminado(tTablero const& tab) {
	bool condicion = true;
	int i = 0;
	int j = 0;
	while (i < tab.nFils && condicion) {
		while (j < tab.nFils && condicion) {
			if (estaIluminada(tab.tablero[i][j]) || esPared(tab.tablero[i][j]) || esBombilla(tab.tablero[i][j])) j++;
			else condicion = false;
		}
		i++;
	}
	return condicion;
}


bool esPosQuit(int x, int y){
	bool coincide = false;
	if (x == -1 && y == 0) coincide = true;
	return coincide;
}

void ejecutarPos(tTablero& tab, int x, int y){
	if(esPared(tab.tablero[x][y]) || estaIluminada(tab.tablero[x][y])){
		cout << "(" << x << "," << y << ")" << " No es una posicion valida" << endl;
		cout << "Porfavor introduzcalo de nuevo" << endl;
	}
	else {
		bool iluminar;
		if (esBombilla(tab.tablero[x][y])) {
			iluminar = false;
			apagaCelda(tab.tablero[x][y]);

		}
		else {
			iluminar = true;
			ponBombilla(tab.tablero[x][y]);
		}
		bool terminarIz = false, terminarDe = false, terminarAr = false, terminarAb = false;
		int i = 1;
		while (!terminarIz || !terminarDe || !terminarAr || !terminarAb) {
			
			if (esPared(tab.tablero[x][y + i]) && y + i < tab.nFils) terminarAb = true;
			else actualizaIluminaciónCelda(tab.tablero[x][y + i], true);

			if (esPared(tab.tablero[x][y - i]) && y - i >= 0) terminarAr = true;
			else actualizaIluminaciónCelda(tab.tablero[x][y - i], true);

			if (esPared(tab.tablero[x - i][y]) && x - i >= 0) terminarIz = true;
			else actualizaIluminaciónCelda(tab.tablero[x - i][y], true);

			if (esPared(tab.tablero[x + i][y]) && x + i < tab.nCols) terminarDe = true;
			else actualizaIluminaciónCelda(tab.tablero[x + i][y], true);

				
			i++;
		}
		actualizaIluminaciónCelda(tab.tablero[x][y], true);

	}
}