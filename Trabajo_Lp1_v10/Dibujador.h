/* 
 * File:   Dibujador.h
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 11:24 AM
 */

#ifndef DIBUJADOR_H
#define	DIBUJADOR_H
#include "Laberinto.h"
#include "Avatar.h"

class Dibujador {
private:
    int A;
    int B;
public:
    Dibujador();
    virtual ~Dibujador();
    void SetB(int B);
    int GetB() const;
    void SetA(int A);
    int GetA() const;
    void dibujarEsquemaVersion2(Laberinto &lab, Avatar Av);
};

#endif	/* DIBUJADOR_H */

