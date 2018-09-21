#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Screens.h"

# define PI           3.14159265358979323846  /* pi */

using namespace std;
using namespace sf;

int main(int argc, char** argv)
{
	//Variables for screens
	vector<cScreen*> Screens;
	int screen = 0;

	//Window creation
	RenderWindow GameScreen(VideoMode(480, 480, 16), "It's High Noon!");
	GameScreen.setVerticalSyncEnabled(true);
	GameScreen.setFramerateLimit(60);

	//Screen preparation and push back to the stack
	Main_Menu s0;
	Screens.push_back(&s0);
	Game_Loop s1;
	Screens.push_back(&s1);
	High_Scores s2;
	Screens.push_back(&s2);
	Game_Over s3;
	Screens.push_back(&s3);

	//Main loop for switching screens (value returned from screen determines which screen is moved to next)
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(GameScreen);
	}

	//clean exits
	return EXIT_SUCCESS;
}

//Code for switching succinctly between screens and colour changing menu
//selection created by Daemon L. Schmidt
//Source: https://github.com/SFML/SFML/wiki/Tutorial:-Manage-different-Screens
//Accessed 15/04/18

//Code used as follows:

//class cScreen
//{
//public:
//	virtual int Run(sf::RenderWindow &App) = 0;
//};

//while (screen >= 0)
//{
//	screen = Screens[screen]->Run(App);
//}

//{
//	//Applications variables
//	std::vector<cScreen*> Screens;
//	int screen = 0;
//
//	//Window creation
//	sf::RenderWindow App(sf::VideoMode(640, 480, 32), "SFML Demo 3");
//
//	//Mouse cursor no more visible
//	App.setMouseCursorVisible(false);
//
//	//Screens preparations
//	screen_0 s0;
//	Screens.push_back(&s0);
//	screen_1 s1;
//	Screens.push_back(&s1);
//
//	//Main loop
//	while (screen >= 0)
//	{
//		screen = Screens[screen]->Run(App);
//	}
//
//	return EXIT_SUCCESS;
//}

//#ifndef SCREENS_HPP_INCLUDED
//#define SCREENS_HPP_INCLUDED
//
////Basic Screen Class
//#include "cScreen.hpp"
//
////Including each screen of application
//#include "screen_0.hpp"
//#include "screen_1.hpp"
//
//#endif // SCREENS_HPP_INCLUDED

//class screen_0 : public cScreen
//{
//private:
//	int alpha_max;
//	int alpha_div;
//	bool playing;
//public:
//	screen_0(void);
//	virtual int Run(sf::RenderWindow &App);
//};
//
//screen_0::screen_0(void)
//{
//	alpha_max = 3 * 255;
//	alpha_div = 3;
//}
//if (alpha<alpha_max)
//{
//	alpha++;
//}
//Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));