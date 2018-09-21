#pragma once
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

using namespace std;
using namespace sf;

//Loads the game map from text file in to a coordinate vector and then into the map vector to be used with the tile set.
void LoadMapCounter(string MapTxtFile, vector<vector<Vector2i>>(&Map))
{
	vector<Vector2i>MapCounter;
	ifstream MapFile(MapTxtFile);
	if (!MapFile)
	{
		cout << MapTxtFile << "is missing. Cannot run program";
	}

	int FirstCord = 0;
	int SecondCord = 0;

	//while the file is open, until the end of the file.
	while (!MapFile.eof())
	{
		string str;
		MapFile >> str;

		stringstream ss(str);
		vector<int> Coordinates;

		int i;

		//while the string stream loads each part of the string to i, ignoring commas, it pushes i onto the coordinate vector.
		while (ss >> i)
		{
			Coordinates.push_back(i);

			if (ss.peek() == ',')
				ss.ignore();
		}

		int FirstCord = Coordinates[0];
		int SecondCord = Coordinates[1];

		//The coordinate vectors are loaded into the map counters.
		MapCounter.push_back(Vector2i(SecondCord, FirstCord));

		//Map counter increases x counter every time it loops, and increases y if a newline is present in the file.
		if (MapFile.peek() == '\n')
		{
			//Added to the main map vector.
			Map.push_back(MapCounter);
			MapCounter.clear();
		}
	}
	//Last push back added so last line of the file is properly loaded.
	Map.push_back(MapCounter);
	//close the file
	MapFile.close();
}

//Loads and checks texture file.
void SetTextureFile(string TextureFile, Texture& TileTexture, Sprite& Tiles)
{
	TileTexture.loadFromFile(TextureFile);
	if (!TileTexture.loadFromFile(TextureFile))
	{
		cout << TextureFile << "is not present, cannot run program." << endl;;
	}
	Tiles.setTexture(TileTexture);
}

//Draws the map tile sprites to the screen.
void DrawMapTiles(vector<vector<Vector2i>>(&Map), Sprite& Tiles, RenderWindow& GameScreen)
{
	for (int i = 0; i < Map.size(); i++)
	{	//The map[i] is because of the vector, map.size would be one direction, map[i].size would be the other (like with a 2d array).
		for (int j = 0; j < Map[i].size(); j++)
		{
			Tiles.setPosition(j * 16, i * 16);
			Tiles.setTextureRect(IntRect((Map)[i][j].x * 16, (Map)[i][j].y * 16, 16, 16));
			GameScreen.draw(Tiles);
		}
	}
}

//Creates the collision tiles, defined from a map text file
void CreateColTiles(vector<vector<Vector2i>>(&Map), vector<CollisionTile>(&ColTiles))
{
	for (int i = 0; i < Map.size(); i++)
	{
		for (int j = 0; j < Map[i].size(); j++)
		{
			if (Map[i][j].x == 0 && Map[i][j].y == 0)
			{
				CollisionTile CTile(Vector2f((j * 16), (i * 16)), Vector2f(16, 16), Color::Transparent);
				CTile.Collision = false;
				ColTiles.push_back(CTile);
			}
			else if (Map[i][j].x > 0 || Map[i][j].y > 0)
			{
				CollisionTile CTile(Vector2f((j * 16), (i * 16)), Vector2f(16, 16), Color::Transparent);
				CTile.Collision = true;
				ColTiles.push_back(CTile);
			}
		}
	}
}

//Empty constructor
CollisionTile::CollisionTile(void)
{
}

//Collision tile constructor
CollisionTile::CollisionTile(Vector2f position, Vector2f size, Color transparent)
{
	CTile.setPosition(position);
	CTile.setSize(size);
	CTile.setFillColor(transparent);
}

//Collision tile destructor
CollisionTile::~CollisionTile(void)
{
}

//Collision tile get boundary positions
void CollisionTile::CheckTilePos()
{
	top = CTile.getPosition().y;
	bottom = CTile.getPosition().y + CTile.getSize().y;
	left = CTile.getPosition().x;
	right = CTile.getPosition().x + CTile.getSize().x;
}


