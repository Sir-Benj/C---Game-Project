#pragma once
#include <SFML\Graphics.hpp>

//Acts as the parent class for creating virtual screen objects.
//All other screens inherit from this class.
class cScreen
{
public:
	virtual int Run(sf::RenderWindow &App) = 0;
};