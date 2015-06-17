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
#include "Arma.h"
#include "Armadura.h"
#include "PocionCuracion.h"
#include "Saco.h"
using namespace std;

Saco::Saco() {
    indice = 0;
}

Saco::~Saco() {
}

void Saco::AgregarAlSaco(Arma artefact){
    if(indice<10){
        artefacto[indice]=artefact;
        cout << "Artefacto agregado al saco" << endl;
        indice++;
    }else{
        cout << "Saco lleno, no puede agregarse el artefacto" << endl;
    }
}

void Saco::AgregarAlSaco(Armadura artefact){
    if(indice<10){
        artefacto[indice]=artefact;
        cout << "Artefacto agregado al saco" << endl;
        indice++;
    }else{
        cout << "Saco lleno, no puede agregarse el artefacto" << endl;
    }
}

void Saco::AgregarAlSaco(PocionCuracion artefact){
    if(indice<10){
        artefacto[indice]=artefact;
        cout << "Artefacto agregado al saco" << endl;
        indice++;
    }else{
        cout << "Saco lleno, no puede agregarse el artefacto" << endl;
    }
}
int Saco::GetIndice(){
    return indice;
}

void Saco::Imprimir(){
    for(int i=0;i<indice;i++){
        artefacto[i].Imprimir();
    }
}