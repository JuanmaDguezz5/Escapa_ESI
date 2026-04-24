#include "Ficheros.h"

int AbrirFicherosLectura(Ficheros *F) {
    F->Jugadores    = fopen("jugadores.txt", "r");
    F->Salas        = fopen("salas.txt", "r");
    F->Conexiones   = fopen("conexiones.txt", "r");
    F->Objetos      = fopen("objetos.txt", "r");
    F->Puzles       = fopen("puzles.txt", "r");
    F->Partidas     = fopen("partidas.txt", "r");

    if (!F->Salas || !F->Conexiones || !F->Puzles || !F->Objetos) {
        printf("Error: Faltan los ficheros base del mundo para poder jugar.\n");
        return -1;
    }
    return 0;
}

int AbrirFicherosEscritura(Ficheros *F) {
    F->Jugadores    = fopen("jugadores.txt", "a+"); 
    F->Salas        = NULL; 
    F->Conexiones   = NULL; 
    F->Objetos      = NULL; 
    F->Puzles       = NULL; 
    F->Partidas     = fopen("partidas.txt", "w"); 

    if (!F->Partidas || !F->Jugadores) {
        printf("Error al abrir los ficheros para guardar.\n");
        return -1;
    }
    return 0;
}

int AbrirFicherosRegistro(Ficheros *F) {
    F->Jugadores    = fopen("jugadores.txt", "a+"); 
    F->Salas        = NULL;
    F->Conexiones   = NULL;
    F->Objetos      = NULL;
    F->Puzles       = NULL;
    F->Partidas     = NULL;

    if (!F->Jugadores) {
        printf("Error al abrir fichero de registro.\n");
        return -1;
    }
    return 0;
}

void CerrarFicheros(Ficheros *F) {
    if (F->Jugadores) fclose(F->Jugadores);
    if (F->Salas) fclose(F->Salas);
    if (F->Conexiones) fclose(F->Conexiones);
    if (F->Objetos) fclose(F->Objetos);
    if (F->Puzles) fclose(F->Puzles);
    if (F->Partidas) fclose(F->Partidas);
}
