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
void GuardarObjetosActualizados(Ficheros *F, objeto *arrayObjetos, int numObjetos) {
    if (F->Objetos == NULL) return;

    for (int i = 0; i < numObjetos; i++) {
        // Evitamos guardar estructuras vacías de la memoria dinámica
        if(arrayObjetos[i].id_objeto[0] != '\0') {
            fprintf(F->Objetos, "%s-%s-%s-%s\n", 
                    arrayObjetos[i].id_objeto, 
                    arrayObjetos[i].nombre,
                    arrayObjetos[i].descripcion, 
                    arrayObjetos[i].lugar);
        }
    }
}

// Sobrescribe el archivo de conexiones para guardar las puertas que se han abierto
void GuardarConexionesActualizadas(Ficheros *F, conexiones *arrayConexiones, int numConexiones) {
    if (F->Conexiones == NULL) return;

    for (int i = 0; i < numConexiones; i++) {
        // Evitamos guardar estructuras vacías
        if(arrayConexiones[i].id_conexion[0] != '\0') {
            fprintf(F->Conexiones, "%s-%s-%s-%s-%s\n", 
                    arrayConexiones[i].id_conexion, 
                    arrayConexiones[i].id_origen,
                    arrayConexiones[i].id_destino, 
                    arrayConexiones[i].Estado, 
                    arrayConexiones[i].condicion);
        }
    }
}
