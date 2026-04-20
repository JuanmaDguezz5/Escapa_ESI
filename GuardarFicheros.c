#include "GuardarFicheros.h"

void GuardarDatos (Ficheros *F) {
    // Parte de jugadores y salas
    fprintf (F->Partidas, "JUGADOR: %d\nSALA: %s\n", jugadorActual.id_jugador, salaActual.nombre);

    // Parte de obejtos e inventario
    for (int i = 0 ; i < 7 ; i++) {
        fprintf (F->Partidas, "OBJETO: %s-%s\n", jugadorActual.inventario[i].nombre, jugadorActual.inventario[i].lugar);
    }

    // Parte de conexiones
    for (int i = 0 ; i < 18 ; i++){
        if ((Conexiones[i].Estado[0] == 'A') && Conexiones[i].condicion[0] != '0') {
            fprintf (F->Partidas, "CONEXION: %s-%s\n", Conexiones[i].id_conexion, Conexiones[i].Estado);
        }
    }

    // Parte de los puzles
    for (int i = 0 ; i < 7 ; i++) {
        if (Puzles[i].resuelto) {
            fprintf (F->Partidas, "PUZLE: %s-Resuelto\n", Puzles[i].id_puzle);
        }
    }
}

void GuardarJugador (Ficheros *F) {
    fprintf (F->Jugadores, "%d-%s-%s-%s\n", jugadorActual.id_jugador, jugadorActual.Nomb_jugador, jugadorActual.jugador, jugadorActual.contrasenia);
    return;
}

void GuardarObjetos (Ficheros *F) {
    for (int i = 0 ; i < 7 ; i++) {
        fprintf (F->Objetos, "%s-%s-%s-%s\n", jugadorActual.inventario[i].id_objeto, jugadorActual.inventario[i].nombre,
                                           jugadorActual.inventario[i].descripcion, jugadorActual.inventario[i].lugar);
    }
}

void GuardarConexiones (Ficheros *F) {
    for (int i = 0 ; i < 18 ; i++) {
        fprintf (F->Conexiones, "%s-%s-%s-%s-%s\n", Conexiones[i].id_conexion, Conexiones[i].id_origen,
                                                 Conexiones[i].id_destino, Conexiones[i].Estado, Conexiones[i].condicion);
    }
}