#include "Ficheros.h"

int CrearFicheros (Ficheros *F) {
    F->Jugadores    = fopen ("Jugadores.txt", "a+");
    F->Salas        = fopen ("Salas.txt", "w");
    F->Conexiones   = fopen ("Conexiones.txt", "w");
    F->Objetos      = fopen ("Objetos.txt", "w");
    F->Puzles       = fopen ("Puzles.txt", "a+");
    F->Partidas     = fopen ("Partidas.txt", "w");

    if (F->Jugadores == NULL || F->Salas == NULL || F->Conexiones == NULL || F->Objetos == NULL || F->Puzles == NULL || F->Partidas == NULL) {
        printf("Error al crear los ficheros.\n");
        return -1;
    }
    return 0;
}

void CerrarFicheros (Ficheros *F) {
    if (F->Jugadores) fclose (F->Jugadores);
    if (F->Salas) fclose (F->Salas);
    if (F->Conexiones) fclose (F->Conexiones);
    if (F->Objetos) fclose (F->Objetos);
    if (F->Puzles) fclose (F->Puzles);
    if (F->Partidas) fclose (F->Partidas);
}
