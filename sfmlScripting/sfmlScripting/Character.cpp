#include "Character.h"

Character::Character()
{
	this->character = sf::CircleShape(5.f);
	this->character.setPosition(128, 500);
	this->character.setFillColor(sf::Color::Green);

	this->tileSize = 128; //4 ggr 32
	this->moveCD = 1;
	
	//hitbox
	//Samma som character
	this->hitbox.setPosition(this->character.getPosition());
	this->hitbox.setOrigin(sf::Vector2f(this->character.getPosition()));
	this->hitbox.setSize(sf::Vector2f(64, 64));
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

	//hitbox
	this->hitbox.move(velocity);
	this->hitbox.updateHitboxDrawable();
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(this->hitbox);
	target.draw(this->character);
}

sf::CircleShape Character::getCharacter()
{
	return this->character;
}

Hitbox Character::getHitbox()
{
	return this->hitbox;
}
