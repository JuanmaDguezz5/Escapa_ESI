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

void examinarSala(salas *salaActual, objeto *listaObjetos, int numObjetos, conexiones *listaConexiones, int numConexiones, salas *arraySalas, int numSalas) { 
    printf("Examinando la sala: %s...\n", salaActual->nombre);
    printf("Descripcion: %s\n", salaActual->descripcion);

    // 1. Listar Objetos en la sala
    printf("\nObjetos en la sala:\n");
    int objetosEncontrados = 0;
    for (int i = 0; i < numObjetos; i++) {
        if (listaObjetos[i].id_objeto[0] == '\0') continue;
        if (strcmp(listaObjetos[i].lugar, salaActual->id_sala) == 0) {
            printf("- %s: %s\n", listaObjetos[i].nombre, listaObjetos[i].descripcion);
            objetosEncontrados++;
        }
    }
    if (objetosEncontrados == 0) {
        printf("- No hay objetos visibles en esta sala.\n");
    }

    // 2. Listar Salidas 
    printf("\nSalidas visibles:\n");
    int salidasEncontradas = 0;
    for (int i = 0; i < numConexiones; i++) {
        if (listaConexiones[i].id_conexion[0] == '\0') continue;

        if (strcmp(listaConexiones[i].id_origen, salaActual->id_sala) == 0) {
            
            // --- NUEVO: Buscamos el nombre de la sala de destino ---
            char nombreDestino[50] = "Desconocida";
            for(int j = 0; j < numSalas; j++) {
                if(strcmp(arraySalas[j].id_sala, listaConexiones[i].id_destino) == 0) {
                    strcpy(nombreDestino, arraySalas[j].nombre);
                    break;
                }
            }
            // --------------------------------------------------------

            if (strcmp(listaConexiones[i].Estado, "Abierta") == 0 || strcmp(listaConexiones[i].Estado, "Activa") == 0) {
                printf("- Hacia la sala %s (%s) [ABIERTA]\n", listaConexiones[i].id_destino, nombreDestino);
            } else {
                printf("- Hacia la sala %s (%s) [BLOQUEADA - Necesitas: %s]\n", listaConexiones[i].id_destino, nombreDestino, listaConexiones[i].condicion);
            }
            salidasEncontradas++;
        }
    }
    if (salidasEncontradas == 0) {
        printf("- No hay salidas aparentes.\n");
    }
}

/*
  Permite al jugador moverse de la sala actual a una sala de destino.
 */
