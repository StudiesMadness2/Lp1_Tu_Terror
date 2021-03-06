/* 
 * File:   Armadura.h
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 11:15 AM
 */
#include "Artefacto.h"
#ifndef ARMADURA_H
#define	ARMADURA_H

class Armadura : public Artefacto {
private:
    int defensa;
    char * nombre;
public:
    Armadura(int def = 0);    
    void AsignarArmadura(int, char*);
    void Imprimir();    
    void SetDefensa(int defensa);
    int GetDefensa() const;
    void SetNombre(char* nombre);
    char* GetNombre() const;        
    void usar(class Entidad &E, int ind);

};

#endif	/* ARMADURA_H */

