#include "Character.h"

Character::Character()
{
	this->character = sf::CircleShape(50.f);
	this->character.setFillColor(sf::Color::Green);
	this->character.setPosition(0, 500);
	this->goingUp = false;
}

Character::~Character()
{

}

void Character::update()
{
	move();
}

void Character::move()
{
	this->velocity.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->goingUp = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= 0.1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += 0.1;
	}
	
	if (this->goingUp)
	{
		//grejer
	}


	//Sätter karaktärens nya position
	this->character.setPosition(this->character.getPosition().x + velocity.x, this->character.getPosition().y + velocity.y);
}

sf::CircleShape Character::getCharacter()
{
	return this->character;
}