#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contenidos.h"


/**
 * Muestra la información de la sala actual y verifica la victoria.
 *  {Pre}  salaActual != NULL. El puntero debe apuntar a una sala válida.
 * {Post} Se imprime por pantalla el nombre y la descripción de la sala. 
 * Si el tipo de sala es "SALIDA", se muestra el mensaje de victoria.
 */

void describirSala(salas *salaActual) {
    if (salaActual == NULL) {
        printf("Error: No se ha podido cargar la sala.\n");
        return;
    }
    //Mostar el nombre y la descripción de la sala
    printf("\n--- %s ---\n", salaActual->nombre);
    printf("%s\n", salaActual->descripcion);

    //Comprobar si la sala es la SALIDA
    if (strcmp(salaActual->Tipo, "SALIDA") == 0) {
        printf("¡Has encontrado la salida! ¡Felicidades!\n");
    }
}

/**
 *  Gestiona la interacción con un puzle y desbloquea conexiones.
 * * {pre}  puzleActual y conexionesJuego != NULL. numConexiones >= 0. 
 * {post} Si la respuesta es correcta, marca el puzle como resuelto y cambia el 
 * estado de las conexiones asociadas a "Activa". 
 */

void interactuarPuzle(puzle *puzleActual, conexiones *conexionesJuego, int numConexiones){

    char respuestaUsuario[50];
    //1. Mostrar el puzle al usuario
    printf("RETO: %s \n", puzleActual->descripcion);
    //2. Solicitar la respuesta al usuario
    printf("Introduce tu respuesta: ");
    scanf("%s", respuestaUsuario);

    //3. Verificar la respuesta
    if (strcmp(respuestaUsuario, puzleActual->solucion) == 0) {
        printf("¡Respuesta correcta! El puzle ha sido resuelto.\n");
        puzleActual->resuelto = 1; //Marcar el puzle como resuelto

        for (int i = 0; i < numConexiones; i++) {
            if (strcmp(conexionesJuego[i].condicion, puzleActual->id_puzle) == 0) {
                strcpy(conexionesJuego[i].Estado, "Activa");
                printf("Se ha escuchado un clic: La conexion a %s ahora esta abierta.\n", conexionesJuego[i].id_destino);            }
        }
        
    } else {
        printf("Respuesta incorrecta. Inténtalo de nuevo.\n");
    }
}

/**
 *  Gestiona la recogida de objetos de una sala.
 * * {pre}  listaObjetos y sala != NULL. idObjBuscado debe ser un ID de 4 caracteres. 
 * {post} Si el objeto está en la sala y el ID coincide, su lugar cambia a "inv". 
 * Se garantiza que el objeto deja de estar en la sala. 
 */
void gestionObjetos (objeto *listaObjetos, int numObjetos, salas *sala, char *idObjBuscado){
    for (int i = 0; i < numObjetos; i++) {
        //Buscamos el objeto por su ID y verificamos su Locaalización
        if (strcmp(listaObjetos[i].lugar, sala->id_sala) == 0) {
            // Comparamos IDs para confirmar que es el objeto que queremos recoger
            if(strcmp(listaObjetos[i].id_objeto, idObjBuscado) == 0){
            strcpy(listaObjetos[i].lugar, "inv");
            printf("Has recogido el objeto: %s\n", listaObjetos[i].nombre);
            return;
          }
       }
   }
    printf("No has encontrado el objeto que buscabas.\n");
}

/**
 * Gestiona la acción de soltar un objeto del inventario en la sala actual.
 * {Pre} listaObjetos y salaActual != NULL. idObjBuscado debe ser un ID de 4 caracteres.
 * {Post} Si el objeto está en el inventario y coincide con el ID, su lugar cambia 
 * al ID de la sala actual.
 */

 void soltarObjeto(objeto *listaObjetos, int numObjetos, salas *salaActual, char *idObjBuscado){
    for (int i = 0; i < numObjetos; i++) {
        //Buscamos el objeto por su ID y verificamos que esté en el inventario
        if (strcmp(listaObjetos[i].id_objeto, idObjBuscado) == 0) {
            // Comparamos IDs para confirmar que es el objeto que queremos soltar
            if(strcmp(listaObjetos[i].lugar, "inv") == 0){
            // 3. Asignamos el ID de la sala actual al lugar del objeto
            strcpy(listaObjetos[i].lugar, salaActual->id_sala);
            printf("Has soltado el objeto: %s en la sala %s\n", listaObjetos[i].nombre, salaActual->nombre);
            return;
          } else {
            printf("El objeto %s no está en tu inventario, no puedes soltarlo.\n", listaObjetos[i].nombre);
            return;
          }

       }
   }
    printf("El objeto que intentas soltar no existe en el sistema.\n");
}

