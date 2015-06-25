/* 
 * File:   FuncionesExtras.h
 * Author: Junior
 *
 * Created on 7 de junio de 2015, 01:07 AM
 */

#ifndef FUNCIONESEXTRAS_H
#define	FUNCIONESEXTRAS_H

void mostrarOpciones(); 
void mostrarOpcionesGenerales() ; 
void LecturaMoviento(char &c1);
int CargarMonstruos(Monstruo *&, int &);
void CargarArmas(Arma *&, Arma *&, int &, int &);
void CargarArmaduras(Armadura *&, int &);
void CargarPociones(PocionCuracion *&, int &);

#endif	/* FUNCIONESEXTRAS_H */

