#ifndef FICHERO_H
#define FICHERO_H

#include "contenidos.h"
#include "GuardarFicheros.h"
#include <stdio.h>

typedef struct {
    FILE *Jugadores;
    FILE *Salas;
    FILE *Conexiones;
    FILE *Objetivos;
    FILE *Puzles;
    FILE *Partidas;
} Ficheros;

int CrearFicheros (Ficheros *F);
void CerrarFicheros (Ficheros *F);

#endif