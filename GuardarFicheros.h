#ifndef GUARDARFICHEROS_H
#define GUARDARFICHEROS_H

#include "Ficheros.h"

// Precondición: Ninguna
// Postcondición: Guardado completo de datos
void GuardarDatos();

// Precondición: Ninguna
// Postcondición: Guarda los datos de los jugadores (ahora mismo pregunta por cada dato)
void GuardarJugador ();

// Precondición: Ninguna
// Postcondición: Guarda datos de los objetos en el fichero Objetos.txt
void GuardarObjetos ();

// Precondición: Ninguna
// Postondición: Guarda el estado de las conexiones en el fichero Conexiones.txt
void GuardarConexiones ();

#endif