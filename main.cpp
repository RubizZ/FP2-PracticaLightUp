// Practica FP2 LIGHTUP
//
// Hecho por Rubén Hidalgo Arias y Álvaro Moreno Arribas

using namespace std;

#include <iostream>
#include <fstream>
#include "listaPartidas.h"

void cargaArchivoCorrecto(tListaPartidas& listaPartidas);
int eligeNivel(const tListaPartidas& listaPartidas);
void guardaEnArchivo(const tListaPartidas& listaPartidas);

int main() {
	tListaPartidas partidas;

	cargaArchivoCorrecto(partidas);

	int index = eligeNivel(partidas);

	if (!juega(*dameElem(partidas, index))) {
		eliminarPartida(partidas, *dameElem(partidas, index));
	}
	guardaEnArchivo(partidas);
	destruyeListaPartidas(partidas);
	return 33;
}

void cargaArchivoCorrecto(tListaPartidas& listaPartidas) {
	string nombre;
	ifstream input;
	bool primera = true;
	do {
		if (!primera && input.is_open()) {
			cout << "ERROR: El archivo no es una lista de partidas valida\n\n";
			input.close();
		}
		else primera = false;
		do {
			cout << "Introduce el archivo de la lista de partidas\n\n-> ";
			cin >> nombre;
			cout << endl;
			input.open(nombre);
			if (!input.is_open()) cout << "ERROR: El archivo no existe\n\n";
		} while (!input.is_open());
		cout << "Archivo existente, leyendo la lista...\n\n";
		iniciaListaPartidas(listaPartidas);
	} while (!cargarListaPartidas(input, listaPartidas));
	input.close();
}

int eligeNivel(const tListaPartidas& listaPartidas) {
	int nivel;
	cout << "Elige un nivel de dificultad\n\n-> ";
	cin >> nivel;
	cout << endl;
	return buscaPos(listaPartidas, nivel);
}

void guardaEnArchivo(const tListaPartidas& listaPartidas) {
	string nombre;
	ofstream output;
	do {
		cout << "En que archivo quieres guardar la lista de partidas\n\n-> ";
		cin >> nombre;
		cout << endl;
	} while (nombre == "");
	output.open(nombre);
	guardarListaPartidas(output, listaPartidas);
	output.close();
	cout << "Se han guardado las partidas correctamente\n";
}
