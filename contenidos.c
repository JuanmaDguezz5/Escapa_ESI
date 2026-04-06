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

void interactuarPuzle(Puzle *puzleActual, conexiones *conexionesJuego, int numConexiones){

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




