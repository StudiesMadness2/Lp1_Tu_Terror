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
    
    //Arma
    for(int i=0;i<36;i++) cout << " ";cout << char(186) << "  Arma: ";
    if(this->GetArma()!=NULL){
        cout<<left << setw(3) << this->GetArma()->GetNombre();
        for(int i=0;i<58-strlen(this->GetArma()->GetNombre());i++) cout << " ";cout << char(186) << endl;
    }
    else{
        cout << left << "No tiene";
        for(int i=0;i<50;i++) cout << " ";cout << char(186) << endl;
    }
   
    //Armadura
    for(int i=0;i<36;i++) cout << " ";cout << char(186) << "  Armadura: ";
    if(this->GetArmadura()!=NULL){
        cout << left << setw(3) << this->GetArmadura()->GetNombre(); 
        for(int i=0;i<54-strlen(this->GetArmadura()->GetNombre());i++) cout << " ";cout << char(186) << endl;
    }
    else{
        cout << left << "No tiene";
        for(int i=0;i<46;i++) cout << " ";cout << char(186) << endl;
    }
    
}