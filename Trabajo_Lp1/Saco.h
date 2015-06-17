/* 
 * File:   Saco.h
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 11:14 AM
 */
#include "Artefacto.h"
#include "Arma.h"
#include "Armadura.h"
#include "PocionCuracion.h"
#ifndef SACO_H
#define	SACO_H

class Saco {
private:
    Artefacto *artefacto; //genera un máximo de 10 artefactos en la bolsa
    int indice;
public:
    Saco();
    virtual ~Saco();
    void AgregarAlSaco(Arma);
    void AgregarAlSaco(Armadura);
    void AgregarAlSaco(PocionCuracion);
    int GetIndice();
    void Imprimir();
};

#endif	/* SACO_H */

