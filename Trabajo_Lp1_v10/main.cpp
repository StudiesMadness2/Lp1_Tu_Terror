#include "Constantes.h"
#include <cstdlib>
#include <cstdio>
#include "Juego.h"
#include "FuncionesExtras.h"
#include "Monstruo.h"
#include "Arma.h"
#include "Armadura.h"
#include "PocionCuracion.h"
#include "Laberinto.h"
#include "Artefacto.h"
#include <WINDOWS.h> 
#include <MMSystem.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    
    system("mode 140, 45");
    PlaySound(("castlevania.wav"), NULL, SND_ASYNC); //funcion para iniciar un sonido
    char opcion,cadena[50] ; 
    int flag = 1, numM, numAM, numAA, numAd, numP, flagLoser=0;    
    
    Juego nuevoJuego;

    Monstruo *Mons;
    Arma *ArmA, *ArmM;
    Armadura *Armd;
    PocionCuracion *Poc;
    
    nuevoJuego.historiaDelJuego();
    
    // Monstruos 
    int MaxLevel = CargarMonstruos(Mons, numM);
    // Artefactos 
    CargarArmas(ArmA, ArmM, numAA, numAM);
    CargarArmaduras(Armd, numAd);
    CargarPociones(Poc, numP);


    Dibujador dibujadorNuevo;
    dibujadorNuevo.SetA(10);
    dibujadorNuevo.SetB(8);

    nuevoJuego.SetDibujador(dibujadorNuevo);
    nuevoJuego.CargarLaberintos(MaxLevel);
    nuevoJuego.iniciarPosicionAvatar();

    nuevoJuego.distribuirMonstruosXLaberinto(Mons, numM, ArmM, numAM, Armd, numAd, Poc, numP);

    PlaySound(NULL, NULL, 0); //Funcion para detener un sonido
    PlaySound(("Doom_2-Level_1.wav"), NULL, SND_ASYNC);
    while (1) {
        if (flag == 1) {   
            nuevoJuego.dibujadorDeEsquema();
            nuevoJuego.GetAvatar().mostrarDatosMapa();
            nuevoJuego.ImprimirSaco();
            mostrarOpcionesGenerales();
        }
        LecturaMoviento(opcion);
        int ind;

        if (opcion == DIR_ARRIBA || opcion == DIR_ABAJO || opcion == DIR_DERECHA || opcion == DIR_IZQUIERDA && opcion != FIN) {
            nuevoJuego.intentarmosMoverAvatar(opcion, flag);
            if (opcion == FIN) {
                MessageBox(NULL, "Y0U WIN", "Congratulations", MB_OK);
                CREAR BASICOS ESPACIOS;printf("\nYOU WIN :D\n");
                break;
            }
        } else if (opcion == 'a') { // iteractuira con el monstruo o artefacto

            nuevoJuego.intentamosInteractuarAvatar(numAA, numAd, numP, ArmA, Armd, Poc, flag, flagLoser);
            if(flagLoser==1){
                system("cls");
                Laberinto final;
                final = nuevoJuego.FinalDelJuego();
                final.impresion();
                //DIBUJAR TODO EL LABERINTO
                MessageBox(NULL, "Y0U LOSE", "Rayos! Esfuerzate mas...", MB_OK);
                CREAR BASICOS ESPACIOS; printf("\nPerdiste :(\n");
                break;
            }

        } else if (opcion == 's') { // usar algo 
            printf("s");            
            while (scanf("%d", &ind) == 0) {
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << "  Escriba un indice correcto             :s";
                gets(cadena);
            }
            if (!nuevoJuego.usarArtefacto(ind)) {
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << "     Elige un Artefacto Correcto\n";
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << "  Escriba una accion         :";
                flag = 0;
            } else {
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << " Se utilizo el artefacto correctamente " << endl;
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << " Cargando ... " << endl;
                nuevoJuego.tiempo(2);
                flag = 1;
            }
        } else if (opcion == 'b') {
            printf("%b");            
            while (scanf("%d", &ind) == 0) {
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << "  Escriba un indice correcto             :s";
                gets(cadena);
            }
            if (!nuevoJuego.botarArtefacto(ind)) {
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << "     Elige un Artefacto Correcto\n";
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << "  Escriba una accion         :";
                flag = 0;
            }
            else {
              //  nuevoJuego.botarArtefactoGrafico();
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << "Se boto y perdio el artefacto :( " << ind << endl;
                for (int i = 0; i < 46; i++) putchar(' ');
                cout << " Cargando ... " << endl;
                nuevoJuego.tiempo(2);
                flag = 1;
            }
            // botar 
        } else if (opcion == FIN) { // Falta reconocoer Escape
            MessageBox(NULL, "CLOSE SUCCESFULLY", "Why bro !!!", MB_OK);
            putchar('\n');
            for (int i = 0; i < 56; i++) cout << " ";
            printf(">>>>CLOSE SUCCESFULLY<<<<\n");
            break;
        } else flag = 0;
    }
    return 0;
}