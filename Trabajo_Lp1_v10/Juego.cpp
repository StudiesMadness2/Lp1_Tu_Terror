/* 
 * File:   Juego.cpp
 * Author: Brayan
 * 
 * Created on 5 de junio de 2015, 11:18 AM
 */
#include <unistd.h>
#include "Constantes.h"
#include "rlutil.h"
#include <fstream>
#include <dirent.h>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <time.h>
#include <iostream>
#include "Arma.h"
#include "Juego.h"
#include "Armadura.h"
#include "PocionCuracion.h"
#include <WINDOWS.h> 
#include <MMSystem.h>
#include <fstream>
#include <iomanip>
#define GESTION 40
#define SEGURIDAD 40
#define ED 40
#define BASES 40
#define FUNDA 40
#define ALGORITMIA 40
#define OAC 40 
#define SOFTWARE 40
#define LP1 40
#define APLICA 40
using namespace std;

Juego::Juego() {
    monstruo = new Monstruo[10]; // 10 es un ejemplo puede ser cualquie valor 
    arreLaberintos = new Laberinto[10]; // Suponiendo como maximos 10
    posLaberintoActual = 0; // Por empieza en el principio         
}

Juego::~Juego() {
    delete[] arreLaberintos;
}

void desordenar(int arre[], int N_elementos) {
    srand(time(NULL));
    int ordenado[100], usado[100] = {0};
    for (int i = 0; i < N_elementos; i++) {
        ordenado[i] = i;
    }
    int index = 0;
    for (int i = 0; i < N_elementos; i++) {
        do {
            index = (rand() % N_elementos);
        } while (usado[index]);
        arre[i] = ordenado[index];
        usado[index] = true;
    }
}

void leerLaberintos(char arreNombArch2[][50], int &cant) {
    char aux[50];
    cant = 0;
    ifstream archivoLab("Registro_Laberintos.txt");
    while (1) {
        archivoLab.getline(arreNombArch2[cant], 50);
        //printf("%s\n", arreNombArch2[cant]);
        if (strlen(arreNombArch2[cant]) == 0) break;
        cant++;
    }
    archivoLab.close();
}

void Juego::CargarLaberintos(int MaxLevel) {
    int cant_Labs = 0, indices[100] = {0};
    char arreNombArch[50][50] = {0};
    leerLaberintos(arreNombArch, cant_Labs);
    desordenar(indices, cant_Labs);
    arreLaberintos = new Laberinto[cant_Labs];
    int tam = int (MaxLevel / cant_Labs);
    if(tam==0) tam=1;
    for (int i = 0; i < cant_Labs; i++) {
        arreLaberintos[i] = gestorLaberinto.crear(arreNombArch[indices[i]]);
        if (i == cant_Labs - 1) arreLaberintos[i].setNivelesMonstruo(tam, i * tam, MaxLevel);
        else arreLaberintos[i].setNivelesMonstruo(tam, i*tam, (i * tam) + tam);
    }
    posLaberintoActual = 0;
    LaberintoActual = arreLaberintos[0];
    cantidadDeLaberintos = cant_Labs;
    return;
}

void Juego::iniciarPosicionAvatar() {
    this->avatar.SetPosX(this->LaberintoActual.getX_Ant());
    int a = this->LaberintoActual.getX_Ant();
    //  printf("%d ",a) ; 
    this->avatar.SetPosY(this->LaberintoActual.getY_Ant());
    int b = this->LaberintoActual.getY_Ant();
    //  printf("%d ",b) ; 
}

void Juego::distribuirMonstruosXLaberinto(Monstruo *Mons, int numM, Arma* armas, int numArmas, Armadura *armaduras, int numArmad, PocionCuracion *pociones, int numPociones) {
    for (int i = 0; i < cantidadDeLaberintos; i++) {
        arreLaberintos[i].distribuirMonstruosRandom(Mons, numM, armas, numArmas, armaduras, numArmad, pociones, numPociones);
        //cout << endl <<cantidadDeLaberintos <<endl ; 
        //cout << arreLaberintos[i].getCantMonstruos() << endl ; 
    }
}

