#ifndef CONTENIDOS_H
#define CONTENIDOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id_objeto[5];       
    char nombre[30];       
    char descripcion[151];
    char lugar[15];         // Guarda el ID de la sala o "inv" si está en el inventario
} objeto;

typedef struct {
    int id_jugador;
    int id_sala_int; 
    char id_sala_str[5];    // Para manejar el ID de texto (ej: "01")
} estado_partida;

typedef struct {
    int id_jugador; 
    char Nomb_jugador[50];  // Ampliado para nombres completos largos
    char jugador[11];       // Nombre de usuario
    char contrasenia[9];    // Contraseña de 8 caracteres + \0
} jugadores;

typedef struct {
    char id_puzle[5];      
    char nombre[30];       
    int id_sala;          
    char tipo[10];         
    char descripcion[151]; 
    char solucion[51];     
    int resuelto;           // 0 para Pendiente, 1 para Resuelto
} puzle;

typedef struct {
    char id_conexion[5];       
    char id_origen[3];       
    char id_destino[3];
    char Estado[11];        // "Abierta", "Bloqueada" o "Activa"
    char condicion[6];      // ID del objeto o puzle necesario para abrirla
} conexiones;

typedef struct {
    char id_sala[3];       
    char nombre[30];       
    char Tipo[11];          // "INICIAL", "NORMAL" o "SALIDA"
    char descripcion[151];
} salas;



/*
 * Función: describirSala
 * Precondición: El puntero salaActual no debe ser NULL y debe apuntar a una sala válida.
 * Postcondición: Muestra por pantalla el nombre y la descripción de la sala. Si la sala 
 * es de tipo "SALIDA", imprime un mensaje de victoria.
 */
void describirSala(salas *salaActual); 

/*
 * Función: examinarSala
 * Precondición: Los punteros a salaActual, listaObjetos, listaConexiones y arraySalas deben ser válidos. 
 * Las cantidades (numObjetos, numConexiones, numSalas) deben ser mayores o iguales a 0.
 * Postcondición: Imprime la lista de objetos presentes en la sala actual y todas las salidas 
 * visibles con su estado correspondiente (Abierta/Bloqueada) y nombre de destino.
 */
void examinarSala(salas *salaActual, objeto *listaObjetos, int numObjetos, conexiones *listaConexiones, int numConexiones, salas *arraySalas, int numSalas);

/*
 * Función: moverSala
 * Precondición: Los punteros deben ser válidos. idDestino debe ser una cadena de texto válida.
 * Postcondición: Si existe una conexión abierta/activa hacia idDestino, devuelve un puntero a la 
 * nueva sala. Si está bloqueada o no existe, devuelve el puntero a la sala actual.
 */
salas* moverSala(salas *salaActual, conexiones *listaConexiones, int numConexiones, char *idDestino, salas *arraySalas, int numSalas);

/*
 * Función: cogerObjetos
 * Precondición: Punteros válidos. idObjBuscado debe contener el ID del objeto a recoger.
 * Postcondición: Si el objeto se encuentra en la sala actual, se modifica su atributo "lugar" 
 * a "inv" (inventario) y se notifica al jugador.
 */
void cogerObjetos(objeto *listaObjetos, int numObjetos, salas *sala, char *idObjBuscado);

/*
 * Función: usarObjeto
 * Precondición: Punteros válidos. El jugador debe tener el objeto (idObjBuscado) en su inventario.
 * Postcondición: Si el objeto coincide con la condición de alguna conexión bloqueada de la sala 
 * actual, cambia el estado de dicha conexión a "Abierta".
 */
void usarObjeto(objeto *listaObjetos, int numObjetos, salas *salaActual, conexiones *listaConexiones, int numConexiones, char *idObjBuscado);

/*
 * Función: soltarObjeto
 * Precondición: Punteros válidos. El objeto indicado debe estar actualmente en el inventario ("inv").
 * Postcondición: Modifica el atributo "lugar" del objeto, cambiándolo de "inv" al ID de la sala actual.
 */
void soltarObjeto(objeto *listaObjetos, int numObjetos, salas *salaActual, char *idObjBuscado);

/*
 * Función: mostrar_inventario
 * Precondición: Punteros válidos. numObjetos debe ser mayor o igual a 0.
 * Postcondición: Muestra por pantalla el nombre y descripción de todos los objetos 
 * cuyo atributo "lugar" sea igual a "inv".
 */
void mostrar_inventario(objeto *listaObjetos, int numObjetos);

/*
 * Función: interactuarPuzle
 * Precondición: Punteros válidos. El puzleActual no debe estar resuelto (resuelto == 0).
 * Postcondición: Si la respuesta del usuario coincide con la solución, marca el puzle como 
 * resuelto (1), abre las conexiones que dependían de él y traslada los 
 * objetos ocultos dentro del puzle al inventario del jugador.
 */
void interactuarPuzle(puzle *puzleActual, conexiones *conexionesJuego, int numConexiones, objeto *listaObjetos, int numObjetos);


// FUNCIONES DE MEMORIA DINÁMICA


/*
 * Función: inicializarSalas
 * Precondición: numSalas debe ser mayor que 0.
 * Postcondición: Reserva y devuelve un puntero a un bloque de memoria dinámica 
 * suficiente para almacenar 'numSalas' estructuras de tipo salas.
 */
salas* inicializarSalas(int numSalas);

/*
 * Función: inicializarObjetos
 * Precondición: numObjetos debe ser mayor que 0.
 * Postcondición: Reserva y devuelve un puntero a un bloque de memoria dinámica 
 * suficiente para almacenar 'numObjetos' estructuras de tipo objeto.
 */
objeto* inicializarObjetos(int numObjetos);

/*
 * Función: inicializarConexiones
 * Precondición: numConexiones debe ser mayor que 0.
 * Postcondición: Reserva y devuelve un puntero a un bloque de memoria dinámica 
 * suficiente para almacenar 'numConexiones' estructuras de tipo conexiones.
 */
conexiones* inicializarConexiones(int numConexiones);

/*
 * Función: inicializarPuzles
 * Precondición: numPuzles debe ser mayor que 0.
 * Postcondición: Reserva y devuelve un puntero a un bloque de memoria dinámica 
 * suficiente para almacenar 'numPuzles' estructuras de tipo puzle.
 */
puzle* inicializarPuzles(int numPuzles);

/*
 * Función: liberarMemoriaContenidos
 * Precondición: Los punteros proporcionados deben apuntar a bloques de memoria 
 * previamente reservados con malloc/calloc (pueden ser NULL).
 * Postcondición: Libera correctamente la memoria dinámica de todos los arrays pasados 
 * por parámetro para evitar fugas de memoria (memory leaks).
 */
void liberarMemoriaContenidos(salas *arraySalas, objeto *arrayObjetos, conexiones *arrayConexiones, puzle *arrayPuzles);

#endif
