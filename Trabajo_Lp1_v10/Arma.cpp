/* 
 * File:   Arma.cpp
 * Author: alulab14
 * 
 * Created on 5 de junio de 2015, 11:15 AM
 */
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Artefacto.h"
#include "Arma.h"
#include "Entidad.h"


using namespace std;

Arma::Arma(int min, int max) {
    SetTipo(0);
    SetDanhoMin(min);
    SetDanhoMax(max);
    nombre = NULL;
}

void Arma::AsignarArma(int min, int max, char *name) {
    danhoMin = min;
    danhoMax = max;
    nombre = new char[strlen(name) + 1];
    strcpy(nombre, name);
}

void Arma::SetDanhoMax(int danhoMax) {
    this->danhoMax = danhoMax;
}

int Arma::GetDanhoMax() const {
    return danhoMax;
}

void Arma::SetDanhoMin(int danhoMin) {
    this->danhoMin = danhoMin;
}

int Arma::GetDanhoMin() const {
    return danhoMin;
}

void Arma::Imprimir() {
    cout << "Arma:     " << left << setw(20) << nombre << " - Danho: " << left << setw(3) << danhoMin << "(Min) - " << left << setw(3) << danhoMax << "(Max) " << char(186) << endl;
}

void Arma::usar() {
    cout << "uso Arma \n";
}

void Arma::usar2(class Entidad &E, int ind) {
    if (E.GetArma()== NULL) {
        E.SetArma(this);
        E.botarArtefacto(ind);
    } else {
        Arma *aux = this;
        Arma *actual = E.GetArma();
        E.botarArtefacto(ind);
        E.agregarArtefactoAlSaco(actual, 1);
        E.SetArma(aux);
    }
}

void Arma::SetNombre(char* nombre) {
    this->nombre = new char[strlen(nombre)+1]; 
    strcpy(this->nombre,nombre);
}

char* Arma::GetNombre() const {
    return nombre;
}