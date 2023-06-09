#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include "EasyPIO.h"
void ameba(void);
void newton(void);


#define MAX_INTENTOS 3
#define CLAVE "12345"

const int led[] = {14, 15, 18, 23, 24, 25, 8, 7};
const int num_leds = sizeof(led) / sizeof(led[0]);

int velocidad = 200000; // Velocidad inicial (200 milisegundos)

extern void ameba_arm();
extern void newton_arm();

void hidePassword(char* password) {
    int ch;
    int i = 0;

    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (i > 0) {
                i--;
                password[i] = '\0';
                printw("\b \b");
            }
        } else {
            password[i] = ch;
            i++;
            printw("*");
        }
        refresh();
    }

    password[i] = '\0';
}

void disp_binary(int i) {
    int t;
    for (t = 128; t > 0; t = t / 2) {
        if (i & t)
            digitalWrite(led[t/2], 1);
        else
            digitalWrite(led[t/2], 0);
    }
    usleep(velocidad);
}

void ameba() {
    ameba_arm();
}

void autoFantastico(int repeticiones) {
    for (int i = 0; i < repeticiones; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                if (k == j)
                    digitalWrite(led[k], 1);
                else
                    digitalWrite(led[k], 0);
            }
            usleep(velocidad);
        }
        for (int j = 7; j >= 0; j--) {
            for (int k = 0; k < 8; k++) {
                if (k == j)
                    digitalWrite(led[k], 1);
                else
                    digitalWrite(led[k], 0);
            }
            usleep(velocidad);
        }
    }
}

void secuenciaChoque(const unsigned char *secuencia, int repeticiones) {
    for (int i = 0; i < repeticiones; i++) {
        for (int j = 0; j < 8; j++) {
            unsigned char patron = secuencia[j];

            for (int k = 0; k < 8; k++) {
                if ((patron >> k) & 1)
                    digitalWrite(led[k], 1);
                else
                    digitalWrite(led[k], 0);
            }
            usleep(velocidad);
        }
    }
}

void Newton() {
    char bolitaFija = '*';
    char bolitaMovil = '*';
    int direccionDerecha = 1;
    int posicionMovil = 0;

    while (1) {
        for (int i = 0; i < 7; i++) {
            if (i == posicionMovil) {
                printf("%c", bolitaMovil);
                digitalWrite(led[i], 1);
            } else if (i == 3) {
                printf("%c", bolitaFija);
                digitalWrite(led[i], 1);
            } else {
                printf("_");
                digitalWrite(led[i], 0);
            }
        }
        printf("\n");
        usleep(velocidad);

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

void ajustarVelocidad(int tecla) {
    switch (tecla) {
        case KEY_UP:
            velocidad -= 10000;
            break;
        case KEY_DOWN:
            velocidad += 10000;
            break;
    }

    if (velocidad < 1000)
        velocidad = 1000;
    else if (velocidad > 5000000)
        velocidad = 5000000;
}

int main() {
    char claveIngresada[6];
    int intentos = 0;
    unsigned char choque[8] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
    unsigned char ameba[17] = {0x81, 0x41, 0x21, 0x11, 0x09, 0x05, 0x83, 0x83, 0x8C, 0x98, 0xB0, 0xE0, 0xE1, 0x71, 0x39, 0x1D, 0x0F};

    printf("Ingrese su contraseña de 5 dígitos: ");

    while (intentos < MAX_INTENTOS) {
        scanf("%5s", claveIngresada);

        int i;
        for (i = 0; i < strlen(claveIngresada); i++) {
            printf("*");
        }
        printf("\n");

        if (strcmp(claveIngresada, CLAVE) == 0) {
            printf("Bienvenido al Sistema\n");

            pioInit();

            for (int i = 0; i < num_leds; i++) {
                pinMode(led[i], OUTPUT);
            }

            initscr();
            keypad(stdscr, TRUE);
            nodelay(stdscr, TRUE);

            int opcion;
            printf("Ingrese una opción:\n");
            printf("1) Auto Fantástico\n");
            printf("2) Choque\n");
            printf("3) Ameba\n");
            printf("4) Newton\n");
            printf("5) Salir\n");

            scanf("%d", &opcion);

            switch (opcion) {
                case 1:
                    printf("Auto Fantástico\n");
                    autoFantastico(3);
                    break;
                case 2:
                    printf("Choque\n");
                    secuenciaChoque(choque, 3);
                    break;
                case 3:
                    printf("Ameba\n");
                    ameba(10);
                    //    for (i = 0; i < sizeof(ameba); i++) {
                    //                        unsigned char numero = ameba[i];
                    //                        disp_binary(numero);
                    //                    }
                    break;
                case 4:
                    printf("Newton\n");
                    newton(10);
                    //newton(4);
                    break;
                case 5:
                    printf("Chauuuuu\n");
                    break;
                default:
                    printf("Opción inválida\n");
                    break;
            }

            endwin();
            pioExit();

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

    return 0;
}
