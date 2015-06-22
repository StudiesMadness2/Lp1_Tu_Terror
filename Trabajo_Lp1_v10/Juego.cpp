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
            posLaberintoActual -= 1; // Se mueve y se cambia de laberinto
            LaberintoActual = arreLaberintos[posLaberintoActual];
            avatar.SetPosX(LaberintoActual.getX_Sig());
            avatar.SetPosY(LaberintoActual.getY_sig());

        }
    } else if (LaberintoActual.getCelda()[ny][nx].GetTipo() == SIGUIENTE) {
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
    for (int f = -1; f < 2; f++) {
        for (int k = -1; k < 2; k++) { //recorrido alrededor del Avatar
            
            if (!(f == k) && !(k == (-f))) { // para evitar que revise la posicicion actual del Avatar y en cruz
                
                tipo = (char) LaberintoActual.getCelda()[y + f][x + k].GetTipo();
                
                if (tipo == MONSTRUO || tipo == ARTEFACTO) {
                    
                    int val, pelea;
                    flag = 1;
                    
                    switch (tipo) {
                        
                        case MONSTRUO:
                            pelea = PreguntarPelearConMonstruo(this->posLaberintoActual);
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

void impresionDeMonstruos() {
    int asciiMonster = rand() % 5;
    switch (asciiMonster) {
        case 0:
            printf("           \\                  /\n"
                    "    _________))                ((__________\n"
                    "   /.-------./\\    \\    /    //\\.--------.\\\n"
                    "  //#######//##\\   ))  ((   //##\\########\\\n"
                    " //#######//###((  ((    ))  ))###\\########\\\n"
                    "((#######((#####\\  \\  //  //#####))########))\n"
                    " \\##' `###\\######\\  \\)(/  //######/####' `##/\n"
                    "  )'    ``#)'  `##\\`->oo<-'/##'  `(#''     `(\n"
                    "          (       ``\\`..'/''       )\n"
                    "                     \\'''\n"
                    "                      `- )\n"
                    "                      / /\n"
                    "                     ( /\\  \n"
                    "                     /\\| \\\n"
                    "                    (  \\\n"
                    "                        )\n"
                    "                       /\n"
                    "                      (\n\n");
            break;
        case 1:
            printf("  ,/         \\.\n"
                    " ((           ))\n"
                    "  \\`.       ,'/\n"
                    "   )')     (`(\n"
                    " ,'`/       \\,`.\n"
                    "(`-(         )-')\n"
                    " \\-'\\,-'\"`-./`-/\n"
                    "  \\-')     (`-/\n"
                    "  /`'       `'\\\n"
                    " (  _       _  )\n"
                    " | ( \\     / ) |\n"
                    " |  `.\\   /,'  |\n"
                    " |    `\\ /'    |\n"
                    " (              )\n"
                    "  \\           /\n"
                    "   \\         /\n"
                    "    `.     ,'\n"
                    "hh    `-.-'\n\n");
            break;
        case 2:
            printf("              ._                                            ,\n"
                    "               (`)..                                    ,.-')\n"
                    "                (',.)-..                            ,.-(..`)\n"
                    "                 (,.' ,.)-..                    ,.-(. `.. )\n"
                    "                  (,.' ..' .)-..            ,.-( `.. `.. )\n"
                    "                   (,.' ,.'  ..')-.     ,.-( `. `.. `.. )\n"
                    "                    (,.'  ,.' ,.'  )-.-('   `. `.. `.. )\n"
                    "                     ( ,.' ,.'    _== ==_     `.. `.. )\n"
                    "                      ( ,.'   _==' ~  ~  `==_    `.. )\n"
                    "                       \\  _=='   ----..----  `==_   )\n"
                    "                    ,.-:    ,----___.  .___----.    -..\n"
                    "                ,.-'   (   _--====_  \\/  _====--_   )  `-..\n"
                    "            ,.-'   .__.'`.  `-_I0_-'    `-_0I_-'  .'`.__.  `-..\n"
                    "        ,.-'.'   .'      (          |  |          )      `.   `.-..\n"
                    "    ,.-'    :    `___--- '`.__.    / __ \\    .__.' `---___'    :   `-..\n"
                    "  -'_________`-____________'__ \\  (O)  (O)  / __`____________-'________`-\n"
                    "                              \\ . _  __  _ . /\n"
                    "                               \\ `V-'  `-V' |\n"
                    "                                | \\ \\ | /  /\n"
                    "                                 V \\ ~| ~/V\n"
                    "                                  |  \\  /|\n"
                    "                                   \\~ | V             - JGG\n"
                    "                                    \\  |\n"
                    "                                     VV\n\n");
            break;
        case 3:
            printf("                   .\n"
                    "                 ....8ob.\n"
                    "              o88888888888b.\n"
                    "          ..o888888888888888b..\n"
                    "          888888888888888P""888P\n"
                    "         8888888888888888888888.\n"
                    "        d88888888888888888888888bc.\n"
                    "       o8888888888888888" "\"38888Poo..\n"
                    "      .8888888888P888888        \"38888888\n"
                    "      88888888888 8888888eeeeee.   \"\"38\"8\n"
                    "     P\" 888888888 \"\"'\"\"\"       `\"\"o._.oP\n"
                    "        8888888888.\n"
                    "        88888888888\n"
                    "        '888888888 8b.\n"
                    "         \"88888888b  \"\"\"\"3booooooo..\n"
                    "          \"888888888888888b         \"b.\n"
                    "           \"8888888888888888888888b    \"8\n"
                    "            \"8888888888888888888888888   b\n"
                    "                \"\"888888888888888888888  c\n"
                    "                   \"8888888888888888888  P\n"
                    "                    \"88888888888888888888\"\n"
                    "                    .88888888888888888888\n"
                    "                   .888NICK8888888888888P    (c) by Nick 28.02.99\n"
                    "                 od888888888888888888P\n\n");
            break;
        case 4:
            printf("                 __\n"
                    "                / _\\ #\n"
                    "                \\c /  #\n"
                    "                / \\___ #\n"
                    "                \\`----`#==>  \n"
                    "                |  \\  #\n"
                    "     ,%.-\"\"\"---'`--'\\#_\n"
                    "    %%/             |__`\\\n"
                    "   .%'\\     |   \\   /  //\n"
                    "   ,%' >   .'----\\ |  [/\n"
                    "      < <<`       ||\n"
                    "       `\\\\       ||\n"
                    "         )\\\\      )\\\n\n");
            break;
    }
}

void Juego::MostrarDatosPrevioBatalla(Monstruo monster) {
    cout << endl << "El monstruo tiene:\n" << endl;
    cout << "vida: " << monster.GetMaxVida() << endl;
    cout << "Danho base: " << monster.GetDanhoBase() << endl;

    if (monster.GetArmadura() != NULL)
        cout << "armadura:" << monster.GetArmadura()->GetDefensa() << endl;
    else
        cout << "armadura: No tiene" << endl;
    if (monster.GetArma() != NULL) {
        cout << "arma (danho max): " << monster.GetArma()->GetDanhoMax() << endl;
        cout << "arma (danho min): " << monster.GetArma()->GetDanhoMin() << endl;
    } else
        cout << "arma: No tiene" << endl;

    cout << endl << "tienes " << this->GetAvatar().GetVidaActual() << " de vida actual\n" << endl;

    printf("\n\n Deseas pelear con el monstruo ('yes' or 'no') ?   ");
}

int Juego::PreguntarPelearConMonstruo(int numLab) {

    PlaySound(NULL, NULL, 0);
    PlaySound(("Doom_Level_1.wav"), NULL, SND_ASYNC);
    char linea[30];
    Monstruo monster;
    system("cls");

    impresionDeMonstruos();
    MostrarDatosPrevioBatalla(monster);
    gets(linea);
    int yes, no, flag;

    while (1) {
        yes = (strcmp(linea, "yes") == 0) ? 1 : 0; //si es igual a "yes"
        no = (strcmp(linea, "no") == 0) ? 1 : 0; // si es igual a "no"
        if (yes || no) break; //Si responde correctamente sale del bucle
        printf("Tienes que escribir \"yes\" o \"no\" :  ");
        gets(linea);
    }
    if (yes) { // en caso acepte la batalla
        PelearConMonstruo(monster, flag);
    }
    return flag;
}

void imprimirAtaqueMonstruo() {
    cout << "El Curso usa ";
    int num = rand() % 5;
    switch (num) {
        case 0:
            cout << "Final imposible" << endl;
            break;
        case 1:
            cout << "Prueba tipo C" << endl;
            break;
        case 2:
            cout << "Laboratorio innovador" << endl;
            break;
        case 3:
            cout << "Parcial Nivel asiatico" << endl;
            break;
        case 4:
            cout << "Practica Troll" << endl;
            break;
    }
}

void imprimirContraAtaqueMonstruo() {
    cout << "Usaste :";
    int num = rand() % 6;
    switch (num) {
        case 0:
            cout << "Kit Completo en Tetrix" << endl;
            break;
        case 1:
            cout << "Planchon salvaje" << endl;
            break;
        case 2:
            cout << "Usb salvador" << endl;
            break;
        case 3:
            cout << "Estudiar con anticipacion" << endl;
            break;
        case 4:
            cout << "Amanecida Hardcore" << endl;
            break;
        case 5:
            cout << "Camara de entrenamiento de Goku" << endl;
            break;
    }
    cout << endl;

}

void Juego::PelearConMonstruo(Monstruo monster, int &flag) {

    int max = 0;
    if (monster.GetArma() != NULL) max = monster.GetArma()->GetDanhoMax();
    int min = 0;
    if (monster.GetArma() != NULL) min = monster.GetArma()->GetDanhoMin();

    int aleatorioMonster = rand() % (max - min + 1);
    int danhoM = monster.GetDanhoBase() + aleatorioMonster;

    max = 0;
    if (avatar.GetArma() != NULL) max = avatar.GetArma()->GetDanhoMax();
    min = 0;
    if (avatar.GetArma() != NULL) min = avatar.GetArma()->GetDanhoMin();

    int aleatorioAvatar = rand() % (max - min + 1);
    int danhoA = avatar.GetDanhoBase() + aleatorioAvatar;
    system("cls");
    while ((avatar.GetVidaActual() > 0) && (monster.GetVidaActual() > 0)) {

        char opcion;

        cout << "Elija una opcion: " << endl;
        cout << "a) Atacar!" << endl;
        cout << "f) Retirarse del curso" << endl << endl << "? ";
        cin >> opcion;

        while (1) {
            
            int a = (opcion=='a') ? 1:0;
            int f = (opcion=='f') ? 1:0;
            
            if (a || f ) break;
            
            cout << "Debe seleccionar una de las dos opciones ";
            cin >> opcion;
        }
        if (opcion == 'a') {
            imprimirAtaqueMonstruo();
            imprimirContraAtaqueMonstruo();

            if (avatar.GetArmadura() != NULL) {
                danhoM = (int) (danhoM - (avatar.GetArmadura()->GetDefensa()/10));
            }
            int vidaActualAvatar = avatar.GetVidaActual();
            avatar.SetVidaActual(vidaActualAvatar - danhoM);

            if (monster.GetArmadura() != 0) {
                danhoA = (int) (danhoA - (monster.GetArmadura()->GetDefensa()/10));
            }
            monster.SetVidaActual(monster.GetVidaActual() - danhoA);
        }
        if (opcion == 'f'){
            system("cls");
            int huida = rand() %101;
            if(huida <25){
                cout << "Te retiraste del curso" << endl;
                break;
            }
            else{
                cout << "No has podido retirarte del curso :( " << endl;
                cout << "sigue luchando campeon!\n" << endl;
            }
        }
        cout << "El monstruo tiene " << monster.GetVidaActual() << "de vida\n" << endl;
        cout << "tienes " << avatar.GetVidaActual() << " de vida\n" << endl;

    }

    if ((avatar.GetVidaActual() <= 0)) {
        cout << "HAS PERDIDO\n" << endl;
        flag = 0;
    } else {

        cout << "Ganaste la Batalla! Felicitaciones!\n" << endl;
        flag = 1;
        cout << "tienes " << avatar.GetVidaActual() << " de vida\n" << endl;
        int num = rand() % 10;

        cout << "Te has ganado un:  \n\n";

    }



    cout << "Aprente una tecla para continuar: ";
    while (cin.get() != '\n');

}

void Juego::SetDibujador(Dibujador dibujador) {
    this->dibujador = dibujador;
}

Dibujador Juego::GetDibujador() const {
    return dibujador;
}

void Juego::dibujarEsquema() {
    int posX_Avatar = this->avatar.GetPosX();
    int m = this->LaberintoActual.getM();
    int n = this->LaberintoActual.getN();
    int posY_Avatar = this->avatar.GetPosY();
    int mitad_ancho = this->dibujador.GetA();
    int mitad_alto = this->dibujador.GetB();
    
    int i_arriba, i_abajo, j_izq, j_der;
    i_arriba = posY_Avatar - mitad_alto;
    
    if (i_arriba < 0) i_arriba = 0;
    i_abajo = posY_Avatar + mitad_alto;
    
    if (i_abajo > m - 1) i_abajo = m - 1;
    j_izq = posX_Avatar - mitad_ancho;
    
    if (j_izq < 0) j_izq = 0;
    j_der = posX_Avatar + mitad_ancho;
    
    if (j_der > n - 1) j_der = n - 1;
    //for (int k = 0; k < 40 - (j_der - j_izq) / 2; k++)printf(" ");
    
    system("cls");
    
    for (int i = i_arriba; i <= i_abajo; i++) {
        //     for (int k = 0; k < 40 - (j_der - j_izq) / 2; k++)printf(" "); // Para poder centrar el esquema

        for (int j = j_izq; j <= j_der; j++) {
            
            char celda = (char) this->LaberintoActual.getCelda()[i][j].GetTipo();
            
            if (avatar.GetPosX() == j && avatar.GetPosY() == i) {
                rlutil::setColor(114);
                printf("%c", IMAG_AVATAR);
            }
            else if (celda == '-' || celda == '+') {
                rlutil::setColor(121); // Entra  y Sale
                printf("%c", celda);
            } 
            else if (celda == 'M' ||
                    celda == 'A') {
                rlutil::setColor(124);
                printf("%c", celda);
            } 
            else {
                rlutil::setColor(112); // 96 176 112
                printf("%c", celda);
            }
        }
        printf("\n");
    }
    rlutil::setColor(7); // Restablece Co
    printf("\n");
    //   for (int k = 0; k < 40 - (j_der - j_izq) / 2; k++)printf(" ");
    //printf("====Esquema_Avatar====\n");
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
    for (int i = 0; i < 36; i++) cout << " ";
    cout << char(186);
    for (int i = 0; i < 66; i++) cout << " ";
    cout << char(186) << endl;
    for (int i = 0; i < 36; i++) cout << " ";
    cout << char(186) << "  Elementos en el Saco: ";
    for (int i = 0; i < 42; i++) cout << " ";
    cout << char(186) << endl;
    for (int i = 0; i < this->avatar.GetSaco().GetIndice(); i++) {
        for (int j = 0; j < 36; j++) cout << " ";
        cout << char(186) << "  " << right << setw(2) << i << "  ";
        this->avatar.GetSaco()[i]->Imprimir();
    }
    for (int i = 0; i < 36; i++) cout << " ";
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