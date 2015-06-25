/* 
 * File:   Juego.cpp
 * Author: Brayan
 * 
 * Created on 5 de junio de 2015, 11:18 AM
 */
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


using namespace std;

Juego::Juego() {
    monstruo = new Monstruo[10]; // 10 es un ejemplo puede ser cualquie valor 
    arreLaberintos = new Laberinto[10]; // Suponiendo como maximos 10
    posLaberintoActual = 0; // Por empieza en el principio         
}

Juego::~Juego() {

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
                            if (pelea == 1) LaberintoActual.getCelda()[y + f][x + k].SetTipo(ADENTRO);
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
            CREAR MURCIELAGO ESPACIOS;            printf("           \\                  /\n");
            CREAR MURCIELAGO ESPACIOS;            printf("    _________))                ((__________\n");
            CREAR MURCIELAGO ESPACIOS;            printf("   /.-------./\\    \\    /    //\\.--------.\\\n");
            CREAR MURCIELAGO ESPACIOS;            printf("  //#######//##\\   ))  ((   //##\\########\\\n");
            CREAR MURCIELAGO ESPACIOS;            printf(" //#######//###((  ((    ))  ))###\\########\\\n");
            CREAR MURCIELAGO ESPACIOS;            printf("((#######((#####\\  \\  //  //#####))########))\n");
            CREAR MURCIELAGO ESPACIOS;            printf(" \\##' `###\\######\\  \\)(/  //######/####' `##/\n");
            CREAR MURCIELAGO ESPACIOS;            printf("  )'    ``#)'  `##\\`->oo<-'/##'  `(#''     `(\n");
            CREAR MURCIELAGO ESPACIOS;            printf("          (       ``\\`..'/''       )\n");
            CREAR MURCIELAGO ESPACIOS;            printf("                     \\'''\n");
            CREAR MURCIELAGO ESPACIOS;            printf("                      `- )\n");
            CREAR MURCIELAGO ESPACIOS;            printf("                      / /\n");
            CREAR MURCIELAGO ESPACIOS;            printf("                     ( /\\  \n");
            CREAR MURCIELAGO ESPACIOS;            printf("                     /\\| \\\n");
            CREAR MURCIELAGO ESPACIOS;            printf("                    (  \\\n");
            CREAR MURCIELAGO ESPACIOS;            printf("                        )\n");
            CREAR MURCIELAGO ESPACIOS;            printf("                       /\n");
            CREAR MURCIELAGO ESPACIOS;            printf("                      (\n\n");
            break;
        case 1:
            CREAR CASCO ESPACIOS;            printf("  ,/         \\.\n");
            CREAR CASCO ESPACIOS;            printf(" ((           ))\n");
            CREAR CASCO ESPACIOS;            printf("  \\`.       ,'/\n");
            CREAR CASCO ESPACIOS;            printf("   )')     (`(\n");
            CREAR CASCO ESPACIOS;            printf(" ,'`/       \\,`.\n");
            CREAR CASCO ESPACIOS;            printf("(`-(         )-')\n");
            CREAR CASCO ESPACIOS;            printf(" \\-'\\,-'\"`-./`-/\n");
            CREAR CASCO ESPACIOS;            printf("  \\-')     (`-/\n");
            CREAR CASCO ESPACIOS;            printf("  /`'       `'\\\n");
            CREAR CASCO ESPACIOS;            printf(" (  _       _  )\n");
            CREAR CASCO ESPACIOS;            printf(" | ( \\     / ) |\n");
            CREAR CASCO ESPACIOS;            printf(" |  `.\\   /,'  |\n");
            CREAR CASCO ESPACIOS;            printf(" |    `\\ /'    |\n");
            CREAR CASCO ESPACIOS;            printf(" (              )\n");
            CREAR CASCO ESPACIOS;            printf("  \\           /\n");
            CREAR CASCO ESPACIOS;            printf("   \\  ||||   /\n");
            CREAR CASCO ESPACIOS;            printf("    `.     ,'\n");
            CREAR CASCO ESPACIOS;            printf("      `-.-'\n\n");
            break;
        case 2:
            CREAR STARDEMON ESPACIOS;            printf("              ._                                            ,\n");
            CREAR STARDEMON ESPACIOS;            printf("               (`)..                                    ,.-')\n");
            CREAR STARDEMON ESPACIOS;            printf("                (',.)-..                            ,.-(..`)\n");
            CREAR STARDEMON ESPACIOS;            printf("                 (,.' ,.)-..                    ,.-(. `.. )\n");
            CREAR STARDEMON ESPACIOS;            printf("                  (,.' ..' .)-..            ,.-( `.. `.. )\n");
            CREAR STARDEMON ESPACIOS;            printf("                   (,.' ,.'  ..')-.     ,.-( `. `.. `.. )\n");
            CREAR STARDEMON ESPACIOS;            printf("                    (,.'  ,.' ,.'  )-.-('   `. `.. `.. )\n");
            CREAR STARDEMON ESPACIOS;            printf("                     ( ,.' ,.'    _== ==_     `.. `.. )\n");
            CREAR STARDEMON ESPACIOS;            printf("                      ( ,.'   _==' ~  ~  `==_    `.. )\n");
            CREAR STARDEMON ESPACIOS;            printf("                       \\  _=='   ----..----  `==_   )\n");
            CREAR STARDEMON ESPACIOS;            printf("                    ,.-:    ,----___.  .___----.    -..\n");
            CREAR STARDEMON ESPACIOS;            printf("                ,.-'   (   _--====_  \\/  _====--_   )  `-..\n");
            CREAR STARDEMON ESPACIOS;            printf("            ,.-'   .__.'`.  `-_I0_-'    `-_0I_-'  .'`.__.  `-..\n");
            CREAR STARDEMON ESPACIOS;            printf("        ,.-'.'   .'      (          |  |          )      `.   `.-..\n");
            CREAR STARDEMON ESPACIOS;            printf("    ,.-'    :    `___--- '`.__.    / __ \\    .__.' `---___'    :   `-..\n");
            CREAR STARDEMON ESPACIOS;            printf("  -'_________`-____________'__ \\  (O)  (O)  / __`____________-'________`-\n");
            CREAR STARDEMON ESPACIOS;            printf("                              \\ . _  __  _ . /\n");
            CREAR STARDEMON ESPACIOS;            printf("                               \\ `V-'  `-V' |\n");
            CREAR STARDEMON ESPACIOS;            printf("                                | \\ \\ | /  /\n");
            CREAR STARDEMON ESPACIOS;            printf("                                 V \\ ~| ~/V\n");
            CREAR STARDEMON ESPACIOS;            printf("                                  |  \\  /|\n");
            CREAR STARDEMON ESPACIOS;            printf("                                   \\~ | V \n");
            CREAR STARDEMON ESPACIOS;            printf("                                    \\  |\n");
            CREAR STARDEMON ESPACIOS;            printf("                                     VV\n\n");
            break;
        case 3:
            CREAR CABALLO ESPACIOS;            printf("                   .\n");
            CREAR CABALLO ESPACIOS;            printf("                 ....8ob.\n");
            CREAR CABALLO ESPACIOS;            printf("              o88888888888b.\n");
            CREAR CABALLO ESPACIOS;            printf("          ..o888888888888888b..\n");
            CREAR CABALLO ESPACIOS;            printf("          888888888888888P""888P\n");
            CREAR CABALLO ESPACIOS;            printf("         8888888888888888888888.\n");
            CREAR CABALLO ESPACIOS;            printf("        d88888888888888888888888bc.\n");
            CREAR CABALLO ESPACIOS;            printf("       o8888888888888888" "\"38888Poo..\n");
            CREAR CABALLO ESPACIOS;            printf("      .8888888888P888888        \"38888888\n");
            CREAR CABALLO ESPACIOS;            printf("      88888888888 8888888eeeeee.   \"\"38\"8\n");
            CREAR CABALLO ESPACIOS;            printf("     P\" 888888888 \"\"'\"\"\"       `\"\"o._.oP\n");
            CREAR CABALLO ESPACIOS;            printf("        8888888888.\n");
            CREAR CABALLO ESPACIOS;            printf("        88888888888\n");
            CREAR CABALLO ESPACIOS;            printf("        '888888888 8b.\n");
            CREAR CABALLO ESPACIOS;            printf("         \"88888888b  \"\"\"\"3booooooo..\n");
            CREAR CABALLO ESPACIOS;            printf("          \"888888888888888b         \"b.\n");
            CREAR CABALLO ESPACIOS;            printf("           \"8888888888888888888888b    \"8\n");
            CREAR CABALLO ESPACIOS;            printf("            \"8888888888888888888888888   b\n");
            CREAR CABALLO ESPACIOS;            printf("                \"\"888888888888888888888  c\n");
            CREAR CABALLO ESPACIOS;            printf("                   \"8888888888888888888  P\n");
            CREAR CABALLO ESPACIOS;            printf("                    \"88888888888888888888\"\n");
            CREAR CABALLO ESPACIOS;            printf("                    .88888888888888888888\n");
            CREAR CABALLO ESPACIOS;            printf("                   .888NICK8888888888888P\n");
            CREAR CABALLO ESPACIOS;            printf("                 od888888888888888888P\n\n");
            break;
        case 4:
            CREAR CENTAURO ESPACIOS;            printf("                 __\n");
            CREAR CENTAURO ESPACIOS;            printf("                / _\\ #\n");
            CREAR CENTAURO ESPACIOS;            printf("                \\c /  #\n");
            CREAR CENTAURO ESPACIOS;            printf("                / \\___ #\n");
            CREAR CENTAURO ESPACIOS;            printf("                \\`----`#==>  \n");
            CREAR CENTAURO ESPACIOS;            printf("                |  \\  #\n");
            CREAR CENTAURO ESPACIOS;            printf("     ,%.-\"\"\"---'`--'\\#_\n");
            CREAR CENTAURO ESPACIOS;            printf("    %%/             |__`\\\n");
            CREAR CENTAURO ESPACIOS;            printf("   .%'\\     |   \\   /  //\n");
            CREAR CENTAURO ESPACIOS;            printf("   ,%' >   .'----\\ |  [/\n");
            CREAR CENTAURO ESPACIOS;            printf("      < <<`       ||\n");
            CREAR CENTAURO ESPACIOS;            printf("       `\\\\       ||\n");
            CREAR CENTAURO ESPACIOS;            printf("         )\\\\      )\\\n\n");
            break;
    }
}

