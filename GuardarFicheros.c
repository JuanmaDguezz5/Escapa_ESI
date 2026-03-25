#include "GuardarFicheros.h"

int main() {
    Ficheros F;
    CrearFicheros(&F);
    int opcion;
    do {
        printf("Que quiere hacer?\n0. Salir\n\n1. Guardar datos\n2. Cargar datos\n");
        scanf ("%d", &opcion);
        switch (opcion) {
            case 0:
            printf ("Saliendo del programa\n");
                break;
            case 1:
                GuardarDatos(&F);
                break;
            case 2:
                CargarPartida(&F);
                break;
            default:
                printf("Opcion no valida\n");
        }
    } while (opcion != 0);    
    CerrarFicheros(&F);
    return 0;
}

void GuardarDatos (Ficheros *F) {
    GuardarJugador(F);
   /* GuardarSalas();
    GuardarConexiones();
    GuardarObjetos();
    GuardarPuzles();
    GuardarPartidas(); */
}

void GuardarJugador (Ficheros *F) {
    FILE *Jugadores = fopen ("Jugadores.txt", "a");
    fprintf (Jugadores, "%d-%s-%s-%s\n", jugadorActual.id_jugador, jugadorActual.Nomb_jugador, jugadorActual.jugador, jugadorActual.contrasenia);
    fclose(Jugadores);
    return;
}

void GuardarSalas () {

    return;
}

void CargarPartida (Ficheros *F) {

    int identificador;
    char nombre[20];
    char nombreSistema[10];
    char contrasena[8];

    char LineaFichero[100];
    FILE *Jugadores = fopen("Jugadores.txt", "r");
    if (Jugadores == NULL) {
        printf("Error al abrir el fichero de jugadores\n");
        return;
    }

    // Lee una línea del archivo
    if (fgets(LineaFichero, sizeof(LineaFichero), Jugadores) == NULL) {
        printf("Error al leer el archivo o el archivo es vacio\n");
        fclose(Jugadores);
        return;
    }

    char *saltoLinea = strchr (LineaFichero, '\n'); // Busca si hay '\n', si lo hay lo guarda en un puntero
    if (saltoLinea) *saltoLinea = '\0';             // Si tiene '\n' lo sustituye por '\0'

    char *Puntero;
    Puntero = strtok (LineaFichero, "-");
    if (Puntero != NULL) {              // Cada Puntero != NULL hace que lea algo que realmente existe
        identificador = atoi(Puntero);  // Convierte a entero
    }

    Puntero = strtok (NULL, "-");       // NULL porque 'strtok' sustituye el '-' por '\0'
    if (Puntero != NULL) {              // si se pusiera LineaFichero de nuevo leerá desde el principio
        strcpy (nombre, Puntero);
    }

    Puntero = strtok (NULL, "-");
    if (Puntero != NULL) {
        strcpy (nombreSistema, Puntero);
    }

    Puntero = strtok (NULL, "-");
    if (Puntero != NULL) {
        strcpy (contrasena, Puntero);
    }

    fclose(Jugadores);
    return;
}


// ############# COSAS QUE HACER #############
/*
    * Guardar datos de todos lo ficheros
    * Cargar datos de todos los ficheros
    * Implementar que se guarde el inventario
    * Intentar arreglar que tenga que abrir ficheros en cada funcion
    * A ver como meto que se guarde manualmente la partida
*/