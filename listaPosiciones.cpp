#include "listaPosiciones.h"

void iniciaListaPosiciones(tListaPosiciones& lp) {
	lp.cont = 0;
	lp.size = DIM;
}
void destruyeListaPosiciones(tListaPosiciones& lp) {
	delete[] lp.arrayPos;
}
void insertar(tListaPosiciones& lp, const tPosicion& pos) {
	if (lp.cont == lp.size) {
		lp.size = lp.size * 2;
		tPosicion* aux = new tPosicion[lp.size];
		for (int i = 0; i < lp.cont; i++) {
			aux[i] = lp.arrayPos[i];
		}
		delete[] lp.arrayPos;
		lp.arrayPos = aux;
		aux = nullptr;
	}
	lp.arrayPos[lp.cont] = pos; //Arreglar esta puta vergüenza de linea
	lp.cont++;
}
int dameNumElem(const tListaPosiciones& lp) {
	return lp.cont;
}
tPosicion dameElem(const tListaPosiciones& lp, int i) {
	return lp.arrayPos[i];
}
void guardarListaBombillas(ofstream& archivo, const tListaPosiciones& lp) {
	archivo << lp.cont << endl;
	for (int i = 0; i < lp.cont; i++) guardarPosicion(archivo, lp.arrayPos[i]);
}