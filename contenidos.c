#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contenidos.h"

/*
  Muestra la información de la sala actual y verifica la victoria.
 */
void describirSala(salas *salaActual) {
    if (salaActual == NULL) {
        printf("Error: No se ha podido cargar la sala.\n");
        return;
    }
    // Mostrar el nombre y la descripcion de la sala
    printf("\n--- %s ---\n", salaActual->nombre);
    printf("%s\n", salaActual->descripcion);

    // Comprobar si la sala es la SALIDA
    if (strcmp(salaActual->Tipo, "SALIDA") == 0) {
        printf("¡Has encontrado la salida! ¡Felicidades!\n");
    }
}

/*
  Lista los elementos interactuables de la ubicacion actual.
 */
void examinarSala(salas *salaActual, objeto *listaObjetos, int numObjetos, conexiones *listaConexiones, int numConexiones) { 
    printf("Examinando la sala: %s...\n", salaActual->nombre);
    printf("Descripcion: %s\n", salaActual->descripcion);

    // 1. Listar Objetos en la sala
    printf("Objetos en la sala:\n");
    int objetosEncontrados = 0;
    for (int i = 0; i < numObjetos; i++) {
        if (strcmp(listaObjetos[i].lugar, salaActual->id_sala) == 0) {
            printf("- %s: %s\n", listaObjetos[i].nombre, listaObjetos[i].descripcion);
            objetosEncontrados++;
        }
    }
    if (objetosEncontrados == 0) {
        printf("No hay objetos visibles en esta sala.\n");
    }

    // 2. Listar conexiones disponibles
    printf("SALIDAS VISIBLES:\n");
    int conexionesEncontradas = 0;
    for (int i = 0; i < numConexiones; i++) {
        if (strcmp(listaConexiones[i].id_origen, salaActual->id_sala) == 0) {
            conexionesEncontradas++;
            if (strcmp(listaConexiones[i].Estado, "Abierta") == 0 || strcmp(listaConexiones[i].Estado, "Activa") == 0) {
                printf("- Hacia %s (ABIERTA)\n", listaConexiones[i].id_destino);
            } else {
                printf("- Hacia %s (Bloqueada - Necesitas: %s)\n", listaConexiones[i].id_origen, listaConexiones[i].condicion);
            }
        }
    } 
    
    if (conexionesEncontradas == 0) {
        printf("Parece que no hay salidas... Estas atrapado.\n");
    }
}

/*
  Permite al jugador moverse de la sala actual a una sala de destino.
 */
salas* moverSala(salas *salaActual, conexiones *listaConexiones, int numConexiones, char *idDestino, salas *arraySalas, int numSalas) {
    for (int i = 0; i < numConexiones; i++) {
        if (strcmp(listaConexiones[i].id_origen, salaActual->id_sala) == 0 && strcmp(listaConexiones[i].id_destino, idDestino) == 0) {
            
            if (strcmp(listaConexiones[i].Estado, "Abierta") == 0 || strcmp(listaConexiones[i].Estado, "Activa") == 0) {
                // Buscar la sala de destino en el array de salas
                for (int j = 0; j < numSalas; j++) {
                    if (strcmp(arraySalas[j].id_sala, idDestino) == 0) {
                        printf("Te has movido a la sala: %s\n", arraySalas[j].nombre);
                        describirSala(&arraySalas[j]);
                        
                        return &arraySalas[j]; 
                    }
                }
                printf("Error: La sala de destino no existe en el sistema.\n");
                return salaActual; 
                
            } else {
                printf("La salida hacia %s esta bloqueada. Necesitas: %s\n", idDestino, listaConexiones[i].condicion);
                return salaActual; 
            }
        }
    }
    printf("No hay una conexion directa hacia la sala %s desde aqui.\n", idDestino);
    return salaActual; 
}

/*
  Gestiona la recogida de objetos de una sala.
 */
void cogerObjetos(objeto *listaObjetos, int numObjetos, salas *sala, char *idObjBuscado) {
    for (int i = 0; i < numObjetos; i++) {
        // Buscamos el objeto por su ID y verificamos su Localizacion
        if (strcmp(listaObjetos[i].lugar, sala->id_sala) == 0) {
            // Comparamos IDs para confirmar que es el objeto que queremos recoger
            if (strcmp(listaObjetos[i].id_objeto, idObjBuscado) == 0) {
                strcpy(listaObjetos[i].lugar, "inv");
                printf("Has recogido el objeto: %s\n", listaObjetos[i].nombre);
                return;
            }
        }
    }
    printf("No has encontrado el objeto que buscabas.\n");
}

/*
  Gestiona la accion de soltar un objeto del inventario en la sala actual.
 */
void soltarObjeto(objeto *listaObjetos, int numObjetos, salas *salaActual, char *idObjBuscado) {
    for (int i = 0; i < numObjetos; i++) {
        // Buscamos el objeto por su ID y verificamos que este en el inventario
        if (strcmp(listaObjetos[i].id_objeto, idObjBuscado) == 0) {
            if (strcmp(listaObjetos[i].lugar, "inv") == 0) {
                // Asignamos el ID de la sala actual al lugar del objeto
                strcpy(listaObjetos[i].lugar, salaActual->id_sala);
                printf("Has soltado el objeto: %s en la sala %s\n", listaObjetos[i].nombre, salaActual->nombre);
                return;
            } else {
                printf("El objeto %s no esta en tu inventario, no puedes soltarlo.\n", listaObjetos[i].nombre);
                return;
            }
        }
    }
    printf("El objeto que intentas soltar no existe en el sistema.\n");
}

