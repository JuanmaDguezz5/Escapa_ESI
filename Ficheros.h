#ifndef FICHERO_H
#define FICHERO_H

#include "contenidos.h"

typedef struct {
    FILE *Jugadores;
    FILE *Salas;
    FILE *Conexiones;
    FILE *Objetos;
    FILE *Puzles;
    FILE *Partidas;
} Ficheros;

int CrearFicheros (Ficheros *F);
void CerrarFicheros (Ficheros *F);

#endif