#include <cstdio>
#include <cstring>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Monstruo.h"
#include "Arma.h"
#include "Armadura.h"
#include "PocionCuracion.h"
#include "Constantes.h"
#include <time.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using namespace std;

void mostrarOpcionesGenerales() {    
    cout << endl;
    CREAR GENERALES ESPACIOS; cout << char(201);
    for(int i=0;i<46;i++) cout << char(205);
    cout << char(187) << endl ;
    CREAR GENERALES ESPACIOS;cout << char(186) << "  OPCIONES:                                   " << char(186) << endl;
    CREAR GENERALES ESPACIOS;cout << char(186) << "        Mover        -----> Direcciones       " << char(186) << endl;
    CREAR GENERALES ESPACIOS;cout << char(186) << "        Interactuar  ----->  (a)              " << char(186) << endl;
    CREAR GENERALES ESPACIOS;cout << char(186) << "        Usar         ----->  (s)(numero)      " << char(186) << endl;
    CREAR GENERALES ESPACIOS;cout << char(186) << "        Botar        ----->  (b)(numero)      " << char(186) << endl;
    CREAR GENERALES ESPACIOS;cout << char(186) << "        Salir        ----->  (p)              " << char(186) << endl;
    CREAR GENERALES ESPACIOS;cout << char(200);
    for(int i=0;i<46;i++) cout << char(205);
    cout << char(188) << endl ;
    CREAR GENERALES ESPACIOS;cout << "  Escriba una accion                     :";
}

void LecturaMoviento(char &c1){
    int c;
    while (1) {
        c = 0;
        c = getch();
        if( 'A' <= c && c <= 'Z' || 'a' <= c && c <= 'z') {
            c1 = (char) c ; 
            return ; 
        }
        switch ((c = getch())) {
            case KEY_UP:
                //cout << endl << "Up" << endl;//key up
                c1 = 'i' ; 
                return;
            case KEY_DOWN:
                c1 = 'k';
                return;
            case KEY_LEFT:
                c1 = 'j';
                return;
            case KEY_RIGHT:
                c1 = 'l';
                return;
            default:
                for(int i=0;i<46;i++) cout << " ";cout << endl << "null" << endl; // key left
                return ;
        }
    }
}

int CargarMonstruos(Monstruo *&Mons, int &numM){
    ifstream archM("Monstruos.txt");
    char cadena[100], nombre[100];
    int nivel, max, maxLevel=0,imagen;
    archM.getline(cadena, 100);
    numM = atoi(cadena);
    Mons = new Monstruo[numM];
    for(int i=0;i<numM;i++){
        archM.getline(cadena, 100);
        strcpy(nombre, cadena);
        archM.getline(cadena, 100);
        nivel = atoi(cadena);
        archM.getline(cadena, 100);
        max = atoi(cadena);
        archM.getline(cadena, 100);
        imagen = atoi(cadena);
        if(maxLevel<nivel) maxLevel=nivel;
        //archM.getline(cadena, 100);
        //archM.getline(cadena, 100);
        Mons[i].AsignarMons(nivel,max,max,nombre,imagen);
    }
    archM.close();
    return maxLevel;
}

void CargarArmas(Arma *&ArmA, Arma *&ArmC, int &numAA, int &numAC){
    ifstream archAr("Armas.txt");
    char cadena[100], nombre[100];
    int min, max;
    archAr.getline(cadena, 100);
    numAA = atoi(cadena);
    ArmA = new Arma[numAA];
    for(int i=0;i<numAA;i++){
        archAr.getline(cadena, 100);
        strcpy(nombre, cadena);
        archAr.getline(cadena, 100);
        min = atoi(cadena);
        archAr.getline(cadena, 100);
        max = atoi(cadena);
        ArmA[i].AsignarArma(min,max,nombre);
    }
    archAr.getline(cadena, 100);
    numAC = atoi(cadena);
    ArmC = new Arma[numAC];
    for(int i=0;i<numAC;i++){
        archAr.getline(cadena, 100);
        strcpy(nombre, cadena);
        archAr.getline(cadena, 100);
        min = atoi(cadena);
        archAr.getline(cadena, 100);
        max = atoi(cadena);
        ArmC[i].AsignarArma(min,max,nombre);
    }
    archAr.close();
}

void CargarArmaduras(Armadura *&Armd, int &numAd){
    ifstream archAd("Armaduras.txt");
    char cadena[100], nombre[100];
    int defensa;
    archAd.getline(cadena, 100);
    numAd = atoi(cadena);
    Armd = new Armadura[numAd];
    for(int i=0;i<numAd;i++){
        archAd.getline(cadena, 100);
        strcpy(nombre, cadena);
        archAd.getline(cadena, 100);
        defensa = atoi(cadena);
        Armd[i].AsignarArmadura(defensa,nombre);
    }
    archAd.close();
}

void CargarPociones(PocionCuracion *&Poc, int &numP){
    ifstream archP("Pociones.txt");
    char cadena[100], nombre[100];
    int ptos;
    archP.getline(cadena, 100);
    numP = atoi(cadena);
    Poc = new PocionCuracion[numP];
    for(int i=0;i<numP;i++){
        archP.getline(cadena, 100);
        strcpy(nombre, cadena);
        archP.getline(cadena, 100);
        ptos = atoi(cadena);
        Poc[i].AsignarPocion(ptos, nombre);
    }
    archP.close();
}
