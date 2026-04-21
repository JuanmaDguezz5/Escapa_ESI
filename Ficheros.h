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

int AbrirFicherosLectura(Ficheros *F);
int AbrirFicherosEscritura(Ficheros *F);
int AbrirFicherosRegistro(Ficheros *F); 
void CerrarFicheros(Ficheros *F);

#endif
