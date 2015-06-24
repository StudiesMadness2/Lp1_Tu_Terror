/* 
 * File:   Laberinto.h
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 11:19 AM
 */

#ifndef LABERINTO_H
#define	LABERINTO_H

#include "Celda.h"
#include "Monstruo.h"
#define CAP 40 

class Laberinto {
private:
    int M;
    int N;
    double pctMonstruo;
    int *nivelesMonstruo;
    double pctArtefacto;
    int *nivelesArtefacto;
    int x_Ant;
    int y_Ant;
    int x_Sig;
    int y_sig;
    Celda **celda;
    Monstruo monstruosXlab[CAP];
    int cantMonstruos;
public:
    // Constuctores y destructores 
    Laberinto();
    Laberinto(int m, int n);
    virtual ~Laberinto();
    // Get y Set 
    void setCelda(Celda** celda);
    Celda** getCelda() const;
    void setNivelesArtefacto(int* nivelesArtefacto);
    int* getNivelesArtefacto() const;
    void setPctArtefacto(double pctArtefacto);
    double getPctArtefacto() const;
    void setNivelesMonstruo(int tam, int ini, int fin);
    int* getNivelesMonstruo() const;
    void setPctMonstruo(double pctMonstruo);
    double getPctMonstruo() const;   
    int getN() const;
    int getM() const;
    // Metodos 
    //  Laberinto creaion(char *);
    void impresion();
    void setY_sig(int y_sig);
    int getY_sig() const;
    void setX_Sig(int x_Sig);
    int getX_Sig() const;
    void setY_Ant(int y_Ant);
    int getY_Ant() const;
    void setX_Ant(int x_Ant);
    int getX_Ant() const;
    char getCasilla(int x , int y) ; 
    void distribuirMonstruosRandom(Monstruo *Mons, int numM,Arma* armas, int numArmas, Armadura *armaduras, int numArmad, PocionCuracion *pociones, int numPociones);
    void distribuirArtefactosMonstruos( Arma* armas, int numArmas, Armadura *armaduras, int numArmad, PocionCuracion *pociones, int numPociones);
    Monstruo busquedaMonstruo( int, int   );
    int getCantMonstruos() const;
};

#endif	/* LABERINTO_H */

