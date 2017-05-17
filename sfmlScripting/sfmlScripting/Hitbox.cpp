#include "Hitbox.h"

Hitbox::Hitbox()
{
	this->hitboxDrawable.setSize(sf::Vector2f(128, 128));
	this->hitboxDrawable.setOutlineColor(sf::Color::Red);
	this->hitboxDrawable.setOutlineThickness(5);
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
	//return this->box.intersects(other.());
	return false;
}

void Hitbox::move(sf::Vector2f velocity)
{
	this->position.x += velocity.x;
	this->position.y += velocity.y;
	this->box.left = position.x - origin.x;
	this->box.top = position.y - origin.y;
}

void Hitbox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->hitboxDrawable);
}

void Hitbox::updateHitboxDrawable()
{
	this->hitboxDrawable.setPosition(this->position);
}

sf::FloatRect Hitbox::getBox()
{
	return this->box;
}

sf::Vector2f Hitbox::getPosition()
{
	return this->position;
}

sf::FloatRect Hitbox::getBoundingBox()
{
	return this->hitboxDrawable.getGlobalBounds();
}
