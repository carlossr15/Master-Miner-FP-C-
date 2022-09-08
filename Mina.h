/*
Practica realizada por:
	- Sergio Alejo Garcia
	- Carlos Sobrados Risco
1ºE
*/

#ifndef mina_h
#define mina_h


#include <iostream>
#include <Windows.h>

using namespace std;

enum tTiposCasilla { LIBRE, TIERRA, GEMA, PIEDRA, MURO, SALIDA, MINERO, DINAMITA };

// Entrada y salida del tipo enumerado
tTiposCasilla char2casilla(char c);
char casill2char(tTiposCasilla c);

const int MAX = 50;
typedef tTiposCasilla tPlano[MAX][MAX];

struct tMina {
	tPlano plano;
	int numFilas, numCols;
	int filaActual, colActual; // fila y columna donde se encuentra el minero
};

typedef char tPlanoCaracteres[3 * MAX][3 * MAX];
typedef int tPlanoColores[3 * MAX][3 * MAX];

// Comprueba si una posición pertenece al plano
bool dentroPlano(tMina const& mina, int x, int y);
// Carga desde un fichero los datos de la mina
void cargar_mina(std::istream& fichero, tMina& mina);
// Dibuja el plano en escala 1:1
void dibujar1_1(tMina const& mina);
// Dibuja el plano en escala 1:3 usango la  siguiente
void dibujar1_3(tMina const& mina);
// Dibuja las casillas aumentadas tres veces, actualiza planos y coles
// en i,j
void dibuja3_3(tTiposCasilla casilla, tPlanoCaracteres caracteres, tPlanoColores colores, int i, int j);

void mostrarCasillas(const tTiposCasilla casilla);

void colorFondo(int color);

#endif /* mina_h */