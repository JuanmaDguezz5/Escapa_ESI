#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct {
    char id_puzle[4];      
    char nombre[16];       
    int id_sala;          
    char tipo[10];         // Código o Palabra 
    char descripcion[151]; 
    char solucion[51];     
    int resuelto;          // 0 para Pendiente, 1 para Resuelto 
} Puzle;

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
    char id_sala[4];       
    char nombre[16];       
    char Tipo[11]; //Inicial, normal o salida
    char descripcion[151];
} salas;

#endif