void Juego::intentarmosMoverAvatar(char& movimiento, int &flag) {
    int nx, ny;
    nx = avatar.GetPosX();
    ny = avatar.GetPosY();
    switch (movimiento) {
        case DIR_ARRIBA: ny = ny - 1;
            break;
        case DIR_ABAJO: ny = ny + 1;
            break;
        case DIR_IZQUIERDA: nx = nx - 1;
            break;
        case DIR_DERECHA: nx = nx + 1;
            break;
    }
    //    char s = (char) LaberintoActual.getCelda()[nx][ny].GetTipo() ;
    if (LaberintoActual.getCelda()[ny][nx].GetTipo() == PARED) {
        flag = 0;
    } else if (LaberintoActual.getCelda()[ny][nx].GetTipo() == ADENTRO) {
        flag = 1;
        avatar.SetPosX(nx);
        avatar.SetPosY(ny);
    } else if (LaberintoActual.getCelda()[ny][nx].GetTipo() == ARTEFACTO) {
        flag = 0;
    } else if (LaberintoActual.getCelda()[ny][nx].GetTipo() == MONSTRUO) {
        flag = 0;
    } else if (LaberintoActual.getCelda()[ny][nx].GetTipo() == ANTERIOR) {
        flag = 1; // Solo se mueve 
        if (posLaberintoActual == 0) {
            avatar.SetPosX(nx); // Se mueve pero no se cambia de laberinto
            avatar.SetPosY(ny);
        } else {
            avatar.setflagLabs(avatar.getflagLabs()+1);
            posLaberintoActual -= 1; // Se mueve y se cambia de laberinto
            LaberintoActual = arreLaberintos[posLaberintoActual];
            avatar.SetPosX(LaberintoActual.getX_Sig());
            avatar.SetPosY(LaberintoActual.getY_sig());

        }
    } else if (LaberintoActual.getCelda()[ny][nx].GetTipo() == SIGUIENTE) {
        if(avatar.getflagLabs()==0) avatar.SetDanhoBase(avatar.GetDanhoBase()+10);
        avatar.setflagLabs(avatar.getflagLabs()-1);
        flag = 1;
        if (posLaberintoActual == cantidadDeLaberintos - 1) {
            movimiento = FIN;
            avatar.SetPosX(nx);
            avatar.SetPosY(ny);
        } else {
            posLaberintoActual += 1;
            LaberintoActual = arreLaberintos[posLaberintoActual];
            avatar.SetPosX(LaberintoActual.getX_Ant());
            avatar.SetPosY(LaberintoActual.getY_Ant());
        }
    }
}

void Juego::intentamosInteractuarAvatar(int numAA, int numAd, int numP, Arma *ArmA, Armadura *Armd, PocionCuracion *Poc, int& flag) {
    char tipo;

    int y = avatar.GetPosY();
    int x = avatar.GetPosX();
    srand(time(NULL));
    flag = 0;
    int g , h ; 
    for (int f = -1; f < 2; f++) {
        for (int k = -1; k < 2; k++) { //recorrido alrededor del Avatar

            if (!(f == k) && !(k == (-f))) { // para evitar que revise la posicicion actual del Avatar y en cruz

                tipo = (char) LaberintoActual.getCelda()[y + f][x + k].GetTipo();

                if (tipo == MONSTRUO || tipo == ARTEFACTO) {

                    int val, pelea;
                    flag = 1;

                    switch (tipo) {

                        case MONSTRUO:
                            g  = y + f ; 
                            h   = x + k ; 
                            pelea = PreguntarPelearConMonstruo(this->posLaberintoActual, y + f, x + k);
                            PlaySound(NULL, NULL, 0);
                            PlaySound(("Doom_2-Level_1.wav"), NULL, SND_ASYNC);
                            if (pelea == 1) LaberintoActual.getCelda()[y + f][x + k].SetTipo(ARTEFACTO);
                            k = 3;
                            f = 3; //para salir del bucle
                            break;

                        case ARTEFACTO:
                            if (this->avatar.poseeElSacoLLeno()) {
                                cout << "Se lleno el saco\n";
                                flag = 0;
                                return;
                            }
                            int tip = rand() % 3;
                            switch (tip) {
                                case 0:
                                {
                                    //TIPO ARMA                                    
                                    val = rand() % numAA;
                                    this->avatar.agregarArtefactoAlSaco(&ArmA[val], 0);
                                    break;
                                }
                                case 1:
                                {
                                    //TIPO ARMADURA                                    
                                    val = rand() % numAd;
                                    this->avatar.agregarArtefactoAlSaco(&Armd[val], 0);
                                    break;
                                }
                                case 2:
                                {
                                    //TIPO POCION                                    
                                    val = rand() % numP;
                                    this->avatar.agregarArtefactoAlSaco(&Poc[val], 0);
                                    break;
                                }
                            }
                            if (this->avatar.GetSaco().GetIndice() < 11) LaberintoActual.getCelda()[y + f][x + k].SetTipo(ADENTRO);
                            break;
                    }

                }
            }
        }
    }
}

