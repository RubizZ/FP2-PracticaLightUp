// Practica FP2 LIGHTUP
//
// Hecho por Rubén Hidalgo Arias y Álvaro Moreno Arribas

#include "reglasJuego.h"
#include "tablero.h"
#include "listaPosiciones.h";

void colocarBombillas(ifstream& archivo, tTablero& tab);

int main() {
	tTablero tablero;
	ifstream archivo;
	ofstream archivo2;
	string nombre;

	bool primera = true;
	do {
		if (!primera && archivo.is_open()) {
			cout << "ERROR: El archivo no es un tablero valido\n\n";
			archivo.close();
		}
		else primera = false;
		do {
			cout << "Introduce el archivo del tablero\n\n-> ";
			cin >> nombre;
			cout << endl;
			archivo.open(nombre);
			if (!archivo.is_open()) cout << "ERROR: El archivo no existe\n\n";
		} while (!archivo.is_open());
		cout << "Archivo existente, leyendo el tablero...\n\n";
	} while (!leerTablero(archivo, tablero) || estaTerminado(tablero));
	
	colocarBombillas(archivo, tablero);
	archivo.close();
	mostrarTablero(tablero);
	
	int x = -1, y = 0;
	do {
		cout << "En que posicion quieres poner o quitar una bombilla?\n-1 0 para salir, -1 -1 para resetear\n\n-> ";
		cin >> x;
		cin >> y;
		cout << endl;
		
		if (!esPosQuit(x, y)) {
			if (!ejecutarPos(tablero, x, y)) cout << "ERROR: Esa no es una posicion valida\n";
			else mostrarTablero(tablero);
			if (estaTerminado(tablero)) cout << "Has terminado el juego!\n";
		}
		else cout << "Saliendo del juego...\n";

	} while (!esPosQuit(x, y) && !estaTerminado(tablero));

	return 33;
}

void colocarBombillas(ifstream& archivo, tTablero& tab) {
	int bombillas = 0;
	archivo >> bombillas;
	if (bombillas > 0) {
		for (int i = 0; i < bombillas; i++) {
			int fila, columna;
			archivo >> fila;
			archivo >> columna;
			tCelda c;
			ponBombilla(c);
			ponCeldaEnPos(tab, fila, columna, c);
			iluminarAlrededor(tab, fila, columna, true);
		}
	}
}