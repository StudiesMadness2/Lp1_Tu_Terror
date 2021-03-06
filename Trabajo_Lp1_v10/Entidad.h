/* 
 * File:   Entidad.h
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 11:11 AM
 */
#include "Saco.h"
#include "Arma.h"
#include "Armadura.h"
#include "Artefacto.h"
#include "PocionCuracion.h"
#ifndef ENTIDAD_H
#define	ENTIDAD_H

class Entidad {
private:
    int posY;
    int posX;
    int maxVida;
    int VidaActual;
    int danhoBase;
    char* nombre;
    Saco saco;
    int items;
    Armadura *armadura;
    Arma *arma;

public:
    Entidad(int max = 0, int vida = 0);
    virtual ~Entidad();
    void agregarArtefactoAlSaco(Artefacto*, int);  
    Saco GetSaco() const;    
    void SetNombre(char* nombre);
    char* GetNombre() const;
    void SetVidaActual(int VidaActual);
    int GetVidaActual() const;
    void SetMaxVida(int maxVida);
    int GetMaxVida() const;
    void SetPosX(int posX);
    int GetPosX() const;
    void SetPosY(int posY);
    int GetPosY() const;
    void SetDanhoBase(int danhoBase);
    int GetDanhoBase() const;
    int poseeElSacoLLeno();
    int usarArteFactor(int);
    int botarArtefacto(int);
    int cantArtefactos();
    void SetArma(Arma* arma);
    Arma* GetArma() const;
    void SetArmadura(Armadura* armadura);
    Armadura* GetArmadura() const;
    friend class Artefacto;
};

#endif	/* ENTIDAD_H */