void Juego::impresionDeMonstruos(int indLabActual, int x, int y) {
    
    int num = this->arreLaberintos[indLabActual].busquedaMonstruo( x , y ).GetImagen();
    
    switch (num) {
        case 0:
            CREAR GESTION ESPACIOS; cout << "ooooo ooooo      ooo oooooooooo.     .oooo.     oooooooo   .o " << endl;
            CREAR GESTION ESPACIOS; cout << "`888' `888b.     `8' `888'   `Y8b  .dP' 'Y88b  dP''''''' o888 " << endl;
            CREAR GESTION ESPACIOS; cout << " 888   8 `88b.    8   888      888       ]8P' d88888b.    888 " << endl;
            CREAR GESTION ESPACIOS; cout << " 888   8   `88b.  8   888      888     .d8P'      `Y88b   888 " << endl;
            CREAR GESTION ESPACIOS; cout << " 888   8     `88b.8   888      888   .dP'           ]88   888 " << endl;
            CREAR GESTION ESPACIOS; cout << " 888   8       `888   888     d88' .oP     .o o.   .88P   888 " << endl;
            CREAR GESTION ESPACIOS; cout << "o888o o8o        `8  o888bood8P'   8888888888 `8bd88P'   o888o" << endl;
            break;
        case 1:
           CREAR SEGURIDAD ESPACIOS; cout << "ooooo ooooo      ooo oooooooooo.     .oooo.    .ooooo.     .oooo.  " << endl;
           CREAR SEGURIDAD ESPACIOS; cout << "`888' `888b.     `8' `888'   `Y8b  .dP' 'Y88b 888' `Y88. d8P' `Y8b " << endl;
           CREAR SEGURIDAD ESPACIOS; cout << " 888   8 `88b.    8   888      888       ]8P' 888    888 888    888" << endl;
           CREAR SEGURIDAD ESPACIOS; cout << " 888   8   `88b.  8   888      888     .d8P'   `Vbood888 888    888" << endl;
           CREAR SEGURIDAD ESPACIOS; cout << " 888   8     `88b.8   888      888   .dP'           888' 888    888" << endl;
           CREAR SEGURIDAD ESPACIOS; cout << " 888   8       `888   888     d88' .oP     .o     .88P'  `88b  d88'" << endl;
           CREAR SEGURIDAD ESPACIOS; cout << "o888o o8o        `8  o888bood8P'   8888888888   .oP'      `Y8bd8P' " << endl;
            break;
        case 2:
            CREAR ED ESPACIOS; cout << "ooooo oooooooooooo oooooooooooo   .oooo.     .oooo.    .ooooo.  " << endl;
            CREAR ED ESPACIOS; cout << "`888' `888'     `8 `888'     `8 .dP' 'Y88b  .dP' 'Y88 888' `Y88." << endl;
            CREAR ED ESPACIOS; cout << " 888   888          888               ]8P'       ]8P' 888    888" << endl;
            CREAR ED ESPACIOS; cout << " 888   888oooo8     888oooo8        .d8P'      .d8P'   `Vbood888" << endl;
            CREAR ED ESPACIOS; cout << " 888   888    '     888    '      .dP'       .dP'           888'" << endl;
            CREAR ED ESPACIOS; cout << " 888   888       o  888       o .oP     .o .oP     .o     .88P' " << endl;
            CREAR ED ESPACIOS; cout << "o888o o888ooooood8 o888ooooood8 8888888888 8888888888   .oP'    " << endl;
            break;
        case 3:
            CREAR BASES ESPACIOS; cout << "ooooo ooooo      ooo oooooooooooo   .oooo.         .o       .ooo  " << endl;
            CREAR BASES ESPACIOS; cout << "`888' `888b.     `8' `888'     `8 .dP' '88b      .d88     .88'    " << endl;
            CREAR BASES ESPACIOS; cout << " 888   8 `88b.    8   888               ]8P'   .d'888    d88'     " << endl;
            CREAR BASES ESPACIOS; cout << " 888   8   `88b.  8   888oooo8        .d8P'  .d'  888   d888P Ybo." << endl;
            CREAR BASES ESPACIOS; cout << " 888   8     `88b.8   888    '      .dP'     88ooo888oo Y88[   ]88" << endl;
            CREAR BASES ESPACIOS; cout << " 888   8       `888   888         .oP     .o      888   `Y88   88P" << endl;
            CREAR BASES ESPACIOS; cout << "o888o o8o        `8  o888o        8888888888     o888o   `88bod8' " << endl;
            break;
        case 4:
            CREAR FUNDA ESPACIOS; cout << "ooooo ooooo      ooo oooooooooooo   .oooo.     .oooo.     .oooo.  " << endl;
            CREAR FUNDA ESPACIOS; cout << "`888' `888b.     `8' `888'     `8 .dP' 'Y88b  .dP' 'Y88  d8P'`Y8b " << endl;
            CREAR FUNDA ESPACIOS; cout << " 888   8 `88b.    8   888               ]8P'       ]8P' 888    888" << endl;
            CREAR FUNDA ESPACIOS; cout << " 888   8   `88b.  8   888oooo8        .d8P'      .d8P'  888    888" << endl;
            CREAR FUNDA ESPACIOS; cout << " 888   8     `88b.8   888    '      .dP'       .dP'     888    888" << endl;
            CREAR FUNDA ESPACIOS; cout << " 888   8       `888   888         .oP     .o .oP     .o `88b  d88'" << endl;
            CREAR FUNDA ESPACIOS; cout << "o888o o8o        `8  o888o        8888888888 8888888888  `Y8bd8P' " << endl;
            break ; 
        case 5 : 
            CREAR ALGORITMIA ESPACIOS; cout << "ooooo ooooo      ooo oooooooooooo   .oooo.       .ooo     .oooo.  " << endl;
            CREAR ALGORITMIA ESPACIOS; cout << "`888' `888b.     `8' `888'     `8 .dP' 'Y88b    .88'    .dP' 'Y88b " << endl;
            CREAR ALGORITMIA ESPACIOS; cout << " 888   8 `88b.    8   888               ]8P'  d88'            ]8P'" << endl;
            CREAR ALGORITMIA ESPACIOS; cout << " 888   8   `88b.  8   888oooo8        .d8P'  d888P'Ybo.     <88b. " << endl;
            CREAR ALGORITMIA ESPACIOS; cout << " 888   8     `88b.8   888    '      .dP'     Y88[   ]88      `88b." << endl;
            CREAR ALGORITMIA ESPACIOS; cout << " 888   8       `888   888         .oP     .o `Y88   88P o.   .88P " << endl;
            CREAR ALGORITMIA ESPACIOS; cout << "o888o o8o        `8  o888o        8888888888  `88bod8'  `8bd88P'  " << endl;
            break;
        case 6:
            CREAR OAC ESPACIOS; cout << "ooooo oooooooooooo oooooooooooo   .oooo.         .o     .oooo.  " << endl;
            CREAR OAC ESPACIOS; cout << "`888' `888'     `8 `888'     `8 .dP' 'Y88b      .d88    d8P'`Y8b " << endl;
            CREAR OAC ESPACIOS; cout << " 888   888          888               ]8P'   .d'888   888    888" << endl;
            CREAR OAC ESPACIOS; cout << " 888   888oooo8     888oooo8        .d8P'  .d'  888   888    888" << endl;
            CREAR OAC ESPACIOS; cout << " 888   888          888    '      .dP'     88ooo888oo 888    888" << endl;
            CREAR OAC ESPACIOS; cout << " 888   888       o  888       o .oP     .o      888   `88b  d88'" << endl;
            CREAR OAC ESPACIOS; cout << "o888o o888ooooood8 o888ooooood8 8888888888     o888o   `Y8bd8P' " << endl;
            break; 
      case 7 : 
            CREAR LP1 ESPACIOS; cout << "ooooo ooooo      ooo oooooooooooo   .oooo.    .ooooo.     .o " << endl;
            CREAR LP1 ESPACIOS; cout << "`888' `888b.     `8' `888'     `8 .dP' 'Y88b  d88'   `8. o888 " << endl;
            CREAR LP1 ESPACIOS; cout << " 888   8 `88b.    8   888               ]8P' Y88..  .8'  888 " << endl;
            CREAR LP1 ESPACIOS; cout << " 888   8   `88b.  8   888oooo8        .d8P'   `88888b.   888 " << endl;
            CREAR LP1 ESPACIOS; cout << " 888   8     `88b.8   888    '      .dP'     .8'  ``88b  888 " << endl;
            CREAR LP1 ESPACIOS; cout << " 888   8       `888   888         .oP     .o `8.   .88P  888 " << endl;
            CREAR LP1 ESPACIOS; cout << "o888o o8o        `8  o888o        8888888888  `boood8'  o888o" << endl;
            break ; 
        case 8 : 
            CREAR APLICA ESPACIOS; cout << "ooooo ooooo      ooo oooooooooooo   .oooo.       .ooo     oooooooo" << endl;
            CREAR APLICA ESPACIOS; cout << "`888' `888b.     `8' `888'     `8 .dP' 'Y88b   .88'     dP'''''''" << endl;
            CREAR APLICA ESPACIOS; cout << " 888   8 `88b.    8   888               ]8P'  d88'      d88888b.  " << endl;
            CREAR APLICA ESPACIOS; cout << " 888   8   `88b.  8   888oooo8        .d8P'  d888P'Ybo.     `Y88b " << endl;
            CREAR APLICA ESPACIOS; cout << " 888   8     `88b.8   888    '      .dP'     Y88[   ]88       ]88 " << endl;
            CREAR APLICA ESPACIOS; cout << " 888   8       `888   888         .oP     .o `Y88   88P o.   .88P " << endl;
            CREAR APLICA ESPACIOS; cout << "o888o o8o        `8  o888o        8888888888  `88bod8'  `8bd88P'  " << endl;
            break ; 
     
        case 9 : 
            CREAR SOFTWARE ESPACIOS; cout << "ooooo ooooo      ooo oooooooooooo   .oooo.         .o     oooooooo" << endl;
            CREAR SOFTWARE ESPACIOS; cout << "`888' `888b.     `8' `888'     `8 .dP' 'Y88b      .d88   dP'''''''" << endl;
            CREAR SOFTWARE ESPACIOS; cout << " 888   8 `88b.    8   888               ]8P'   .d'888   d88888b.  " << endl;
            CREAR SOFTWARE ESPACIOS; cout << " 888   8   `88b.  8   888oooo8        .d8P'  .d'  888       `Y88b " << endl;
            CREAR SOFTWARE ESPACIOS; cout << " 888   8     `88b.8   888    '      .dP'     88ooo888oo       ]88 " << endl;
            CREAR SOFTWARE ESPACIOS; cout << " 888   8       `888   888         .oP     .o      888   o.   .88P " << endl;
            CREAR SOFTWARE ESPACIOS; cout << "o888o o8o        `8  o888o        8888888888     o888o  `8bd88P'  " << endl;
            break ; 
    }
}

