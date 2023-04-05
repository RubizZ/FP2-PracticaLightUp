#include "reglasJuego.h"
#include "tablero.h"

int main() {
	tTablero tablero;
	ifstream archivo;
	string nombre;

	do {
		if (archivo.is_open()) {
			cout << "ERROR: El archivo no es un tablero valido\n\n";
			archivo.close();
		}
		else 
		do {
			cout << "Introduce el archivo del tablero\n\n-> ";
			cin >> nombre;
			cout << endl;
			archivo.open(nombre);
			if (!archivo.is_open()) cout << "ERROR: El archivo no existe\n\n";
		} while (!archivo.is_open());
		cout << "Archivo existente, leyendo el tablero...\n\n";
	} while (!leerTablero(archivo, tablero) && !estaTerminado(tablero));
	
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
