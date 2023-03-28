#include "reglasJuego.h"
#include "tablero.h"

int main() {
	tTablero tablero;
	ifstream archivo;
	string nombre;

	cout << "Introduce el nombre del tablero\n\n-> ";
	cin >> nombre;
	cout << endl;

	while (!leerTablero(archivo, tablero, nombre)) {
		cout << "El fichero no es un tablero valido\nIntroduce el nombre del tablero\n\n-> ";
		cin >> nombre;
		cout << endl;
	}

	int x = 0, y = 0;
	while (!esPosQuit(x, y) && !estaTerminado(tablero)) {
		mostrarTablero(tablero);
		cout << "En que posicion quieres poner o quitar una bombilla? -1 0 para salir, -1 -1 para resetear\n\n-> ";
		cin >> x;
		cin >> y;
		cout << endl;
		if (!esPosQuit(x, y)) {
			ejecutarPos(tablero, x, y);
			if (estaTerminado(tablero)) {
				mostrarTablero(tablero);
				cout << "Has terminado el juego!";
			}
		}
	}
}