void ImprimirOpcionesDeBatalla(){
    CREAR BASICOS+4 ESPACIOS; cout << char(201);
    for(int i=0;i<66;i++) cout << char(205);
    cout << char(187) << endl ;
    
    CREAR BASICOS+4 ESPACIOS; cout << char(186) << " Elija una opcion:                            ";
    CREAR BASICOS-13 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(186) << "            Atacar!          ----> (a)        ";
    CREAR BASICOS-13 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(186) << "            Ataque automatico----> (r)        ";
    CREAR BASICOS-13 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(186) << "            Usar artefacto   ----> (s)        ";
    CREAR BASICOS-13 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(186) << "            Retirarse del curso--> (f)        ";
    CREAR BASICOS-13 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(200);
    for (int i = 0; i < 66; i++) cout << char(205); cout << char(188) << endl << endl; 
    CREAR BASICOS+4 ESPACIOS; cout << "Escriba una opcion :\n";
    CREAR BASICOS+4 ESPACIOS; cout << "? ";
}

void Juego::MostrarDatosPrevioBatalla(Monstruo & monster ) {
    cout << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(201);
    for(int i=0;i<66;i++) cout << char(205);
    cout << char(187) << endl ;
    CREAR BASICOS+4 ESPACIOS;cout << char(186) << " Este es tu Monstruo!";
    CREAR GENERALES-1 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS;cout << char(186) << " Curso : "<< monster.GetNombre();
    for(int i=0;i<57-strlen(monster.GetNombre());i++) cout << " "; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS;cout << char(186) << " Vida: " << left << setw(4) << monster.GetVidaActual();
    CREAR BASICOS+3 ESPACIOS;cout << " Danho base: " << left << left << setw(6)<< monster.GetDanhoBase() << char(186) <<endl;

    if (monster.GetArmadura() != NULL){
        CREAR BASICOS+4 ESPACIOS; 
        cout << char(186) << " Armadura:";
        monster.GetArmadura()->Imprimir();
        cout << char(186) << endl;
    }
    else{
        CREAR BASICOS+4 ESPACIOS; cout << char(186) << " Armadura: No tiene "; 
        CREAR GENERALES ESPACIOS; cout << char(186) << endl;
    } if (monster.GetArma() != NULL) {
        CREAR BASICOS+4 ESPACIOS; 
        cout << char(186) << " Arma: ";
        monster.GetArma()->Imprimir() ;
        cout << char(186) << endl;
    } else{
        CREAR BASICOS+4 ESPACIOS; cout << char(186) << " Arma: No tiene ";
        CREAR GENERALES+4 ESPACIOS; cout << char(186) << endl;
    }
    CREAR BASICOS+4 ESPACIOS;
    cout << char(200);
    for (int i = 0; i < 66; i++) cout << char(205);
    cout << char(188) << endl << endl;  

    this->GetAvatar().mostrarDatosMapa();
    CREAR BASICOS+4 ESPACIOS;
    cout << char(200);
    for (int i = 0; i < 66; i++) cout << char(205);
    cout << char(188) << endl << endl << endl;     
}


