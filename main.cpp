/*
Practica realizada por:
	- Sergio Alejo Garcia
	- Carlos Sobrados Risco
1ºE
*/


#include <iostream>
#include <fstream>
#include <vector>//esto para parsear la entrada con el istream
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <math.h>
#include "juego.h"
#include"Puntuaciones.h"

using namespace std;
const int A = 10;
const int B = 2;



// Menu para pedir la escala con que se muestra el plano
int menu();

// Menu para indicar como se introduciran los movimientos
int menuMovimientos();

// Menu para pasar al siguiente nivel
int menuNivel();
//Menu para saber que mina recorrer
int menuMina(int i, const tPuntuaciones& marcador);

void inicializar(tJuego& juego);


int main() {

	bool salir = false;
	int nivel = 1;
	int aux = 0;
	int sigNivel;
	tJuego juego;
	string nomMoviminetos;
	tPuntuaciones marcador;
	string nombre;
	int pos = 0;
	ifstream entrada, movimientos;
	int mina;
	cargar_Marcador(marcador);
	inicializar(juego);
	int puntosMinaAux;

	cout << setw(20) << "Introduce tu nombre de jugador/a: ";
	cin >> nombre;
	cout << endl << endl;
	if (buscar(nombre, marcador, pos)) {
		cout << setw(20) << right << "Ya estas registrado/a." << endl << endl;
		mostrar_Minas_Usuario(marcador, pos);
	}
	else {
		insertar(marcador, nombre, pos);
		cout << setw(20) << right << "Eres nuevo/a: " << nombre << endl << endl;
		mostrar_Alfabetico(marcador);
		system("pause");
	}

	mina = menuMina(pos, marcador);

	if (mina == 0) salir = true;

	//DESPUES DE ESTO HABRIA QUE EMPEZAR EN EL NIVEL Q TE DEVUELVE ESTE MENU
	while (!salir && !juego.suicidio) {
		juego.unoTres = menu();
		if (juego.unoTres != 0) juego.tecladoFichero = menuMovimientos();
		if (juego.unoTres == 0 || juego.tecladoFichero == 0) salir = true;
		else {
			string level = to_string(mina) + ".txt";
			entrada.open(level);// Para seleccionar la mina y abrirla
			if (juego.tecladoFichero == 2) {
				cout << "Que archivo quieres usar para recorrer la mina por fichero? ";
				cin >> nomMoviminetos;
				movimientos.open(nomMoviminetos + ".txt");
			}
			jugar(juego, entrada, movimientos);
		
			if (juego.suicidio) cout << "Te has suicidado, fin de la partida" << endl << endl;
			else
			{ 
				if (juego.ganadoNivel) {
					if (!recorrida(mina, marcador, pos, aux)) { // Si el jugador ha recorrido la mina con idMina = mina devuelve true
						marcador.array_clasificacion[pos].minasRecorridas++;
						puntosMinaAux = juego.mina.numCols * juego.mina.numFilas + (A * juego.numGemas) - juego.numMovimientos - (B * juego.numTNT);
						marcador.array_clasificacion[pos].vMinasRecorridas[marcador.array_clasificacion[pos].minasRecorridas - 1].numDinamitas = juego.numTNT;
						marcador.array_clasificacion[pos].vMinasRecorridas[marcador.array_clasificacion[pos].minasRecorridas - 1].numGemas = juego.numGemas;
						marcador.array_clasificacion[pos].vMinasRecorridas[marcador.array_clasificacion[pos].minasRecorridas - 1].numMovimientos = juego.numMovimientos;
						marcador.array_clasificacion[pos].vMinasRecorridas[marcador.array_clasificacion[pos].minasRecorridas - 1].IdMina = mina;
						marcador.array_clasificacion[pos].punt_total -= marcador.array_clasificacion[pos].vMinasRecorridas[marcador.array_clasificacion[pos].minasRecorridas - 1].puntosMina;
						marcador.array_clasificacion[pos].vMinasRecorridas[marcador.array_clasificacion[pos].minasRecorridas - 1].puntosMina = puntosMinaAux;
						marcador.array_clasificacion[pos].punt_total += marcador.array_clasificacion[pos].vMinasRecorridas[marcador.array_clasificacion[pos].minasRecorridas - 1].puntosMina;
						
					}
					else {
						puntosMinaAux = juego.mina.numCols * juego.mina.numFilas + (A * juego.numGemas) - juego.numMovimientos - (B * juego.numTNT);
						if (puntosMinaAux > marcador.array_clasificacion[pos].vMinasRecorridas[aux].puntosMina) {
							marcador.array_clasificacion[pos].vMinasRecorridas[aux].numDinamitas = juego.numTNT;
							marcador.array_clasificacion[pos].vMinasRecorridas[aux].numGemas = juego.numGemas;
							marcador.array_clasificacion[pos].vMinasRecorridas[aux].numMovimientos = juego.numMovimientos;
							marcador.array_clasificacion[pos].vMinasRecorridas[aux].IdMina = mina;
							marcador.array_clasificacion[pos].punt_total -= marcador.array_clasificacion[pos].vMinasRecorridas[aux].puntosMina;
							marcador.array_clasificacion[pos].vMinasRecorridas[aux].puntosMina = puntosMinaAux;
							marcador.array_clasificacion[pos].punt_total += marcador.array_clasificacion[pos].vMinasRecorridas[aux].puntosMina;
						}
					}
				}
				mostrar_Minas_Usuario(marcador, pos);
				mina = menuMina(pos, marcador);
				if (mina == 0) salir = true;



			}
			entrada.close();
			movimientos.close();
			inicializar(juego);//para volver a poner a 0 todo
		}
	}
	mostrar_Alfabetico(marcador);
	guardar_Marcador(marcador);
	destruir(marcador);
	system("pause");
	return 0;
}


int menu() {
	int op;
	cout << "1. Jugar a escala 1:1" << endl;
	cout << "2. Jugar a escala 1:3" << endl;
	cout << "0. Salir" << endl << endl;
	do {
		cout << "Introduce una opcion valida ";
		cin >> op;
	} while (op < 0 || op > 2);
	return op;
}

int menuMovimientos() {

	int op;
	cout << "1. Introducir movimientos por teclado" << endl;
	cout << "2. Introducir movimientos por fichero" << endl;
	cout << "0. Salir" << endl << endl;
	do {
		cout << "Introduce una opcion valida ";
		cin >> op;
	} while (op < 0 || op > 2);
	return op;
}

int menuNivel() {
	int op;
	cout << "1. Jugar siguiente nivel" << endl;
	cout << "0. Salir" << endl << endl;
	do {
		cout << "Introduce una opcion valida ";
		cin >> op;
	} while (op < 0 || op > 1);
	return op;
}

void inicializar(tJuego& juego) {
	juego.terminado = false;
	juego.cargado = false;
	juego.suicidio = false;
	juego.numGemas = 0;
	juego.numMovimientos = 0;
	juego.numTNT = 0;
	juego.ganadoNivel = false;
}
int menuMina(int i, const tPuntuaciones & marcador) {
	int op;
	cout << marcador.array_clasificacion[i].nombre << ", Que mina quieres explorar?." << endl;
	cout << "Introduce un numero entre 1 y 5 para explorar una mina y 0 para salir" << endl;
	do {
		cin >> op;
	} while (op < 0 || op>5);

	return op;
}




