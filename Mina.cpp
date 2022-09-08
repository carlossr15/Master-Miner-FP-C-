/*
Practica realizada por:
	- Sergio Alejo Garcia
	- Carlos Sobrados Risco
1ºE
*/

#include "mina.h"

tTiposCasilla char2casilla(char c) {
	tTiposCasilla casilla;
	if (c == 'G') casilla = GEMA;
	else if (c == 'M') casilla = MURO;
	else if (c == 'J') casilla = MINERO;
	else if (c == 'T') casilla = TIERRA;
	else if (c == 'P') casilla = PIEDRA;
	else if (c == 'S') casilla = SALIDA;
	else casilla = LIBRE;
	return casilla;
}

char casill2char(tTiposCasilla c) {
	char ch;
	if (c == 0) ch = ' ';
	else if (c == 1) ch = '.';
	else if (c == 2) ch = 'G';
	else if (c == 3) ch = '@';
	else if (c == 4) ch = 'X';
	else if (c == 5) ch = 'S';
	else if (c == 6) ch = 'J';
	else ch = 'D';
	return ch;
}

void cargar_mina(std::istream& fichero, tMina& mina) {
	tTiposCasilla casilla;
	char aux;
	fichero >> mina.numFilas >> mina.numCols;
	for (int i = 0; i < mina.numFilas; i++) {
		fichero.get(aux);
		for (int j = 0; j < mina.numCols; j++) { // Va diferenciando cada caracter del txt y lo convierte en un tTiposCasilla
			fichero.get(aux);
			if (aux == 'G') casilla = GEMA;
			else if (aux == 'M') casilla = MURO;
			else if (aux == 'J') {
				casilla = MINERO;
				mina.filaActual = i;
				mina.colActual = j;
			}
			else if (aux == 'T') casilla = TIERRA;
			else if (aux == 'P') casilla = PIEDRA;
			else if (aux == 'S') casilla = SALIDA;
			else casilla = LIBRE;
			mina.plano[i][j] = casilla;
		}
	}
}


void dibujar1_1(tMina const& mina) {
	tTiposCasilla casilla;

	for (int i = 0; i < mina.numFilas; i++) {
		for (int j = 0; j < mina.numCols; j++) {
			mostrarCasillas(mina.plano[i][j]);
		}
		cout << endl;
	}

}

void mostrarCasillas(const tTiposCasilla casilla) {

	if (casilla == 0) {
		colorFondo(4); // Primero da el color correspondiente
		cout << " "; //Muestra el caracter
		colorFondo(0); // Luego le pone el color negro
	}
	else if (casilla == 1) {
		colorFondo(4);
		cout << ".";
		colorFondo(0);
	}
	else if (casilla == 2) {
		colorFondo(10);
		cout << "G";
		colorFondo(0);
	}
	else if (casilla == 3) {
		colorFondo(4);
		cout << "@";
		colorFondo(0);
	}
	else if (casilla == 4) {
		colorFondo(4);
		cout << "X";
		colorFondo(0);
	}
	else if (casilla == 5) {
		colorFondo(1);
		cout << "S";
		colorFondo(0);
	}
	else if (casilla == 6) {
		colorFondo(7);
		cout << "J";
		colorFondo(0);
	}
	else if (casilla == 7) {
		colorFondo(13);
		cout << "D";
		colorFondo(0);
	}
}

void dibujar1_3(tMina const& mina) {
	char aux;
	typedef char tMat[MAX * 3][MAX * 3];
	tMat m;
	tPlanoCaracteres pl;
	tPlanoColores cl;
	for (int i = 0; i < mina.numFilas; i++) {
		for (int j = 0; j < mina.numCols; j++) {
			dibuja3_3(mina.plano[i][j], pl, cl, i, j);
		}

	}for (int t = 0; t < mina.numFilas * 3; t++) {
		for (int y = 0; y < mina.numCols * 3; y++) {
			colorFondo(cl[t][y]); // Primero da el color correspondiente al planosColores
			cout << pl[t][y] << " ";
			colorFondo(0); // Luego pone el color negro


		}
		cout << endl;

	}
}

void dibuja3_3(tTiposCasilla casilla, tPlanoCaracteres caracteres, tPlanoColores colores, int i, int j) {
	tPlanoCaracteres aux;
	tPlanoColores auxColores;
	if (casilla == 0) {
		aux[i][j] = ' '; // guarda el caracter en un planoCaracteres auxiliar para  luego poder hacer las submatrices 3x3
		auxColores[i][j] = 4; // guarda el numero del color en un planoColores auxiliar para  luego poder hacer las submatrices 3x3
	}
	else if (casilla == 1) {
		aux[i][j] = '.';
		auxColores[i][j] = 4;
	}
	else if (casilla == 2) {
		aux[i][j] = 'G';
		auxColores[i][j] = 10;
	}
	else if (casilla == 3) {
		aux[i][j] = '@';
		auxColores[i][j] = 4;
	}
	else if (casilla == 4) {
		aux[i][j] = 'X';
		auxColores[i][j] = 4;
	}
	else if (casilla == 5) {
		aux[i][j] = 'S';
		auxColores[i][j] = 1;
	}
	else if (casilla == 6) {
		aux[i][j] = 'J';
		auxColores[i][j] = 7;
	}
	else {
		aux[i][j] = 'D';
		auxColores[i][j] = 13;

	}
	for (int k = 3 * i; k < 3 * i + 3; k++) { // ESTO ES PARA PODER HACER LAS SUBMATRICES
		for (int l = 3 * j; l < 3 * j + 3; l++) { // PARA ELLO CREO UNA MATRIZ AUXILIAR PARA IR GUARDANDO AHI LOS CARACTERES
			caracteres[k][l] = aux[i][j];
			colores[k][l] = auxColores[i][j];
		}

	}
}


bool dentroPlano(tMina const& mina, int x, int y) {
	bool dentro = false;
	if (x >= 0 && x < mina.numFilas && y >= 0 && y < mina.numCols) dentro = true;

	return dentro;
}





void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}