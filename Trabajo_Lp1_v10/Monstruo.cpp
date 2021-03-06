/* 
 * File:   Monstruo.cpp
 * Author: alulab14
 * 
 * Created on 5 de junio de 2015, 11:18 AM
 */
#include "Entidad.h"
#include "Monstruo.h"
#include <iostream>
#include <cstdlib>

using namespace std; 

Monstruo::Monstruo(int level) {
    
    nivel = level;
    this->SetMaxVida(400*(level+1));
    this->SetVidaActual(400*(level+1));
    this->SetDanhoBase(30*(level+1));
}

Monstruo::~Monstruo() {

}


void Monstruo::AsignarMons(int level, int max, int vida, char *name,int imagen){
    nivel = level;
    this->SetNombre(name);
    this->SetMaxVida(max);
    this->SetVidaActual(vida);
    this->SetImagen(imagen);
}

void  Monstruo :: imp(){
  cout << this->GetNombre() ; 
  cout << this->GetPosX() ; 
  //cout << this->G

}

int Monstruo::GetNivel() const {
    return nivel;
}

void Monstruo::SetImagen(int imagen) {
    this->imagen = imagen;
}

int Monstruo::GetImagen() const {
    return imagen;
}