/**
 * Gestiona el uso de un objeto del inventario para desbloquear conexiones adyacentes.
 * {Pre} Punteros válidos a las listas. idObjBuscado debe ser de 4 caracteres.
 * {Post} Si el objeto está en el inventario y coincide con la condición de una 
 * conexión bloqueada en la sala actual, la conexión pasa a estado "Abierta".
 */

 void usarObjeto(objeto *listaObjetos, int numObjetos, salas *salaActual, conexiones *listaConexiones, int numConexiones, char *idObjBuscado){
    
    int tieneObjeto = 0;

    //1. Verificar que el objeto está en el inventario
    for (int i = 0; i < numObjetos; i++) {
        if (strcmp(listaObjetos[i].id_objeto, idObjBuscado) == 0) {
            if(strcmp(listaObjetos[i].lugar, "inv") == 0){
                tieneObjeto = 1;
                break;
            }
        }
    }
    //2. Buscar conexiones bloqueadas en la sala actual que requieran este objeto
    if(!tieneObjeto){
        printf("No tienes el objeto %s en tu inventario.\n", idObjBuscado);
        return;
    }
    
    int usadoConExito = 0;

    for (int i = 0; i < numConexiones; i++) {
        // Miramos si la conexión sale de nuestra sala actual

        if (strcmp(listaConexiones[i].id_origen, salaActual->id_sala) == 0) {
       
            // Miramos si la conexión está bloqueada (nota: en tu .txt a veces dice "Bloqueda" y otras "Bloqueada")
           
            if (strcmp(listaConexiones[i].Estado, "Bloqueada") == 0 || strcmp(listaConexiones[i].Estado, "Bloqueada") == 0) {
           // Verificamos si la condición de esa conexión pide exactamente el objeto que queremos usar
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
        printf("El objeto %s no se puede usar aquí o no desbloquea ninguna salida.\n", idObjBuscado);
    }
}


/**
 *  Lista los elementos interactuables de la ubicación actual.
 * * {pre}  Punteros válidos. numObjetos y numConexiones reflejan el tamaño de los arrays. 
 * {post} Muestra por pantalla objetos en el suelo y estado de las salidas (Abiertas/Bloqueadas). 
 */

void examinarSala(salas *salaActual, objeto *listaObjetos, int numObjetos, conexiones *listaConexiones, int numConexiones){ 
    printf("Examinando la sala: %s...\n", salaActual->nombre);
    printf("Descripción: %s\n", salaActual->descripcion);

    //1. Listar Objetos en la sala
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

    //2. Listar conexiones disponibles
    printf("SALIDAS VISIBLES:\n");
    int conexionesEncontradas = 0;
    for (int i = 0; i < numConexiones; i++) {
        if (strcmp(listaConexiones[i].id_origen, salaActual->id_sala) == 0) {
            printf("- Hacia %s (ABIERTA)\n", listaConexiones[i].id_destino);
        } else {
            printf("- Hacia %s (Bloqueada - Necesitas: %s)\n", listaConexiones[i].id_origen, listaConexiones[i].condicion);
        }
        conexionesEncontradas++;
    }
    
    if (conexionesEncontradas == 0) {
        printf("Parece que no hay salidas... Estas atrapado.\n");
    }
}

/**
 * Reserva memoria dinámica para el array de salas.
 * {Pre} numSalas > 0.
 * {Post} Devuelve un puntero al bloque de memoria reservado. Termina el programa si hay error.
 */

 salas* inicializarSalas(int numSalas) {
    salas *arraySalas = (salas *)malloc(numSalas * sizeof(salas));
    if (arraySalas == NULL) {
        printf("Error al reservar memoria para las salas.\n");
        exit(1);
    }
    return arraySalas;
}

/**
 * Reserva memoria dinámica para el array de objetos.
 * {Pre} numObjetos > 0.
 * {Post} Devuelve un puntero al bloque de memoria reservado. Termina el programa si hay error.
 */

 objeto* inicializarObjetos(int numObjetos) {
    objeto *arrayObjetos = (objeto *)malloc(numObjetos * sizeof(objeto));
    if (arrayObjetos == NULL) {
        printf("Error al reservar memoria para los objetos.\n");
        exit(1);
    }
    return arrayObjetos;
 }

/**
* Reserva memoria dinámica para el array de conexiones.
 * {Pre} numConexiones > 0.
 * {Post} Devuelve un puntero al bloque de memoria reservado. Termina el programa si hay error.
 */

 conexiones* inicializarConexiones(int numConexiones) {
    conexiones *arrayConexiones = (conexiones *)malloc(numConexiones * sizeof(conexiones));
    if (arrayConexiones == NULL) {
        printf("Error al reservar memoria para las conexiones.\n");
        exit(1);
    }
    return arrayConexiones;
}

/**
 * Reserva memoria dinámica para el array de puzles.
 * {Pre} numPuzles > 0.
 * {Post} Devuelve un puntero al bloque de memoria reservado. Termina el programa si hay error.
 */

 puzle* inicializarPuzles(int numPuzles) {
    puzle *arrayPuzles = (puzle *)malloc(numPuzles * sizeof(puzle));
    if (arrayPuzles == NULL) {
        printf("Error al reservar memoria para los puzles.\n");
        exit(1);
    }
    return arrayPuzles;
}

/**
 * Libera toda la memoria dinámica reservada para las estructuras del contenido.
 * Se debe llamar al cerrar el programa.
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
    printf("Memoria liberada correctamente. ¡Gracias por jugar!\n");    
    }




