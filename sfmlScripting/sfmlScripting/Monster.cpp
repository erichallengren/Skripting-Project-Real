#include "Monster.h"

Monster::Monster()
{
	this->monsterSize = { 5, 5 };
	this->monster = sf::RectangleShape(monsterSize);
	this->monster.setPosition(1000, 500);
	this->monster.setFillColor(sf::Color::Black);

	this->moveCD = 1;
}

Monster::~Monster()
{

}

void Monster::update(float sec)
{
	this->moveCD += sec;
	if (this->moveCD >= 1)
	{
		this->move(sec);
	}
}

void Monster::move(float sec)
{
	velocity = { 0, 0 };

	int moveNumber = rand() % 4 + 1;

	switch (moveNumber)
	{
	case 1: 
		velocity.y -= 128;
		this->moveCD = 0;
		break;
	case 2:
		velocity.y += 128;
		this->moveCD = 0;
		break;
	case 3:
		velocity.x -= 128;
		this->moveCD = 0;
		break;
	case 4:
		velocity.x += 128;
		this->moveCD = 0;
		break;
	}

	//Sätter monstrets nya position
	this->monster.move(velocity.x, velocity.y);
}

sf::RectangleShape Monster::getMonster()
{
	return this->monster;
}