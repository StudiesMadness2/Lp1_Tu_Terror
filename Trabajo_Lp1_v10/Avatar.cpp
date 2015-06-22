#include "Entidad.h"
#include "Avatar.h"
#include <iostream>
#include <iomanip>

using namespace std;

Avatar::Avatar() {
    this->SetPosX(3);
    this->SetPosY(3);
    this->SetMaxVida(1000);
    this->SetVidaActual(1000);
    this->SetDanhoBase(120);
}

//Avatar::Avatar(const Avatar& orig) {
//    this->SetPosX(orig.GetPosX()) ; 
//    this->SetPosY(orig.GetPosY()) ; 
//    this->SetMaxVida(orig.GetMaxVida()) ; 
//}

Avatar::~Avatar() {
}

void Avatar::mostrarDatosMapa(){
    cout << endl;
    for(int i=0;i<36;i++) cout << " "; cout << char(201);
    for(int i=0;i<66;i++) cout << char(205);
    cout << char(187) << endl ;
    for(int i=0;i<36;i++) cout << " ";cout << char(186) << "  Vida: " << left << setw(4) << this->GetVidaActual() ;
    for(int i=0;i<35;i++) cout << " ";cout << "Danho Base: " << left << setw(4) << this->GetDanhoBase() << "   " << char(186) << endl;
    for(int i=0;i<36;i++) cout << " ";cout << char(186) << "  X: " << left << setw(3) << this->GetPosX() << " Y: " << left << setw(3) << this->GetPosY(); 
    for(int i=0;i<51;i++) cout << " ";cout << char(186) << endl;
}