salas* moverSala(salas *salaActual, conexiones *listaConexiones, int numConexiones, char *idDestino, salas *arraySalas, int numSalas) {
    for (int i = 0; i < numConexiones; i++) {
        if (strcmp(listaConexiones[i].id_origen, salaActual->id_sala) == 0 && strcmp(listaConexiones[i].id_destino, idDestino) == 0) {
            if (strcmp(listaConexiones[i].Estado, "Abierta") == 0 || strcmp(listaConexiones[i].Estado, "Activa") == 0) {
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
        if (strcmp(listaObjetos[i].lugar, sala->id_sala) == 0 && strcmp(listaObjetos[i].id_objeto, idObjBuscado) == 0) {
            strcpy(listaObjetos[i].lugar, "inv");
            printf("Has recogido el objeto: %s\n", listaObjetos[i].nombre);
            return;
        }
    }
    printf("No has encontrado el objeto que buscabas.\n");
}

/*
  Gestiona la accion de soltar un objeto del inventario en la sala actual.
 */
void soltarObjeto(objeto *listaObjetos, int numObjetos, salas *salaActual, char *idObjBuscado) {
    for (int i = 0; i < numObjetos; i++) {
        if (strcmp(listaObjetos[i].id_objeto, idObjBuscado) == 0) {
            if (strcmp(listaObjetos[i].lugar, "inv") == 0) {
                strcpy(listaObjetos[i].lugar, salaActual->id_sala);
                printf("Has soltado el objeto: %s en la sala %s\n", listaObjetos[i].nombre, salaActual->nombre);
                return;
            } else {
                printf("El objeto %s no esta en tu inventario.\n", listaObjetos[i].nombre);
                return;
            }
        }
    }
    printf("El objeto que intentas soltar no existe.\n");
}

/*
  Gestiona el uso de un objeto del inventario para desbloquear conexiones adyacentes.
 */
void usarObjeto(objeto *listaObjetos, int numObjetos, salas *salaActual, conexiones *listaConexiones, int numConexiones, char *idObjBuscado) {
    int tieneObjeto = 0;
    for (int i = 0; i < numObjetos; i++) {
        if (strcmp(listaObjetos[i].id_objeto, idObjBuscado) == 0 && strcmp(listaObjetos[i].lugar, "inv") == 0) {
            tieneObjeto = 1; break;
        }
    }
    
    if (!tieneObjeto) {
        printf("No tienes el objeto %s en tu inventario.\n", idObjBuscado);
        return;
    }
    
    int usadoConExito = 0;
    for (int i = 0; i < numConexiones; i++) {
        if (strcmp(listaConexiones[i].id_origen, salaActual->id_sala) == 0 && strcmp(listaConexiones[i].Estado, "Bloqueada") == 0) {
            if (strcmp(listaConexiones[i].condicion, idObjBuscado) == 0) {
                strcpy(listaConexiones[i].Estado, "Abierta");
                printf("Has usado el objeto %s para desbloquear la salida hacia %s.\n", idObjBuscado, listaConexiones[i].id_destino);
                usadoConExito = 1;
            }
        }
    }

    if (!usadoConExito) printf("El objeto %s no desbloquea ninguna salida aqui.\n", idObjBuscado);
}

/*
  Muestra el inventario del jugador
 */
void mostrar_inventario(objeto *listaObjetos, int numObjetos) {
    int objetosEnInventario = 0;
    printf("\n--- INVENTARIO ---\n");
    for (int i = 0; i < numObjetos; i++) {
        if (strcmp(listaObjetos[i].lugar, "inv") == 0) {
            printf("- %s: %s\n", listaObjetos[i].nombre, listaObjetos[i].descripcion);
            objetosEnInventario++;
        }
    }
    if (objetosEnInventario == 0) printf("Tu inventario esta vacio.\n");
    printf("------------------\n");
} 

/*
  Gestiona la interaccion con un puzle y desbloquea conexiones.
 */
void interactuarPuzle(puzle *puzleActual, conexiones *conexionesJuego, int numConexiones, objeto *listaObjetos, int numObjetos) {
    char respuestaUsuario[50];
    
    // Evitar que el jugador resuelva el mismo puzle dos veces
    if (puzleActual->resuelto == 1) {
        printf("\nYa has resuelto este puzle anteriormente.\n");
        return;
    }

    printf("\nRETO: %s \n", puzleActual->descripcion);
    printf("Introduce tu respuesta: ");
    scanf("%49s", respuestaUsuario);

    if (strcmp(respuestaUsuario, puzleActual->solucion) == 0) {
        printf("\n¡Respuesta correcta! El puzle ha sido resuelto.\n");
        puzleActual->resuelto = 1; 

        // 1. DESBLOQUEAR PUERTAS DIRECTAMENTE (Para el puzle final P07)
        for (int i = 0; i < numConexiones; i++) {
            if (conexionesJuego[i].id_conexion[0] == '\0') continue;
            if (strcmp(conexionesJuego[i].condicion, puzleActual->id_puzle) == 0) {
                strcpy(conexionesJuego[i].Estado, "Abierta");
                printf("- ¡Se ha escuchado un clic! La conexion hacia la sala %s ahora esta ABIERTA.\n", conexionesJuego[i].id_destino);            
            }
        }

        // 2. DAR EL OBJETO DIRECTAMENTE AL INVENTARIO
        for (int i = 0; i < numObjetos; i++) {
            if (listaObjetos[i].id_objeto[0] == '\0') continue;
            
            // Comparamos solo los primeros 3 caracteres (ej. "P05") por máxima seguridad
            if (strncmp(listaObjetos[i].lugar, puzleActual->id_puzle, 3) == 0) {
                
                strcpy(listaObjetos[i].lugar, "inv"); // Va directo al inventario del jugador
                
                printf("- ¡Has conseguido un objeto secreto! Se ha anadido a tu inventario: %s\n", listaObjetos[i].nombre);
            }
        }
    } else {
        printf("\nRespuesta incorrecta. Intentalo de nuevo.\n");
    }
}

//////////////////// Funciones de Inicialización de Memoria Dinámica ////////////////////

salas* inicializarSalas(int numSalas) { 
    return (salas *)malloc((size_t)numSalas * sizeof(salas)); 
}
objeto* inicializarObjetos(int numObjetos) { 
    return (objeto *)malloc((size_t)numObjetos * sizeof(objeto)); 
}
conexiones* inicializarConexiones(int numConexiones) { 
    return (conexiones *)malloc((size_t)numConexiones * sizeof(conexiones)); 
}
puzle* inicializarPuzles(int numPuzles) { 
    return (puzle *)malloc((size_t)numPuzles * sizeof(puzle)); 
}

/*
 Libera toda la memoria dinámica reservada
 */
void liberarMemoriaContenidos(salas *arraySalas, objeto *arrayObjetos, conexiones *arrayConexiones, puzle *arrayPuzles) {
    if (arraySalas) free(arraySalas);
    if (arrayObjetos) free(arrayObjetos);
    if (arrayConexiones) free(arrayConexiones);
    if (arrayPuzles) free(arrayPuzles);
}