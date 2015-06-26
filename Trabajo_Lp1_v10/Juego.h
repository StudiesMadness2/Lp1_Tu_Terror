/* 
 * File:   Juego.h
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 11:18 AM
 */

#include "Avatar.h"
#include "Monstruo.h"
#include "Dibujador.h"
#include "Laberinto.h"
#include "GestorLaberinto.h"
#include "Arma.h"
#include "Armadura.h"
#include "PocionCuracion.h"
#ifndef JUEGO_H
#define	JUEGO_H

class Juego {
private:
    Avatar avatar;
    Monstruo *monstruo;
    Dibujador dibujador;
    GestorLaberinto gestorLaberinto;
    Laberinto LaberintoActual;
    int posLaberintoActual;
    int cantidadDeLaberintos;
    Laberinto *arreLaberintos;
    Artefacto *artefactos[MAX_ARTEF_EN_SACO];
public:
    Juego();

    virtual ~Juego();

    void CargarLaberintos(int);
    void iniciarPosicionAvatar();

    void intentarmosMoverAvatar(char&, int&);
    void intentamosInteractuarAvatar(int, int, int, Arma *, Armadura *, PocionCuracion *, int& , int &);
    int PreguntarPelearConMonstruo(int, int , int, int &);
    void impresionDeMonstruos(int,int, int);
    friend void imprimirAtaqueMonstruo();
    friend void imprimirContraAtaqueMonstruo();
    void botarArtefactoGrafico() ;

    void MostrarDatosPrevioBatalla(Monstruo &);
    void PelearConMonstruo(Monstruo & , int &, int,int,int, int &);
    void ImprimirSaco();
    friend void ImprimirOpcionesDeBatalla();

    void SetDibujador(Dibujador dibujador);
    Dibujador GetDibujador() const;
    void dibujarEsquema();
    Laberinto GetLaberintoActual() const;
    void SetAvatar(Avatar avatar);
    Avatar GetAvatar() const;
    void SetPosLaberintoActual(int posLaberintoActual);
    int GetPosLaberintoActual() const;
    void dibujadorDeEsquema();


    void cargarArtefactos();

    int usarArtefacto(int);
    int botarArtefacto(int);

    void distribuirMonstruosXLaberinto(Monstruo *Mons, int numM, Arma *armas, int numA, Armadura *armaduras, int numArmad, PocionCuracion *pociones , int numPociones);
    
    void historiaDelJuego();
    void tiempo(int) ; 
    Laberinto FinalDelJuego();
};

#endif	/* JUEGO_H */

