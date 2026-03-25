#ifndef CONTENIDOS_H
#define CONTENIDOS_H

#include <stdio.h>
#include <stdlib.h>

// Muestra la descripción de la sala y verifica si es la SALIDA 
void describirSala(salas *salaActual); 

// Permite resolver un puzle mediante código o palabra 
void interactuarPuzle(Puzle *puzleActual, conexiones *conexionesJuego, int numConexiones);

// Traslada un objeto de la sala al inventario 
void gestionObjetos (objeto *listaObjetos, int numObjetos, salas *sala, char *idObjBuscado);

// Lista objetos y salidas indicando si están bloqueadas o abiertas
void examinarSala(salas *salaActual, objeto *listaObjetos, int numObjetos, conexiones *listaConexiones, int numConexiones, int numConexiones);

#endif
