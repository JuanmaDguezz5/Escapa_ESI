#ifndef GUARDARFICHEROS_H
#define GUARDARFICHEROS_H

#include "Ficheros.h"

// Precondición: Ninguna
// Postcondición: Guardado completo de datos
void GuardarEstadoPartida(Ficheros *F, jugadores j, salas s, puzle *arrayPuzles, int numPuzles);

// Precondición: Ninguna
// Postcondición: Guarda los datos de los jugadores (ahora mismo pregunta por cada dato)
void GuardarRegistroJugador(Ficheros *F, jugadores j);

// Precondición: Ninguna
// Postcondición: Guarda datos de los objetos en el fichero Objetos.txt
void GuardarObjetosActualizados(Ficheros *F, objeto *arrayObjetos, int numObjetos); 

// Precondición: Ninguna
// Postcondición: Guarda datos de las conexiones en el fichero Conexiones.txt
void GuardarConexionesActualizadas(Ficheros *F, conexiones *arrayConexiones, int numConexiones);

#endif