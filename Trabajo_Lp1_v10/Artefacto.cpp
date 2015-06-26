/* 
 * File:   Artefacto.cpp
 * Author: alulab14
 * 
 * Created on 5 de junio de 2015, 11:14 AM
 */
#include "Arma.h"
#include "Armadura.h"
#include "PocionCuracion.h"
#include "Artefacto.h"

void Artefacto::SetTipo(int tipo) {
    this->tipo = tipo;
}

int Artefacto::GetTipo() const {
    return tipo;
}
