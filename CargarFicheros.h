#ifndef CARGARFICHEROS_H
#define CARGARFICHEROS_H

#include "Ficheros.h"

// Precondición: Tener datos guardados
// Postcondición: Carga los datos que estén guardados en el fichero Jugadores.txt
void CargarJugador (Ficheros *F);

// Precondición: Tener datos guardados
// Postcondición: Cargar los datos que estén guardados en el fichero Conexiones.txt
void CargarConexiones (Ficheros *F);

// Precondición: Tener datos guardados
// Postcondición: Cargar los datos que estén guardados en el fichero Objetos.txt
void CargarObjetos (Ficheros *F);

// Precondición: Tener datos guardados
// Postcondición: Cargar los datos que estén guardados en el fichero Partidas.txt
void CargarPartida (Ficheros *F);

#endif