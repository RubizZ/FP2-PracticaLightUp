#pragma once
#include"colores.h"
using namespace std;

typedef enum tTipo { PARED, BOMBILLA, LIBRE };
typedef struct {
	tTipo tipo;
	int numBombillas;
} tCelda;


char celdaToChar(const tCelda& c);
tCelda charToCelda(char c);
bool esPared(const tCelda& c);
bool esParedRestringida(const tCelda& c);
int numParedRestringida(const tCelda& c);
bool esBombilla(const tCelda& c);
bool estaApagada(const tCelda& c);
bool estaIluminada(const tCelda& c);
void apagaCelda(tCelda& c);
void actualizaIluminaciónCelda(tCelda& c, bool iluminar);
void ponBombilla(tCelda& c);
