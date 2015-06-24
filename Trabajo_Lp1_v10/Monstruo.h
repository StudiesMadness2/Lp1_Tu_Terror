/* 
 * File:   Monstruo.h
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 11:18 AM
 */
#include "Entidad.h"

#ifndef MONSTRUO_H
#define	MONSTRUO_H

class Monstruo : public Entidad {
private:
    int nivel;
    int imagen;
public:
    Monstruo(int level = 0);
    virtual ~Monstruo();
    void AsignarMons(int level, int max, int vida, char*name, int);
   // void AsignarImagen(int);
    void imp();
    
    Entidad GetDatos() const;
    int GetNivel() const;
    void SetImagen(int imagen);
    int GetImagen() const;
};

#endif	/* MONSTRUO_H */

