#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contenidos.h"

// Prototipos de funciones 
int menuAccesoInicial();
int registrarUsuario();
int iniciarSesion();
void menuPrincipal();

// Prototipo de la función de la partida
void menuPartida(salas *salaActual, objeto *listaObjetos, int numObjetos, conexiones *listaConexiones, int numConexiones, puzle *puzleActual);

// Nota: He añadido este prototipo que usa tu bloque "flotante"
void iniciarBucleJuego(salas *arraySalas, int numSalas, objeto *arrayObjetos, int numObjetos, conexiones *arrayConexiones, int numConexiones, puzle *arrayPuzles, int numPuzles, salas *salaInicio, int idJugador);

int main() {
    // 1. Primero se pide al usuario que se registre o inicie sesion y se verifica
    int accesoConcedido = menuAccesoInicial();

    if (accesoConcedido == 1) {
        // 2. Si se concede el acceso, pasamos al menu principal del juego
        menuPrincipal();
    } else {
        printf("Saliendo del sistema...\n");
    }

    return 0;
}

int menuAccesoInicial() {
    int opcion;
    int k;

    do {
        k = 0; 

        printf("\n========================================\n");
        printf("          ACCESO A ESI SCAPE           \n");
        printf("========================================\n");
        printf("1. Iniciar Sesion\n");
        printf("2. Registrarse\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("\n[ERROR] Entrada no valida. Por favor, introduzca un numero.\n");
            while (getchar() != '\n'); 
            k = 1;
        } else {
            switch(opcion) {
                case 1:
                    return iniciarSesion();
                case 2:
                    if (registrarUsuario() == 1) {
                        return 1; 
                    }
                    return iniciarSesion();
                case 3:
                    return 0; 
                default:
                    printf("\n[ERROR] Opcion no valida, introduzca una opcion del 1 al 3.\n");
                    k = 1; 
                    break;
            }
        }
    } while (k != 0);

    return 0; 
}

void menuPrincipal() {
    int opcion;
    int k;
    int sesionIniciada = 1; // Para que el bloque del 'if' funcione dentro del menu
    int idJugadorActual = 1; // Valor inicial simulado

    do {
        k = 0; 
        
        printf("\n\n");
        printf("  _____  ____  ___     ____   ____    _      ____   _____ \n");
        printf(" | ____|/ ___||_ _|   / ___| / ___|   / \\    |  _ \\ | ____|\n");
        printf(" |  _|  \\___ \\ | |    \\___ \\| |      / _ \\   | |_) ||  _|  \n");
        printf(" | |___  ___) || |     ___) | |___  / ___ \\  |  __/ | |___ \n");
        printf(" |_____||____/|___|   |____/ \\____|/_/   \\_\\ |_|    |_____|\n");
        printf("\n");
        printf("                  =================\n");
        printf("                  BIENVENIDO/A\n");
        printf("                  =================\n\n");
        
        printf("Menú:\n");
        printf("       ESI SCAPE\n");
        printf("----------------------------------\n");
        printf("1. Nueva Partida\n");
        printf("2. Cargar Partida\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            opcion = 0; 
            while (getchar() != '\n'); 
        }

        switch (opcion) {
            case 1:
                // --- AQUÍ HE METIDO EL BLOQUE QUE ESTABA FLOTANDO ---
                if (sesionIniciada == 1) {
                    printf("\nCargando datos del sistema (Simulacion)...\n");
                    
                    int numSalas = 5, numObjetos = 5, numConexiones = 5, numPuzles = 5;
                    
                    // Inicialización de memoria dinámica (funciones de contenidos.h)
                    salas *arraySalas = inicializarSalas(numSalas);
                    objeto *arrayObjetos = inicializarObjetos(numObjetos);
                    conexiones *arrayConexiones = inicializarConexiones(numConexiones);
                    puzle *arrayPuzles = inicializarPuzles(numPuzles);
                    
                    // Simulamos la sala inicial para que el motor arranque sin crashear
                    strcpy(arraySalas[0].id_sala, "01");
                    strcpy(arraySalas[0].nombre, "Conserjeria");
                    strcpy(arraySalas[0].descripcion, "Pequeño habitaculo a la entrada.");
                    strcpy(arraySalas[0].Tipo, "INICIAL");
                    
                    printf("\n¡Todo listo! Entrando a ESI-ESCAPE...\n");
                    
                    // Llamamos al Bucle Principal (He mapeado esto a menuPartida para que use tu lógica actual)
                    menuPartida(&arraySalas[0], arrayObjetos, numObjetos, arrayConexiones, numConexiones, &arrayPuzles[0]);
                    
                    // Al terminar el juego, liberamos la memoria dinámica
                    liberarMemoriaContenidos(arraySalas, arrayObjetos, arrayConexiones, arrayPuzles);
                }
                k = 1; // Volver al menú después de la partida
                break;

            case 2:
                printf("\nCargando partida guardada...\n");
                k = 1; 
                break;
            case 3:
                printf("\nSaliendo de ESI ESCAPE...\n");
                k = 0; 
                break;
            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
                k = 1; 
                while (getchar() != '\n'); 
                break;
        }
    } while (k != 0);
}

