/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 5 de junio de 2015, 10:57 AM
 */
#include "Constantes.h"
#include <cstdlib>
#include <cstdio>
#include "Juego.h"
#include "FuncionesExtras.h"
#include "Monstruo.h"
#include "Arma.h"
#include "Armadura.h"
#include "PocionCuracion.h"

#include <unistd.h>

#include "Artefacto.h"
#include <WINDOWS.h> 
#include <MMSystem.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    //system("mode CON: COLS=50");
    system("mode 140, 45");
    PlaySound(("castlevania.wav"), NULL, SND_ASYNC); //funcion para iniciar un sonido
    char c1;
    int flag = 1, numM, numAM, numAA, numAd, numP;
    Monstruo *Mons;
    Arma *ArmA, *ArmM;
    Armadura *Armd;
    PocionCuracion *Poc;
    historiaDelJuego();
    Juego nuevoJuego;
    Dibujador dibujadorNuevo;
    dibujadorNuevo.SetA(10);
    dibujadorNuevo.SetB(10);
    nuevoJuego.SetDibujador(dibujadorNuevo);
    nuevoJuego.CargarLaberintos();
    nuevoJuego.iniciarPosicionAvatar();
    // nuevoJuego.GetLaberintoActual().impresion(); //<--- elmetodo de impresio(despues borrarlo))
    // nuevoJuego.GetAvatar().impresionInformacionAvatar() ; 

    // Monstruos 
    CargarMonstruos(Mons, numM);
    // Artefactos 
    CargarArmas(ArmA, ArmM, numAA, numAM);
    CargarArmaduras(Armd, numAd);
    CargarPociones(Poc, numP);


    //    Arma aaa;
    //    Armadura arm;
    //    arm.AsignarArmadura(100, "Armadura 1");
    //    arm.Imprimir();
    //    aaa.AsignarArma(10, 200, "Arma 1");
    //    aaa.Imprimir();
    //    cout << endl;
    //    Saco sss;
    //    sss.AgregarAlSaco(&aaa);
    //    sss.AgregarAlSaco(&arm);
    //    sss[0]->Imprimir();
    //    sss[1]->Imprimir();





    PlaySound(NULL, NULL, 0); //Funcion para detener un sonido
    PlaySound(("Doom_2-Level_1.wav"), NULL, SND_ASYNC);
    while (1) {
        if (flag == 1) {
            // nuevoJuego.dibujarEsquema();            
            nuevoJuego.dibujador2();
            nuevoJuego.GetAvatar().mostrarDatosMapa();
            nuevoJuego.ImprimirSaco();
            mostrarOpcionesGenerales();
        }

        LecturaMoviento(c1);
        if (c1 == DIR_ARRIBA || c1 == DIR_ABAJO || c1 == DIR_DERECHA || c1 == DIR_IZQUIERDA && c1 != FIN) {
            nuevoJuego.intentarmosMoverAvatar(c1, flag);
            if (c1 == FIN) {
                MessageBox(NULL, "Y0U WIN", "Congratulations", MB_OK);
                printf("\nYOU WIN :D\n");
                break;
            }
        } else if (c1 == 'a') { // iteractuira con el monstruo o artefacto
            nuevoJuego.intentamosInteractuarAvatar(numAA, numAd, numP, ArmA, Armd, Poc, flag);
        } else if (c1 == 's') { // usar algo 
            printf("s");
            int ind;
            scanf("%d", &ind);
            if (!nuevoJuego.usarArtefacto(ind)) {
                cout << "     Elige un Artefacto Correcto\n";
                cout << "- Escriba una accion         :";
                flag = 0;
            } else {
                sleep(3); // 
                flag = 1;
            }

        } else if (c1 == FIN) { // Falta reconocoer Escape
            MessageBox(NULL, "CLOSE SUCCESFULLY", "Why bro !!!", MB_OK);
            printf("\n>>>>CLOSE SUCCESFULLY<<<<\n");
            break;
        } else flag = 0;
    }
    return 0;
}