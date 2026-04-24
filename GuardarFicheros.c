#include "GuardarFicheros.h"

// Guarda el progreso temporal del jugador (dónde está y qué puzles ha resuelto)
void GuardarEstadoPartida(Ficheros *F, jugadores j, salas s, puzle *arrayPuzles, int numPuzles) {
    if (F->Partidas == NULL) return;

    // Guardamos el ID del jugador y la sala actual
    fprintf(F->Partidas, "JUGADOR: %d\n", j.id_jugador);
    fprintf(F->Partidas, "SALA: %s\n", s.id_sala);

    // Guardamos solo los puzles que ya han sido resueltos
    for (int i = 0; i < numPuzles; i++) {
        if (arrayPuzles[i].resuelto == 1) {
            fprintf(F->Partidas, "PUZLE: %s-Resuelto\n", arrayPuzles[i].id_puzle);
        }
    }
}

// Guarda un nuevo jugador en la base de datos (se usa al registrarse)
void GuardarRegistroJugador(Ficheros *F, jugadores j) {
    if (F->Jugadores == NULL) return;

    fprintf(F->Jugadores, "%d-%s-%s-%s\n", j.id_jugador, j.Nomb_jugador, j.jugador, j.contrasenia);
}

// Sobrescribe el archivo de objetos para guardar sus nuevas ubicaciones (inventario o sala)
// Guarda la nueva ubicación de los objetos en partidas.txt
void GuardarObjetosActualizados(Ficheros *F, objeto *arrayObjetos, int numObjetos) {
    if (F->Partidas == NULL) return; 

    for (int i = 0; i < numObjetos; i++) {
        if(arrayObjetos[i].id_objeto[0] != '\0') {
            fprintf(F->Partidas, "OBJETO: %s-%s\n", 
                    arrayObjetos[i].id_objeto, 
                    arrayObjetos[i].lugar);
        }
    }
}

// Guarda el estado de las puertas en partidas.txt
void GuardarConexionesActualizadas(Ficheros *F, conexiones *arrayConexiones, int numConexiones) {
    if (F->Partidas == NULL) return; // Guardamos en el archivo de partida

    for (int i = 0; i < numConexiones; i++) {
        if(arrayConexiones[i].id_conexion[0] != '\0') {
            fprintf(F->Partidas, "CONEXION: %s-%s\n", 
                    arrayConexiones[i].id_conexion, 
                    arrayConexiones[i].Estado);
        }
    }
}
