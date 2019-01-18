#include "pch.h"
#include "SistemaJumbottusImpl.h"


SistemaJumbottusImpl::SistemaJumbottusImpl()
{

	this->tiempoSolucionSecuencial = 0;
	this->tiempoSolucionParalelo = 0;
	LeerProductos();
}

void SistemaJumbottusImpl::LeerProductos()
{
	string linea; // Crea un string en el que guarda cada linea de texto
	ifstream archivo;
	archivo.open("Stock.txt"); // Abre el archivo con los productos

	if (archivo.fail()) { // Si el archivo no existe o no se encuentra registra el error

		cout << "No se pudo abrir el archivo Stock.txt" << endl;

		system("PAUSE");
	}

	while (getline(archivo, linea)) { // Lee el archivo linea por linea

		stringstream ss(linea); // Permite extraer cadenas de texto de la linea

		while (!ss.eof()) { // Minetras la linea no se haya acabado

			string nombreProducto;
			string cantInicialStr;
			string cantFinalStr;
			string tamaño;

			int cantInicial = 0;
			int cantFinal = 0;

			getline(ss, nombreProducto, ',');
			getline(ss, cantInicialStr, ',');
			getline(ss, cantFinalStr, ',');
			getline(ss, tamaño, ',');

			/*
				Para facilitar las comparaciones entre strings
			*/

			toUpper(nombreProducto);
			toUpper(tamaño);

			try {

				cantInicial = stoi(cantInicialStr);
				cantFinal = stoi(cantFinalStr);

			}
			catch (...) {

			}

			Producto* nuevoProducto = new Producto(nombreProducto, cantInicial, cantFinal, tamaño);

			productos.push_back(nuevoProducto);
		}
	}
	archivo.close(); // Se cierra el archivo
}

void SistemaJumbottusImpl::SolucionSecuencial()
{

	unsigned tiempoInicial = clock(); // Inicio de la medicion del tiempo de ejecucion de la funcion

	int perdidasTotales = 0; // La cantidad de dinero que se perdio en total por los robos

	for (int i = 0; i < productos.size(); i++) {

		Producto* productoActual = productos[i];

		string nombreProducto = productoActual->getNombre();
		int cantInicial = productoActual->getCantInicial();
		int cantFinal = productoActual->getCantFinal();
		string tamaño = productoActual->getTamaño();

		int cantVendidaReal = CantVendidos(nombreProducto);
		int cantVendidaTeorica = cantInicial - cantFinal;
		int productosRobados = cantVendidaTeorica - cantVendidaReal;

		if (productosRobados != 0) {

			int perdidas;

			if (tamaño == "CHICO") { // Se calculan las perdidas del robo dependiendo del tamaño del producto

				perdidas = productosRobados * 10;
			}
			else {

				perdidas = productosRobados * 50;
			}

			toCapitalize(nombreProducto); // Se retorna el nombre del producto al original

			cout << "\n- " + nombreProducto + "; Cantidad Robada: " + to_string(productosRobados) + "; Monto de la perdida: $" + to_string(perdidas) << endl; // Se despliega la informacion del producto robado

			perdidasTotales += perdidas; // Se aumentan las perdidas totales
		}

	}

	if (perdidasTotales != 0) { // Si habian productos robados

		cout << "\n\nPerdidas Totales: $" + to_string(perdidasTotales) << endl;
	}
	else {

		cout << "\nNINGUN PRODUCTO HA SIDO ROBADO" << endl;
	}

	unsigned tiempoFinal = clock(); // Termino de la medicion del tiempo de ejecucion

	this->tiempoSolucionSecuencial = (double(tiempoFinal - tiempoInicial) / CLOCKS_PER_SEC);

	cout << "\nTiempo de Ejecucion: " + to_string(tiempoSolucionSecuencial) + " segundos\n" << endl;
}

