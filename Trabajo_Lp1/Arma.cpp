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
using namespace std;

Arma::Arma(int min,int max) {
    SetDanhoMin(min);
    SetDanhoMax(max);
    nombre=NULL;
}

void Arma::AsignarArma(int min, int max, char *name){
    danhoMin=min;
    danhoMax=max;
    nombre = new char[strlen(name)+1];
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

void Arma::Imprimir(){
    cout << "Arma: " << left << setw(35) << nombre << " - Daño: " << danhoMin << "(Min) - " << danhoMax << "(Max)" << endl;
}