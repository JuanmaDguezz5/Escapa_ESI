#include "CargarFicheros.h"

void CargarPartida (Ficheros *F) {
    char linea[256];
    while (fgets(linea, sizeof(linea), F->Partidas)) {
        linea [strcspn(linea, "\n")] = '\0'; // Busca el salto de linea al final de la linea para quitarlo
        if (!strncmp(linea, "JUGADOR: ", 9)) { // A diferencia de strcmp strncmp compara N caracteres, de ahí el 9
            sscanf (linea, "JUGADOR: %d", &PartidaCargada.id_jugador);
        }
        if (!strncmp(linea, "SALA: ", 6)) {
            sscanf (linea, "SALA: %d", &PartidaCargada.id_sala);
        }
        if (!strncmp(linea, "OBJETO: OB", 9)) {
            sscanf (linea, "OBJETO: OB%d-%15s", &PartidaCargada.id_obj, jugadorActual.inventario[PartidaCargada.id_obj].lugar);
        }
    }
}

void CargarConexiones (Ficheros *F) {
    for (int i = 0 ; i < 18 ; i++) {
        fscanf (F->Conexiones, "%s-%s-%s-%s-%s", Conexiones[i].id_conexion, Conexiones[i].id_origen,
                                                 Conexiones[i].id_destino, Conexiones[i].Estado, Conexiones[i].condicion);
    }

}

void CargarObjetos (Ficheros *F) {
    for (int i = 0 ; i < 7 ; i++) {
        fscanf (F->Objetos, "%s-%s-%s-%s", jugadorActual.inventario[i].id_objeto, jugadorActual.inventario[i].nombre,       // Lee los datos de los objetos
                                           jugadorActual.inventario[i].descripcion, jugadorActual.inventario[i].lugar);     // del fichero Objetos.txt
    }
}

void CargarJugador (Ficheros *F) {
    char idJugadorBuscado[11];
    char contraseñaIntroducida[9];
    printf ("Cual es la nombre de usuario del jugador que quiera iniciar sesion?\n(Ej: Jugador1)\n");
    scanf ("%10s", idJugadorBuscado);
    while (!feof(F->Jugadores)) {
        fscanf (F->Jugadores, "%d-%s-%s-%s", &jugadorActual.id_jugador, jugadorActual.Nomb_jugador,
                                             jugadorActual.jugador, jugadorActual.contrasenia);
        if (!strcmp(jugadorActual.jugador, idJugadorBuscado)) {
            do {
                printf ("Introduzca su contrasena:\n(8 carácteres máximo) (Escribir 'Salir' para regresar)\n");
                scanf ("%8s", contraseñaIntroducida);
            } while (strcmp(jugadorActual.contrasenia, contraseñaIntroducida) && strcmp(contraseñaIntroducida, "Salir"));
        }
        if (!strcmp(contraseñaIntroducida, "Salir")) {
            printf ("Volviendo al menú principal\n");
            return;
        }
        printf ("Bienvenido %s\n", jugadorActual.Nomb_jugador);
        return;
    }
}
