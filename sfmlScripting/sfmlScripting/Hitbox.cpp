#include "Hitbox.h"

Hitbox::Hitbox()
{

}

Hitbox::~Hitbox()
{

}

void Hitbox::setOrigin(sf::Vector2f origin)
{
	this->origin = origin;
}

void Hitbox::setPosition(sf::Vector2f position)
{
	this->position = position;
	box.left = position.x - origin.x;
	box.top = position.y - origin.y;
}

void Hitbox::setSize(sf::Vector2f size)
{
	this->box.width = size.x;
	this->box.height = size.y;
}

bool Hitbox::intersect(const Hitbox &other)
{
	return this->box.intersects(other.box);
}

void Hitbox::move(sf::Vector2f velocity)
{
	this->position.x += velocity.x;
	this->position.y += velocity.y;
	this->box.left = position.x - origin.x;
	this->box.top = position.y - origin.y;
}
