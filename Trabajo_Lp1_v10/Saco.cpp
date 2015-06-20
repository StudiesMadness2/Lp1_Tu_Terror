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
#include "Constantes.h"
using namespace std;

Saco::Saco() {
    indice = 0;
    for (int i = 0; i < MAX_ARTEF_EN_SACO; i++)
        artefacto[i] = NULL;
}

Saco::~Saco() {
}

int Saco::estaLleno() {
    if (indice < MAX_ARTEF_EN_SACO) {
        return 0 ; 
    }
    return 1 ;
}

void Saco::AgregarAlSaco(Artefacto *art) {
    if (indice < MAX_ARTEF_EN_SACO) {
        //cout << ">>>" << indice << "<<<" ; 
        artefacto[indice] = art;
        indice++;
    }
}
//void Saco::AgregarAlSaco(Arma artefact){
//    if(indice<10){
//        artefacto[indice]=artefact;
//        cout << "Artefacto agregado al saco" << endl;
//        indice++;
//    }else{
//        cout << "Saco lleno, no puede agregarse el artefacto" << endl;
//    }
//}
//
//void Saco::AgregarAlSaco(Armadura artefact){
//    if(indice<10){
//        artefacto[indice]=artefact;
//        cout << "Artefacto agregado al saco" << endl;
//        indice++;
//    }else{
//        cout << "Saco lleno, no puede agregarse el artefacto" << endl;
//    }
//}
//
//void Saco::AgregarAlSaco(PocionCuracion artefact){
//    if(indice<10){
//        artefacto[indice]=artefact;
//        cout << "Artefacto agregado al saco" << endl;
//        indice++;
//    }else{
//        cout << "Saco lleno, no puede agregarse el artefacto" << endl;
//    }
//}

int Saco::GetIndice() {
    return indice;
}
//void Saco::Imprimir(){
//    for(int i=0;i<indice;i++){
//        artefacto[i].Imprimir();
//    }
//}

Artefacto* Saco::operator[](int ind) {
    return artefacto[ind]; // Puntero artefacto
}