/* 
 * File:   Arma.h
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 11:15 AM
 */
#include "Artefacto.h"
#ifndef ARMA_H
#define	ARMA_H
class Arma : public Artefacto {    
private:
    int danhoMin;
    int danhoMax;
    char* nombre;
public:
    Arma(int min=0,int max=0);
    void AsignarArma(int, int, char*);
    void Imprimir();
    void SetDanhoMax(int danhoMax);
    int GetDanhoMax() const;
    void SetDanhoMin(int danhoMin);
    int GetDanhoMin() const;
    void usar();
    void usar2(class Entidad &E,int ind);
};

#endif	/* ARMA_H */

