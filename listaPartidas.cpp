#include "listaPartidas.h"

void mueve(tListaPartidas& listaPartidas, const int i, const bool derecha);

void iniciaListaPartidas(tListaPartidas& listaPartidas) {
	listaPartidas.nElem = 0;
}

void cargarListaPartidas(ifstream& archivo, tListaPartidas& listaPartidas) {
	archivo >> listaPartidas.nElem;
	for (int i = 0; i < listaPartidas.nElem; i++) {
		
		tPartida partida;
		iniciaPartida(partida);
		cargarPartida(archivo, partida);

		insertarOrd(listaPartidas, partida);
	}
}

void insertarOrd(tListaPartidas& listaPartidas, const tPartida& partida) {
	int i = 0;
	bool terminar = false;
	
	while (i < listaPartidas.nElem && !terminar) {
		if (partida < *listaPartidas.datos[i]) terminar = true;
		else i++;
	}
	mueve(listaPartidas, i, true);
	listaPartidas.datos[i] = new tPartida(partida);
	listaPartidas.nElem++;
}

void mueve(tListaPartidas& listaPartidas, const int i, const bool derecha) {
	for (int j = i; j < listaPartidas.nElem - 1; j++) {
		if (derecha) listaPartidas.datos[j + 1] = listaPartidas.datos[j];
		else listaPartidas.datos[j] = listaPartidas.datos[j + 1];
	}
}

int buscaPos(const tListaPartidas& listaPartidas, int nivel) {
	bool encontrado = false;
	int i = 0;
	while (!encontrado && i < listaPartidas.nElem) {
		if (*listaPartidas.datos[i] < nivel) i++;
		else encontrado = true;
	}
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
	while (!terminar) {
		if (*listaPartidas.datos[i] == partida) terminar = true;
		else i++;
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
	delete[] listaPartidas.datos;
}