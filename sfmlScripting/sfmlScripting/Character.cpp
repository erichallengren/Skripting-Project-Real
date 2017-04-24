#include "Character.h"

Character::Character()
{
	this->character = sf::CircleShape(5.f);
	this->character.setPosition(64, 500);
	this->character.setFillColor(sf::Color::Green);

	this->tileSize = 128; //4 ggr 32
	this->moveCD = 1;
}

Character::~Character()
{

}

void Character::update(float sec)
{
	this->moveCD += sec;
	if (this->moveCD >= 1)
	{
		this->move(sec);
	}
}

void Character::move(float sec)
{
	velocity = { 0, 0 };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y -= 128;
		this->moveCD = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y += 128;
		this->moveCD = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= 128;
		this->moveCD = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += 128;
		this->moveCD = 0;
	}
	


	//Sätter karaktärens nya position
	this->character.move(velocity);
	this->hitbox.move(velocity);
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(this->character);
}

sf::CircleShape Character::getCharacter()
{
	return this->character;
}