void SistemaJumbottusImpl::SolucionParalela(int cantHilos)
{
	/*
		Suponemos dos casos que trataremos de por separado:

		1- Cuando la cantidad de hilos es mayor o igual a la cantidad de productos

		2- Cuando la cantidad de hilos es menor a la cantidad de productos
	*/

	unsigned tiempoInicial = clock(); // Inicio de la medicion del tiempo de ejecucion de la funcion

	int perdidasTotales = 0;
	int * perdidas = new int[productos.size()];
	string * productosRobados = new string[productos.size()];

	vector<thread> hilos;

	for (int i = 0; i < productos.size(); i++) {

		perdidas[i] = 0;
		productosRobados[i] = "";
	}

	if (cantHilos >= productos.size()) {

		for (int i = 0; i < productos.size(); i++) {

			hilos.push_back(thread(&SistemaJumbottusImpl::SolucionParalelaMayor, this, productos[i], productosRobados, perdidas, i));
		}

		for (int i = 0; i < hilos.size(); i++) {

			hilos[i].join();
		}

		for (int i = 0; i < productos.size(); i++) {

			if (productosRobados[i] != "") {

				cout << productosRobados[i] << endl;
			}

			perdidasTotales += perdidas[i];
		}

	}
	else {

		int cantElementosPorParticion = ceil((float)productos.size() / (float)cantHilos); // Cuantos elementos debe tener cada seccion del vector. Usamos la funcion techo para tener una aproximacion directa, para que la funcion techo funcione debemos castear los elementos a dividir como float

		for (int i = 0; i < cantHilos; i++) {

			int posInicial = i * cantElementosPorParticion;
			int posFinal = posInicial + cantElementosPorParticion;

			// Estas condicionales solo sirven si el vector tiene un tamaño impar. Si el tamaño del vector es par no afectara en nada

			if (posInicial < productos.size()) { // Si la posicion inicial no esta fuera del vector

				if (posFinal > productos.size()) { // Si la posicion final es mayor a la cantidad de elementos que hay en el vector se ajusta

					posFinal = productos.size();
				}

				hilos.push_back(thread(&SistemaJumbottusImpl::SolucionParalelaMenor, this, productosRobados, perdidas, posInicial, posFinal));
			}
		}

		for (int i = 0; i < hilos.size(); i++) {

			hilos[i].join();
		}

		for (int i = 0; i < productos.size(); i++) {

			if (productosRobados[i] != "") {

				cout << productosRobados[i] << endl;
			}

			perdidasTotales += perdidas[i];
		}
	}


	if (perdidasTotales != 0) { // Si habian productos robados

		cout << "\n\nPerdidas Totales: $" + to_string(perdidasTotales) << endl;
	}
	else {

		cout << "\nNINGUN PRODUCTO HA SIDO ROBADO" << endl;
	}

	unsigned tiempoFinal = clock(); // Termino de la medicion del tiempo de ejecucion

	this->tiempoSolucionParalelo = (double(tiempoFinal - tiempoInicial) / CLOCKS_PER_SEC);

	cout << "\nTiempo de Ejecucion: " + to_string(tiempoSolucionParalelo) + " segundos\n" << endl;
}

void SistemaJumbottusImpl::SolucionParalelaMayor(Producto * productoActual, string * productosRobadosV, int * perdidasV, int posActual)
{

	string nombreProducto = productoActual->getNombre();
	int cantInicial = productoActual->getCantInicial();
	int cantFinal = productoActual->getCantFinal();
	string tamaño = productoActual->getTamaño();

	int cantVendidaReal = CantVendidos(nombreProducto);
	int cantVendidaTeorica = cantInicial - cantFinal;
	int productosRobados = cantVendidaTeorica - cantVendidaReal;

	if (productosRobados != 0) {

		int perdidas;

		if (tamaño == "CHICO") { // Se calculan las perdidas del robo dependiendo del tamaño del producto

			perdidas = productosRobados * 10;
		}
		else {

			perdidas = productosRobados * 50;
		}

		toCapitalize(nombreProducto); // Se retorna el nombre del producto al original

		productosRobadosV[posActual] = "\n" + to_string(posActual + 1) + ") " + nombreProducto + "; Cantidad Robada: " + to_string(productosRobados) + "; Monto de la perdida: $" + to_string(perdidas);
		perdidasV[posActual] = perdidas;
	}
}

void SistemaJumbottusImpl::SolucionParalelaMenor(string * productosRobadosV, int * perdidasV, int posInicial, int posFinal)
{

	for (int i = posInicial; i < posFinal; i++) {

		Producto* productoActual = productos[i];

		string nombreProducto = productoActual->getNombre();
		int cantInicial = productoActual->getCantInicial();
		int cantFinal = productoActual->getCantFinal();
		string tamaño = productoActual->getTamaño();

		int cantVendidaReal = CantVendidos(nombreProducto);
		int cantVendidaTeorica = cantInicial - cantFinal;
		int productosRobados = cantVendidaTeorica - cantVendidaReal;

		if (productosRobados != 0) {

			int perdidas;

			if (tamaño == "CHICO") { // Se calculan las perdidas del robo dependiendo del tamaño del producto

				perdidas = productosRobados * 10;
			}
			else {

				perdidas = productosRobados * 50;
			}

			toCapitalize(nombreProducto); // Se retorna el nombre del producto al original

			productosRobadosV[i] = "\n" + to_string(i + 1) + ") " + nombreProducto + "; Cantidad Robada: " + to_string(productosRobados) + "; Monto de la perdida: " + to_string(perdidas);
			perdidasV[i] = perdidas;
		}
	}
}


