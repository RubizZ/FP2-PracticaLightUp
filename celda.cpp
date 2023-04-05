#include "celda.h"

char celdaToChar(const tCelda& cel){
	char tipo = ' ';	//Si no es nada de los if, sera una celda vacia (un espacio)
	if (cel.tipo == BOMBILLA) {
		tipo = '*';
	}
	else if (cel.tipo == PARED && cel.numBombillas != -1) {
		switch (cel.numBombillas) {
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
	//else tipo = ' ';
	return tipo;
}

tCelda charToCelda(char c) {
	tCelda cel = {LIBRE, 0};	//Si no es nada de los if, sera un . (LIBRE y 0)
	if (c == 'X') {
		cel.tipo = PARED;
		cel.numBombillas = -1;
	}
	else if (c == '*') {
		cel.tipo = BOMBILLA;
		cel.numBombillas = 0;
	}
	else if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4') {
		cel.tipo = PARED;
		cel.numBombillas = charAInt(c);
	}
	/*
	else if (c == '.') {
		cel.tipo = LIBRE;
		cel.numBombillas = 0;
	}
	*/
	return cel;
}
int charAInt(char c) {
	int n = 4;
	if (c == '0') n = 0;
	else if (c == '1') n = 1;
	else if (c == '2') n = 2;
	else if (c == '3') n = 3;
	//else if (c == '4') n = 4;
	return n;
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