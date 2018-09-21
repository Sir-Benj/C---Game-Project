#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;
using namespace sf;

//Load map text file into 2ivectors, gets map size from size of the row + column in text file. 
//Each coordinate of the map, contains what was at that coordinate in the text file.
void LoadMapCounter(string MapTxtFile, vector<vector<Vector2i>>(&Map));

//Sets texture file for tile sprites.
void SetTextureFile(string TextureFile, Texture& TileTexture, Sprite& Tiles);

//Uses map vector and texture file to draw the part of the tileset that each coordinate in the
//map file represented. This sets the textRect for each sprite to the correct one in the tile set.
void DrawMapTiles(vector<vector<Vector2i>>(&map), Sprite& Tiles, RenderWindow& GameScreen);

//Collision tile class, holds all info for the collision tiles of the map.
struct CollisionTile 
{
	CollisionTile();
	CollisionTile(Vector2f position, Vector2f size, Color Transparent);
	~CollisionTile();
	bool Collision;
	RectangleShape CTile;
	float top, bottom, left, right;
	void CheckTilePos();
};

//Creates collision tiles from a map vector.
void CreateColTiles(vector<vector<Vector2i>>(&map), vector<CollisionTile>(&ColTiles));
