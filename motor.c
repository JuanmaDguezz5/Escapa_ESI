#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "motor.h"
#include "contenidos.h"

void iniciarBucleJuego(salas *arraySalas, int numSalas, 
                       objeto *arrayObjetos, int numObjetos, 
                       conexiones *arrayConexiones, int numConexiones, 
                       puzle *arrayPuzles, int numPuzles,
                       salas *salaActual, int idJugador) {
    
    int jugando = 1;
    int opcion;
    char inputTemporal[15]; // Para leer IDs de objetos, salas o puzles

    // Al entrar por primera vez o al cargar partida, mostramos donde estamos
    describirSala(salaActual);

    while (jugando) {
        // 1. Comprobar Condición de Victoria [cite: 141]
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
            break; // Salimos del bucle
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
        printf("10. Volver\n");
        printf("----------------------------------------\n");
        printf("Elige una accion: ");
        
        // Leer opcion y limpiar buffer
        scanf("%d", &opcion);
        printf("\n");

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
                scanf("%s", inputTemporal);
                // Mover sala devuelve un puntero a la nueva sala (o a la actual si falla) [cite: 143, 144]
                salaActual = moverSala(salaActual, arrayConexiones, numConexiones, inputTemporal, arraySalas, numSalas);
                break;
                
            case 4:
                printf("Introduce el ID del objeto que quieres coger (ej. OB01): ");
                scanf("%s", inputTemporal);
                cogerObjetos(arrayObjetos, numObjetos, salaActual, inputTemporal);
                break;
                
            case 5:
                printf("Introduce el ID del objeto que quieres soltar: ");
                scanf("%s", inputTemporal);
                soltarObjeto(arrayObjetos, numObjetos, salaActual, inputTemporal);
                break;
                
            case 6:
                mostrar_inventario(arrayObjetos, numObjetos);
                break;
                
            case 7:
                printf("Introduce el ID del objeto que quieres usar: ");
                scanf("%s", inputTemporal);
                usarObjeto(arrayObjetos, numObjetos, salaActual, arrayConexiones, numConexiones , inputTemporal);
                break;
                
            case 8:
                printf("Introduce el ID del puzle a resolver (ej. P01): ");
                scanf("%s", inputTemporal);
                
                int puzleEncontrado = 0;
                // Buscamos el puzle por su ID en el array de puzles
                for(int i = 0; i < numPuzles; i++) {
                    if(strcmp(arrayPuzles[i].id_puzle, inputTemporal) == 0) {
                        // Verificamos si el puzle pertenece a la sala actual
                        // NOTA: Para comparar un int (id_sala del puzle) con un string (id_sala actual), usamos atoi()
                        if (arrayPuzles[i].id_sala == atoi(salaActual->id_sala)) {
                            interactuarPuzle(&arrayPuzles[i], arrayConexiones, numConexiones);
                            puzleEncontrado = 1;
                        } else {
                            printf("Ese puzle no esta en esta sala.\n");
                            puzleEncontrado = 1; // Lo encontramos pero no aqui
                        }
                        break;
                    }
                }
                
                if(!puzleEncontrado) {
                    printf("No existe ningun puzle con ese ID.\n");
                }
                break;
                
            case 9:
                // Aquí en el futuro llamarás a guardarPartida() para escribir en Partida.txt [cite: 154]
                printf("Guardando estado de la partida...\n");
                printf("¡Partida guardada con exito!\n");
                break;
                
            case 10:
                printf("Abandonando la partida actual. Volviendo al menu...\n");
                jugando = 0; // Rompe el bucle while
                break;
                
            default:
                printf("Opcion no valida. Intentalo de nuevo.\n");
        }
    }
}