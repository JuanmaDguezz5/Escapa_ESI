#include "CargarFicheros.h"

// Carga el estado guardado de la partida
// Carga el estado guardado de la partida
estado_partida CargarEstadoGuardado(Ficheros *F, puzle *arrayPuzles, int numPuzles, objeto *arrayObjetos, int numObjetos, conexiones *arrayConexiones, int numConexiones, int id_jugador_actual) {
    estado_partida ep = {0, 0, ""};
    if (F->Partidas == NULL) return ep; 
    
    char linea[256];
    int esMiPartida = 0; // Candado de seguridad

    while (fgets(linea, sizeof(linea), F->Partidas)) {
        linea[strcspn(linea, "\n")] = '\0';
        
        if (!strncmp(linea, "JUGADOR: ", 9)) {
            sscanf(linea, "JUGADOR: %d", &ep.id_jugador);
            
            // Comprobamos si el guardado pertenece a quien está jugando
            if (ep.id_jugador == id_jugador_actual) {
                esMiPartida = 1; // Abrimos el candado
            } else {
                // No es su partida. Marcamos error (-1) y abortamos lectura.
                ep.id_jugador = -1;
                return ep;
            }
        } else if (esMiPartida == 1) { // Solo si el candado está abierto, leo los datos
            if (!strncmp(linea, "SALA: ", 6)) {
                sscanf(linea, "SALA: %s", ep.id_sala_str);
            } else if (!strncmp(linea, "PUZLE: ", 7)) {
                char idPuzle[15];
                if (sscanf(linea, "PUZLE: %[^-]-Resuelto", idPuzle) == 1) {
                    for (int i = 0; i < numPuzles; i++) {
                        if (strcmp(arrayPuzles[i].id_puzle, idPuzle) == 0) arrayPuzles[i].resuelto = 1;
                    }
                }
            } else if (!strncmp(linea, "OBJETO: ", 8)) {
                char idObj[15], lugar[15];
                if (sscanf(linea, "OBJETO: %[^-]-%s", idObj, lugar) == 2) {
                    for (int i = 0; i < numObjetos; i++) {
                        if (strcmp(arrayObjetos[i].id_objeto, idObj) == 0) strcpy(arrayObjetos[i].lugar, lugar);
                    }
                }
            } else if (!strncmp(linea, "CONEXION: ", 10)) {
                char idCon[15], estado[15];
                if (sscanf(linea, "CONEXION: %[^-]-%s", idCon, estado) == 2) {
                    for (int i = 0; i < numConexiones; i++) {
                        if (strcmp(arrayConexiones[i].id_conexion, idCon) == 0) strcpy(arrayConexiones[i].Estado, estado);
                    }
                }
            }
        }
    }
    return ep;
}

// Verifica si el usuario existe y coincide la contraseña
int CargarLoginUsuario(Ficheros *F, jugadores *jDestino) {
    if (F->Jugadores == NULL) return 0;
    
    char idJugadorBuscado[11];
    char contraseniaIntroducida[9]; 
    printf("Nombre de usuario:\n-> ");
    scanf("%10s", idJugadorBuscado);
    
    int encontrado = 0;
    char linea[256];
    
    while (fgets(linea, sizeof(linea), F->Jugadores)) {
        linea[strcspn(linea, "\n")] = '\0';
        linea[strcspn(linea, "\r")] = '\0'; // Limpia saltos de línea de Windows
        if(strlen(linea) < 5) continue;
        
        jugadores temp;
        char *token = strtok(linea, "-");
        if(token) temp.id_jugador = atoi(token);
        
        token = strtok(NULL, "-");
        if(token) strcpy(temp.Nomb_jugador, token);
        
        token = strtok(NULL, "-");
        if(token) strcpy(temp.jugador, token);
        
        token = strtok(NULL, "-");
        if(token) strcpy(temp.contrasenia, token);

        if (strcmp(temp.jugador, idJugadorBuscado) == 0) {
            encontrado = 1;
            *jDestino = temp;
            do {
                printf("Introduzca su contrasena (Escribir 'Salir' para cancelar):\n-> ");
                scanf("%8s", contraseniaIntroducida);
            } while (strcmp(jDestino->contrasenia, contraseniaIntroducida) && strcmp(contraseniaIntroducida, "Salir"));
            break;
        }
    }
    
    if (encontrado && !strcmp(contraseniaIntroducida, "Salir")) {
        return 0; 
    } else if (encontrado) {
        printf("\n¡Bienvenido/a de nuevo, %s!\n", jDestino->Nomb_jugador);
        return 1; 
    } else {
        printf("Usuario no encontrado.\n");
        return 0; 
    }
}

