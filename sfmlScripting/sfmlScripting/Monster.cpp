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

}

Monster::~Monster()
{

}

void Monster::update(Character& character, bool nextTo, lua_State * L)
{
	if (character.getMoved() == true)
	{
		this->move(character, nextTo, L);
		character.setMoved(false);
	}
}

void Monster::move(Character& character, bool nextTo, lua_State * L)
{
	velocity = { 0, 0 };

	sf::Vector2f rayToCharacter = character.getMiddlePoint() - this->middlePoint;

	int moveNumber = rand() % 1 + 1;

	int error = luaL_dofile(L, "monster.lua");

	lua_getglobal(L, "move");

	lua_pushnumber(L, velocity.x);
	lua_pushnumber(L, velocity.y);
	lua_pushnumber(L, rayToCharacter.x);
	lua_pushnumber(L, rayToCharacter.y);
	lua_pushnumber(L, moveNumber);

	error = lua_pcall(L, 5, 5, NULL);

	moveNumber = lua_tonumber(L, -1); //får sista
	rayToCharacter.y = lua_tonumber(L, -2);
	rayToCharacter.x = lua_tonumber(L, -3);
	velocity.y = lua_tonumber(L, -4);
	velocity.x = lua_tonumber(L, -5);

	lua_pop(L, 5);



	//lua_pushnumber(L, velocity.y);
	//lua_pushnumber(L, this->moveCD);
	//lua_pushboolean(L, this->moved);
	//lua_pushstring(L, this->lastMove.c_str());

	//error = lua_pcall(L, 4, 4, NULL);

	//this->lastMove = lua_tostring(L, -1); //får sista
	//this->moved = lua_toboolean(L, -2);
	//this->moveCD = lua_tonumber(L, -3);
	//velocity.y = lua_tonumber(L, -4);

	//lua_pop(L, 4); //tar bort alla fyra

	
	/*if (rayToCharacter.x == 0 && rayToCharacter.y != 0)
	{
		if (rayToCharacter.y >= 0)
		{
			velocity.y += 128;
		}
		else
		{
			velocity.y -= 128;
		}
	}
	
	if (rayToCharacter.y == 0 && rayToCharacter.x != 0)
	{
		if (rayToCharacter.x >= 0)
		{
			velocity.x += 128;
		}
		else
		{
			velocity.x -= 128;
		}
	}

	if (rayToCharacter.x != 0 && rayToCharacter.y != 0)
	{
		int randRow = rand() % 2 + 1;

		if (randRow == 1)
		{
			if (rayToCharacter.x >= 0)
			{
				velocity.x += 128;
			}
			else
			{
				velocity.x -= 128;
			}
		}
		else if (randRow == 2)
		{
			if (rayToCharacter.y >= 0)
			{
				velocity.y += 128;
			}
			else
			{
				velocity.y -= 128;
			}
		}
	}*/
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

