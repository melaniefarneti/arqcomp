// no usar cout, usar printf

// prj.s
// Arqui I UCC

/*
.text

.global main
main:
LDR R3, =array // load base address of a into R3
... more code here
done: NOP            // dummy instruction for breakpoint
MOV PC,L       // return from main

.data
        array:
.byte 0x08
.byte 0x10
.byte 0xFF
... more data here
.end
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INTENTOS 3
#define CLAVE "12345"

int main() {
    char claveIngresada[6]; // 5 dígitos + 1 para el carácter nulo '\0'
    int intentos = 0;

    printf("Ingrese su contraseña de 5 dígitos: ");

    while (intentos < MAX_INTENTOS) {
        // Leer la entrada del usuario
        scanf("%5s", claveIngresada);

        // Imprimir un asterisco (*) por cada dígito ingresado
        int i;
        for (i = 0; i < strlen(claveIngresada); i++) {
            printf("*");
        }
        printf("\n");

        // Comparar con la clave almacenada
        if (strcmp(claveIngresada, CLAVE) == 0) {
            printf("Bienvenido al Sistema\n");
            break;
        } else {
            printf("Contraseña no válida\n");
            intentos++;
            if (intentos < MAX_INTENTOS) {
                printf("Ingrese su contraseña de 5 dígitos: ");
            }
        }
    }

    if (intentos == MAX_INTENTOS) {
        printf("Ha excedido el número máximo de intentos. El programa abortará.\n");
    }

    int opcion;
    printf("Ingrese una opción (1-4): ");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            printf("Auto Fantástico\n");
            break;
        case 2:
            printf("Choque\n");
            break;
        case 3:
            printf("Secuencia 1\n");
            break;
        case 4:
            printf("Secuencia 2\n");
            break;
        default:
            printf("Opción inválida\n");
            break;
    }

    return 0;
}


