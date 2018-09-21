#pragma once
#include "cScreen.h"
#include "Globals.h"

//Inherits from cScreen - main menu screen
class Main_Menu : public cScreen
{
public:
	Main_Menu(void);
	virtual int Run(sf::RenderWindow &App);

private:
	int alpha_max;
	int alpha_div;
};