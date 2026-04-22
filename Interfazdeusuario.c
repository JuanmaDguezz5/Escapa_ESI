#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Módulos del proyecto
#include "contenidos.h"
#include "CargarFicheros.h"
#include "GuardarFicheros.h"
#include "Ficheros.h"
#include "motor.h"

// Prototipos de funciones locales
int menuAccesoInicial(jugadores *jActual);
int registrarUsuario();
int iniciarSesion(jugadores *jActual);
void menuPrincipal(jugadores jActual);

// ==========================================
// FUNCIÓN PRINCIPAL
// ==========================================
int main() {
    jugadores jActual; // El "dueño" de los datos del jugador en esta sesión
    
    // 1. Acceso (Login o Registro)
    int accesoConcedido = menuAccesoInicial(&jActual);

    if (accesoConcedido == 1) {
        // 2. Si el acceso es correcto, entramos al menú del juego
        menuPrincipal(jActual);
    } else {
        printf("\nSaliendo del sistema de ESI-ESCAPE...\n");
    }

    return 0;
}

// ==========================================
// GESTIÓN DE ACCESO (LOGIN / REGISTRO)
// ==========================================
int menuAccesoInicial(jugadores *jActual) {
    int opcion, k;
    do {
        k = 0; 
        printf("\n========================================\n");
        printf("          ACCESO A ESI-ESCAPE           \n");
        printf("========================================\n");
        printf("1. Iniciar Sesion\n2. Registrarse\n3. Salir\nSeleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("\n[ERROR] Entrada no valida.\n");
            while (getchar() != '\n'); 
            k = 1;
        } else {
            switch(opcion) {
                case 1: 
                    return iniciarSesion(jActual);
                case 2: 
                    if (registrarUsuario() == 1) {
                        return iniciarSesion(jActual);
                    }
                    k = 1; break;
                case 3: 
                    return 0; 
                default: 
                    printf("\n[ERROR] Opcion no valida.\n"); 
                    k = 1; break;
            }
        }
    } while (k != 0);
    return 0; 
}

int registrarUsuario() {
    jugadores nuevo;
    
    // Limpiamos el buffer para usar fgets correctamente
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("\n--- REGISTRO DE NUEVO JUGADOR ---\n");
    printf("Nombre completo: "); 
    fgets(nuevo.Nomb_jugador, sizeof(nuevo.Nomb_jugador), stdin);
    nuevo.Nomb_jugador[strcspn(nuevo.Nomb_jugador, "\n")] = 0; // Quitar el salto de línea

    printf("Nombre de usuario (ej. juan88): "); 
    scanf("%10s", nuevo.jugador);
    
    printf("Contrasena (max. 8 caracteres): "); 
    scanf("%8s", nuevo.contrasenia);
    
    nuevo.id_jugador = 1; // ID por defecto (se podría hacer autoincremental leyendo el fichero)
    
    Ficheros F;
    if (AbrirFicherosRegistro(&F) == 0) {
        GuardarRegistroJugador(&F, nuevo);
        CerrarFicheros(&F);
        printf("\n¡Registro completado con exito!\n");
        return 1;
    }
    return 0;
}

int iniciarSesion(jugadores *jActual) {
    Ficheros F;
    int exito = 0;
    if (AbrirFicherosLectura(&F) == 0) {
        exito = CargarLoginUsuario(&F, jActual);
        CerrarFicheros(&F); 
    }
    return exito; 
}

