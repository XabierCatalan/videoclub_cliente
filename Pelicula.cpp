/*
 * Pelicula.cpp
 *
 *  Created on: 23 may 2023
 *      Author: Usuario
 */

#include "Pelicula.h"
#include "string.h"
#include <iostream>

Pelicula::Pelicula() {
	this->id_pelicula=0;
		this->titulo=NULL;
		this->genero=NULL;
		this->director=NULL;
		this->formato=NULL;
		this->precio=0;
		this->cantidad=0;

}
Pelicula::Pelicula(int id_pelicula, char *titulo, char *genero,
			char *director, char *formato, float precio, int cantidad){
	this->id_pelicula=id_pelicula;
	this->titulo=titulo;
	this->genero=genero;
	this->director=director;
	this->formato=formato;
	this->precio=precio;
	this->cantidad=cantidad;
}

Pelicula::~Pelicula() {
	// TODO Auto-generated destructor stub
}

void Pelicula::imprimirPeli(){
	printf("Id_Pelicula: %i | Titulo: %s | Genero: %s | Director: %s | Formato: %s | Precio: %.2f | Cantidad: %i \n ",
			this->id_pelicula, this->titulo, this->genero , this->director, this->formato, this->precio, this->cantidad);
}
//void Pelicula::imprimirPeliculas(Pelicula* p, int cant){
//	for (int i = 0; i < cant; ++i) {
//		p[i].imprimirPeli;
//	}
//}
