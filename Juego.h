/*
Practica realizada por:
	- Sergio Alejo Garcia
	- Carlos Sobrados Risco
1ºE
*/

#ifndef juego_h
#define juego_h
#include "mina.h"
#include <conio.h>
#include<Windows.h>
#include <string>
#include<stdio.h>
#include<stdlib.h>

enum tTecla { ARRIBA, ABAJO, DCHA, IZDA, SALIR, NADA, TNT };


struct tJuego {
	tMina mina;  // Plano de la mina
	int numGemas;  // Numero de gemas recolectadas
	int numMovimientos;  // Numero de movimientos realizados
	int numTNT;
	int unoTres;
	bool terminado; // terminado el nivel
	bool suicidio; // cuando te suicidas con tnt
	bool cargado;
	int tecladoFichero;
	bool ganadoNivel;//para ver cuando se llega a la salida
	// Otras de interes que se te ocurran.
};


void jugar(tJuego& juego, std::istream& entrada, std::istream& movimientos);

void leerMovimiento(tJuego& juego, tTecla& mov, std::istream& movimientos); // Te da un tipo enum y aqui llama a leerTecla();

void menuMov(); // leyenda de movimientos

tTecla leerTecla(std::istream& movimientos); // Lee el caracter del movimientos.txt. Recibe un fichero dentro de leerMovimiento(). 

tTecla leerTecla();


void realizarMovimiento(tJuego& juego, tTecla mov);

void caidaPiedras(tJuego& juego, int px, int py);

void dibujar(tJuego const& juego);

void movimientoLados(tJuego& juego, int aux);

void lanzarTNT(tJuego& juego);





#endif /* juego_h */

