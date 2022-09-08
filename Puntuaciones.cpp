/*
Practica realizada por:
	- Sergio Alejo Garcia
	- Carlos Sobrados Risco
1ºE
*/


#include "Puntuaciones.h"


bool cargar_Marcador(tPuntuaciones& marcador) {
	bool cargado = false;
	string nombreAux;
	int idAux;
	inicializar_Marcador(marcador);
	ifstream archivo;
	archivo.open("Puntuaciones.txt");
	if (archivo.is_open()) {
		do {
			//getline(archivo, nombreAux);
			archivo >> nombreAux;
			if (nombreAux == "000") cargado = true;

			else {
				if (marcador.num_jugadores == marcador.capacidad) aumentar_Capacidad(marcador);
				marcador.array_clasificacion[marcador.num_jugadores].nombre = nombreAux;
				archivo >> marcador.array_clasificacion[marcador.num_jugadores].punt_total;
				archivo >> marcador.array_clasificacion[marcador.num_jugadores].minasRecorridas;

				for (int i = 0; i < marcador.array_clasificacion[marcador.num_jugadores].minasRecorridas; i++) {
					archivo >> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[i].IdMina;
					archivo >> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[i].numMovimientos;
					archivo >> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[i].numGemas;
					archivo >> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[i].numDinamitas;
					archivo >> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[i].puntosMina;
				}
				for (int j = marcador.array_clasificacion[marcador.num_jugadores].minasRecorridas; j < NUM_TOTAL_MINAS; j++) {
					marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[j].numMovimientos = 0;
					marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[j].numGemas = 0;
					marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[j].numDinamitas = 0;
					marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[j].puntosMina = 0;
				}
				marcador.num_jugadores++;
				
			}
		} while (!cargado);
		archivo.close();
	}
	return cargado;
}

bool guardar_Marcador(tPuntuaciones& marcador) {
	bool guardado = false;
	ofstream archivo;
	archivo.open("Puntuaciones.txt");
	if (archivo.is_open()) {
		for (int i = 0; i < marcador.num_jugadores; i++) {
			archivo << marcador.array_clasificacion[i].nombre << endl;
			archivo << marcador.array_clasificacion[i].punt_total << endl;
			archivo << marcador.array_clasificacion[i].minasRecorridas << endl;
			for (int j = 0; j < marcador.array_clasificacion[i].minasRecorridas; j++) {
				archivo << marcador.array_clasificacion[i].vMinasRecorridas[j].IdMina << " ";
				archivo << marcador.array_clasificacion[i].vMinasRecorridas[j].numMovimientos << " ";
				archivo << marcador.array_clasificacion[i].vMinasRecorridas[j].numGemas << " ";
				archivo << marcador.array_clasificacion[i].vMinasRecorridas[j].numDinamitas << " ";
				archivo << marcador.array_clasificacion[i].vMinasRecorridas[j].puntosMina << endl;
			}
		}
		archivo << "000";
		archivo.close();
		guardado = true;
	}

	return guardado;
}

void ordenar_Minas_Usuario(const tPuntuaciones& marcador, int cont) { //Usamos el metodo de la burbuja para ordenar el marcador
	bool inter = true;
	int i = 0;
	while ((i < marcador.array_clasificacion[cont].minasRecorridas - 1) && inter) {
		inter = false;
		for (int j = marcador.array_clasificacion[cont].minasRecorridas - 1; j > i; j--) {
			if (marcador.array_clasificacion[cont].vMinasRecorridas[j].IdMina < marcador.array_clasificacion[cont].vMinasRecorridas[j - 1].IdMina) {
				tDatosMina tmp;
				tmp = marcador.array_clasificacion[cont].vMinasRecorridas[j];
				marcador.array_clasificacion[cont].vMinasRecorridas[j] = marcador.array_clasificacion[cont].vMinasRecorridas[j - 1];
				marcador.array_clasificacion[cont].vMinasRecorridas[j - 1] = tmp;
				inter = true;
			}
		}
		if (inter) i++;
	}
}
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont) {
	ordenar_Minas_Usuario(marcador, cont);

	cout << setw(20) << "Mira las minas que has recorrido ordenadas por nivel." << endl << endl;
	cout << marcador.array_clasificacion[cont].nombre << setw(15) << "Movimientos" << setw(15) << "Gemas" << setw(15) << "Dinamitas" << setw(15) << "Puntos" << endl;
	for (int k = 0; k < marcador.array_clasificacion[cont].minasRecorridas; k++) {
		cout << "Mina " << marcador.array_clasificacion[cont].vMinasRecorridas[k].IdMina;
		cout << setw(15) << marcador.array_clasificacion[cont].vMinasRecorridas[k].numMovimientos;
		cout << setw(15) << marcador.array_clasificacion[cont].vMinasRecorridas[k].numGemas;
		cout << setw(15) << marcador.array_clasificacion[cont].vMinasRecorridas[k].numDinamitas;
		cout << setw(15) << marcador.array_clasificacion[cont].vMinasRecorridas[k].puntosMina << endl;
	}
	cout << endl << endl << setw(45) << "Puntos en total" << endl;
	cout << setw(38) << marcador.array_clasificacion[cont].punt_total << endl << endl;
}
void mostrar_Alfabetico(const tPuntuaciones& marcador) {
	ordenar_Alfabetico(marcador);

	cout << "Mira las puntuaciones de los otros jugadores." << endl << endl;
	cout << "------------ LISTA DE JUGADORES -----------------" << endl << endl;
	for (int k = 0; k < marcador.num_jugadores; k++) {
		cout << setw(15) << marcador.array_clasificacion[k].nombre << "  " << marcador.array_clasificacion[k].punt_total << endl;
	}


}
void ordenar_Alfabetico(const tPuntuaciones& marcador) { //Usamos el metodo de la burbuja para ordenar el marcador

	tPuntuacionJugador tmp;
	for (int i = 0; i < marcador.num_jugadores - 1; i++) {
		for (int j = marcador.num_jugadores - 1; j > i; j--) {
			if (marcador.array_clasificacion[j].nombre < marcador.array_clasificacion[j - 1].nombre) {
				tmp = marcador.array_clasificacion[j];
				marcador.array_clasificacion[j] = marcador.array_clasificacion[j - 1];
				marcador.array_clasificacion[j - 1] = tmp;
			}
		}
	}

}

