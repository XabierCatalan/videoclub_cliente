/*
 * cliente.h
 *
 *  Created on: 22 may 2023
 *      Author: Usuario
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

class Cliente {
private:
	int id;
	char* nombre;
	char* mail;
	char* contra;
	float saldo;
public:
	Cliente();
	virtual ~Cliente();
	char* getNombre();
	char* getContra();

};

#endif /* CLIENTE_H_ */
