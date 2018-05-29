#include "Character.h"

Character::Character()
{
}

Character::Character(sf::Texture * texture)
//:character()
{
	this->animatedCharacter = AnimatedSprite(*texture, sf::Vector2i(32.f, 32.f), 0.15f);
	this->animatedCharacter.setPosition({ 128, 512 });

	this->animatedCharacter.addAnimation("Idle", { 0, 8 });
	this->animatedCharacter.addAnimation("Attack", { 9, 21 });

	this->animatedCharacter.setAnimation("Idle");

	this->characterSize = 64.f;
	this->character = sf::CircleShape(this->characterSize);
	this->character.setPosition(128, 512);

	//middlepoint
	this->middlePoint = this->character.getPosition();
	this->middlePoint.x += this->characterSize;
	this->middlePoint.y += this->characterSize;

	this->tileSize = 128; //4 ggr 32
	this->moveCD = 1;
	this->moved = false;
	this->lastMove = "W";
	this->attacking = false;
	this->hasAttacked = false;
}

Character::~Character()
{

}

void Character::update(float sec, lua_State * L)
{
	this->animatedCharacter.update(sec);

	int error = luaL_dofile(L, "update.lua");

	if (error)
	{
		std::cout << "Errormsg: " << lua_tostring(L, -1);
		lua_pop(L, 1);
	}

	lua_getglobal(L, "update");

	lua_pushnumber(L, moveCD);
	lua_pushnumber(L, sec);

	error = lua_pcall(L, 2, 2, NULL); //L, in, ut, NULL

	if (error)
	{
		std::cout << "Errormsg: " << lua_tostring(L, -1);
		lua_pop(L, 1);
	}

	bool runMove = lua_toboolean(L, -1);
	this->moveCD = lua_tonumber(L, -2);

	lua_pop(L, 2);

	if (runMove)
	{
		this->move(L, sec);
	}
}

void Character::luaMove(lua_State* L, int velocityXChange, int velocityYChange, float moveCDChange,
	bool movedChange, string lastMoveChange, bool hasAttackedChange)
{
	int error = luaL_dofile(L, "character.lua");

	lua_getglobal(L, "move");

	//de som ska ändras
	lua_pushnumber(L, velocity.x);
	lua_pushnumber(L, velocity.y);

	//det som ska ändras med
	lua_pushnumber(L, velocityXChange);
	lua_pushnumber(L, velocityYChange);

	//ta tillbaka svar
	error = lua_pcall(L, 4, 2, NULL); //L, in, ut, NULL

	velocity.y = lua_tonumber(L, -1);
	velocity.x = lua_tonumber(L, -2);

	lua_pop(L, 2);

	//sätt dem i c++
	this->hasAttacked = hasAttackedChange; //får sista
	this->lastMove = lastMoveChange;
	this->moved = movedChange;
	this->moveCD = moveCDChange;
}

void Character::luaAttack(lua_State* L, int moveCDChange, bool movedChange, bool attackingChange,
	bool hasAttackedChange)
{
	//fixad föreddeta lua function
	this->moveCD = moveCDChange;
	this->moved = movedChange;
	this->attacking = attackingChange;
	this->hasAttacked = hasAttackedChange;
}

void Character::move(lua_State * L, float sec)
{
	velocity = { 0, 0 };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->luaAttack(L, 0, true, false, true);

		animatedCharacter.playAnimation("Attack", "Idle");
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->luaMove(L, 0, -128, 0, true, "N", false);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->luaMove(L, 0, 128, 0, true, "S", false);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->luaMove(L, -128, 0, 0, true, "A", false);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->luaMove(L, 128, 0, 0, true, "D", false);
	}





	//Sätter karaktärens nya position
	this->character.move(velocity);
	this->animatedCharacter.move(velocity);

	this->updateMiddlePoint();
}

void Character::updateMiddlePoint()
{
	this->middlePoint = this->character.getPosition();
	this->middlePoint.x += this->characterSize;
	this->middlePoint.y += this->characterSize;
}



void Character::setPos(int x, int y)
{
	this->animatedCharacter.setPosition({ float(x) * 128, float(y) * 128 });
	this->character.setPosition({ float(x) * 128, float(y) * 128 });
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	//target.draw(this->hurtbox);
	//target.draw(this->hitbox);
	//target.draw(this->character);
	//target.draw(this->debugMidPoint);
	target.draw(this->animatedCharacter);
}


sf::CircleShape Character::getCharacter()
{
	return this->character;
}

sf::FloatRect Character::getBoundingBox()
{
	return character.getGlobalBounds();
}

bool Character::getMoved()
{
	return this->moved;
}

sf::Vector2f Character::getMiddlePoint()
{
	return this->middlePoint;
}

string Character::getLastMoved()
{
	return this->lastMove;
}

bool Character::getHasAttacked()
{
	return this->hasAttacked;
}

void Character::setMoved(bool moved)
{
	this->moved = moved;
}

void Character::setMove(float x, float y)
{
	velocity = { x, y };
	this->character.move(velocity);
	this->animatedCharacter.move(velocity);

	this->updateMiddlePoint();
}

void Character::setHasAttacked(bool state)
{
	this->hasAttacked = state;
}
