#pragma once
#include "cScreen.h"
#include "Screens.h"
#include "Map.h"
#include "Globals.h"
#include <SFML\Graphics.hpp>

//Inherits from cScreen - Game Over screen
class Game_Over : public cScreen
{
public:
	Game_Over(void);
	virtual int Run(sf::RenderWindow &App);

private:
	int alpha_max;
	int alpha_div;
};

