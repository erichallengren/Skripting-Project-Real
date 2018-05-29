#pragma once
#include "Includes.h"


class Tile : public sf::Drawable
{
private:

	sf::RectangleShape tile;
	sf::Vector2f tileSize;
	int getTilePoss(string tile);

public:
	Tile();
	Tile(sf::Texture * texture, string tile, int x = 0, int y = 0, bool small = false);
	Tile(sf::Texture * texture, int tile, int x = 0, int y = 0, bool small = false, bool select = false);
	~Tile();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	sf::FloatRect getBoundingBox();
};