void ImprimirOpcionesDeBatalla(){
    CREAR BASICOS+4 ESPACIOS; cout << char(201);
    for(int i=0;i<66;i++) cout << char(205);
    cout << char(187) << endl ;
    CREAR BASICOS+4 ESPACIOS; cout << char(186) << " Elija una opcion:                  ";
    CREAR BASICOS-3 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(186) << " a) Atacar!                         ";
    CREAR BASICOS-3 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(186) << " r) Ataque automatico               ";
    CREAR BASICOS-3 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(186) << " s) Usar artefacto (sin implementar)";
    CREAR BASICOS-3 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(186) << " f) Retirarse del curso             ";
    CREAR BASICOS-3 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(200);
    for (int i = 0; i < 66; i++) cout << char(205); cout << char(188) << endl << endl; 
    CREAR BASICOS+4 ESPACIOS; cout << "? ";
}

void Juego::MostrarDatosPrevioBatalla(Monstruo monster) {
    cout << endl;
    CREAR BASICOS+4 ESPACIOS; cout << char(201);
    for(int i=0;i<66;i++) cout << char(205);
    cout << char(187) << endl ;
    CREAR BASICOS+4 ESPACIOS;cout << char(186) << " Este es tu Monstruo!";
    CREAR GENERALES-1 ESPACIOS; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS;cout << char(186) << " Curso : "<< monster.GetNombre();
    for(int i=0;i<57-strlen(monster.GetNombre());i++) cout << " "; cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS;cout << char(186) << " Vida: " << left << setw(4) << monster.GetMaxVida();
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

    CREAR BASICOS+4 ESPACIOS; printf("Deseas pelear con el monstruo ('yes' or 'no') ?   ");
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

void Juego::PelearConMonstruo(Monstruo monster, int &flag,int indLabActual,int x,int y) {
    char opcion[30];
    system("cls");
    int a, f, s, r = 0;
    while ((avatar.GetVidaActual() > 0) && (monster.GetVidaActual() > 0)) {
        if (!r) {
            system("cls");
            
            impresionDeMonstruos(indLabActual,x,y);
            //////////////////////////////////////77
            CREAR BASICOS+4 ESPACIOS;
            cout << char(201);
            for (int i = 0; i < 66; i++) cout << char(205);
            cout << char(187) << endl;
            this->ImprimirSaco();
            ///////////////////////////////////////77
            ImprimirOpcionesDeBatalla();
            
            cin >> opcion;

            while (1) {

                a = 0;
                s = 0; //para que no entré al if que baja vida al mosntruo
                f = 0;

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
            
            system("cls");
            
            CREAR BASICOS+4 ESPACIOS;
            cout << char(201);
            for (int i = 0; i < 66; i++) cout << char(205);
            cout << char(187) << endl;
            this->ImprimirSaco();
            
            cout << endl << "Elija un artefacto: ";
            cin >> ind;
            
            while (!usarArtefacto(ind)) {
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << "     Elige un Artefacto Correcto\n";
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << "  Escriba una accion         :";
                flag = 0;
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
            CREAR BASICOS+4 ESPACIOS; cout << "Aprente una tecla para continuar: ";
            while (cin.get() != '\n');
        }

        if (a || r || f || s) {

            system("cls");
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
        CREAR BASICOS+4 ESPACIOS; cout << "Aprente una tecla para continuar: ";
        while (cin.get() != '\n');
        while (cin.get() != '\n');

    }
    
    system("cls");
    if ((avatar.GetVidaActual() <= 0)) {
        //CREAR BASICOS+4 ESPACIOS;cout << "HAS PERDIDO \n" << endl;
        flag = 0;
    } else {

        CREAR BASICOS+4 ESPACIOS;cout << "Ganaste la Batalla! Felicitaciones!\n" << endl;
        flag = 1;
       // cout << "tienes " << avatar.GetVidaActual() << " de vida\n" << endl;
        int num = rand() % 10;

        CREAR BASICOS+4 ESPACIOS;cout << "Te has ganado un:  \n\n";

    }
    cout << endl;
    CREAR BASICOS+4 ESPACIOS;cout << "Aprente una tecla para continuar: ";
    while (cin.get() != '\n');
}

void Juego::SetDibujador(Dibujador dibujador) {
    this->dibujador = dibujador;
}

Dibujador Juego::GetDibujador() const {
    return dibujador;
}

void Juego::dibujador2() {
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

CREAR BASICOS+8 ESPACIOS; printf("Nombre: ");
char nombre[200];
cin.getline(nombre,200);
if (strlen(nombre)>50) nombre[50]='\0';
avatar.SetNombre(nombre);
}