// Carga las Salas
void CargarSalas(Ficheros *F, salas *arraySalas, int numSalas) {
    char linea[300];
    int i = 0;
    while (fgets(linea, sizeof(linea), F->Salas) && i < numSalas) {
        linea[strcspn(linea, "\n")] = '\0';
        linea[strcspn(linea, "\r")] = '\0';
        if(strlen(linea) < 5) continue;

        strcpy(arraySalas[i].id_sala, strtok(linea, "-"));
        strcpy(arraySalas[i].nombre, strtok(NULL, "-"));
        strcpy(arraySalas[i].Tipo, strtok(NULL, "-"));
        strcpy(arraySalas[i].descripcion, strtok(NULL, "-"));
        i++;
    }
}

// Carga los Objetos
void CargarObjetos(Ficheros *F, objeto *arrayObjetos, int numObjetos) {
    char linea[300];
    int i = 0;
    while (fgets(linea, sizeof(linea), F->Objetos) && i < numObjetos) {
        linea[strcspn(linea, "\n")] = '\0';
        linea[strcspn(linea, "\r")] = '\0';
        if(strlen(linea) < 5) continue;

        strcpy(arrayObjetos[i].id_objeto, strtok(linea, "-"));
        strcpy(arrayObjetos[i].nombre, strtok(NULL, "-"));
        strcpy(arrayObjetos[i].descripcion, strtok(NULL, "-"));
        strcpy(arrayObjetos[i].lugar, strtok(NULL, "-"));
        i++;
    }
}

// Carga las Conexiones (FORMATO ESTRICTO DE 5 CAMPOS)
void CargarConexiones(Ficheros *F, conexiones *arrayConexiones, int numConexiones) {
    char linea[300];
    int i = 0;
    while (fgets(linea, sizeof(linea), F->Conexiones) && i < numConexiones) {
        linea[strcspn(linea, "\n")] = '\0';
        linea[strcspn(linea, "\r")] = '\0';
        if(strlen(linea) < 5) continue;

        // 1. ID Conexion
        strcpy(arrayConexiones[i].id_conexion, strtok(linea, "-")); 
        
        // 2. ID Origen
        strcpy(arrayConexiones[i].id_origen, strtok(NULL, "-"));    
        
        // 3. ID Destino
        strcpy(arrayConexiones[i].id_destino, strtok(NULL, "-"));   
        
        // 4. Estado
        char *estado = strtok(NULL, "-");
        if(estado) strcpy(arrayConexiones[i].Estado, estado);       
        
        // 5. Condicion (Objeto o Puzle)
        char *condicion = strtok(NULL, "-");
        if(condicion) strcpy(arrayConexiones[i].condicion, condicion); 
        else strcpy(arrayConexiones[i].condicion, "0");
        
        i++;
    }
}

// Carga los Puzles (Añadiendo el estado "resuelto = 0" automáticamente)
void CargarPuzles(Ficheros *F, puzle *arrayPuzles, int numPuzles) {
    char linea[300];
    int i = 0;
    while (fgets(linea, sizeof(linea), F->Puzles) && i < numPuzles) {
        linea[strcspn(linea, "\n")] = '\0';
        linea[strcspn(linea, "\r")] = '\0';
        if(strlen(linea) < 5) continue;

        strcpy(arrayPuzles[i].id_puzle, strtok(linea, "-"));
        strcpy(arrayPuzles[i].nombre, strtok(NULL, "-"));
        arrayPuzles[i].id_sala = atoi(strtok(NULL, "-"));
        strcpy(arrayPuzles[i].tipo, strtok(NULL, "-"));
        strcpy(arrayPuzles[i].descripcion, strtok(NULL, "-"));
        strcpy(arrayPuzles[i].solucion, strtok(NULL, "-"));
        
        arrayPuzles[i].resuelto = 0; // Por defecto pendiente
        i++;
    }
}