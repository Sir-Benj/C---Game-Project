#pragma once
#include "cScreen.h"
#include "Screens.h"
#include "SFML\Graphics.hpp"

//Inherits from cScreen - High scores screen
class High_Scores : public cScreen
{
public:
	High_Scores(void);
	virtual int Run(sf::RenderWindow &App);

private:
	int alpha_max;
	int alpha_div;
};