int Juego::PreguntarPelearConMonstruo(int indLabActual, int x, int y) {

    PlaySound(NULL, NULL, 0);
    PlaySound(("Doom_Level_1.wav"), NULL, SND_ASYNC);
    char linea[30];
    //busquedaMonstruo(this->LaberintoActual.)
    Monstruo monster = this->arreLaberintos[indLabActual].busquedaMonstruo( x , y );
    system("cls");
    impresionDeMonstruos(indLabActual,x,y);
    MostrarDatosPrevioBatalla(monster);
    fflush( stdin );
    CREAR BASICOS+4 ESPACIOS; printf("Deseas pelear con el monstruo ('yes' or 'no') ?   ");
    gets(linea);
    int yes, no, flag;

    while (1) {
        yes = (strcmp(linea, "yes") == 0) ? 1 : 0; //si es igual a "yes"
        no = (strcmp(linea, "no") == 0) ? 1 : 0; // si es igual a "no"
        if (yes || no) break; //Si responde correctamente sale del bucle
        CREAR BASICOS+4 ESPACIOS; cout << "Tienes que escribir \"yes\" o \"no\" :  ";
        gets(linea);
    }
    if (yes) { // en caso acepte la batalla
        PelearConMonstruo(monster, flag,indLabActual,x,y);
    }
    return flag;
}

void Juego::botarArtefactoGrafico() {
    int x, y;
    x = avatar.GetPosX();
    y = avatar.GetPosY();

    int cont = 0;
    char c;
    for (int f = -1; f < 3 && cont != 1 ; f++) {
        for (int k = -1; k < 2  && cont != 1 ; k++) { //recorrido alrededor del Avatar
            if (!(f == k) && !(k == (-f))) {
                c = arreLaberintos[posLaberintoActual].getCelda()[y + k ][ x + f ].GetTipo();
                if (c == ADENTRO) {
                    arreLaberintos[posLaberintoActual].getCelda()[y + k ][ x + f ].SetTipo('A');
                    cont++;
                }
            }            
        }

    }
}

void imprimirAtaqueMonstruo() {
    CREAR BASICOS+4 ESPACIOS; cout << char(201);
    for(int i=0;i<66;i++) cout << char(205);
    cout << char(187) << endl ;
    CREAR BASICOS+4 ESPACIOS; cout << char(186) << "El Curso usa ";
    int num = rand() % 6;
    switch (num) {
        case 0:
            cout << "Final imposible       ";
            break;
        case 1:
            cout << "Prueba tipo C         ";
            break;
        case 2:
            cout << "Laboratorio innovador ";
            break;
        case 3:
            cout << "Parcial Nivel asiatico";
            break;
        case 4:
            cout << "Practica Troll        ";
            break;
        case 5:
            cout << "El Jp vende humo      ";
            break;
    }
    CREAR 31 ESPACIOS; cout << char(186) << endl;
}

