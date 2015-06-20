/* 
 * File:   Entidad.cpp
 * Author: alulab14
 * 
 * Created on 5 de junio de 2015, 11:11 AM
 */
#include "Artefacto.h"
#include "Entidad.h"
#include <cstdio>
#include <cstring>

Entidad::Entidad(int max, int vida) {
    maxVida = max;
    VidaActual = vida;
    nombre = NULL;
}

Entidad::~Entidad() {

}

void Entidad::agregarArtefactoAlSaco(Artefacto* art) {
    (this->saco).AgregarAlSaco(art);
}
//void Entidad::SetSaco(Arma artefact) {
//    Saco sac;
//    sac.AgregarAlSaco(artefact);
//    this->saco = sac;
//}
//void Entidad::SetSaco(Armadura artefact) {
//    Saco sac;
//    sac.AgregarAlSaco(artefact);
//    this->saco = sac;
//}
//void Entidad::SetSaco(PocionCuracion artefact) {
//    Saco sac;
//    sac.AgregarAlSaco(artefact);
//    this->saco = sac;
//}
//int Entidad::GetSacoIndice(){
//    return this->saco.GetIndice();
//}
//

Saco Entidad::GetSaco() const {
    return saco;
}

void Entidad::SetNombre(char* name) {
    this->nombre = new char[strlen(name) + 1];
    strcpy(this->nombre, name);
}

char* Entidad::GetNombre() const {
    char *aux;
    aux = new char[strlen(nombre) + 1 ];
    strcpy(aux, nombre);
    return aux;
}

void Entidad::SetVidaActual(int VidaActual) {
    this->VidaActual = VidaActual;
}

int Entidad::GetVidaActual() const {
    return VidaActual;
}

void Entidad::SetMaxVida(int maxVida) {
    this->maxVida = maxVida;
}

int Entidad::GetMaxVida() const {
    return maxVida;
}

void Entidad::SetPosX(int posX) {
    this->posX = posX;
}

int Entidad::GetPosX() const {
    return posX;
}

void Entidad::SetPosY(int posY) {
    this->posY = posY;
}

int Entidad::GetPosY() const {
    return posY;
}

void Entidad::SetArma(Arma arma) {
    this->arma = arma;
}

Arma Entidad::GetArma() const {
    return arma;
}

void Entidad::SetArmadura(Armadura armadura) {
    this->armadura = armadura;
}

Armadura Entidad::GetArmadura() const {
    return armadura;
}

void Entidad::SetDanhoBase(int danhoBase) {
    this->danhoBase = danhoBase;
}

int Entidad::GetDanhoBase() const {
    return danhoBase;
}

int Entidad::poseeElSacoLLeno() {
    return this->saco.estaLleno();
}

int Entidad::usarArteFactor(int ind) {
    if (this->saco[ind]) {
        this->saco[ind]->usar2((*this));
        return 1;
    }
    return 0;
}

int Entidad::cantArtefactos() {
    return this->saco.GetIndice();
}

int Entidad::botarArtefacto(int ind) {
    if (this->saco[ind] == NULL) return 0;
    else
        return this->saco.votarArteFacto(ind);
    
}