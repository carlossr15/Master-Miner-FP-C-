/*
Practica realizada por:
	- Sergio Alejo Garcia
	- Carlos Sobrados Risco
1ºE
*/


#ifndef Puntuaciones_h
#define Puntuaciones_h

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;


const int TAM_INICIAL = 2;
const int NUM_TOTAL_MINAS = 5;




typedef struct {
	int IdMina;
	int numMovimientos;
	int numGemas;
	int numDinamitas;
	int puntosMina;
} tDatosMina;

typedef struct {
	string nombre;
	int punt_total;
	int minasRecorridas;
	tDatosMina vMinasRecorridas[NUM_TOTAL_MINAS];
} tPuntuacionJugador;


typedef struct {
	int capacidad;
	int num_jugadores;
	tPuntuacionJugador* array_clasificacion;
} tPuntuaciones;


bool cargar_Marcador(tPuntuaciones& marcador);
bool guardar_Marcador(tPuntuaciones& marcador);
void ordenar_Minas_Usuario(const tPuntuaciones& marcador, int cont);
void mostrar_Alfabetico(const tPuntuaciones& marcador);
void ordenar_Alfabetico(const tPuntuaciones& marcador);
void mostrar_Datos_Usuario(const tPuntuaciones& marcador);
void inicializar_Marcador(tPuntuaciones& marcador);
void aumentar_Capacidad(tPuntuaciones& marcador);
void destruir(tPuntuaciones& marcador);
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos);
void insertar(tPuntuaciones& marcador, string const& nombre, int pos);
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont);
bool recorrida(int id, tPuntuaciones marcador, int pos, int& mina);




#endif