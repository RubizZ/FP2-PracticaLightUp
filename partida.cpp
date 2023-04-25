#include "partida.h"
#include "reglasJuego.h"
#include <string>

void colocaEnArrayBombillas(ifstream& archivo, tListaPosiciones& listaBombillas);
void ponBombillas(tPartida& partida);

void iniciaPartida(tPartida& partida) {
	iniciaListaPosiciones(partida.listaBombillas);
}

void cargarPartida(ifstream& archivo, tPartida& partida) {
	string aux;
	getline(archivo, aux, ' ');

	archivo >> partida.nivel;
	leerTablero(archivo, partida.tablero);
	colocaEnArrayBombillas(archivo, partida.listaBombillas);
}

void colocaEnArrayBombillas(ifstream& archivo, tListaPosiciones& listaBombillas) {
	
	int bombillas = 0;
	archivo >> bombillas;
	if (bombillas > 0) {
		for (int i = 0; i < bombillas; i++) {
			int fila, columna;
			archivo >> fila;
			archivo >> columna;
			
			tPosicion pos;
			iniciaPosicion(pos, fila, columna);
			insertar(listaBombillas, pos);
		}
	}
}

bool operator<(const tPartida& partida, int nivel) {
	return partida.nivel < nivel;
}

bool operator<(const tPartida& partida1, const tPartida& partida2) {
	return partida1.nivel < partida2.nivel;
}

bool esigual(const tPartida& partida, int nivel){
	bool coincide = false;
	if (partida.nivel == nivel) coincide = true;
	return coincide;
}

bool juega(tPartida& partida, int& nIt) {
	bool abandono = false;
	
	ponBombillas(partida);

	mostrarTablero(partida.tablero);

	int x = -1, y = 0;
	do {
		cout << "En que posicion quieres poner o quitar una bombilla?\n-1 0 para salir, -1 -1 para resetear\n\n-> ";
		cin >> x;
		cin >> y;
		cout << endl;

		if (!esPosQuit(x, y)) {
			if (ejecutarPos(partida.tablero, x, y)) mostrarTablero(partida.tablero);
			if (estaTerminado(partida.tablero)) cout << "Has terminado el juego!\n";
		}
		else {
			cout << "Saliendo del juego...\n";
			abandono = true;
		}

	} while (!esPosQuit(x, y) && !estaTerminado(partida.tablero));
	return abandono;
}

void ponBombillas(tPartida& partida) {
	for (int i = 0; i < dameNumElem(partida.listaBombillas); i++) {
		int x = dameX(dameElem(partida.listaBombillas, i));
		int y = dameY(dameElem(partida.listaBombillas, i));
		bool aux = ejecutarPos(partida.tablero, x, y);
	}
}

void guardarPartida(ofstream& archivo, const tPartida& partida) {
	char c;

	archivo << partida.nivel << endl;
	archivo << getNumFilas(partida.tablero) << " "<< getNumCols(partida.tablero)<<endl;
	
	for (int i = 0;i < getNumFilas(partida.tablero) ;i++) {
		for (int j = 0; j < getNumCols(partida.tablero); j++) {
			c = celdaToChar(celdaEnPos(partida.tablero, i, j));
			if (c == ' ') archivo << ".";
			else if (c == '0') archivo << "X";
			else if (c == '1' || c == '2' || c == '3' || c == '4') archivo << c;
		}
		archivo << endl;
	}
}

void destruyePartida(tPartida& partida) {
	destruyeListaPosiciones(partida.listaBombillas);
}