// ==========================================
// MENÚ PRINCIPAL DEL JUEGO
// ==========================================
void menuPrincipal(jugadores jActual) {
    int opcion, k;
    // Tamaños según la especificación de tu proyecto
    int numSalas = 13, numObjetos = 7, numConexiones = 18, numPuzles = 7;

    do {
        k = 0; 
        printf("\n  _____  ____  ___     ____   ____    _      ____   _____ \n");
        printf(" | ____|/ ___||_ _|   / ___| / ___|   / \\    |  _ \\ | ____|\n");
        printf(" |  _|  \\___ \\ | |    \\___ \\| |      / _ \\   | |_) ||  _|  \n");
        printf(" | |___  ___) || |     ___) | |___  / ___ \\  |  __/ | |___ \n");
        printf(" |_____||____/|___|   |____/ \\____|/_/   \\_\\ |_|    |_____|\n");
        printf("\n                  MENU PRINCIPAL\n");
        printf("----------------------------------\n");
        printf("1. Nueva Partida\n2. Cargar Partida\n3. Salir\nSeleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            opcion = 0; while (getchar() != '\n'); 
        }

        switch (opcion) {
            case 1: // NUEVA PARTIDA
                printf("\nGenerando nuevo mundo...\n");
                
                salas *arraySalas = inicializarSalas(numSalas);
                objeto *arrayObjetos = inicializarObjetos(numObjetos);
                conexiones *arrayConexiones = inicializarConexiones(numConexiones);
                puzle *arrayPuzles = inicializarPuzles(numPuzles);
                
                Ficheros F;
                if (AbrirFicherosLectura(&F) == 0) {
                    CargarSalas(&F, arraySalas, numSalas);
                    CargarPuzles(&F, arrayPuzles, numPuzles);
                    CargarConexiones(&F, arrayConexiones, numConexiones); 
                    CargarObjetos(&F, arrayObjetos, numObjetos);
                    CerrarFicheros(&F);

                    // Buscar la sala de inicio
                    salas *salaInicio = NULL;
                    for(int i = 0; i < numSalas; i++) {
                        if(strcmp(arraySalas[i].Tipo, "INICIAL") == 0) {
                            salaInicio = &arraySalas[i]; break;
                        }
                    }
                    if(salaInicio == NULL) salaInicio = &arraySalas[0];

                    printf("\n--- INICIO DE ESI-ESCAPE ---\n");
                    // LLAMADA AL MOTOR PASANDO EL ID DEL JUGADOR
                    iniciarBucleJuego(arraySalas, numSalas, arrayObjetos, numObjetos, arrayConexiones, numConexiones, arrayPuzles, numPuzles, salaInicio, jActual.id_jugador);
                    
                    liberarMemoriaContenidos(arraySalas, arrayObjetos, arrayConexiones, arrayPuzles);
                }
                k = 1; break;

            case 2: // CARGAR PARTIDA
                printf("\nRecuperando partida guardada...\n");
                
                salas *arraySalasC = inicializarSalas(numSalas);
                objeto *arrayObjetosC = inicializarObjetos(numObjetos);
                conexiones *arrayConexionesC = inicializarConexiones(numConexiones);
                puzle *arrayPuzlesC = inicializarPuzles(numPuzles);

                Ficheros F_cargar;
                if (AbrirFicherosLectura(&F_cargar) == 0) {
                    CargarSalas(&F_cargar, arraySalasC, numSalas);
                    CargarPuzles(&F_cargar, arrayPuzlesC, numPuzles);
                    CargarConexiones(&F_cargar, arrayConexionesC, numConexiones);
                    CargarObjetos(&F_cargar, arrayObjetosC, numObjetos);
                    
                    // Cargamos el estado específico usando el struct que devuelve la función
                    estado_partida ep = CargarEstadoGuardado(&F_cargar, arrayPuzlesC, numPuzles);
                    CerrarFicheros(&F_cargar);

                    // Buscamos la sala donde se quedó el jugador
                    salas *salaGuardada = NULL;
                    for(int i = 0; i < numSalas; i++) {
                        if(strcmp(arraySalasC[i].id_sala, ep.id_sala_str) == 0) {
                            salaGuardada = &arraySalasC[i]; break;
                        }
                    }
                    if(salaGuardada == NULL) salaGuardada = &arraySalasC[0];

                    printf("\n--- PARTIDA REANUDADA ---\n");
                    // LLAMADA AL MOTOR CON EL ESTADO CARGADO Y EL ID RECUPERADO
                    iniciarBucleJuego(arraySalasC, numSalas, arrayObjetosC, numObjetos, arrayConexionesC, numConexiones, arrayPuzlesC, numPuzles, salaGuardada, ep.id_jugador);
                    
                    liberarMemoriaContenidos(arraySalasC, arrayObjetosC, arrayConexionesC, arrayPuzlesC);
                }
                k = 1; break;

            case 3:
                printf("\n¡Gracias por jugar a ESI-ESCAPE!\n");
                k = 0; break;
                
            default:
                printf("\nOpcion no valida.\n");
                k = 1; break;
        }
    } while (k != 0);
}
