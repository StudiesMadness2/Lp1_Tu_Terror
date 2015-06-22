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
#include "Entidad.h"
using namespace std;

PocionCuracion::PocionCuracion(int ptos) {
    SetTipo(2);
    puntosVida = ptos;
    nombre = NULL;
}

PocionCuracion::PocionCuracion(const PocionCuracion& orig) {
}

PocionCuracion::~PocionCuracion() {

}

void PocionCuracion::AsignarPocion(int ptos, char *name) {
    puntosVida = ptos;
    nombre = new char[strlen(name) + 1];
    strcpy(nombre, name);
}

void PocionCuracion::Imprimir() {
    cout << "Pocion:   " << left << setw(20) << nombre << " - Puntos Vida  : " << left << setw(3) << puntosVida << "         " << char(186) << endl;
}

void PocionCuracion::usar() {
    cout << "uso Pocion\n";
}

void PocionCuracion ::usar2(class Entidad &E,int ind) {
    if(E.GetVidaActual()<E.GetMaxVida()){
        E.botarArtefacto(ind);
        if((E.GetVidaActual()+this->puntosVida)>E.GetMaxVida())
            E.SetVidaActual(E.GetMaxVida());
        else
            E.SetVidaActual(E.GetVidaActual()+this->puntosVida);
    }
}