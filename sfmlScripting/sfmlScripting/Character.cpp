#include "Character.h"

Character::Character()
{
	this->character = sf::CircleShape(100.f);
	this->character.setFillColor(sf::Color::Green);

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->goingUp = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += 1;
	}
	
	if (this->goingUp == true)
	{
		velocity.y += 0.1;

		if (velocity.y > 0.5)
		{
			velocity.y -= 0.1;
		}
	}

	//Sätter karaktärens nya position
	this->character.setPosition(this->character.getPosition().x + velocity.x, this->character.getPosition().y + velocity.y);
}

sf::CircleShape Character::getCharacter()
{
	return this->character;
}