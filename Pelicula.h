/*
 * Pelicula.h
 *
 *  Created on: 23 may 2023
 *      Author: Usuario
 */

#ifndef PELICULA_H_
#define PELICULA_H_

class Pelicula {
public:
	int id_pelicula;
	char *titulo;
	char *genero;  //crear una tabla en la base de datos con cod_genero y genero
	char *director;
	char *formato;  //crear una tabla en la base de datos con cod_formato y formato
	float precio;
	int cantidad;
	Pelicula();
	Pelicula(int id_pelicula, char *titulo, char *genero,
			char *director, char *formato, float precio, int cantidad);
	virtual ~Pelicula();
	void imprimirPeli();
	void imprimirPeliculas(Pelicula* p, int cant);

};

#endif /* PELICULA_H_ */
