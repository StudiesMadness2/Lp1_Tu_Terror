/* 
 * File:   PocionCuracion.cpp
 * Author: alulab14
 * 
 * Created on 5 de junio de 2015, 11:17 AM
 */
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "Artefacto.h" 
#include "PocionCuracion.h"
using namespace std;

PocionCuracion::PocionCuracion(int ptos) {
    puntosVida=ptos;
    nombre = NULL;
}

PocionCuracion::PocionCuracion(const PocionCuracion& orig) {
}

PocionCuracion::~PocionCuracion() {

}

void PocionCuracion::AsignarPocion(int ptos, char *name){
    puntosVida=ptos;
    nombre = new char[strlen(name)+1];
    strcpy(nombre,name);
}

void PocionCuracion::Imprimir(){
    cout << left << setw(35) << nombre << " - Puntos Vida: " << puntosVida << endl;
}