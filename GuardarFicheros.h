#ifndef GUARDARFICHEROS_H
#define GUARDARFICHEROS_H

#include "Ficheros.h"
#include "contenidos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Precondición: Ninguna
// Postcondición: Engloba todas las funciones de guardado
void GuardarDatos();

// Precondición: Ninguna
// Postcondición: Guarda los datos de los jugadores (ahora mismo pregunta por cada dato)
void GuardarJugador ();

// Precondición: Ninguna
// Postcondición: Guarda datos de las salas que intervienen
void GuardarSalas ();

// Precondición: Ninguna
// Postcondición: Guarda información de las conexiones entre salas
void GuardarConexiones ();

// Precondición: Ninguna
// Postcondición: Guarda información de los objetos
void GuardarObjetos ();

// Precondición: Ninguna
// Postcondición: Guarda información de los puzles
void GuardarPuzles ();

// Precondición: Ninguna
// Postcondición: Guarda la información de la partida (ID, Sala, Objetos, Conexiones abiertas, Puzles resueltos)
void GuardarPartidas ();

// Precondición: Tener datos guardados
// Postcondición: Actualmente lee solo datos del fichero de jugadores,
//                después tendrá que leer datos de Partida.txt y cargar datos de ahí
void CargarPartida ();

#endif