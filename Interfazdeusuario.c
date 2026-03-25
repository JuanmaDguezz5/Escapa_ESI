#include<stdio.h>
#include<stdlib.h>

int registrarUsuario();
int iniciarSesion();

int main() {
    printf("\n\n");
    printf("  _____  ____  ___     ____   ____     _      ____   _____ \n");
    printf(" | ____|/ ___||_ _|   / ___| / ___|   / \\    |  _ \\ | ____|\n");
    printf(" |  _|  \\___ \\ | |    \\___ \\| |      / _ \\   | |_) ||  _|  \n");
    printf(" | |___  ___) || |     ___) | |___  / ___ \\  |  __/ | |___ \n");
    printf(" |_____||____/|___|   |____/ \\____|/_/   \\_\\ |_|    |_____|\n");
    printf("\n");
    printf("                  =================\n");
    printf("                   BIENVENIDO/A\n");
    printf("                  =================\n\n");
    printf("Bienvenido a la interfaz de usuario\n");
    printf("Seleccione una opcion:\n");
    printf("1. Nueva Partida\n");
    printf("2. Cargar Partida\n");
    printf("3. Salir\n");

    int opcion;
    int opcion2;
    int k;
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            printf("1. Registrate:\n");
            printf("2. Inicia Sesion:\n");
                 
                do {
                    k=0;
                    scanf("%d", &opcion2);

                        switch (opcion2) {

                        case 1:
                            printf("Registrate:\n");
                            registrarUsuario();
                            //función para registrarse
                        break;
                        case 2:
                            printf("Inicia Sesion:\n");
                            iniciarSesion();
                            //funcion para iniciar sesion
                        break;
                        default:
                            printf("Opcion no valida, introduzca una opcion valida\n");
                            k++;
                            fflush(stdin);
                        break;
                }
            } while (k!=0);

                        
                    
        break; 
                  
        case 2:
            printf("Inicia Sesion:\n");
                    iniciarSesion();
                //función para iniciar sesión
            break;
        case 3:
            printf("Saliendo...\n");
            return 0;
            break;
        default:
            printf("Opcion no valida\n");
            break;
    }

    return 0;
}

int registrarUsuario() {
    char Nomb_jugador[10];
    char Usuario[20];
    char contraseña[8];

    printf("Ingrese su nombre: ");
    scanf("%s", Nomb_jugador);
    printf("Ingrese su nombre de usuario: ");
    scanf("%s", Usuario);
    printf("Ingrese su contrasena: ");
    scanf("%s", contraseña);

    // código para guardar los datos del usuario en el fichero
 
    printf("Registro exitoso\n");
    return 0;
}


 int iniciarSesion() {
    char Usuario[20];
    char contraseña[8];

    printf("Ingrese su nombre de usuario: ");
    scanf("%s", Usuario);
    printf("Ingrese su contraseña: ");
    scanf("%s", contraseña);

    // código para verificar los datos del usuario en el fichero

    printf("Inicio de sesion exitoso\n");
    return 0;
    }
   
    
   
