//(-1,0) para salir y (-1, -1) para resetear
#include <iostream>
#include"celda.h"


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
	bool condicion;
	if (c.tipo == PARED) condicion = true;
	else condicion = false;
	return condicion;
}
bool esParedRestringida(const tCelda& c){
	bool condicion;	
	if (esPared(c) && c.numBombillas != -1) condicion = true;
	else condicion = false; 
	return condicion;
}
int numParedRestringida(const tCelda& c){
	return c.numBombillas;
}
bool esBombilla(const tCelda& c){
	bool condicion;
	if (c.tipo == BOMBILLA) condicion = true;
	else condicion = false;
	return condicion;
}
bool estaApagada(const tCelda& c){
	bool condicion;
	if (c.tipo == LIBRE && c.numBombillas == 0) condicion = true;
	else condicion = false;
	return condicion;
}
bool estaIluminada(const tCelda& c) {
	bool condicion;
	if (c.tipo == LIBRE && c.numBombillas > 0) condicion = true;
	else condicion = false;
	return condicion;
}
void apagaCelda(tCelda& c) {
	c.tipo = LIBRE;
	c.numBombillas = 0;
}
void actualizaIluminacionCelda(tCelda& c, bool iluminar) {
	if (iluminar) c.numBombillas++;
	else {
		c.tipo = LIBRE;
		c.numBombillas--;
	}
}
void ponBombilla(tCelda& c) {
	c.tipo = BOMBILLA;
	c.numBombillas++;
}