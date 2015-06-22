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
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using namespace std;



void historiaDelJuego() {
for(int i=0;i<36;i++) cout << " ";printf("                                                         .--.\n"); 
for(int i=0;i<36;i++) cout << " ";printf("                                                        /  .  \\\n"); 
for(int i=0;i<36;i++) cout << " ";printf("                                                       |\\_/|   |\n"); 
for(int i=0;i<36;i++) cout << " ";printf("                                                       |   |  /|\n"); 
for(int i=0;i<36;i++) cout << " ";printf("      .------------------------------------------------------' |\n");
for(int i=0;i<36;i++) cout << " ";printf("     /  .-.       En un mundo muy muy lejano habia una vez...  |\n");
for(int i=0;i<36;i++) cout << " ";printf("    |  /   \\   No! Alumno PUCP, esta historia no empieza asi,  |\n");
for(int i=0;i<36;i++) cout << " ";printf("    | |\\_.  |       Esta es la realidad, TU REALIDAD           |\n");
for(int i=0;i<36;i++) cout << " ";printf("    |\\|  | /|    Pero no te preocupes! Te vamos a ayudar :)    |\n");
for(int i=0;i<36;i++) cout << " ";printf("    | `---' |  Para que te prepares muy bien para sobrevivir   |\n");
for(int i=0;i<36;i++) cout << " ";printf("    |       |              en esta Jungla PUCP!                |\n");
for(int i=0;i<36;i++) cout << " ";printf("    |       |                                                  |\n");
for(int i=0;i<36;i++) cout << " ";printf("    |       |          ESTO ES ... STUDIES MADNESS 8D          |\n");
for(int i=0;i<36;i++) cout << " ";printf("    |       |        QUIERES EMPEZAR? (PRESIONA ENTER :D)      /\n");
for(int i=0;i<36;i++) cout << " ";printf("     \\      |------------------------------------------------'       \n");
for(int i=0;i<36;i++) cout << " ";printf("      \\    /       \n");
for(int i=0;i<36;i++) cout << " ";printf("       `--'                            ");
while (cin.get() != '\n');
}

//int opciones_contiene_palabra_mover(char opcion[], const char*pal) {
//    for (int i = 0; opcion[i]; i++) {
//        if (opcion[i] == ' ') opcion[i] = 0;
//    }
//    return strcmp(opcion, pal);
//}

void mostrarOpcionesGenerales() {    
    cout << endl;
    for(int i=0;i<46;i++) cout << " "; cout << char(201);
    for(int i=0;i<46;i++) cout << char(205);
    cout << char(187) << endl ;
    for(int i=0;i<46;i++) cout << " ";cout << char(186) << "  OPCIONES:                                   " << char(186) << endl;
    //for(int i=0;i<46;i++) cout << " ";cout << char(186) << "        Mover        -----> Direcciones         " << endl;
    for(int i=0;i<46;i++) cout << " ";cout << char(186) << "        Interactuar  ----->  (a)              " << char(186) << endl;
    for(int i=0;i<46;i++) cout << " ";cout << char(186) << "        Usar         ----->  (s)(numero)      " << char(186) << endl;
    for(int i=0;i<46;i++) cout << " ";cout << char(186) << "        Botar        ----->  (b)(numero)      " << char(186) << endl;
    for(int i=0;i<46;i++) cout << " ";cout << char(186) << "        Salir        ----->  (p)              " << char(186) << endl;
    for(int i=0;i<46;i++) cout << " ";cout << char(200);
    for(int i=0;i<46;i++) cout << char(205);
    cout << char(188) << endl ;
    for(int i=0;i<46;i++) cout << " ";cout << "  Escriba una accion                     :";
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
    int nivel, max, maxLevel=0;
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
        if(maxLevel<nivel) maxLevel=nivel;
        //archM.getline(cadena, 100);
        //archM.getline(cadena, 100);
        Mons[i].AsignarMons(nivel,max,max,nombre);
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