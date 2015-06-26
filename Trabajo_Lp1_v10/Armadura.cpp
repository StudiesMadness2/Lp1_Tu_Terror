#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include "Artefacto.h"
#include "Armadura.h"
#include "Arma.h"
#include "Entidad.h"
using namespace std;

Armadura::Armadura(int def) {
    SetTipo(1);
    SetDefensa(def);
    nombre = NULL;
}

Armadura::~Armadura() {
}

void Armadura::AsignarArmadura(int def, char *name) {
    defensa = def;
    nombre = new char[strlen(name) + 1];
    strcpy(nombre, name);
}

void Armadura::SetDefensa(int defensa) {
    this->defensa = defensa;
}

int Armadura::GetDefensa() const {
    return defensa;
}

void Armadura::Imprimir() {
    cout << "Armadura: " << left << setw(20) << nombre << " - Defensa      : " << left << setw(3) << defensa << "         " << char(186) << endl;
}



void Armadura::usar(class Entidad &E, int ind) {
    if (E.GetArmadura() == NULL) {
        E.SetArmadura(this);
        E.botarArtefacto(ind);
    } else {
        Armadura *aux = this;
        Armadura *actual = E.GetArmadura();
        E.botarArtefacto(ind);
        E.agregarArtefactoAlSaco(actual, 1);
        E.SetArmadura(aux);
    }
}

void Armadura::SetNombre(char* nombre) {
    this->nombre = new char[strlen(nombre)+1];
    strcpy(this->nombre,nombre);
}

char* Armadura::GetNombre() const {
    return nombre;
}