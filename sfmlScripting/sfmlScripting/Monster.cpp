#include "Monster.h"

Monster::Monster()
{
	this->monsterSize = { 128, 128 };
	this->monster = sf::RectangleShape(monsterSize);
	this->monster.setPosition(128, 512);
	this->monster.setFillColor(sf::Color::Black);
	this->hasAttacked = false;
	
	//middlepoint
	this->middlePoint = this->monster.getPosition();
	this->middlePoint.x += this->monsterSize.x * 0.5;
	this->middlePoint.y += this->monsterSize.y * 0.5;

	//hitboxs
	//Samma som monstret
	this->hitbox.setPosition(this->monster.getPosition());
	this->hitbox.setOrigin(sf::Vector2f(this->monster.getPosition()));
	this->hitbox.setSize(sf::Vector2f(128, 128));

	this->hurtbox.setPosition(this->monster.getPosition());
	this->hurtbox.setOrigin(sf::Vector2f(this->monster.getPosition()));
	this->hurtbox.setSize(sf::Vector2f(128, 128));

	//debug
	this->debugMidPoint.setRadius(10);
	this->debugMidPoint.setFillColor(sf::Color::Red);

	//venne
	this->nextTo = false;
	this->inside = false;
}

Monster::Monster(sf::Texture * texture, int x, int y)
	//: monster()
{
	this->monsterSize = { 128, 128 };
	this->monster = sf::RectangleShape(monsterSize);
	this->monster.setPosition(128, 512);
	//this->monster.setFillColor(sf::Color::Black);
	this->hasAttacked = false;

	//middlepoint
	this->middlePoint = this->monster.getPosition();
	this->middlePoint.x += this->monsterSize.x * 0.5;
	this->middlePoint.y += this->monsterSize.y * 0.5;

	//hitboxs
	//Samma som monstret
	this->hitbox.setPosition(this->monster.getPosition());
	this->hitbox.setOrigin(sf::Vector2f(this->monster.getPosition()));
	this->hitbox.setSize(sf::Vector2f(128, 128));

	this->hurtbox.setPosition(this->monster.getPosition());
	this->hurtbox.setOrigin(sf::Vector2f(this->monster.getPosition()));
	this->hurtbox.setSize(sf::Vector2f(128, 128));

	//debug
	this->debugMidPoint.setRadius(10);
	this->debugMidPoint.setFillColor(sf::Color::Red);
	//new shit
	//this->monster.setPosition(x, y);
	this->monster.setTexture(texture);
	this->monster.setTextureRect(sf::IntRect(6*32, 0, 32, 32));

	//venne
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

	//lua_getglobal(L, "moveOld");

	//lua_pushnumber(L, velocity.x);
	//lua_pushnumber(L, velocity.y);
	//lua_pushnumber(L, rayToCharacter.x);
	//lua_pushnumber(L, rayToCharacter.y);
	//lua_pushnumber(L, moveNumber);

	//error = lua_pcall(L, 5, 5, NULL);

	//moveNumber = lua_tonumber(L, -1); //får sista
	//rayx = lua_tonumber(L, -2);
	//rayy = lua_tonumber(L, -3);
	//rayToCharacter.y = rayx;
	//rayToCharacter.x = rayy;
	//velocity.y = lua_tonumber(L, -4);
	//velocity.x = lua_tonumber(L, -5);

	//lua_pop(L, 5);


	
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

		//hitbox
		this->hitbox.move(velocity);
		this->hitbox.setPosition(hitbox.getPosition());
		this->hitbox.updateHitboxDrawable();

		this->hurtbox.setPosition(hitbox.getPosition());
		this->hurtbox.updateHitboxDrawable();

		this->updateMiddlePoint();
	}
	else
	{
		//hitboxs
		//Samma som monstret
		this->hitbox.setPosition(this->monster.getPosition());
		this->hitbox.setOrigin(sf::Vector2f(this->monster.getPosition()));
		this->hitbox.setSize(sf::Vector2f(128, 128));
		this->hasAttacked = true;

		//Samma som monstret
		this->hurtbox.setPosition(this->monster.getPosition());
		this->hurtbox.setOrigin(sf::Vector2f(this->monster.getPosition()));
		this->hurtbox.setSize(sf::Vector2f(128, 128));
		//hurtbox move
		this->hurtbox.move(velocity);
		this->hurtbox.setPosition(hurtbox.getPosition());
		this->hurtbox.updateHitboxDrawable();
	}



}

void checkIfCanAttack()
{
	//position - charactär position vector kolla dens längd
}

void Monster::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(this->hurtbox);
	target.draw(this->hitbox);
	target.draw(this->monster);
	target.draw(this->debugMidPoint);
}

void Monster::updateMiddlePoint()
{
	this->middlePoint = this->monster.getPosition();
	this->middlePoint.x += this->monsterSize.x * 0.5;
	this->middlePoint.y += this->monsterSize.y * 0.5;

	this->debugMidPoint.setPosition(this->middlePoint - sf::Vector2f(this->debugMidPoint.getRadius(), this->debugMidPoint.getRadius()));
}


sf::RectangleShape Monster::getMonster()
{
	return this->monster;
}

Hitbox Monster::getHitbox()
{
	return this->hitbox;
}

Hitbox Monster::getHurtbox()
{
	return this->hurtbox;
}

sf::FloatRect Monster::getBoundingBox()
{
	return this->hitbox.getBoundingBox();
}

sf::FloatRect Monster::getHurtboxBoundingBox()
{
	return this->hurtbox.getBoundingBox();
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

		//hitbox

		this->hitbox.move(velocity);
		this->hitbox.setPosition(hitbox.getPosition());
		this->hitbox.updateHitboxDrawable();

		this->hurtbox.move(velocity);
		this->hurtbox.setPosition(hurtbox.getPosition());
		this->hurtbox.updateHitboxDrawable();

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
		}
	}

	if (this->inside == true)
	{
		score--;
	}
}