int registrarUsuario() {
    char Nomb_jugador[20];
    char jugador[11];
    char contrasenia[9];

    printf("Ingrese su nombre completo: ");
    scanf("%19s", Nomb_jugador); 
    printf("Ingrese su nombre de usuario: ");
    scanf("%10s", jugador);
    printf("Ingrese su contrasena: ");
    scanf("%8s", contrasenia);

    printf("Registro exitoso\n");
    return 1;
}

int iniciarSesion() {
    char jugador[11];
    char contrasenia[9];

    printf("Ingrese su nombre de usuario: ");
    scanf("%10s", jugador);
    printf("Ingrese su contrasenia: ");
    scanf("%8s", contrasenia);

    printf("Inicio de sesion exitoso\n");
    return 1;
}
    
void menuPartida(salas *salaActual, objeto *listaObjetos, int numObjetos, conexiones *listaConexiones, int numConexiones, puzle *puzleActual) {
    int opcion;
    char idObjBuscado[5];

    do {
        printf("\n========================================\n");
        printf("Menú:\n");
        printf("          Sala: %s\n", salaActual->nombre);
        printf("----------------------------------------\n");
        printf("1. Describir sala\n");
        printf("2. Examinar (objetos y salidas)\n");
        printf("3. Entrar en otra sala\n");
        printf("4. Coger objeto\n");
        printf("5. Soltar objeto\n");
        printf("6. Inventario\n");
        printf("7. Usar objeto\n");
        printf("8. Resolver puzle / introducir codigo\n");
        printf("9. Guardar partida\n");
        printf("10. Volver\n");
        printf("----------------------------------------\n");
        printf("Seleccione una accion: ");
        
        if (scanf("%d", &opcion) != 1) {
            opcion = 0;
            while (getchar() != '\n'); 
        }

        switch(opcion) {
            case 1: describirSala(salaActual); break;
            case 2: examinarSala(salaActual, listaObjetos, numObjetos, listaConexiones, numConexiones); break;
            case 4: 
                printf("\nIntroduce el ID del objeto a coger: ");
                scanf("%4s", idObjBuscado);
                cogerObjetos(listaObjetos, numObjetos, salaActual, idObjBuscado); 
                break;
            case 5: 
                printf("\nIntroduce el ID del objeto a soltar: ");
                scanf("%4s", idObjBuscado);
                soltarObjeto(listaObjetos, numObjetos, salaActual, idObjBuscado); 
                break;
            case 6: mostrar_inventario(listaObjetos, numObjetos); break;
            case 7: 
                printf("\nIntroduce el ID del objeto a usar: ");
                scanf("%4s", idObjBuscado);
                usarObjeto(listaObjetos, numObjetos, listaConexiones, numConexiones, salaActual, idObjBuscado); 
                break;
            case 8: interactuarPuzle(puzleActual, listaConexiones, numConexiones); break;
            case 10: printf("\n-> Volviendo al menu principal...\n"); break;
            default: printf("\n-> Opcion no disponible o no implementada todavia.\n"); break;
        }
    } while (opcion != 10);
}
