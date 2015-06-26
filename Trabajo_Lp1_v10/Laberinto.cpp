/* 
 * File:   Laberinto.cpp
 * Author: alulab14
 * 
 * Created on 5 de junio de 2015, 11:19 AM
 */
#include "Laberinto.h"
#include "GestorLaberinto.h"
#include "FuncionesExtras.h"
#include "rlutil.h"
#include <iostream>
using namespace std;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include "Constantes.h"

Laberinto::Laberinto() {
    M = 30;
    N = 30;
    pctArtefacto = 0;
    pctArtefacto = 0;
    nivelesArtefacto = NULL;
    nivelesMonstruo = NULL;
    celda = NULL;
    cantMonstruos = 0;
    //    celda = new Celda*[M];
    //    for (int i = 0; i < M; i++) {
    //        celda[i] = new Celda[N];
    //    }
}

Laberinto::Laberinto(int m, int n) {
    M = m;
    N = n;
    srand(unsigned(time(NULL)));
    pctArtefacto = (rand() % 1000) / 1000.0;
    pctMonstruo = (rand() % 1000) / 1000.0;
    nivelesArtefacto = new int[10]; 
    nivelesMonstruo = new int[10]; 
    celda = new Celda*[M];
    for (int i = 0; i < M; i++) {
        celda[i] = new Celda[N];
    }
    cantMonstruos = 0;
}


char Laberinto::getCasilla(int x, int y) {
    return this->celda[x][y].GetTipo();
}

void Laberinto::distribuirArtefactosMonstruos(Arma* armas, int numArmas, Armadura *armaduras, int numArmad, PocionCuracion *pociones, int numPociones) {

    int random;
    srand(unsigned(time(NULL)));
    random = rand() % 3; // 0 ,1 , 2 // tipos de artefacto
    switch (random) {
        case 0:
            random = rand() % numArmas;
            monstruosXlab[cantMonstruos].agregarArtefactoAlSaco(&armas[random], 0);
            break;
        case 1:
            random = rand() % numArmad;
            monstruosXlab[cantMonstruos].agregarArtefactoAlSaco(& armaduras[random], 0);
            break;
        case 2:
            random = rand() % numPociones;
            monstruosXlab[cantMonstruos].agregarArtefactoAlSaco(&pociones[random], 0);
            break;
    }
}

void Laberinto::distribuirMonstruosRandom(Monstruo *Mons, int numM, Arma* armas, int numArmas, Armadura *armaduras, int numArmaDuras, PocionCuracion *pociones, int numPociones) {
    char casilla;
    int indMonst, indImagen;
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            casilla =  getCasilla(i, j);         
            
            if (casilla == MONSTRUO) {                
                //cout << casilla ; 
                srand(time(NULL));
              
                indMonst = (rand()+i+j) % numM;
                
                monstruosXlab[cantMonstruos].AsignarMons(Mons[indMonst].GetNivel(), Mons[indMonst].GetMaxVida(),
                        Mons[indMonst].GetVidaActual(), Mons[indMonst].GetNombre(), Mons[indMonst].GetImagen());
                monstruosXlab[cantMonstruos].SetPosX(i);
                monstruosXlab[cantMonstruos].SetPosY(j);
                distribuirArtefactosMonstruos(armas, numArmas, armaduras, numArmaDuras, pociones, numPociones);         
                cantMonstruos++;
            }
        }
    }
}

Monstruo Laberinto::busquedaMonstruo(int x, int y) {
    for (int i = 0; i < cantMonstruos; i++) {
        if (monstruosXlab[i].GetPosX() == x && monstruosXlab[i].GetPosY() == y) {
            return monstruosXlab[i];
        }
    }
    cout << "El mosntruos no esta NO DEBERIA PASAR POR AQUI" << endl;
    return Monstruo(0);
}

int Laberinto::getCantMonstruos() const {
    return cantMonstruos;
}

void Laberinto::impresion() {
    char cel ; 
    for (int i = 0 ; i < 11 ; i++) putchar('\n');
    for (int i = 0; i < M; i++) {
        rlutil::setColor(7);
        for (int k = 0; k <40; k++)printf(" ");
        for (int j = 0; j < N; j++) {
            cel = this->getCasilla(i, j);
            if (cel == '-' || cel == '+') {
                rlutil::setColor(121); // Entra  y Sale
                printf("%c", cel);
            } else if (cel == 'M'  ) {
                rlutil::setColor(124);
                printf("%c", cel);
            }else if (cel == 'A'){
                rlutil::setColor(118);
                printf("%c", cel);                
            } else {
                rlutil::setColor(112); // 96 176 112
                if (cel == ADENTRO) printf("%c", celda);
                else printf("%c", PAREDVISUAL);
            }
        }
        cout << endl;
    }
    rlutil::setColor(7);    
}

void Laberinto::setY_sig(int y_sig) {
    this->y_sig = y_sig;
}

int Laberinto::getY_sig() const {
    return y_sig;
}

void Laberinto::setX_Sig(int x_Sig) {
    this->x_Sig = x_Sig;
}

int Laberinto::getX_Sig() const {
    return x_Sig;
}

void Laberinto::setY_Ant(int y_Ant) {
    this->y_Ant = y_Ant;
}

int Laberinto::getY_Ant() const {
    return y_Ant;
}

void Laberinto::setX_Ant(int x_Ant) {
    this->x_Ant = x_Ant;
}

int Laberinto::getX_Ant() const {
    return x_Ant;
}

void Laberinto::setCelda(Celda** celda) {
    this->celda = celda;
}

Celda** Laberinto::getCelda() const {
    return celda;
}

void Laberinto::setNivelesArtefacto(int* nivelesArtefacto) {
    this->nivelesArtefacto = nivelesArtefacto;
}

int* Laberinto::getNivelesArtefacto() const {
    return nivelesArtefacto;
}

void Laberinto::setPctArtefacto(double pctArtefacto) {
    this->pctArtefacto = pctArtefacto;
}

double Laberinto::getPctArtefacto() const {
    return pctArtefacto;
}

void Laberinto::setNivelesMonstruo(int tam, int ini, int fin) {
    this->nivelesMonstruo = new int[tam + 2];
    int j = 1;
    this->nivelesMonstruo[0] = tam;
    for (int i = ini; i <= fin; i++) {
        this->nivelesMonstruo[j] = i;
        j++;
    }
}

int* Laberinto::getNivelesMonstruo() const {
    return nivelesMonstruo;
}

void Laberinto::setPctMonstruo(double pctMonstruo) {
    this->pctMonstruo = pctMonstruo;
}

double Laberinto::getPctMonstruo() const {
    return pctMonstruo;
}

int Laberinto::getN() const {
    return N;
}

int Laberinto::getM() const {
    return M;
}