#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "motor.h"
#include "contenidos.h"
#include "Ficheros.h"
#include "GuardarFicheros.h"

void iniciarBucleJuego(salas *arraySalas, int numSalas, 
                       objeto *arrayObjetos, int numObjetos, 
                       conexiones *arrayConexiones, int numConexiones, 
                       puzle *arrayPuzles, int numPuzles,
                       salas *salaActual, int idJugador) {
    
    int jugando = 1;
    int opcion;
    char inputTemporal[15]; 

    // Al entrar por primera vez o al cargar partida, mostramos donde estamos
    describirSala(salaActual);

    while (jugando) {
        // 1. Comprobar Condición de Victoria 
        if (strcmp(salaActual->Tipo, "SALIDA") == 0) {
            printf("\n====================================================\n");
            printf("  ¡HAS ESCAPADO! Mision cumplida. Fin del juego.\n");
            printf("====================================================\n");
            printf("Presiona ENTER para volver al menu principal...\n");
            
            // Limpiar buffer y pausar
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
            getchar(); 
            
            jugando = 0;
            break; 
        }

        // 2. Mostrar Menú de Acciones 
        printf("\n========================================\n");
        printf("          SALA: %s\n", salaActual->nombre);
        printf("========================================\n");
        printf("1. Describir sala\n");
        printf("2. Examinar (objetos y salidas)\n");
        printf("3. Entrar en otra sala\n");
        printf("4. Coger objeto\n");
        printf("5. Soltar objeto\n");
        printf("6. Inventario\n");
        printf("7. Usar objeto\n");
        printf("8. Resolver puzle / introducir codigo\n");
        printf("9. Guardar partida\n");
        printf("10. Volver al menu\n");
        printf("----------------------------------------\n");
        printf("Elige una accion: ");
        
        if (scanf("%d", &opcion) != 1) {
            opcion = 0; 
            while (getchar() != '\n'); 
        }

        // 3. Procesar la Acción
        switch (opcion) {
            case 1: 
                describirSala(salaActual); 
                break;
                
            case 2: 
                examinarSala(salaActual, arrayObjetos, numObjetos, arrayConexiones, numConexiones); 
                break;
                
            case 3:
                printf("Introduce el ID de la sala a la que quieres ir (ej. 02): ");
                scanf("%14s", inputTemporal);
                salaActual = moverSala(salaActual, arrayConexiones, numConexiones, inputTemporal, arraySalas, numSalas);
                break;
                
            case 4:
                printf("Introduce el ID del objeto que quieres coger (ej. OB01): ");
                scanf("%14s", inputTemporal);
                cogerObjetos(arrayObjetos, numObjetos, salaActual, inputTemporal);
                break;
                
            case 5:
                printf("Introduce el ID del objeto que quieres soltar: ");
                scanf("%14s", inputTemporal);
                soltarObjeto(arrayObjetos, numObjetos, salaActual, inputTemporal);
                break;
                
            case 6: 
                mostrar_inventario(arrayObjetos, numObjetos); 
                break;
                
            case 7:
                printf("Introduce el ID del objeto que quieres usar: ");
                scanf("%14s", inputTemporal);
                usarObjeto(arrayObjetos, numObjetos, salaActual, arrayConexiones, numConexiones , inputTemporal);
                break;
                
            case 8:
                printf("Introduce el ID del puzle a resolver (ej. P01): ");
                scanf("%14s", inputTemporal);
                int puzleEncontrado = 0;
                
                // Buscamos el puzle en la memoria dinámica
                for(int i = 0; i < numPuzles; i++) {
                    if(arrayPuzles[i].id_puzle[0] != '\0' && strcmp(arrayPuzles[i].id_puzle, inputTemporal) == 0) {
                        // Verificamos si el jugador está en la sala correcta para resolverlo
                        if (arrayPuzles[i].id_sala == atoi(salaActual->id_sala)) {
                            interactuarPuzle(&arrayPuzles[i], arrayConexiones, numConexiones);
                        } else {
                            printf("Ese puzle no se encuentra en esta sala.\n");
                        }
                        puzleEncontrado = 1; 
                        break;
                    }
                }
                if(!puzleEncontrado) printf("No existe ningun puzle con ese ID.\n");
                break;
                
            case 9:
                printf("\nGuardando estado de la partida...\n"); 
                
                Ficheros F_guardar;
                if (AbrirFicherosEscritura(&F_guardar) == 0) {
                    
                    // Creamos un "jugador temporal" solo para pasarle el ID a la función de guardado
                    jugadores jTemp;
                    jTemp.id_jugador = idJugador;

                    // Pasamos los punteros que ya tenemos, sin tocar variables globales
                    GuardarEstadoPartida(&F_guardar, jTemp, *salaActual, arrayPuzles, numPuzles);
                    GuardarObjetosActualizados(&F_guardar, arrayObjetos, numObjetos);
                    GuardarConexionesActualizadas(&F_guardar, arrayConexiones, numConexiones);
                    
                    CerrarFicheros(&F_guardar); 
                    printf("¡Partida guardada con exito!\n");
                }
                break;
                
            case 10:
                printf("Abandonando la partida actual. Volviendo al menu...\n");
                jugando = 0; 
                break;
                
            default:
                printf("Opcion no valida. Intentalo de nuevo.\n");
        }
    }
}
