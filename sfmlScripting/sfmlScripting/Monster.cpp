#include "Monster.h"

Monster::Monster()
{
}

Monster::Monster(sf::Texture * texture)
	//: monster()
{
	this->monsterSize = { 128, 128 };
	this->monster = sf::RectangleShape(monsterSize);
	this->monster.setPosition(1024, 512);
	//this->monster.setFillColor(sf::Color::Black);
	this->hasAttacked = false;

	//middlepoint
	this->middlePoint = this->monster.getPosition();
	this->middlePoint.x += this->monsterSize.x * 0.5;
	this->middlePoint.y += this->monsterSize.y * 0.5;

	//new shit
	//this->monster.setPosition(x, y);
	this->monster.setTexture(texture);
	this->monster.setTextureRect(sf::IntRect(22*32, 0, 32, 32));

	//attaking variables
	this->nextTo = false;
	this->inside = false;
}

Monster::~Monster()
{

}

void Monster::update(Character& character, bool nextTo, lua_State * L, int & score)
{
	if (character.getMoved() == true)
	{
		this->move(character, nextTo, L);
		this->checkSides(character, score);
		character.setMoved(false);
	}
}

void Monster::move(Character& character, bool nextTo, lua_State * L)
{
	velocity = { 0, 0 };

	sf::Vector2f rayToCharacter = character.getMiddlePoint() - this->middlePoint;

	float rayx, rayy;

	int moveNumber = rand() % 2 + 1;

	int error = luaL_dofile(L, "character.lua");
	
	if (rayToCharacter.x == 0 && rayToCharacter.y != 0)
	{
		if (rayToCharacter.y >= 0)
		{
			lua_getglobal(L, "moveY");

			lua_pushnumber(L, velocity.y);
			lua_pushnumber(L, 128);
			
			error = lua_pcall(L, 2, 1, NULL);
			
			velocity.y = lua_tonumber(L, -1);

			lua_pop(L, 1);
		}
		else
		{
			lua_getglobal(L, "moveY");

			lua_pushnumber(L, velocity.y);
			lua_pushnumber(L, -128);

			error = lua_pcall(L, 2, 1, NULL);

			velocity.y = lua_tonumber(L, -1);

			lua_pop(L, 1);
		}
	}
	
	if (rayToCharacter.y == 0 && rayToCharacter.x != 0)
	{
		if (rayToCharacter.x >= 0)
		{
			lua_getglobal(L, "moveX");

			lua_pushnumber(L, velocity.x);
			lua_pushnumber(L, 128);

			error = lua_pcall(L, 2, 1, NULL);

			velocity.x = lua_tonumber(L, -1);

			lua_pop(L, 1);
		}
		else
		{
			lua_getglobal(L, "moveX");

			lua_pushnumber(L, velocity.x);
			lua_pushnumber(L, -128);

			error = lua_pcall(L, 2, 1, NULL);

			velocity.x = lua_tonumber(L, -1);

			lua_pop(L, 1);
		}
	}

	if (rayToCharacter.x != 0 && rayToCharacter.y != 0)
	{
		int randRow = rand() % 2 + 1;

		if (randRow == 1)
		{
			if (rayToCharacter.x >= 0)
			{
				lua_getglobal(L, "moveX");

				lua_pushnumber(L, velocity.x);
				lua_pushnumber(L, 128);

				error = lua_pcall(L, 2, 1, NULL);

				velocity.x = lua_tonumber(L, -1);

				lua_pop(L, 1);
			}
			else
			{
				lua_getglobal(L, "moveX");

				lua_pushnumber(L, velocity.x);
				lua_pushnumber(L, -128);

				error = lua_pcall(L, 2, 1, NULL);

				velocity.x = lua_tonumber(L, -1);

				lua_pop(L, 1);
			}
		}
		else if (randRow == 2)
		{
			if (rayToCharacter.y >= 0)
			{
				lua_getglobal(L, "moveY");

				lua_pushnumber(L, velocity.y);
				lua_pushnumber(L, 128);

				error = lua_pcall(L, 2, 1, NULL);

				velocity.y = lua_tonumber(L, -1);

				lua_pop(L, 1);
			}
			else
			{
				lua_getglobal(L, "moveY");

				lua_pushnumber(L, velocity.y);
				lua_pushnumber(L, -128);

				error = lua_pcall(L, 2, 1, NULL);

				velocity.y = lua_tonumber(L, -1);

				lua_pop(L, 1);
			}
		}
	}

	if (nextTo == false)
	{
		//Sätter monstrets nya position
		this->monster.move(velocity);
		this->hasAttacked = false;

		this->updateMiddlePoint();
	}
	else
	{
		this->hasAttacked = true;
	}



}

void checkIfCanAttack()
{
	//position - charactär position vector kolla dens längd
}

void Monster::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(this->monster);
}

void Monster::updateMiddlePoint()
{
	this->middlePoint = this->monster.getPosition();
	this->middlePoint.x += this->monsterSize.x * 0.5;
	this->middlePoint.y += this->monsterSize.y * 0.5;
}


sf::RectangleShape Monster::getMonster()
{
	return this->monster;
}

sf::Vector2f Monster::getMiddlePoint()
{
	return this->middlePoint;
}

bool Monster::getHasAttacked()
{
	return this->hasAttacked;
}

void Monster::setMove(float x, float y)
{
		velocity = { x, y };
		this->monster.move(velocity);
		//this->animatedMonster.move(velocity);

		this->updateMiddlePoint();
}

void Monster::setHasAttacked(bool state)
{
	this->hasAttacked = state;
}

void Monster::checkSides(Character & character, int & score)
{
	this->nextTo = false;
	this->inside = false;

	sf::Vector2f distance = (character.getMiddlePoint() - this->middlePoint);

	if (distance.x == 128 && distance.y == 0 || distance.x == 0 && distance.y == 128)
	{
		nextTo = true;
		//score++;
	}

	if (distance.x == -128 && distance.y == 0 || distance.x == 0 && distance.y == -128)
	{
		nextTo = true;
		//score++;
	}

	if (distance.x == 0 && distance.y == 0)
	{
		this->inside = true;
	}

	if (nextTo == true)
	{
		if (character.getHasAttacked() == true)
		{
			score++;
			newMonster(score);
		}
	}

	if (this->inside == true)
	{
		score--;
		if (score % 2 == 0)
		{
			character.setPos(1, 4);
		}
		else
		{
			character.setPos(13, 4);
		}
	}
}

void Monster::newMonster(int score)
{
	if (score % 2 == 0)
	{
		this->monster.setPosition(1664, 512);
	}
	else
	{
		this->monster.setPosition(128, 512);
	}
}

