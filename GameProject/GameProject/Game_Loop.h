#pragma once
#include "cScreen.h"
#include "Screens.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <sstream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include "Player.h"
#include "Enemy.h"
#include "Globals.h"

//Inherits from cScreen - Game Loop screen
class Game_Loop : public cScreen
{
public:
	virtual int Run(sf::RenderWindow &App);
};