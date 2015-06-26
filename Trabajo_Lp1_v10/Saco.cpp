/* 
 * File:   Saco.cpp
 * Author: alulab14
 * 
 * Created on 5 de junio de 2015, 11:14 AM
 */
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "Artefacto.h"
#include "Saco.h"
#include "Constantes.h"
using namespace std;

Saco::Saco() {
    indice = 0;
    for (int i = 0; i < MAX_ARTEF_EN_SACO; i++)
        artefacto[i] = NULL;
}



int Saco::estaLleno() {
    if (indice < MAX_ARTEF_EN_SACO) {
        return 0;
    }
    return 1;
}

int Saco::botarArteFacto(int ind) {
    int j;
    if (artefacto[ind] == NULL) {
        return 0;
    } else {
        for (j = ind; j <= indice - 2; j++) {
            artefacto[j] = artefacto[j + 1];
        }
        indice = indice - 1;
        return 1;
    }
}

void Saco::AgregarAlSaco(Artefacto *art, int flag) {
    if (indice < MAX_ARTEF_EN_SACO) {
        //cout << ">>>" << indice << "<<<" ; 
        artefacto[indice] = art;
        indice++;
    }
}

int Saco::GetIndice() {
    return indice;
}

Artefacto* Saco::operator[](int ind) {
    return artefacto[ind]; // Puntero artefacto
}

