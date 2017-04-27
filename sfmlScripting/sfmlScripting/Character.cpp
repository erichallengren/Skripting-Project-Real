#include "Character.h"

Character::Character()
{
	this->characterSize = 64.f;
	this->character = sf::CircleShape(this->characterSize);
	this->character.setPosition(128, 512);
	this->character.setFillColor(sf::Color::Green);

	//middlepoint
	this->middlePoint = this->character.getPosition();
	this->middlePoint.x += this->characterSize;
	this->middlePoint.y += this->characterSize;

	this->tileSize = 128; //4 ggr 32
	this->moveCD = 1;
	this->moved = false;

	//hitbox
	//Samma som character
	this->hitbox.setPosition(this->character.getPosition());
	this->hitbox.setOrigin(sf::Vector2f(this->character.getPosition()));
	this->hitbox.setSize(sf::Vector2f(128, 128));

	//debug
	this->debugMidPoint.setRadius(10);
	this->debugMidPoint.setFillColor(sf::Color::Red);
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
		this->moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y += 128;
		this->moveCD = 0;
		this->moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= 128;
		this->moveCD = 0;
		this->moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += 128;
		this->moveCD = 0;
		this->moved = true;
	}
	


	//Sätter karaktärens nya position
	this->character.move(velocity);

	//hitbox
	this->hitbox.move(velocity);
	this->hitbox.setPosition(hitbox.getPosition());
	this->hitbox.updateHitboxDrawable();

	this->updateMiddlePoint();
}

void Character::updateMiddlePoint()
{
	this->middlePoint = this->character.getPosition();
	this->middlePoint.x += this->characterSize;
	this->middlePoint.y += this->characterSize;

	this->debugMidPoint.setPosition(this->middlePoint - sf::Vector2f(this->debugMidPoint.getRadius(), this->debugMidPoint.getRadius()));
}

void Character::setPosition(int x, int y)
{
	this->character.setPosition(x, y);
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(this->hitbox);
	target.draw(this->character);
	target.draw(this->debugMidPoint);
}


sf::CircleShape Character::getCharacter()
{
	return this->character;
}

sf::FloatRect Character::getBoundingBox()
{
	return character.getGlobalBounds();
}

Hitbox Character::getHitbox()
{
	return this->hitbox;
}

bool Character::getMoved()
{
	return this->moved;
}

sf::Vector2f Character::getMiddlePoint()
{
	return this->middlePoint;
}

void Character::setMoved(bool moved)
{
	this->moved = moved;
}
