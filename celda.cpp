//(-1,0) para salir y (-1, -1) para resetear
#include <iostream>
#include "celda.h"


char celdaToChar(const tCelda& cel){
	char tipo;
	if (cel.tipo == BOMBILLA) {
		tipo = '*';
	}
	else if (cel.numBombillas != -1) {
		switch (cel.numBombillas)	{
		case 0:
			tipo = '0';
		break;
		case 1:
			tipo = '1';
			break;
		case 2:
			tipo = '2';
			break;
		case 3:
			tipo = '3';
			break;
		case 4:
			tipo = '4';
			break;
		}
	}
	else tipo = ' ';
	return tipo;
}

tCelda charToCelda(char c) {
	tCelda cel;
	if (c == 'X') {
		cel.tipo = PARED;
	}
	else if (c == -1 && 0 && 2 && 3 && 4) {
		cel.numBombillas = c;
	}
	else if (c == '.') {
		cel.tipo = LIBRE;
	}
	else if (c == '*') {
		cel.tipo = BOMBILLA;
	}
	return cel;
}
bool esPared(const tCelda& c){
	return c.tipo == PARED;
}
bool esParedRestringida(const tCelda& c){
	return esPared(c) && c.numBombillas != -1;
}
int numParedRestringida(const tCelda& c){
	return c.numBombillas;
}
bool esBombilla(const tCelda& c){
	return c.tipo == BOMBILLA;
}
bool estaApagada(const tCelda& c){
	return c.tipo == LIBRE && c.numBombillas == 0;
}
bool estaIluminada(const tCelda& c) {
	return c.tipo == LIBRE && c.numBombillas > 0;
}
void apagaCelda(tCelda& c) {
	c.tipo = LIBRE;
	c.numBombillas = 0;
}
void actualizaIluminacionCelda(tCelda& c, bool iluminar) {
	if (iluminar) c.numBombillas++;
	else c.numBombillas--;
}
void ponBombilla(tCelda& c) {
	c.tipo = BOMBILLA;
}