void mostrar_Datos_Usuario(const tPuntuaciones& marcador) {
	ordenar_Alfabetico(marcador);
	for (int i = 0; i < marcador.num_jugadores; i++) mostrar_Minas_Usuario(marcador, i);




}
void inicializar_Marcador(tPuntuaciones& marcador) {
	marcador.capacidad = TAM_INICIAL;
	marcador.num_jugadores = 0;
	marcador.array_clasificacion = new tPuntuacionJugador[TAM_INICIAL];
	

}

void aumentar_Capacidad(tPuntuaciones& marcador) {
	cout << "Se ha llamdo a duplicar tamanho con marcador.num_jugadores= " << marcador.num_jugadores << endl;

	tPuntuacionJugador* aux = new tPuntuacionJugador[2 * marcador.capacidad];

	for (int i = 0; i < marcador.num_jugadores; i++)
	{
		aux[i] = marcador.array_clasificacion[i];
	}

	delete[] marcador.array_clasificacion; //OJO! usar [] para vectores din�micos
	marcador.array_clasificacion = aux;
	marcador.capacidad *= 2;
	aux = nullptr;
}


void destruir(tPuntuaciones& marcador) {

	delete[] marcador.array_clasificacion;
	marcador.array_clasificacion = nullptr;

}
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos) {
	bool encontrado = false;
	int mitad;
	int ini = 0;
	int fin = marcador.num_jugadores - 1;
	ordenar_Alfabetico(marcador);
	while (!encontrado&& ini <= fin) {

		mitad = (ini + fin) / 2;
		if (nombre == marcador.array_clasificacion[mitad].nombre) {
			pos = mitad;
			encontrado = true;
		}
		else if (nombre < marcador.array_clasificacion[mitad].nombre) {
			fin = mitad - 1;

		}
		else {
			ini = mitad + 1;
		}
	}
	if (!encontrado) {
		pos = ini;

	}
	return encontrado;
}

void insertar(tPuntuaciones& marcador, string const& nombre, int pos) {

	if (marcador.num_jugadores == marcador.capacidad)aumentar_Capacidad(marcador);

	for (int i = marcador.num_jugadores - 1; i >= pos; i--) {
		marcador.array_clasificacion[i + 1] = marcador.array_clasificacion[i];
	}
	marcador.array_clasificacion[pos].nombre = nombre;
	marcador.array_clasificacion[pos].minasRecorridas = 0;
	marcador.array_clasificacion[pos].punt_total = 0;
	for (int i = 0; i < NUM_TOTAL_MINAS; i++) {
		marcador.array_clasificacion[pos].vMinasRecorridas[i].numMovimientos = 0;
		marcador.array_clasificacion[pos].vMinasRecorridas[i].numGemas = 0;
		marcador.array_clasificacion[pos].vMinasRecorridas[i].numDinamitas = 0;
		marcador.array_clasificacion[pos].vMinasRecorridas[i].puntosMina = 0;
	}
	marcador.num_jugadores++;

}

bool operatorMenor(const tPuntuacionJugador& j1, const tPuntuacionJugador& j2) {
	bool menor = false;
	if (j1.nombre < j2.nombre) {
		menor = true;
	}
	return menor;
}

bool recorrida(int id, tPuntuaciones marcador, int pos, int& mina) {
	bool recorrida = false;
	int i = 0;
	while (i < marcador.array_clasificacion[pos].minasRecorridas && !recorrida) {
		if (marcador.array_clasificacion[pos].vMinasRecorridas[i].IdMina == id) recorrida = true;
		mina = i;
		i++;
	}
	return recorrida;
}