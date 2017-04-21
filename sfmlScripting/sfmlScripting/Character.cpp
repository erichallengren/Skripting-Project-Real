#include "Character.h"

Character::Character()
{
	this->character = sf::CircleShape(25.f);
	this->character.setPosition(0, 500);
	this->character.setFillColor(sf::Color::Green);

	this->goingUp = false;
}

Character::~Character()
{

}

void Character::update(float sec)
{
	move(sec);
}

void Character::move(float sec)
{
	velocity.x = 0;
	velocity.y = 0;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	//{
	//	this->goingUp = true;
	//}	
	//if (this->goingUp == true)
	//{
	//	velocity.y += 25 * sec;
	//}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y -= 25 * sec;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y += 25 * sec;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= 25 * sec;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += 25 * sec;
	}
	


	//Sätter karaktärens nya position
	this->character.move(velocity.x, velocity.y);
}

sf::CircleShape Character::getCharacter()
{
	return this->character;
}