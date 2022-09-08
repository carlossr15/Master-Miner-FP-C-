/*
Practica realizada por:
	- Sergio Alejo Garcia
	- Carlos Sobrados Risco
1ºE
*/

#include "juego.h"

void jugar(tJuego& juego, std::istream& entrada, std::istream& movimientos) {
	tTecla mov;
	while (!juego.terminado && !juego.suicidio) {
		if (!juego.cargado) {
			cargar_mina(entrada, juego.mina);
			juego.cargado = true;
		}
		dibujar(juego);

		leerMovimiento(juego, mov, movimientos);


		system("cls");
	}

}

tTecla leerTecla() {
	int dir;
	tTecla movimiento;

	cout << "Introduzca el movimiento que quiera hacer " << endl;
	cin.sync();
	dir = _getch();
	if (dir == 0xe0) {//SON LAS TECLAS DE DIRECCION YA QUE LAS FLECHAS NO GENERAN UN CODIGO DE ESC
		dir = _getch();
		if (dir == 72) movimiento = tTecla(0);
		else if (dir == 80)movimiento = tTecla(1);
		else if (dir == 77)movimiento = tTecla(2);
		else if (dir == 75)movimiento = tTecla(3);
	}
	else if (dir == 97) {
		dir = _getch();
		movimiento = tTecla(0);
	}
	else if (dir == 122) {
		dir = _getch();
		movimiento = tTecla(1);
	}
	else if (dir == 109) {
		dir = _getch();
		movimiento = tTecla(2);
	}
	else if (dir == 110) {
		dir = _getch();
		movimiento = tTecla(3);
	}
	else if (dir == 27) {
		dir = _getch();
		movimiento = tTecla(4);//	EN CASO DE QUE LA TECLA SEA ESC
	}
	else if (dir == 68 || dir == 100) {
		dir = _getch();
		movimiento = tTecla(6);//EN PRINCIPIO LA D/d TE GENERA ESTE CODIGO ASCII
	}
	else {
		dir = _getch();
		movimiento = tTecla(5);
	}


	return movimiento;
}

tTecla leerTecla(std::istream& movimientos) {

	char c;
	movimientos >> c;

	switch (c) {
	case 'A': return ARRIBA;

	case 'Z': return ABAJO;

	case 'N': return IZDA;

	case 'M': return DCHA;

	case 'D': return TNT;

	case 'S': return SALIR;

	default: return NADA;
	}
}

void realizarMovimiento(tJuego& juego, tTecla mov) {
	int opcion;
	juego.numMovimientos++;
	switch (mov)
	{
	case ARRIBA:
		opcion = 0;
		movimientoLados(juego, opcion);
		break;
	case ABAJO:
		opcion = 1;
		movimientoLados(juego, opcion);
		break;
	case DCHA:
		opcion = 2;
		movimientoLados(juego, opcion);
		break;
	case IZDA:
		opcion = 3;
		movimientoLados(juego, opcion);
		break;
	case SALIR:
		juego.terminado = true;
		break;
	case NADA:
		break;
	case TNT:
		lanzarTNT(juego);
		break;
	default:
		break;
	}
}

void dibujar(tJuego const& juego) {
	if (juego.unoTres == 1) dibujar1_1(juego.mina);
	else if (juego.unoTres == 2) dibujar1_3(juego.mina);

	cout << "Gemas totales recogidas: " << juego.numGemas << endl;
	cout << "Numero de movimientos: " << juego.numMovimientos << endl;
	cout << "Dinamitas usadas: " << juego.numTNT << endl << endl;
}