void imprimirContraAtaqueMonstruo() {
    CREAR BASICOS+4 ESPACIOS;cout << char(186) << "Usaste  ";
    int num = rand() % 6;
    switch (num) {
        case 0:
            cout << "Kit Completo en Tetrix         ";
            break;
        case 1:
            cout << "Planchon salvaje               ";
            break;
        case 2:
            cout << "Usb salvador                   ";
            break;
        case 3:
            cout << "Estudiar con anticipacion      ";
            break;
        case 4:
            cout << "Amanecida Hardcore             ";
            break;
        case 5:
            cout << "Camara de entrenamiento de Goku";
            break;
    }
    CREAR 27 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS;
    cout << char(200);
    for (int i = 0; i < 66; i++) cout << char(205);
    cout << char(188) << endl << endl << endl;
}

void Juego::PelearConMonstruo(Monstruo &monster, int &flag,int indLabActual,int x,int y) {
    char opcion[30];
    system("cls");
    int a, f, s, r = 0;
    while ((avatar.GetVidaActual() > 0) && (monster.GetVidaActual() > 0)) {
        if (!r) {
            system("cls");
            
            impresionDeMonstruos(indLabActual,x,y);
            //////////////////////////////////////77
            MostrarDatosPrevioBatalla(monster);
            /////            
            ImprimirOpcionesDeBatalla();
            ////////////////////////////////////////
            
            cin >> opcion;

            while (1) {

                a =s = f =  0;
                //para que no entré al if que baja vida al mosntruo                
                s = (strcmp(opcion, "s") == 0) ? 1 : 0;
                r = (strcmp(opcion, "r") == 0) ? 1 : 0;
                a = (strcmp(opcion, "a") == 0) ? 1 : 0;
                f = (strcmp(opcion, "f") == 0) ? 1 : 0;

                if (a || f || r || s) break;

                CREAR BASICOS+4 ESPACIOS; cout << "Debe seleccionar una de las dos opciones ";
                cin >> opcion;
            }
        }

        if (s) {
            int ind;
            
         //   system("cls");
            if (this->GetAvatar().cantArtefactos()>0){
                CREAR BASICOS+4 ESPACIOS;
                cout << char(201);
                for (int i = 0; i < 66; i++) cout << char(205);
                cout << char(187) << endl;
                this->ImprimirSaco();
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << "Escribe un indice\n";
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << "? : ";
                cin >>ind;
                while(1){
                    if (!usarArtefacto(ind)) {
                        for (int i = 0; i < 46; i++) putchar(' ');
                        cout << "     Elige un Artefacto Correcto\n";
                        for (int i = 0; i < 46; i++) putchar(' ');
                        cout << "Escribe un indice\n";
                        for (int i = 0; i < 46; i++) putchar(' ');                                    
                        cout << "? : ";
                        cin >>ind;
                        flag = 0;                
                    }else{                    
                        for (int i = 0; i < 46; i++) putchar(' ');
                        cout <<  "Se utilizo correctamente " << endl ;
                        tiempo(2);
                        break ;
                    }
                }
            }else {
                for (int i = 0; i < 46; i++) putchar(' ');
                cout <<  "Sin elementos en el saco " << endl ;                        
                tiempo(2);
            }
        }
        if (f) {
            system("cls");
            int huida = rand() % 101;
            if (huida < 51) {
                cout << endl;
                CREAR BASICOS+4 ESPACIOS; cout << "Te retiraste del curso" << endl;
                CREAR BASICOS+4 ESPACIOS; cout << "Pero... Perdiste la mitad de tu vida" << endl << endl;
                int quitaVida = avatar.GetVidaActual();
                quitaVida = (int) (quitaVida / 2);
                int vidaRestada = avatar.GetVidaActual() - quitaVida;
                if (vidaRestada < 0) avatar.SetVidaActual(1);
                else avatar.SetVidaActual(vidaRestada);
                CREAR BASICOS+4 ESPACIOS; cout << "Tu vida actual es: " << avatar.GetVidaActual() << endl << endl;
                break;
            } else {
                CREAR BASICOS+4 ESPACIOS; cout << "No has podido retirarte del curso :( " << endl;
                CREAR BASICOS+4 ESPACIOS; cout << "Sigue luchando campeon!\n" << endl;
            }
            CREAR BASICOS+4 ESPACIOS; cout << "Aprente 1 o 2 veces ENTER para continuar: ";
            while (cin.get() != '\n');
        }

        if (a || r || f || s) {

            system("cls");
            impresionDeMonstruos(indLabActual,x,y);
            if (a || !r || s || f) imprimirAtaqueMonstruo();
            if (a && !r && !s && !f) imprimirContraAtaqueMonstruo();
            //////////////////////////////////////////////////
            int maxM = 0;
            if (monster.GetArma() != NULL) maxM = monster.GetArma()->GetDanhoMax();
            int minM = 0;
            if (monster.GetArma() != NULL) minM = monster.GetArma()->GetDanhoMin();

            int aleatorioMonster = rand() % (maxM - minM + 1);
            int danhoM = monster.GetDanhoBase() + aleatorioMonster;
            //////////////////////////////////////////////////
            int maxA = 0;
            if (avatar.GetArma() != NULL) maxA = avatar.GetArma()->GetDanhoMax();
            int minA = 0;
            if (avatar.GetArma() != NULL) minA = avatar.GetArma()->GetDanhoMin();

            int aleatorioAvatar = rand() % (maxA - minA + 1);
            int danhoA = avatar.GetDanhoBase() + aleatorioAvatar;
            ///////////////////////////////////////////////////
            if (avatar.GetArmadura() != NULL) {
                danhoM = (int) (danhoM - (avatar.GetArmadura()->GetDefensa() / 10));
            }
            int vidaActualAvatar = avatar.GetVidaActual();
            avatar.SetVidaActual(vidaActualAvatar - danhoM);

            if (monster.GetArmadura() != NULL) {
                danhoA = (int) (danhoA - (monster.GetArmadura()->GetDefensa() / 10));
            }
            if (s || f) {
                danhoA = 0;
            }
            monster.SetVidaActual(monster.GetVidaActual() - danhoA);
        }
        
        if ((monster.GetVidaActual() > 0) && !r) {
            CREAR BASICOS+4 ESPACIOS; cout << "El monstruo tiene " << monster.GetVidaActual() << " de vida\n" << endl;
            CREAR BASICOS+4 ESPACIOS; cout << "Tienes " << avatar.GetVidaActual() << " de vida\n" << endl << endl ;
            
        }
        if ((monster.GetVidaActual() <= 0)&&(avatar.GetVidaActual()>0)) {
            CREAR BASICOS+4 ESPACIOS; cout << "Venciste al Monstruo" << endl;
            CREAR BASICOS+4 ESPACIOS; cout << "Te queda " << avatar.GetVidaActual() << " de vida" << endl;
        }
        if((avatar.GetVidaActual()<=0)){
            CREAR BASICOS+4 ESPACIOS; cout << "Perdiste! Este curso te vencio" << endl;
            avatar.setVidas(avatar.getVidas()-1);
            CREAR BASICOS+4 ESPACIOS; 
            if(avatar.getVidas()==3) cout << "Pero aun te queda la BICA!" << endl;
            if(avatar.getVidas()==2) cout << "Pero aun te queda la TRICA!" << endl;
            if(avatar.getVidas()==1) cout << "Pero aun te queda la CARTA!" << endl;
            if(avatar.getVidas()==0){
                CREAR BASICOS+4 ESPACIOS;cout << "Creo que es momento de trasladar tu talento" << endl;
                //poner un mapa final
                
            }
            avatar.SetMaxVida(avatar.GetMaxVida()-(250*(4-avatar.getVidas())));
            avatar.SetVidaActual(avatar.GetMaxVida());
            CREAR BASICOS+4 ESPACIOS;cout << "Tu vida actual es: " << avatar.GetVidaActual() << endl;
            
        }
        CREAR BASICOS+4 ESPACIOS; cout << "Aprente 1 o 2 veces ENTER para continuar: ";
        while (cin.get() != '\n');
        while (cin.get() != '\n');

    }
    
    system("cls");
    if ((avatar.GetVidaActual() <= 0)) {
        //CREAR BASICOS+4 ESPACIOS;cout << "HAS PERDIDO \n" << endl;
        flag = 0;
    } else {
        for(int i = 0 ; i < 20 ; i++) putchar('\n');
        CREAR BASICOS+4 ESPACIOS;
        cout << char(201);
        for (int i = 0; i < 66; i++) cout << char(205);
        cout << char(187) << endl;        
        CREAR BASICOS+4 ESPACIOS;cout << char(186) << "Ganaste la Batalla! Felicitaciones! "  ;         
        CREAR 30 ESPACIOS ;
        cout << char(186)<< endl;
        flag = 1;
       // cout << "tienes " << avatar.GetVidaActual() << " de vida\n" << endl;
       CREAR BASICOS+4 ESPACIOS;
        cout << char(200);
        for (int i = 0; i < 66; i++) cout << char(205);
        cout << char(188) << endl;
        
        CREAR BASICOS+4 ESPACIOS;cout << "\n\n";
               
    }
    cout << endl;
    CREAR BASICOS+4 ESPACIOS;cout << "Aprente 1 o 2 veces ENTER para continuar: ";
    while (cin.get() != '\n');
}

