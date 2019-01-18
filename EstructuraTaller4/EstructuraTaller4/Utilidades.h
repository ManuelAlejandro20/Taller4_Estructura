#pragma once
#include <iostream>
#include <string>
#include "Windows.h"

using namespace std;

namespace utilidades {

	// Toma un string y lo cambia a Upper Case para facilitar las comparaciones entre strings
	inline void toUpper(string & s)
	{
		for (int i = 0; i < s.length(); i++) { // Recorre todos los caracteres de la palabra

			s[i] = toupper(s[i]); // Pasa el caracter a Mayus
		}
	}

	// Toma un string y cambia a mayuscula la letra inicial y el resto lo cambia a minuscula
	inline void toCapitalize(string & s)
	{

		s[0] = toupper(s[0]); // Pasa el caracter a Mayus

		for (int i = 1; i < s.length(); i++) { // Recorre todos los caracteres de la palabra

			s[i] = tolower(s[i]); // Pasa el caracter a Mayus
		}
	}

	inline void capitalize(string &s) {//pone al string ingresado una mayuscula inicial
		s[0] = toupper(s[0]);
	}

	// Verifica que un string pueda ser pasado a int
	inline bool isNumericalInput(string & s) {

		try {

			int input = stoi(s);
			return true;
		}
		catch (...) {

			return false;
		}
	}

	inline void SetColor(int i) // metodo que cambia de color todo lo que esta adelante de la funcion invocada
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
	}

	inline void Limpiar() // metodo que limpia la consola sin mostrar un parapedo en pantalla
	{
		HANDLE hOut;
		COORD Posicion;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		Posicion.X = 0;
		Posicion.Y = 0;
		SetConsoleCursorPosition(hOut, Posicion);
	}

	inline void ShowConsoleCursor(bool showFlag)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO InfoCursor;

		GetConsoleCursorInfo(out, &InfoCursor);
		InfoCursor.bVisible = showFlag; //dependiendo del booleano ingresado se ajusta la visibilidad del cursor
		SetConsoleCursorInfo(out, &InfoCursor);
	}
}
