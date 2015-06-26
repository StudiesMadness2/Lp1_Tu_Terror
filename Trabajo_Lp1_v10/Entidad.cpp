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
    armadura = NULL;
    arma = NULL;
}

Entidad::~Entidad() {

}

void Entidad::agregarArtefactoAlSaco(Artefacto* art, int flag) {
    (this->saco).AgregarAlSaco(art, flag);
}

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

void Entidad::SetDanhoBase(int danhoBase) {
    this->danhoBase = danhoBase;
}

int Entidad::GetDanhoBase() const {
    int danhoExtra = 0;
    if (this->GetArma()) danhoExtra = this->GetArma()->GetDanhoMin();
    return (danhoBase + danhoExtra);
}

int Entidad::poseeElSacoLLeno() {
    return this->saco.estaLleno();
}
int Entidad::usarArteFactor(int ind) {
    if (this->saco[ind]) {
        this->saco[ind]->usar(*this, ind);
        return 1;
    }
    return 0;
}

int Entidad::cantArtefactos() {
    return this->saco.GetIndice();
}

void Entidad::SetArma(Arma* arma) {
    this->arma = arma;
}

Arma* Entidad::GetArma() const {
    return arma;
}

void Entidad::SetArmadura(Armadura* armadura) {
    this->armadura = armadura;
}

Armadura* Entidad::GetArmadura() const {
    return armadura;
}

int Entidad::botarArtefacto(int ind) {
    if (this->saco[ind] == NULL) return 0;
    else
        return this->saco.botarArteFacto(ind);
}