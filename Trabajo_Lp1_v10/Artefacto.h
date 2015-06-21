/* 
 * File:   Artefacto.h
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 11:14 AM
 */

#ifndef ARTEFACTO_H
#define	ARTEFACTO_H

//Hereda a Arma , Armadura y PocionCuracion

class Artefacto {
private:
    int tipo; // 0 , 1 , 2   :::: Arma , Armadura , Pocion
public:
    virtual void Imprimir() = 0;
    void SetTipo(int tipo);
    int GetTipo() const;
    virtual void usar( ) = 0;
    virtual void usar2(class Entidad &E,int ind)=0;
};

#endif	/* ARTEFACTO_H */

