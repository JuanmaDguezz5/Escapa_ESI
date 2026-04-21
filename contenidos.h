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



// Muestra la descripción de la sala y verifica si es la SALIDA 
void describirSala(salas *salaActual); 

// Lista objetos y salidas indicando si están bloqueadas o abiertas
void examinarSala(salas *salaActual, objeto *listaObjetos, int numObjetos, conexiones *listaConexiones, int numConexiones);

// Permite moverse a una sala adyacente si la conexión está abierta o activa
salas* moverSala(salas *salaActual, conexiones *listaConexiones, int numConexiones, char *idDestino, salas *arraySalas, int numSalas);

// Traslada un objeto de la sala al inventario 
void cogerObjetos(objeto *listaObjetos, int numObjetos, salas *sala, char *idObjBuscado);

// Usa un objeto del inventario para abrir una conexión bloqueada adyacente
void usarObjeto(objeto *listaObjetos, int numObjetos, salas *salaActual, conexiones *listaConexiones, int numConexiones, char *idObjBuscado);

// Pasa un objeto del inventario a la sala actual
void soltarObjeto(objeto *listaObjetos, int numObjetos, salas *salaActual, char *idObjBuscado);

// Muestra el inventario del jugador
void mostrar_inventario(objeto *listaObjetos, int numObjetos);

// Permite resolver un puzle mediante código o palabra 
void interactuarPuzle(puzle *puzleActual, conexiones *conexionesJuego, int numConexiones);


// Funciones de Inicialización de Memoria Dinámica

salas* inicializarSalas(int numSalas);
objeto* inicializarObjetos(int numObjetos);
conexiones* inicializarConexiones(int numConexiones);
puzle* inicializarPuzles(int numPuzles);

// Función para liberar la memoria al final del juego
void liberarMemoriaContenidos(salas *arraySalas, objeto *arrayObjetos, conexiones *arrayConexiones, puzle *arrayPuzles);

#endif
