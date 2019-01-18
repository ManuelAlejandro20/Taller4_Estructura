#pragma once
#include <ctime> // Para calcular el tiempo de ejecucion del programa
#include "Utilidades.h"
#include "Producto.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <ios>

using namespace utilidades;

class SistemaJumbottusImpl
{
public:

	SistemaJumbottusImpl();

	void LeerProductos();

	void SolucionSecuencial();
	void SolucionParalela(int cantHilos);

	void SolucionParalelaMayor(Producto * productoActual, string * productosRobadosV, int * perdidasV, int posActual);
	void SolucionParalelaMenor(string * productosRobadosV, int * perdidasV, int posInicial, int posFinal);

	void SolucionSecuencial2();

	int CantVendidos(string nombreProducto);

	float CalcularBonusProgramador();
	bool AmbasSolucionesEjecutadas();

	~SistemaJumbottusImpl();

private:

	vector<Producto*> productos;

	float tiempoSolucionSecuencial;
	float tiempoSolucionParalelo;
};