void Juego::SetDibujador(Dibujador dibujador) {
    this->dibujador = dibujador;
}

Dibujador Juego::GetDibujador() const {
    return dibujador;
}

void Juego::dibujadorDeEsquema() {
    dibujador.dibujarEsquemaVersion2(LaberintoActual, avatar);
}

Laberinto Juego::GetLaberintoActual() const {
    return LaberintoActual;
}

void Juego::SetAvatar(Avatar avatar) {
    this->avatar = avatar;
}

Avatar Juego::GetAvatar() const {
    return avatar;
}

void Juego::SetPosLaberintoActual(int posLaberintoActual) {

    this->posLaberintoActual = posLaberintoActual;
}

int Juego::GetPosLaberintoActual() const {
    return posLaberintoActual;
}

void Juego::ImprimirSaco() {
    CREAR BASICOS+4 ESPACIOS;
    cout << char(186);
    for (int i = 0; i < 66; i++) cout << " ";
    cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS;
    cout << char(186) << "  Elementos en el Saco: ";
    CREAR GENERALES-4 ESPACIOS;
    cout << char(186) << endl;
    for (int i = 0; i < this->avatar.GetSaco().GetIndice(); i++) {
        CREAR BASICOS+4 ESPACIOS;
        cout << char(186) << "  " << right << setw(2) << i << "  ";
        this->avatar.GetSaco()[i]->Imprimir();
    }
    CREAR BASICOS+4 ESPACIOS;
    cout << char(200);
    for (int i = 0; i < 66; i++) cout << char(205);
    cout << char(188) << endl;
}