void movimientoLados(tJuego& juego, int aux) {
	bool desplaza = true;
	int caidaIzq = 1;
	int caidaDer = 1;
	int fila;
	int columna;
	tTiposCasilla casillaDest;
	tTiposCasilla desplazoAux;
	switch (aux) {
	case 0: //ARRIBA
		casillaDest = juego.mina.plano[juego.mina.filaActual - 1][juego.mina.colActual];
		fila = juego.mina.filaActual - 1;

		if (casillaDest == PIEDRA) { // Si la casilla a donde va dirigido el minero es una piedra la empuja si la siguiente casilla esta libre
			desplazoAux = juego.mina.plano[juego.mina.filaActual - 2][juego.mina.colActual];
			if (desplazoAux != LIBRE && dentroPlano(juego.mina, juego.mina.filaActual - 2, juego.mina.colActual)) desplaza = false;
			else {
				juego.mina.plano[juego.mina.filaActual - 2][juego.mina.colActual] = juego.mina.plano[juego.mina.filaActual - 1][juego.mina.colActual];
			}
		}
		if (casillaDest != MURO && desplaza && dentroPlano(juego.mina, fila, juego.mina.colActual)) {
			if (casillaDest == SALIDA) {
				juego.terminado = true;
				juego.ganadoNivel = true;
			}
			juego.mina.plano[juego.mina.filaActual - 1][juego.mina.colActual] = juego.mina.plano[juego.mina.filaActual][juego.mina.colActual];
			juego.mina.plano[juego.mina.filaActual][juego.mina.colActual] = LIBRE;
			juego.mina.filaActual--;

			if (casillaDest == GEMA) juego.numGemas++;
		}
		break;
	case 1: //ABAJO
		casillaDest = juego.mina.plano[juego.mina.filaActual + 1][juego.mina.colActual];
		fila = juego.mina.filaActual + 1;
		if (casillaDest != 4 && casillaDest != 3 && desplaza && dentroPlano(juego.mina, fila, juego.mina.colActual)) {
			if (casillaDest == SALIDA) {
				juego.terminado = true;
				juego.ganadoNivel = true;
			}
			juego.mina.plano[juego.mina.filaActual + 1][juego.mina.colActual] = juego.mina.plano[juego.mina.filaActual][juego.mina.colActual];
			juego.mina.plano[juego.mina.filaActual][juego.mina.colActual] = LIBRE;
			juego.mina.filaActual++;
			caidaPiedras(juego, juego.mina.filaActual - 2, juego.mina.colActual);
			if (casillaDest == GEMA) juego.numGemas++;
		}
		break;
	case 2: //DERECHA
		casillaDest = juego.mina.plano[juego.mina.filaActual][juego.mina.colActual + 1];
		columna = juego.mina.colActual + 1;
		if (casillaDest == PIEDRA) { // Si la casilla a donde va dirigido el minero es una piedra la empuja si la siguiente casilla esta libre
			desplazoAux = juego.mina.plano[juego.mina.filaActual][juego.mina.colActual + 2];
			if (desplazoAux != LIBRE && dentroPlano(juego.mina, juego.mina.filaActual, juego.mina.colActual + 2)) desplaza = false;//////////////
			else {
				juego.mina.plano[juego.mina.filaActual][juego.mina.colActual + 2] = juego.mina.plano[juego.mina.filaActual][juego.mina.colActual + 1];
				if (dentroPlano(juego.mina, juego.mina.filaActual + 1, juego.mina.colActual + 2))  caidaPiedras(juego, juego.mina.filaActual, juego.mina.colActual + 2);
			}
		}
		if (casillaDest != MURO && desplaza && dentroPlano(juego.mina, juego.mina.filaActual, columna)) {////////////
			if (casillaDest == SALIDA) {
				juego.terminado = true;
				juego.ganadoNivel = true;
			}

			juego.mina.plano[juego.mina.filaActual][juego.mina.colActual + 1] = juego.mina.plano[juego.mina.filaActual][juego.mina.colActual];
			juego.mina.plano[juego.mina.filaActual][juego.mina.colActual] = LIBRE;
			if (juego.mina.plano[juego.mina.filaActual - 1][juego.mina.colActual] == PIEDRA || juego.mina.plano[juego.mina.filaActual - 1][juego.mina.colActual] == GEMA) caidaPiedras(juego, juego.mina.filaActual - 1, juego.mina.colActual);
			juego.mina.colActual++;
			if (casillaDest == GEMA) juego.numGemas++;//////////////
		}

		break;
	case 3: //IZQUIERDA
		casillaDest = juego.mina.plano[juego.mina.filaActual][juego.mina.colActual - 1];
		columna = juego.mina.colActual - 1;
		if (casillaDest == PIEDRA) { // Si la casilla a donde va dirigido el minero es una piedra la empuja si la siguiente casilla esta libre
			desplazoAux = juego.mina.plano[juego.mina.filaActual][juego.mina.colActual - 2];
			if (desplazoAux != LIBRE && dentroPlano(juego.mina, juego.mina.filaActual, juego.mina.colActual - 2)) desplaza = false;
			else {
				juego.mina.plano[juego.mina.filaActual][juego.mina.colActual - 2] = juego.mina.plano[juego.mina.filaActual][juego.mina.colActual - 1];
				if (dentroPlano(juego.mina, juego.mina.filaActual + 1, juego.mina.colActual - 2)) caidaPiedras(juego, juego.mina.filaActual, juego.mina.colActual - 2);

			}
		}
		if (casillaDest != MURO && desplaza && dentroPlano(juego.mina, juego.mina.filaActual, columna)) {
			if (casillaDest == SALIDA) {
				juego.ganadoNivel = true;
				juego.terminado = true;
			}
			juego.mina.plano[juego.mina.filaActual][juego.mina.colActual - 1] = juego.mina.plano[juego.mina.filaActual][juego.mina.colActual];
			juego.mina.plano[juego.mina.filaActual][juego.mina.colActual] = LIBRE;
			if (juego.mina.plano[juego.mina.filaActual - 1][juego.mina.colActual] == PIEDRA || juego.mina.plano[juego.mina.filaActual - 1][juego.mina.colActual] == GEMA) caidaPiedras(juego, juego.mina.filaActual - 1, juego.mina.colActual);
			juego.mina.colActual--;
			if (casillaDest == GEMA) juego.numGemas++;
		}
		break;

	default:

		break;
	}


}

