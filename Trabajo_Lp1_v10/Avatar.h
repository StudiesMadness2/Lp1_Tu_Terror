/* 
 * File:   Avatar.h
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 11:17 AM
 */
#include "Entidad.h"
#ifndef AVATAR_H
#define	AVATAR_H

class Avatar : public Entidad{
private:
    int vidas;
    int flagLabs;
public:
    Avatar();
    //Avatar(const Avatar& orig);
    virtual ~Avatar();

    void mostrarDatosMapa();
    int getVidas() const;
    void setVidas(int vidas);
    void setflagLabs(int flagLabs);
    int getflagLabs() const;
};

#endif	/* AVATAR_H */

