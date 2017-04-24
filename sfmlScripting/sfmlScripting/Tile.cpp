#include "Tile.h"

Tile::Tile()
{
	this->tileSize = { 128, 128 };
	this->tile = sf::RectangleShape(tileSize);
	this->tile.setPosition(0, 0);
	this->tile.setFillColor(sf::Color::Green);
}

Tile::Tile(sf::Texture * texture, int x, int y)
{
	this->tileSize = { 128, 128 };
	this->tile = sf::RectangleShape(tileSize);
	this->tile.setPosition(x, y);
	this->tile.setTexture(texture);
}

Tile::~Tile()
{

}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->tile, states);
}
