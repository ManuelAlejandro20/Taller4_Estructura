#include "pch.h"
#include "Menu.h"

Menu::Menu()
{
	this->sistema = SistemaJumbottusImpl();
}

void Menu::MenuPrincipal()
{
	bool salir = false; // Permite matener el menu en un loop infinito 
	int pos, posact; // variables que nos indican la posicion actual y el valor numero de flecha presionada
	ShowConsoleCursor(false); // oculta el cursor
	while (!salir) {
		system("cls");
		pos = posact = 0;
		int colores[4] = { 5,7,7,7 }; // arreglo con los colores a utilizar, tiene el mismo largo que las opciones disponibles
		while (pos != ENTER) { // mientras no se presione enter
			system("title Sistema Jumbottus - Ver 1.00");
			cout << " \t\t\t\t\tษอออออออออออออออออออออออออออออออป\n" <<
				" \t\t\t\t\tบ       Sistema Jumbottus       บ\n" <<
				" \t\t\t\t\tศอออออออออออออออออออออออออออออออผ\n" << endl;
			string opciones[4] = { "[1] Solucion Secuencial" , // arreglo con las opciones disponibles
								   "[2] Solucion en Paralelo",
								   "[3] Bono de Programador",
								   "[4] Salir" };
			for (int i = 0; i < 4; i++) {
				SetColor(colores[i]); cout << opciones[i] << endl; SetColor(7); // cada vez que se despliegan las opciones se muestran con el color que le corresponde en el arreglo colores
			}
			pos = _getch(); // obtiene el valor de la flecha presionada
			colores[posact] = 7; // se cambia de color porque en el switch de adelante si o si cambiara de posicion (en caso de ingresar otra tecla se vuelve a poner el color rojo)
			switch (pos) {
			case UP: // si presiona arriba solo se mueve hacia ese lado si su posicion actual es distinta de 0
				if (posact == 0) {
					posact = 0;
				}
				else {
					posact--;
				}
				colores[posact] = 5; //el color de la posicion actual pasara a ser rojo, mostrando al usuario que se ha movido de posicion
				break;
			case DOWN: //si presiono abajo solo se mueve hacia ese lado si su posicion actual es distinta de 3
				if (posact == 3) {
					posact = 3;
				}
				else {
					posact++;
				}
				colores[posact] = 5; //el color de la posicion actual pasara a ser rojo, mostrando al usuario que se ha movido de posicion
				break;
			default: // si presiono cualquier otra tecla el color se mantiene en la opcion 
				colores[posact] = 5;
				break;
			}

			Limpiar(); // limpia la consola 
			//el algoritmo mostrado es igual para todos los otros menues que se muestran, algunos sufren variaciones que dependen de la cantidad de opciones que se de al usuario
			//para resumir se podria decir que nos estamos moviendo dentro de un rango de numeros (que corresponden a las opciones) y dependiendo de donde estemos se ira activando un determinado color
		}

		switch (posact) { // segun la ultima posicion que obtuvimos entraremos a una opcion o la otra

		case 0:

			system("CLS");

			cout << "LISTA DE PRODUCTOS ROBADOS" << endl;

			sistema.SolucionSecuencial();

			system("PAUSE");

			break;
		case 1:
		{
			system("CLS");

			cout << "\nIngrese el numero de hilos con el que desea trabajar: ";

			string cantHilosStr;

			getline(cin, cantHilosStr);
			
			try {

				while (!isNumericalInput(cantHilosStr) && stoi(cantHilosStr) <= 0) {

					system("CLS");

					cout << "\n######### ERROR: INGRESE UN NUMERO MAYOR QUE 0 POR FAVOR #########\n" << endl;

					system("PAUSE");

					system("CLS");

					cout << "\nIngrese el numero de hilos con el que desea trabajar: ";

					getline(cin, cantHilosStr);
				}
			}
			catch (...) {

			}

			system("CLS");

			cout << "LISTA DE PRODUCTOS ROBADOS" << endl;

			try {
				
				sistema.SolucionParalela(stoi(cantHilosStr));
			}
			catch (...) {

				}

			system("PAUSE");
		}
			break;
		case 2:
		{
			
			system("CLS");
			 
			if (sistema.AmbasSolucionesEjecutadas()) {

				float bonusProgramador = sistema.CalcularBonusProgramador() / 0.1;

				cout << "BONUS POR MS: $" + to_string(bonusProgramador) << endl;
			}
			else {

				cout << "\n######### ERROR: DEBE EJECUTAR CADA UNA DE LAS SOLUCIONES AL MENOS UNA VEZ PARA CALCULAR EL BONO #########\n" << endl;
			}

			system("PAUSE");
		}
			break;
		case 3:

			salir = true;
			system("cls");
			cout << "-------- Has cerrado la aplicacion con exito! ------" << endl;
			break;

		}
	}
}


Menu::~Menu()
{
}   
