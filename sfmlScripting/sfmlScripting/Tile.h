#pragma once
#include "Includes.h"


class Tile : public sf::Drawable
{
private:

	sf::RectangleShape tile;
	sf::Vector2f tileSize;

public:
	Tile();
	Tile(sf::Texture * texture, int x = 0, int y = 0 );
	~Tile();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

};
