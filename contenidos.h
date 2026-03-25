#ifndef CONTENIDOS_H
#define CONTENIDOS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id_jugador;
    int id_sala;
    int id_obj;     // Objeto: Id_obj, Localizacion)
    int id_conexion; // Conexion: Id_conexion, Estado)
} partida;

typedef struct {
    int id_jugador; 
    char Nomb_jugador[21]; // Nombre completo
    char jugador[11];       // Nombre de usuario
    char contrasenia[9];
    int id_obj;     // ID del objeto que posee el jugador, 0 si no tiene ninguno, tantos codigos como objetos posea    
} jugadores;

typedef struct {
    char id_puzle[4];      
    char nombre[16];       
    int id_sala;          
    char tipo[10];         // Código o Palabra 
    char descripcion[151]; 
    char solucion[51];     
    int resuelto;          // 0 para Pendiente, 1 para Resuelto 
} puzle;

typedef struct {
    char id_objeto[5];       
    char nombre[16];       
    char descripcion[151];
    char lugar[11];         //Id_sala o Inventario 
} objeto;

typedef struct {
    char id_conexion[4];       
    char id_origen[3];       
    char id_destino[3];
    char Estado[11];    // Activa o Bloqueada
    int condicion; // 0 si no aplica, Id_obj o Id_puzle
} conexiones;

typedef struct {
    int id_sala;       
    char nombre[16];       
    char Tipo[11]; //Inicial, normal o salida
    char descripcion[151];
} salas;

// Muestra la descripción de la sala y verifica si es la SALIDA 
void describirSala(salas *salaActual); 

// Permite resolver un puzle mediante código o palabra 
void interactuarPuzle(Puzle *puzleActual, conexiones *conexionesJuego, int numConexiones);

// Traslada un objeto de la sala al inventario 
void gestionObjetos (objeto *listaObjetos, int numObjetos, salas *sala, char *idObjBuscado);

// Lista objetos y salidas indicando si están bloqueadas o abiertas
void examinarSala(salas *salaActual, objeto *listaObjetos, int numObjetos, conexiones *listaConexiones, int numConexiones, int numConexiones);

#endif
