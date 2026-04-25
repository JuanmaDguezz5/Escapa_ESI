#ifndef CARGARFICHEROS_H
#define CARGARFICHEROS_H

#include "Ficheros.h"

// Nuevas firmas adaptadas a la arquitectura sin globales
int CargarLoginUsuario(Ficheros *F, jugadores *jDestino);
estado_partida CargarEstadoGuardado(Ficheros *F, puzle *arrayPuzles, int numPuzles, objeto *arrayObjetos, int numObjetos, conexiones *arrayConexiones, int numConexiones, int id_jugador_actual);

// Las firmas de carga de arrays se mantienen igual porque ya funcionaban por parámetro
void CargarConexiones (Ficheros *F, conexiones *arrayConexiones, int numConexiones);
void CargarObjetos (Ficheros *F, objeto *arrayObjetos, int numObjetos);
void CargarSalas (Ficheros *F, salas *arraySalas, int numSalas);
void CargarPuzles (Ficheros *F, puzle *arrayPuzles, int numPuzles);

#endif