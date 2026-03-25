#include<stdio.h>
#include<stdlib.h>
int main() {
    printf("\n");
    printf("  _____  ____  ___     ____   ____    _    ____  _____ \n");
    printf(" | ____|/ ___||_ _|   / ___| / ___|  / \\  |  _ \\| ____|\n");
    printf(" |  _|  \\___ \\ | |    \\___ \\| |     / _ \\ | |_) |  _|  \n");
    printf(" | |___  ___) || |     ___) | |___ / ___ \\|  __/| |___ \n");
    printf(" |_____||____/|___|   |____/ \\____/_/   \\_\\_|   |_____|\n");
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
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            printf("Registrate:\n");
            //función para registrarse
            registrarUsuario();
            break;
        case 2:
            printf("Iniciar Sesión:\n");
            //función para iniciar sesión
            iniciarSesion();
            break;
        case 3:
            printf("Saliendo...\n");
            return 0;
            break;
        default:
            printf("Opción no válida\n");
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
   