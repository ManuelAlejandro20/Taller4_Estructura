#pragma once
#include "Utilidades.h"
#include "SistemaJumbottusImpl.h"
#include "conio.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

constexpr auto UP = 72;
constexpr auto DOWN = 80;
constexpr auto ENTER = 13;
constexpr auto LEFT = 75;
constexpr auto RIGHT = 77;

using namespace utilidades;

class Menu
{
public:
	
	Menu();

	void MenuPrincipal();

	~Menu();
private:

	SistemaJumbottusImpl sistema;
};

