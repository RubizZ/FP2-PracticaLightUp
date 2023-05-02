#include "listaPartidas.h"

void mueve(tListaPartidas& listaPartidas, const int i, const bool derecha);

void iniciaListaPartidas(tListaPartidas& listaPartidas) {
	listaPartidas.nElem = 0;
}

bool cargarListaPartidas(ifstream& archivo, tListaPartidas& listaPartidas) {
	bool condicion = false;
	int numPartidas;
	archivo >> numPartidas;
	if (numPartidas > 0 && numPartidas < MAX_PARTIDAS) {
		condicion = true;
		for (int i = 0; i < numPartidas; i++) {

			tPartida partida;
			cargarPartida(archivo, partida);

			insertarOrd(listaPartidas, partida);
		}
	}
	return condicion;
}

void insertarOrd(tListaPartidas& listaPartidas, const tPartida& partida) {
	int i = 0;
	
	while (i < listaPartidas.nElem && *listaPartidas.datos[i] < partida) {
		i++;
	}
	mueve(listaPartidas, i, true);
	listaPartidas.datos[i] = new tPartida(partida);
	listaPartidas.nElem++;
}

void mueve(tListaPartidas& listaPartidas, const int i, const bool derecha) {
	for (int j = i; j < listaPartidas.nElem; j++) {
		if (derecha) listaPartidas.datos[j + 1] = listaPartidas.datos[j];
		else listaPartidas.datos[j] = listaPartidas.datos[j + 1];
	}
}

int buscaPos(const tListaPartidas& listaPartidas, int nivel) {

	int i = 0;
	while (i < listaPartidas.nElem && *listaPartidas.datos[i] < nivel) {
		i++;
	}
	if (i == listaPartidas.nElem) i--;
	return i;
}

tPtrPartida dameElem(const tListaPartidas& listaPartidas, int pos) {
	return listaPartidas.datos[pos];
}

int dameNumElem(const tListaPartidas& listaPartidas) {
	return listaPartidas.nElem;
}

void eliminarPartida(tListaPartidas& listaPartidas, const tPartida& partida) {
	bool terminar = false;
	int i = 0;
	while (*listaPartidas.datos[i] < partida) {
		i++;
	}
	destruyePartida(*listaPartidas.datos[i]);
	mueve(listaPartidas, i, false);
	listaPartidas.nElem--;
	listaPartidas.datos[listaPartidas.nElem] = nullptr;
}

void guardarListaPartidas(ofstream& archivo, const tListaPartidas& listaPartidas) {
	archivo << listaPartidas.nElem << endl;
	for (int i = 0; i < listaPartidas.nElem; i++) guardarPartida(archivo, *listaPartidas.datos[i]);
}

void destruyeListaPartidas(tListaPartidas& listaPartidas) {
	for (int i = 0; i < listaPartidas.nElem; i++) {
		delete[] listaPartidas.datos[i];
		listaPartidas.datos[i] = nullptr;
	}
	listaPartidas.nElem = 0;
}