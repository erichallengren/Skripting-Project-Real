#include "Tile.h"

Tile::Tile()
{
	this->tileSize = { 128, 128 };
	this->tile = sf::RectangleShape(tileSize);
	this->tile.setPosition(0, 0);
	this->tile.setFillColor(sf::Color::Green);
}

Tile::Tile(sf::Texture * texture, string tile, int x, int y)
{
	this->tileSize = { 128, 128 };
	this->tile = sf::RectangleShape(tileSize);
	this->tile.setPosition(x, y);
	this->tile.setTexture(texture);
	this->tile.setTextureRect(sf::IntRect(getTilePoss(tile), 0, 32, 32));
}

Tile::Tile(sf::Texture * texture, int tile, int x, int y)
{
	this->tileSize = { 128, 128 };
	this->tile = sf::RectangleShape(tileSize);
	this->tile.setPosition(x, y);
	this->tile.setTexture(texture);
	this->tile.setTextureRect(sf::IntRect(tile, 0, 32, 32));
}

int Tile::getTilePoss(string tile)
{
	int tileNumber = 0;
	if (tile == "1")
	{
		tileNumber = 0;
	}
	if (tile == "2")
	{
		tileNumber = 1;
	}
	if (tile == "3")
	{
		tileNumber = 2;
	}
	if (tile == "4")
	{
		tileNumber = 3;
	}
	if (tile == "5")
	{
		tileNumber = 4;
	}
	if (tile == "6")
	{
		tileNumber = 5;
	}
	if (tile == "7")
	{
		tileNumber = 6;
	}
	if (tile == "8")
	{
		tileNumber = 7;
	}
	if (tile == "9")
	{
		tileNumber = 8;
	}
	if (tile == "0")
	{
		tileNumber = 9;
	}
	return (tileNumber * 32);
}


Tile::~Tile()
{

}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->tile, states);
}

sf::FloatRect Tile::getBoundingBox()
{
	return tile.getGlobalBounds();
}