/*
  Gestiona el uso de un objeto del inventario para desbloquear conexiones adyacentes.
 */

void usarObjeto(objeto *listaObjetos, int numObjetos, salas *salaActual, conexiones *listaConexiones, int numConexiones, char *idObjBuscado) {
    int tieneObjeto = 0;

    // 1. Verificar que el objeto esta en el inventario
    for (int i = 0; i < numObjetos; i++) {
        if (strcmp(listaObjetos[i].id_objeto, idObjBuscado) == 0) {
            if (strcmp(listaObjetos[i].lugar, "inv") == 0) {
                tieneObjeto = 1;
                break;
            }
        }
    }
    
    if (!tieneObjeto) {
        printf("No tienes el objeto %s en tu inventario.\n", idObjBuscado);
        return;
    }
    
    int usadoConExito = 0;

    // 2. Buscar conexiones bloqueadas en la sala actual que requieran este objeto
    for (int i = 0; i < numConexiones; i++) {
        if (strcmp(listaConexiones[i].id_origen, salaActual->id_sala) == 0) {
            if (strcmp(listaConexiones[i].Estado, "Bloqueada") == 0) {
                if (strcmp(listaConexiones[i].condicion, idObjBuscado) == 0) {
                    // Cambiamos el estado a ABIERTA
                    strcpy(listaConexiones[i].Estado, "Abierta");
                    printf("Has usado el objeto %s para desbloquear la salida hacia %s.\n", idObjBuscado, listaConexiones[i].id_destino);
                    usadoConExito = 1;
                }
            }
        }
    }

    if (!usadoConExito) {
        printf("El objeto %s no se puede usar aqui o no desbloquea ninguna salida.\n", idObjBuscado);
    }
}

/*
  Muestra el inventario del jugador
 */
void mostrar_inventario(objeto *listaObjetos, int numObjetos) {
    int objetosEnInventario = 0;
    printf("\n--- INVENTARIO ---\n");

    for (int i = 0; i < numObjetos; i++) {
        // Comprobamos si el objeto actual esta en el inventario
        if (strcmp(listaObjetos[i].lugar, "inv") == 0) {
            printf("- %s: %s\n", listaObjetos[i].nombre, listaObjetos[i].descripcion);
            objetosEnInventario++;
        }
    }

    if (objetosEnInventario == 0) {
        printf("Tu inventario esta vacio.\n");
    }
    
    printf("------------------\n");
} 

/*
  Gestiona la interaccion con un puzle y desbloquea conexiones.
 */
void interactuarPuzle(puzle *puzleActual, conexiones *conexionesJuego, int numConexiones) {
    char respuestaUsuario[50];
    
    // 1. Mostrar el puzle al usuario
    printf("RETO: %s \n", puzleActual->descripcion);
    
    // 2. Solicitar la respuesta al usuario
    printf("Introduce tu respuesta: ");
    scanf("%s", respuestaUsuario);

    // 3. Verificar la respuesta
    if (strcmp(respuestaUsuario, puzleActual->solucion) == 0) {
        printf("¡Respuesta correcta! El puzle ha sido resuelto.\n");
        puzleActual->resuelto = 1; // Marcar el puzle como resuelto

        for (int i = 0; i < numConexiones; i++) {
            if (strcmp(conexionesJuego[i].condicion, puzleActual->id_puzle) == 0) {
                strcpy(conexionesJuego[i].Estado, "Activa");
                printf("Se ha escuchado un clic: La conexion a %s ahora esta abierta.\n", conexionesJuego[i].id_destino);            
            }
        }
    } else {
        printf("Respuesta incorrecta. Intentalo de nuevo.\n");
    }
}

//////////////////// // Funciones de Inicialización de Memoria Dinámica ////////////////////

salas* inicializarSalas(int numSalas) {
    salas *arraySalas = (salas *)malloc(numSalas * sizeof(salas));
    if (arraySalas == NULL) {
        printf("Error al reservar memoria para las salas.\n");
        exit(1);
    }
    return arraySalas;
}

objeto* inicializarObjetos(int numObjetos) {
    objeto *arrayObjetos = (objeto *)malloc(numObjetos * sizeof(objeto));
    if (arrayObjetos == NULL) {
        printf("Error al reservar memoria para los objetos.\n");
        exit(1);
    }
    return arrayObjetos;
}

conexiones* inicializarConexiones(int numConexiones) {
    conexiones *arrayConexiones = (conexiones *)malloc(numConexiones * sizeof(conexiones));
    if (arrayConexiones == NULL) {
        printf("Error al reservar memoria para las conexiones.\n");
        exit(1);
    }
    return arrayConexiones;
}

puzle* inicializarPuzles(int numPuzles) {
    puzle *arrayPuzles = (puzle *)malloc(numPuzles * sizeof(puzle));
    if (arrayPuzles == NULL) {
        printf("Error al reservar memoria para los puzles.\n");
        exit(1);
    }
    return arrayPuzles;
}

/*
 Libera toda la memoria dinámica reservada
 */
void liberarMemoriaContenidos(salas *arraySalas, objeto *arrayObjetos, conexiones *arrayConexiones, puzle *arrayPuzles) {
    if (arraySalas != NULL) {
        free(arraySalas);
    }
    if (arrayObjetos != NULL) {
        free(arrayObjetos);
    }
    if (arrayConexiones != NULL) {
        free(arrayConexiones);
    }
    if (arrayPuzles != NULL) {
        free(arrayPuzles);
    } 
    printf("Memoria liberada correctamente. ¡Gracias por jugar!\n");    
}

