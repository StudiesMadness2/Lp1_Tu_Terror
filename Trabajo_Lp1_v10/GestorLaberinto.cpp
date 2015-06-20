/* 
 * File:   GestorLaberinto.cpp
 * Author: alulab14
 * 
 * Created on 5 de junio de 2015, 11:23 AM
 */
#include "Constantes.h"
#include "GestorLaberinto.h"
#include "Laberinto.h"
#include <fstream>
#include <iostream>
#include <io.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

GestorLaberinto::GestorLaberinto() {
}

GestorLaberinto::~GestorLaberinto() {
}

Laberinto GestorLaberinto::crear(char *nombreArchivo) {
    //Laberinto lab ; 
    int m, n;
    char c;
    ifstream archEntrad(nombreArchivo);
    if (!archEntrad) {
        cerr << "No se pudo abrir Archivo" << endl;
        exit(1);
    }
    int contM = 3, contA = 3;
    archEntrad >> m >> n;
    Laberinto lab(m, n);
    c = archEntrad.get(); // Se lee cambio de linea 
    srand(time(NULL));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            c = archEntrad.get();
            if (c == '\n') c = archEntrad.get();
            if (c == ANTERIOR) {
                lab.setX_Ant(j);
                lab.setY_Ant(i);
            }
            if (c == SIGUIENTE) {
                lab.setX_Sig(j);
                lab.setY_sig(i);
            }
            if (c == MONSTRUO) {
                
                int numb = rand() % 10 + 1;
                if (numb < 5 && contM > 0) {
                    c = ' ';
                    contM--;
                }
            }
            if (c == ARTEFACTO) {                
                int numb = rand() % 10 + 1;

                if (numb < 5 && contA > 0) {
                    c = ' ';
                    contA--;
                }
            }
            lab.getCelda()[i][j].SetTipo(c);
        }
    }
    return lab;
}