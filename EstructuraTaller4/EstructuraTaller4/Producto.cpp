#include "pch.h"
#include "Producto.h"


Producto::Producto()
{
}

Producto::Producto(string nombre, int cantInicial, int cantFinal, string tamaño)
{
	this->nombre = nombre;
	this->cantInicial = cantInicial;
	this->cantFinal = cantFinal;
	this->tamaño = tamaño;
}


string Producto::getNombre()
{
	return this->nombre;
}

int Producto::getCantInicial()
{
	return this->cantInicial;
}

int Producto::getCantFinal()
{
	return this->cantFinal;
}

string Producto::getTamaño()
{
	return this->tamaño;
}

Producto::~Producto()
{
}
