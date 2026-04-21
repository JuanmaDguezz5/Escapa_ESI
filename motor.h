#ifndef MOTOR_H
#define MOTOR_H

#include "contenidos.h"

// Inicia y mantiene el bucle principal de la partida
void iniciarBucleJuego(salas *arraySalas, int numSalas, 
                       objeto *arrayObjetos, int numObjetos, 
                       conexiones *arrayConexiones, int numConexiones, 
                       puzle *arrayPuzles, int numPuzles,
                       salas *salaActual, int idJugador);

#endif
