/* 
 * File:   Armadura.cpp
 * Author: alulab14
 * 
 * Created on 5 de junio de 2015, 11:15 AM
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include "Artefacto.h"
#include "Armadura.h"
using namespace std;

Armadura::Armadura(int def) {
    SetTipo(1); 
    SetDefensa(def);
    nombre = NULL;
}

Armadura::~Armadura() {
}

void Armadura::AsignarArmadura(int def, char *name){
    defensa = def;
    nombre = new char[strlen(name)+1];
    strcpy(nombre, name);
}

void Armadura::SetDefensa(int defensa) {
    this->defensa = defensa;
}

int Armadura::GetDefensa() const {
    return defensa;
}

void Armadura::Imprimir(){
    cout << left << setw(15)<< "Armadura"<<"|  " << left << setw(35) << nombre <<"|  " << " - Defensa      : "<<right<<setw(10) << defensa << endl;
}

void Armadura ::  usar(){
    cout << "uso Armadura \n";
}