#include "listaPartidas.h"

void mueveDerecha(tListaPartidas& ptr, const int i);

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
		listaPartidas.nElem++;
	}
}

void insertarOrd(tListaPartidas& listaPartidas, const tPartida& partida) {
	int i = 0;
	bool terminar = false;
	
	if (listaPartidas.nElem == 0) {
		//
	} else while (i < listaPartidas.nElem - 1, !terminar) {
		if (partida < *listaPartidas.datos[i]) {
			mueveDerecha(listaPartidas, i);
			listaPartidas.datos[i] = new tPartida(partida);
			terminar = true;
		} else i++;
	}
}

void mueveDerecha(tListaPartidas& listaPartidas, const int i) {
	for (int j = listaPartidas.nElem; j >= i; j--) {
		listaPartidas.datos[j + 1] = listaPartidas.datos[j];
	}
}

int buscaPos(const tListaPartidas& listaPartidas, int nivel) {
	int pos;
	bool encontrado = false;
	int i = 0;
	while (encontrado = false && i < listaPartidas.nElem){
		listaPartidas.datos[i]




	}


}

tPtrPartida dameElem(const tListaPartidas& listaPartidas, int pos) {
	return listaPartidas.datos[pos];
}

int dameNumElem(const tListaPartidas& listaPartidas) {
	return listaPartidas.nElem;
}

void eliminarPartida(tListaPartidas& listaPartidas, const tPartida& partida) {
	
}

void guardarListaPartidas(ofstream& archivo, const tListaPartidas& listaPartidas) {

}

void destruyeListaPartidas(tListaPartidas& listaPartidas) {
	delete[] listaPartidas.datos;
}