void caidaPiedras(tJuego& juego, int px, int py) { // Actua tambien como caer(...);
	int i = 0;
	int j = 0;

	while (juego.mina.plano[px - j][py] == PIEDRA || juego.mina.plano[px - j][py] == GEMA) {
		i = 0;
		while (juego.mina.plano[px - j + i + 1][py] == LIBRE && dentroPlano(juego.mina, px - j + i + 1, py)) i++; //comprueba cuantas casillas por debajo estan libres
		if (juego.mina.plano[px - j][py] == PIEDRA) juego.mina.plano[px - j + i][py] = PIEDRA;
		else juego.mina.plano[px - j + i][py] = GEMA;
		if (i != 0) juego.mina.plano[px - j][py] = LIBRE;
		system("cls");
		dibujar(juego); // Da la sensacion de que esta cayendo la piedra/gema
		Sleep(300); //Retrasa la caida de las piedras/gemas
		j++;

	}


}

void menuMov() {
	cout << "A -> arriba" << endl;
	cout << "Z -> abajo" << endl;
	cout << "M -> derecha" << endl;
	cout << "N -> izquierda" << endl;
	cout << "D -> dinamita" << endl;
	cout << "Enter -> nada" << endl << endl;

}

void lanzarTNT(tJuego& juego) {//SIEMPRE VA A SALIR SI O SI

	juego.numTNT++;
	int k = 1;
	int filaTNT;
	while (juego.mina.plano[juego.mina.filaActual + k][juego.mina.colActual] == LIBRE) k++; //comprueba cuantas casillas por debajo estan libres
	if (juego.mina.plano[juego.mina.filaActual + k - 1][juego.mina.colActual] == MINERO) juego.suicidio = true;
	else juego.mina.plano[juego.mina.filaActual + k - 1][juego.mina.colActual] = DINAMITA;
	filaTNT = juego.mina.filaActual + k - 1;
	dibujar(juego);
	Sleep(300); // Retrasa la explosion de la TNT
	//explotar en matriz 3 *3
	for (int i = filaTNT - 1; i < filaTNT + 2; i++) {
		for (int j = juego.mina.colActual - 1; j < juego.mina.colActual + 2; j++) {
			if (juego.mina.plano[i][j] == MINERO) 	juego.suicidio = true; //A VECES NO ENTRA PORQUE LA DINAMITA SUSTITUYE AL MINERO
			if (juego.mina.plano[i][j] != SALIDA) juego.mina.plano[i][j] = LIBRE;
		}
	}
	for (int j = juego.mina.colActual - 1; j < juego.mina.colActual + 2; j++) {//PARA RECORRER LAS COLUMNAS DE LA IZQ LA DEL MEDIO Y DE LA DERECHA
		caidaPiedras(juego, filaTNT - 2, j);
	}
}


void leerMovimiento(tJuego& juego, tTecla& mov, std::istream& movimientos) {
	if (juego.tecladoFichero == 2) {
		do {
			mov = leerTecla(movimientos);
			realizarMovimiento(juego, mov);
			system("cls");
			dibujar(juego);
			Sleep(300); // Retrasa la accion del minero introducida por fichero para una mejora visual
			if (movimientos.eof()) juego.terminado = true; // Si se acaban los caracteres a leer del txt se acaba el nivel
		} while (mov != SALIR && !juego.terminado);

		if (mov == SALIR) juego.terminado;
	}
	else {
		mov = leerTecla();
		realizarMovimiento(juego, mov);
	}
}