void SistemaJumbottusImpl::SolucionSecuencial2()
{
	unsigned tiempoInicial = clock(); // Inicio de la medicion del tiempo de ejecucion de la funcion

	int perdidasTotales = 0; // La cantidad de dinero que se perdio en total por los robos

#pragma region Lectura de Stock.txt

	string linea; // Crea un string en el que guarda cada linea de texto
	ifstream archivo;
	archivo.open("Stock.txt"); // Abre el archivo con los productos

	if (archivo.fail()) { // Si el archivo no existe o no se encuentra registra el error

		cout << "No se pudo abrir el archivo Stock.txt" << endl;

		system("PAUSE");
	}

	while (getline(archivo, linea)) { // Lee el archivo linea por linea

		stringstream ss(linea); // Permite extraer cadenas de texto de la linea

		while (!ss.eof()) { // Minetras la linea no se haya acabado

			string nombreProducto;
			string cantInicialStr;
			string cantFinalStr;
			string tamaño;

			int cantInicial = 0;
			int cantFinal = 0;

			getline(ss, nombreProducto, ',');
			getline(ss, cantInicialStr, ',');
			getline(ss, cantFinalStr, ',');
			getline(ss, tamaño, ',');

			/*
				Para facilitar las comparaciones entre strings
			*/

			toUpper(nombreProducto);
			toUpper(tamaño);

			try {

				cantInicial = stoi(cantInicialStr);
				cantFinal = stoi(cantFinalStr);

			}
			catch (...) {

			}

			int cantVendidos = CantVendidos(nombreProducto); // Se lee el archivo Ventas.txt para ver cuantos productos del actual se vendieron

#pragma region Calculos correspondientes a si es o no un producto robado

	/*
		A continuacion se vera la logica detras del calculo de si se robaron o no productos
	*/

			if (cantVendidos < cantFinal) { // Si se vendieron menos productos de los que hay realmente

				int productosRobados = cantFinal - cantVendidos; // Se calcula la cantidad de productos que fueron robados
				int perdidas;

				if (tamaño == "CHICO") { // Se calculan las perdidas del robo dependiendo del tamaño del producto

					perdidas = productosRobados * 10;
				}
				else {

					perdidas = productosRobados * 50;
				}

				toCapitalize(nombreProducto); // Se retorna el nombre del producto al original

				cout << "\n- " + nombreProducto + "; Cantidad Robada: " + to_string(productosRobados) + "; Monto de la perdida: " + to_string(perdidas) << endl; // Se despliega la informacion del producto robado

				perdidasTotales += perdidas; // Se aumentan las perdidas totales
			}

#pragma endregion Calculos correspondientes a si es o no un producto robado
		}
	}
	archivo.close(); // Se cierra el archivo

	if (perdidasTotales != 0) { // Si habian productos robados

		cout << "\n\nPerdidas Totales: $" + to_string(perdidasTotales) << endl;
	}
	else {

		cout << "\nNINGUN PRODUCTO HA SIDO ROBADO" << endl;
	}

#pragma endregion Lectura de Stock.txt

	unsigned tiempoFinal = clock(); // Termino de la medicion del tiempo de ejecucion
	double tiempoSolucionSecuencial = (double(tiempoFinal - tiempoInicial) / CLOCKS_PER_SEC);

	cout << "\nTiempo de Ejecucion: " + to_string(tiempoSolucionSecuencial) << " segundos" << endl;
}

int SistemaJumbottusImpl::CantVendidos(string nombreProducto)
{
	
	int cantVendidos = 0; // Aqui se ira registrando la cantidad de veces que se ha vendido un producto

	string linea; // Crea un string en el que guarda cada linea de texto
	ifstream archivo;
	archivo.open("Ventas.txt"); // Abre el archivo con las ventas de los productos

	if (archivo.fail()) { // Si el archivo no existe o no se encuentra registra el error

		cout << "No se pudo abrir el archivo Stock.txt" << endl;

		system("PAUSE");
	}

	while (getline(archivo, linea)) { // Lee el archivo linea por linea


		stringstream ss(linea); // Permite extraer cadenas de texto de la linea

		while (!ss.eof()) { // Minetras la linea no se haya acabado

			string nombreProductoEncontrado;

			getline(ss, nombreProductoEncontrado, ',');

			toUpper(nombreProductoEncontrado);

			if (nombreProductoEncontrado == nombreProducto) { // Cada vez que encuentre el nombre del producto aumentara en 1 la cantidad de vendidos

				cantVendidos += 1;
			}
		}
	}
	archivo.close(); // Se cierra el archivo

	return cantVendidos;
}

float SistemaJumbottusImpl::CalcularBonusProgramador()
{
	return tiempoSolucionSecuencial - tiempoSolucionParalelo;
}

bool SistemaJumbottusImpl::AmbasSolucionesEjecutadas()
{
	if (tiempoSolucionParalelo != 0 && tiempoSolucionSecuencial != 0) {

		return true;
	} 

	return false;
}


SistemaJumbottusImpl::~SistemaJumbottusImpl()
{
}
