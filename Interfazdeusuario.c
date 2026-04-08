#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "contenidos.h"

// Prototipos de funciones 
int menuAccesoInicial();
int registrarUsuario();
int iniciarSesion();
void menuPrincipal();
void menuPartida();

int main() {
    // 1. Primero se pide al usuario q se registre o inicie sesion y se verifica
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
        k = 0; // Asumimos que todo irá bien en esta iteración

        printf("\n========================================\n");
        printf("          ACCESO A ESI SCAPE           \n");
        printf("========================================\n");
        printf("1. Iniciar Sesion\n");
        printf("2. Registrarse\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");

        // Comprobamos si scanf pudo leer un número correctamente
        if (scanf("%d", &opcion) != 1) {
            printf("\n[ERROR] Entrada no valida. Por favor, introduzca un numero.\n");
            
            // Esta es la forma estándar y 100% segura de limpiar el buffer en C
            // Lee y descarta todo lo que el usuario escribió hasta el "Enter" (\n)
            while (getchar() != '\n'); 
            
            k = 1; // Activamos la bandera para repetir el bucle
        } else {
            // Si entró un número, evaluamos qué número es
            switch(opcion) {
                case 1:
                    return iniciarSesion();
                case 2:
                    // MODIFICACIÓN: Si el registro es 1 (exitoso), devuelve 1 al main
                    if (registrarUsuario() == 1) {
                        return 1; 
                    }
                    // Mantenemos iniciarSesion() por si el registro no fuera exitoso y no borrar código
                    return iniciarSesion();
                case 3:
                    return 0; // Cierra el menú (y el juego)
                default:
                    printf("\n[ERROR] Opcion no valida, introduzca una opcion del 1 al 3.\n");
                    k = 1; // Activamos la bandera para repetir el bucle
                    break;
            }
        }
    } while (k != 0);

    return 0; // no debería llegar aqui, pero es necesario para que el compilador no de error
}

void menuPrincipal() {
    int opcion;
    int k;

    do {
        k = 0; // Asumimos que no hay errores para empezar
        
        printf("\n\n");
        printf("  _____  ____  ___     ____   ____    _      ____   _____ \n");
        printf(" | ____|/ ___||_ _|   / ___| / ___|   / \\    |  _ \\ | ____|\n");
        printf(" |  _|  \\___ \\ | |    \\___ \\| |      / _ \\   | |_) ||  _|  \n");
        printf(" | |___  ___) || |     ___) | |___  / ___ \\  |  __/ | |___ \n");
        printf(" |_____||____/|___|   |____/ \\____|/_/   \\_\\ |_|    |_____|\n");
        printf("\n");
        printf("                  =================\n");
        printf("                   BIENVENIDO/A\n");
        printf("                  =================\n\n");
        
        printf("Menú:\n");
        printf("       ESI SCAPE\n");
        printf("----------------------------------\n");
        printf("1. Nueva Partida\n");
        printf("2. Cargar Partida\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");

        // Si el usuario mete una letra, scanf devuelve 0 (falla). 
        // Forzamos opcion a 0 para que vaya al "default"
        if (scanf("%d", &opcion) != 1) {
            opcion = 0; 
        }

        switch (opcion) {
            case 1:
                printf("\nIniciando NUEVA PARTIDA...\n");
                menuPartida(); 
                k = 1; // Al terminar de jugar, volvemos al menú principal
                break;
            case 2:
                printf("\nCargando partida guardada...\n");
                menuPartida(); 
                k = 1; // Al terminar de jugar, volvemos al menú principal
                break;
            case 3:
                printf("\nSaliendo de ESI ESCAPE...\n");
                k = 0; // Permite que el bucle termine
                break;
            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
                k = 1; // Activa la variable para repetir el menú
                fflush(stdin); // limpio el buffer
                break;
        }
    } while (k != 0);
}

int registrarUsuario() {
    char Nomb_jugador[20];
    char jugador[11];
    char contrasenia[9];

    printf("Ingrese su nombre completo: ");
    scanf("%s", Nomb_jugador);
    printf("Ingrese su nombre de usuario: ");
    scanf("%s", jugador);
    printf("Ingrese su contrasena: ");
    scanf("%s", contrasenia);

    // código para guardar los datos del usuario en el fichero
 
    printf("Registro exitoso\n");
    return 1;
}

int iniciarSesion() {
    char jugador[11];
    char contrasenia[9];

    printf("Ingrese su nombre de usuario: ");
    scanf("%s", jugador);
    printf("Ingrese su contrasenia: ");
    scanf("%s", contrasenia);

    // código para verificar los datos del usuario en el fichero

    printf("Inicio de sesion exitoso\n");
    return 1;
}
    
void menuPartida(salas *salaActual, objeto *listaObjetos, int numObjetos, conexiones *listaConexiones, int numConexiones, puzle *puzleActual) {
    int opcion;
    char nombreSalaActual[30] = "Cafeteria"; 
    
    // Añadimos una variable para guardar el ID del objeto que el usuario quiera 
    char idObjBuscado[5];

    /* * NOTA IMPORTANTE PARA EL FUTURO:
     * Para que estas funciones no den error al compilar, tendrás que pasarle a 
     * menuPartida() los punteros del juego o declararlos globalmente. 
     * Ejemplo: salas *salaActual, objeto *listaObjetos, etc.
     */

    do {
        printf("\n========================================\n");
        printf("Menú:\n");
        printf("          Sala: %s\n", nombreSalaActual);
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
        
        // Limpieza de buffer segura en caso de introducir letras
        if (scanf("%d", &opcion) != 1) {
            opcion = 0;
            while (getchar() != '\n'); 
        }

        switch(opcion) {
            case 1: 
                describirSala(salaActual); 
                break;
                
            case 2: 
                examinarSala(salaActual, listaObjetos, numObjetos, listaConexiones, numConexiones); 
                break;
                
            case 3: 
                // En el .h no hay función para moverse de sala todavía
                printf("\n-> Entrando en otra sala...\n"); 
                break;
                
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
                
            case 6: 
                mostrar_inventario(listaObjetos, numObjetos); 
                break;
                
            case 7: 
                printf("\nIntroduce el ID del objeto a usar: ");
                scanf("%4s", idObjBuscado);
                usarObjeto(listaObjetos, numObjetos, listaConexiones, numConexiones, salaActual, idObjBuscado); 
                break;
                
            case 8: 
                interactuarPuzle(puzleActual, listaConexiones, numConexiones); 
                break;
                
            case 9: 
                printf("\n-> Guardando la partida en Partida.txt...\n"); 
                break;
                
            case 10: 
                printf("\n-> Volviendo al menu principal...\n"); 
                break;
                
            default: 
                printf("\n-> Opcion no valida. Intente de nuevo.\n");
                fflush(stdin);
                break;
        }
    } while (opcion != 10);
}
