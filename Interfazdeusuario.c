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
void ResetearMundo(); // Prototipo del clonador

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
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("\n--- REGISTRO DE NUEVO JUGADOR ---\n");
    printf("Nombre completo: "); 
    fgets(nuevo.Nomb_jugador, sizeof(nuevo.Nomb_jugador), stdin);
    nuevo.Nomb_jugador[strcspn(nuevo.Nomb_jugador, "\n")] = 0;

    printf("Nombre de usuario (ej. juan88): "); 
    scanf("%10s", nuevo.jugador);
    
    printf("Contrasena (max. 8 caracteres): "); 
    scanf("%8s", nuevo.contrasenia);
    
    // --- ASIGNACIÓN DE ID ÚNICO AUTOMÁTICO ---
    int nuevoID = 1;
    FILE *fJug = fopen("jugadores.txt", "r");
    if (fJug) {
        char linea[256];
        while (fgets(linea, sizeof(linea), fJug)) {
            int idTemp;
            if (sscanf(linea, "%d-", &idTemp) == 1) {
                if (idTemp >= nuevoID) nuevoID = idTemp + 1;
            }
        }
        fclose(fJug);
    }
    nuevo.id_jugador = nuevoID;
    
    Ficheros F;
    if (AbrirFicherosRegistro(&F) == 0) {
        GuardarRegistroJugador(&F, nuevo); // <- AQUI ESTABA EL ERROR 1
        CerrarFicheros(&F);
        printf("\n¡Registro completado con exito! Eres el Jugador ID: %d\n", nuevoID);
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
    int numSalas = 13, numObjetos = 7, numConexiones = 22, numPuzles = 7;  
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

            case 1: { // NUEVA PARTIDA
                printf("\n--- INICIANDO AVENTURA DESDE CERO ---\n");
                
                // 1. Inicializamos memoria limpia
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

                    salas *salaInicio = &arraySalas[0]; // Sala 01
                    
                    // 3. Entramos al juego
                    iniciarBucleJuego(arraySalas, numSalas, arrayObjetos, numObjetos, arrayConexiones, numConexiones, arrayPuzles, numPuzles, salaInicio, jActual.id_jugador);
                    liberarMemoriaContenidos(arraySalas, arrayObjetos, arrayConexiones, arrayPuzles);
                }
                k = 1; break;
            }

            case 2: { // CARGAR PARTIDA
                printf("\n--- REANUDANDO PARTIDA ANTERIOR ---\n");
                
                salas *arraySalasC = inicializarSalas(numSalas);
                objeto *arrayObjetosC = inicializarObjetos(numObjetos);
                conexiones *arrayConexionesC = inicializarConexiones(numConexiones);
                puzle *arrayPuzlesC = inicializarPuzles(numPuzles);

                Ficheros F_cargar;
                if (AbrirFicherosLectura(&F_cargar) == 0) {
                    
                    // 1. CARGAMOS LA BASE
                    CargarSalas(&F_cargar, arraySalasC, numSalas);
                    CargarPuzles(&F_cargar, arrayPuzlesC, numPuzles);
                    CargarConexiones(&F_cargar, arrayConexionesC, numConexiones);
                    CargarObjetos(&F_cargar, arrayObjetosC, numObjetos);
                    
                    // 2. APLICAMOS EL GUARDADO (Usando jActual.id_jugador) <- ERROR 2 CORREGIDO
                    estado_partida ep = CargarEstadoGuardado(&F_cargar, arrayPuzlesC, numPuzles, arrayObjetosC, numObjetos, arrayConexionesC, numConexiones, jActual.id_jugador);
                    CerrarFicheros(&F_cargar);

                    // --- SISTEMA DE BLOQUEO DE SEGURIDAD ---
                    if (ep.id_jugador == -1 || ep.id_sala_str[0] == '\0') {
                        printf("\n[AVISO] No se ha encontrado ninguna partida guardada a tu nombre.\n");
                        liberarMemoriaContenidos(arraySalasC, arrayObjetosC, arrayConexionesC, arrayPuzlesC);
                        k = 1; break; 
                    }

                    // 3. BUSCAMOS LA SALA DONDE SE QUEDÓ EL JUGADOR
                    salas *salaGuardada = NULL;
                    for(int i = 0; i < numSalas; i++) {
                        if(strcmp(arraySalasC[i].id_sala, ep.id_sala_str) == 0) {
                            salaGuardada = &arraySalasC[i]; break;
                        }
                    }
                    if(salaGuardada == NULL) salaGuardada = &arraySalasC[0];

                    // 4. ENTRAMOS AL BUCLE DEL JUEGO <- ERROR 3 CORREGIDO
                    iniciarBucleJuego(arraySalasC, numSalas, arrayObjetosC, numObjetos, arrayConexionesC, numConexiones, arrayPuzlesC, numPuzles, salaGuardada, ep.id_jugador);
                    liberarMemoriaContenidos(arraySalasC, arrayObjetosC, arrayConexionesC, arrayPuzlesC);
                }
                k = 1; break;
            }

            case 3:
                printf("\n¡Gracias por jugar a ESI-ESCAPE!\n");
                k = 0; break;
                
            default:
                printf("\nOpcion no valida.\n");
                k = 1; break;
        }
    } while (k != 0);
}

