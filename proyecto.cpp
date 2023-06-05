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
#include <unistd.h> // Para utilizar la función usleep

#define MAX_INTENTOS 3
#define CLAVE "12345"

void disp_binary (int i){
    int t;
    for(t=128; t>0; t=t/2)
        if(i&t) printf("* ");
        else printf("_ ");
    printf("\n"); // Regresar al inicio de la línea

}

void autoFantastico(int repeticiones) {
    for (int i = 0; i < repeticiones; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                if (k == j)
                    printf("*");  // Encender la luz
                else
                    printf("_");  // Apagar la luz
            }
            printf("\n");
        }
        for (int j = 7; j >= 0; j--) {  // Iterar en sentido contrario
            for (int k = 0; k < 8; k++) {
                if (k == j)
                    printf("*");  // Encender la luz
                else
                    printf("_");  // Apagar la luz
            }
            printf("\n");
        }
    }
}

void secuenciaChoque(const unsigned char* secuencia, int repeticiones) {
    for (int i = 0; i < repeticiones; i++) {
        for (int j = 0; j < 8; j++) {
            unsigned char patron = secuencia[j];

            for (int k = 0; k < 8; k++) {
                if ((patron >> k) & 1)
                    printf("*");  // Encender la luz
                else
                    printf("_");  // Apagar la luz
            }
            printf("\n");
        }
    }
}

void PenduloDeNewton() {
    char bolitaFija = '*';
    char bolitaMovil = '*';
    int direccionDerecha = 1;
    int posicionMovil = 0;

    while (1) {
        for (int i = 0; i < 7; i++) {
            if (i == posicionMovil) {
                printf("%c", bolitaMovil);
            } else if (i == 3) {
                printf("%c", bolitaFija);
            } else {
                printf("_");
            }
        }
        printf("\n");

        usleep(100000); // Esperar 100 milisegundos

        if (direccionDerecha) {
            posicionMovil++;
            if (posicionMovil == 6) {
                direccionDerecha = 0;
            }
        } else {
            posicionMovil--;
            if (posicionMovil == 0) {
                direccionDerecha = 1;
            }
        }
    }
}

int main() {
    char claveIngresada[6]; // 5 dígitos + 1 para el carácter nulo '\0'
    int intentos = 0;
    unsigned char choque[8] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
    unsigned char ameba[17] = {0x81, 0x41, 0x21, 0x11, 0x09, 0x05, 0x83, 0x83, 0x8C, 0x98, 0xB0, 0xE0, 0xE1, 0x71, 0x39, 0x1D, 0x0F};


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
            printf("3) Carrera \n");
            printf("4) Ameba \n");
            printf("5) Secuencia 2 \n");

            scanf("%d", &opcion);

            switch (opcion) {
                case 1: {
                    printf("Auto Fantastico\n");
                    autoFantastico(3);
                    break;
                }
                case 2: {
                    printf("Choque\n");
                    secuenciaChoque(choque,3);
                    /*for (char i = 0; i <= 7; i++) {
                        disp_binary(choque[i]);
                    }
                     */
                    break;
                }
                case 3: {
                    printf("Carrera\n");
                    break;
                }
                case 4: {
                    printf("Ameba\n");
                    for (unsigned char numero : ameba) {
                        disp_binary(numero);
                    }
                    break;
                }
                case 5: {
                    printf("Secuencia 2\n");
                    PenduloDeNewton();
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