void Juego::cargarArtefactos() {

}

int Juego::usarArtefacto(int ind) {
    if (ind >= 0 && ind < this->avatar.cantArtefactos()) {
        return this->avatar.usarArteFactor(ind);
        // Sí se puede usar 
    }
    return 0; // Nose puede usar artefacto 
}

int Juego::botarArtefacto(int ind) {
    if (ind >= 0 && ind < this->avatar.cantArtefactos()) {
        return this->avatar.botarArtefacto(ind);
    }
    return 0;
}

void Juego :: tiempo(int t) {
    clock_t t_ini, t_fin;
    double secs;
    t_ini = clock();
    while (1) {
        t_fin = clock();
        secs = (double) (t_fin - t_ini) / CLOCKS_PER_SEC;
        if (secs * 1000.0 > t*1000) break ; 
    }
    //printf("%.16g milisegundos\n", secs * 1000.0);
}

void Juego::historiaDelJuego() {
    
    cout << endl << endl;
    
CREAR BASICOS ESPACIOS;printf("               _=====_                                  _=====_\n");
CREAR BASICOS ESPACIOS;printf("              / _____ \\                                / _____ \\\n");
CREAR BASICOS ESPACIOS;printf("            +.-'_____'-.------------------------------.-'_____'-.+\n");
CREAR BASICOS ESPACIOS;printf("           /   |     |  '.         S O N Y          .'  |  _  |   \\\n");
CREAR BASICOS ESPACIOS;printf("          / ___| /|\\ |___ \\                        / ___| /_\\ |___ \\\n");
CREAR BASICOS ESPACIOS;printf("         / |      |      | ;  __              _   ; | _         _ | ;\n");
CREAR BASICOS ESPACIOS;printf("         | | <---   ---> | | |__|            |_:> | ||_|       (_)| |\n");
CREAR BASICOS ESPACIOS;printf("         | |___   |   ___| ;SELECT          START ; |___       ___| ;\n");
CREAR BASICOS ESPACIOS;printf("         |\\    | \\|/ |    /   _      ___       _   \\    | (X) |    /|\n");
CREAR BASICOS ESPACIOS;printf("         | \\   |_____|  .' ,'\" \"',  |___|   ,'\" \"', '.  |_____|  .' |\n");
CREAR BASICOS ESPACIOS;printf("         |  '-.______.-'  /       \\ ANALOG /       \\  '-._____.-'   |\n");
CREAR BASICOS ESPACIOS;printf("         |               |         |------|        |                |\n");
CREAR BASICOS ESPACIOS;printf("         |              / \\       /        \\       / \\              |\n");
CREAR BASICOS ESPACIOS;printf("         |             /   '.___.'          '.___.'   \\             |\n");
CREAR BASICOS ESPACIOS;printf("         |            /                                \\            |\n");
CREAR BASICOS ESPACIOS;printf("          \\          /                                  \\          /\n");
CREAR BASICOS ESPACIOS;printf("           \\________/                                    \\________/\n");
CREAR BASICOS ESPACIOS;printf("\n\n\n"); 

CREAR BASICOS+3 ESPACIOS;printf("                                                         .--.\n"); 
CREAR BASICOS+3 ESPACIOS;printf("                                                        /  .  \\\n"); 
CREAR BASICOS+3 ESPACIOS;printf("                                                       |\\_/|   |\n"); 
CREAR BASICOS+3 ESPACIOS;printf("                                                       |   |  /|\n"); 
CREAR BASICOS+3 ESPACIOS;printf("      .------------------------------------------------------' |\n");
CREAR BASICOS+3 ESPACIOS;printf("     /  .-.       En un mundo muy muy lejano habia una vez...  |\n");
CREAR BASICOS+3 ESPACIOS;printf("    |  /   \\   No! Alumno PUCP, esta historia no empieza asi,  |\n");
CREAR BASICOS+3 ESPACIOS;printf("    | |\\_.  |       Esta es la realidad, TU REALIDAD           |\n");
CREAR BASICOS+3 ESPACIOS;printf("    |\\|  | /|    Pero no te preocupes! Te vamos a ayudar :)    |\n");
CREAR BASICOS+3 ESPACIOS;printf("    | `---' |  Para que te prepares muy bien para sobrevivir   |\n");
CREAR BASICOS+3 ESPACIOS;printf("    |       |              en esta Jungla PUCP!                |\n");
CREAR BASICOS+3 ESPACIOS;printf("    |       |                                                  |\n");
CREAR BASICOS+3 ESPACIOS;printf("    |       |          ESTO ES ... STUDIES MADNESS 8D          |\n");
CREAR BASICOS+3 ESPACIOS;printf("    |       |        QUIERES EMPEZAR? (ESCRIBA SU NOMBRE )     /\n");
CREAR BASICOS+3 ESPACIOS;printf("     \\      |------------------------------------------------'       \n");
CREAR BASICOS+3 ESPACIOS;printf("      \\    /       \n");
CREAR BASICOS+3 ESPACIOS;printf("       `--'                            \n");

CREAR BASICOS+8 ESPACIOS; printf("                Nombre: ");
char nombre[200];
cin.getline(nombre,200);
if (strlen(nombre)>50) nombre[50]='\0';
else if (strlen(nombre) == 0) strcpy(nombre, "Player 1");
avatar.SetNombre(nombre);
}
