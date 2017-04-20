#include "Character.h"

Character::Character()
{
	this->character = sf::CircleShape(50.f);
	this->character.setFillColor(sf::Color::Green);
	this->character.setPosition(0, 500);

	//jumping
	this->jumpPower = 400;
}

Character::~Character()
{

}

void Character::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	move();
}

void Character::move()
{
	this->velocity.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		jump();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= 0.1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += 0.1;
	}
	


	//Sätter karaktärens nya position
	velocity * deltaTime;
	this->character.move(this->velocity.x, 0);
}

void Character::jump()
{
	//s2 = s1 + v1 * t + (a*t^2) / 2
	float moved = (40 * this->deltaTime) + ((-9.82 * pow(this->deltaTime, 2)) / 2);
	this->character.move(0, moved);
}

sf::CircleShape Character::getCharacter()
{
	return this->character;
}