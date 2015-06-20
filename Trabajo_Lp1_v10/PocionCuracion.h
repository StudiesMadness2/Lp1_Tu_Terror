/* 
 * File:   PocionCuracion.h
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 11:17 AM
 */
#include "Artefacto.h"
#ifndef POCIONCURACION_H
#define	POCIONCURACION_H

class PocionCuracion : public Artefacto {
private:
    int puntosVida;
    char *nombre;
public:
    PocionCuracion(int ptos=0);
    PocionCuracion(const PocionCuracion& orig);
    virtual ~PocionCuracion();
    void AsignarPocion(int, char*);
    void Imprimir();
    void usar();
    void usar2(class Entidad &E);
};

#endif	/* POCIONCURACION_H */

