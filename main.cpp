// Practica FP2 LIGHTUP
//
// Hecho por Rubén Hidalgo Arias y Álvaro Moreno Arribas

#include "reglasJuego.h"
#include "tablero.h"
#include "listaPosiciones.h";
#include "partida.h"

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

	archivo.close();

	juega();

	return 33;
}

