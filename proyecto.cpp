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

void disp_binary (int i){
    int t;
    for(t=128; t>0; t=t/2)
        if(i&t) printf("* ");
        else printf("_ ");
    printf("\n"); // Regresar al inicio de la línea

}

int main() {
    char claveIngresada[6]; // 5 dígitos + 1 para el carácter nulo '\0'
    int intentos = 0;
    unsigned char choque[8] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};

    printf("Ingrese su contrasenia de 5 digitos: ");

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

            int opcion;
            printf("Ingrese una opcion: \n");
            printf("1) Auto Fantastico \n");
            printf("2) Choque \n");
            printf("3) Secuencia 1 \n");
            printf("4) Secuencia 2 \n");

            scanf("%d", &opcion);

            switch (opcion) {
                case 1: {
                    printf("Auto Fantastico\n");
                    break;
                }
                case 2: {
                    printf("Choque\n");
                    for (char i = 0; i <= 7; i++) {
                        disp_binary(choque[i]);
                    }
                    break;
                }
                case 3: {
                    printf("Secuencia 1\n");
                    break;
                }
                case 4: {
                    printf("Secuencia 2\n");
                    break;
                }
                default: {
                    printf("Opcion invalida\n");
                    break;
                }
            }


            break;
        } else {
            printf("Contrasenia no valida\n");
            intentos++;
            if (intentos < MAX_INTENTOS) {
                printf("Ingrese su contrasenia de 5 digitos: ");
            }
        }
    }

    if (intentos == MAX_INTENTOS) {
        printf("Ha excedido el numero maximo de intentos. El programa abortara.\n");
    }

    return 0;
}


