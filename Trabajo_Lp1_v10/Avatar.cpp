#include "Entidad.h"
#include "Avatar.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

Avatar::Avatar() {
    this->SetPosX(3);
    this->SetPosY(3);
    this->SetMaxVida(1000);
    this->SetVidaActual(1000);
    this->SetDanhoBase(50);
    vidas=4;
    flagLabs=0;
}

//Avatar::Avatar(const Avatar& orig) {
//    this->SetPosX(orig.GetPosX()) ; 
//    this->SetPosY(orig.GetPosY()) ; 
//    this->SetMaxVida(orig.GetMaxVida()) ; 
//}

Avatar::~Avatar() {
}

void Avatar::mostrarDatosMapa(){
    CREAR BASICOS+4 ESPACIOS; cout << char(201);
    for(int i=0;i<66;i++) cout << char(205);
    cout << char(187) << endl ;
    CREAR BASICOS+4 ESPACIOS;cout << char(186) << "  Tu Datos!  "; CREAR GENERALES+7 ESPACIOS;cout << char(186) << endl;
    CREAR BASICOS+4 ESPACIOS;cout << char(186) << "  Vida: " << left << setw(4) << this->GetVidaActual() << "  ";
    for(int i=0;i<this->getVidas();i++) cout << char(3);
    if(this->getVidas()==4) cout << " (PRIMA)";
    if(this->getVidas()==3) cout << "  (BICA) ";
    if(this->getVidas()==2) cout << "   (TRICA)";
    if(this->getVidas()==1) cout << "    (CARTA)";
    CREAR BASICOS-10 ESPACIOS;cout << "Danho Base: " << left << setw(4) << this->GetDanhoBase() << " " << char(186) << endl;
    
    //Arma
    CREAR BASICOS+4 ESPACIOS;cout << char(186) << "  Arma: ";
    if(this->GetArma()!=NULL){
        cout<<left << setw(3) << this->GetArma()->GetNombre();
        for(int i=0;i<58-strlen(this->GetArma()->GetNombre());i++) cout << " ";cout << char(186) << endl;
    }
    else{
        cout << left << "No tienes";
        CREAR GENERALES+3 ESPACIOS;cout << char(186) << endl;
    }
   
    //Armadura
    CREAR BASICOS+4 ESPACIOS;cout << char(186) << "  Armadura: ";
    if(this->GetArmadura()!=NULL){
        cout << left << setw(3) << this->GetArmadura()->GetNombre(); 
        for(int i=0;i<54-strlen(this->GetArmadura()->GetNombre());i++) cout << " ";cout << char(186) << endl;
    }
    else{
        cout << left << "No tienes";
        CREAR GENERALES-1 ESPACIOS;cout << char(186) << endl;
    }
    
}

int Avatar::getVidas() const {
    return vidas;
}

void Avatar::setVidas(int vidas) {
    this->vidas = vidas;
}

void Avatar::setflagLabs(int flagLabs) {
    this->flagLabs = flagLabs;
}

int Avatar::getflagLabs() const {
    return flagLabs;
}