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
#include "Constantes.h"

#ifndef SACO_H
#define	SACO_H

class Saco {
private:
    Artefacto *artefacto[MAX_ARTEF_EN_SACO]; //genera un máximo de 10 artefactos en la bolsa
    int indice;
public:
    Saco();
    virtual ~Saco();
    void AgregarAlSaco(Artefacto *);
    int estaLleno();
    //    void AgregarAlSaco(Arma);
    //    void AgregarAlSaco(Armadura);
    //    void AgregarAlSaco(PocionCuracion);
    Artefacto *operator[](int ind);
    int GetIndice();

};

#endif	/* SACO_H */

