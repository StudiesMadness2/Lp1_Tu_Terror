#include "Dibujador.h"
#include "Avatar.h"
#include "Constantes.h"
#include <cstdio>
#include "rlutil.h"

Dibujador::Dibujador() {
    A = 3;
    B = 3;
}

Dibujador::~Dibujador() {
}

void Dibujador::SetB(int B) {
    this->B = B;
}

int Dibujador::GetB() const {
    return B;
}

void Dibujador::SetA(int A) {
    this->A = A;
}

int Dibujador::GetA() const {
    return A;
}

void Dibujador::dibujarEsquemaVersion2(Laberinto &lab, Avatar Ava) {
    int x, y, m, n, i_abajo, i_arriba, j_izq, j_der;
    char celda;

    m = lab.getM();
    n = lab.getN();

    x = Ava.GetPosX();
    y = Ava.GetPosY();

    i_abajo = y + B;
    i_arriba = y - B;

    j_izq = x - A;
    j_der = x + A;

    system("cls");
    printf("\n");

    for (int i = i_arriba; i <= i_abajo; i++) { //aquí se modifica el alto y bajo del mapa

        rlutil::setColor(7);

        for (int k = 0; k < 70 - (j_der - j_izq) / 2; k++)printf(" ");

        for (int j = j_izq - 3; j <= j_der + 3; j++) {
            if ((i < 0 || j < 0) || (i > m - 1 || j > n - 1)) {
                rlutil::setColor(7);
                printf("%c", 178);
                continue;
            }
            celda = lab.getCasilla(i, j);
            if (x == j && y == i) {
                rlutil::setColor(114);
                printf("%c", IMAG_AVATAR);
            } else if (celda == '-' || celda == '+') {
                rlutil::setColor(121); // Entra  y Sale
                printf("%c", celda);
            } else if (celda == 'M'  ) {
                rlutil::setColor(124);
                printf("%c", celda);
            }else if (celda == 'A'){
                rlutil::setColor(118);
                printf("%c", celda);                
            } else {
                rlutil::setColor(112); // 96 176 112
                if (celda == ADENTRO) printf("%c", celda);
                else printf("%c", PAREDVISUAL);
            }
        }
        rlutil::setColor(7);
        printf("\n");
    }
    rlutil::setColor(7); // Regresa al color por defecto
}