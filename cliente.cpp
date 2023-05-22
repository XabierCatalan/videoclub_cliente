/*
 * cliente.cpp
 *
 *  Created on: 22 may 2023
 *      Author: Usuario
 */

#include "cliente.h"
#include <iostream>
#include <stdio.h>

Cliente::Cliente() {
	this->id=0;
	nombre=NULL;
	mail=NULL;
	contra=NULL;

}

Cliente::~Cliente() {
	// TODO Auto-generated destructor stub
}

char* Cliente::getNombre(){
	return this->nombre;
}
char* Cliente::getContra(){
	return this->contra;
}
