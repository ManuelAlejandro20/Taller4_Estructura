#include "pch.h"
#include "Producto.h"


Producto::Producto()
{
}

Producto::Producto(string nombre, int cantInicial, int cantFinal, string tama�o)
{
	this->nombre = nombre;
	this->cantInicial = cantInicial;
	this->cantFinal = cantFinal;
	this->tama�o = tama�o;
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

string Producto::getTama�o()
{
	return this->tama�o;
}

Producto::~Producto()
{
}
