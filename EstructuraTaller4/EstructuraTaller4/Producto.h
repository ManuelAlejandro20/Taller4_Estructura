#pragma once
#include <iostream>

using namespace std;

class Producto
{
public:

	Producto();
	Producto(string nombre, int cantInicial, int cantFinal, string tama�o);

	string getNombre();
	int getCantInicial();
	int getCantFinal();
	string getTama�o();

	~Producto();
private:
	
	/*
		Aunque el atributo cantInicial es completamente presindible para solucionar
		la problematica propuesta, se incluye de igual manera
	*/

	string nombre;
	int cantInicial;
	int cantFinal;
	string tama�o;
};

