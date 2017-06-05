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
	this->lastMove = "W";
	this->attacking = false;
	this->hasAttacked = false;

	//hitbox
	// character
	this->hitbox.setPosition(this->character.getPosition());
	this->hitbox.setOrigin(sf::Vector2f(this->character.getPosition()));
	this->hitbox.setSize(sf::Vector2f(128, 128));

	this->hurtbox.setPosition(this->character.getPosition());
	this->hurtbox.setOrigin(sf::Vector2f(this->character.getPosition()));
	this->hurtbox.setSize(sf::Vector2f(128, 128));

	//debug
	this->debugMidPoint.setRadius(10);
	this->debugMidPoint.setFillColor(sf::Color::Red);
}

Character::Character(sf::Texture * texture, int x, int y) 
	//:character()
{
	this->animatedCharacter = AnimatedSprite(*texture, sf::Vector2i(32.f, 32.f), 0.15f);
	this->animatedCharacter.setPosition({ 128, 512 });

	this->animatedCharacter.addAnimation("Idle", { 0, 8 });
	this->animatedCharacter.addAnimation("Attack", {9, 21});

	this->animatedCharacter.setAnimation("Idle");

	this->characterSize = 64.f;
	this->character = sf::CircleShape(this->characterSize);
	this->character.setPosition(128, 512);
	//this->character.setFillColor(sf::Color::Green);

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

	//hitbox
	// character
	this->hitbox.setPosition(this->character.getPosition());
	this->hitbox.setOrigin(sf::Vector2f(this->character.getPosition()));
	this->hitbox.setSize(sf::Vector2f(128, 128));

	this->hurtbox.setPosition(this->character.getPosition());
	this->hurtbox.setOrigin(sf::Vector2f(this->character.getPosition()));
	this->hurtbox.setSize(sf::Vector2f(128, 128));

	//debug
	this->debugMidPoint.setRadius(10);
	this->debugMidPoint.setFillColor(sf::Color::Red);

	//new shit
	//this->character.setPosition(x, y);
	this->character.setTexture(texture);
	this->character.setTextureRect(sf::IntRect(32*5, 0, 32, 32));

}

Character::~Character()
{

}

void Character::update(float sec, lua_State * L)
{
	this->animatedCharacter.update(sec);
	this->moveCD += sec;
	if (this->moveCD >= 0.5)
	{
		this->move(sec, L);
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
	//lua_pushnumber(L, this->moveCD);
	//lua_pushboolean(L, this->moved);
	//lua_pushstring(L, this->lastMove.c_str());
	//lua_pushboolean(L, this->hasAttacked);

	//det som ska ändras med
	lua_pushnumber(L, velocityXChange);
	lua_pushnumber(L, velocityYChange);
	lua_pushnumber(L, moveCDChange);
	lua_pushboolean(L, movedChange);
	lua_pushstring(L, lastMoveChange.c_str());
	lua_pushboolean(L, hasAttackedChange);

	//ta tillbaka svar
	error = lua_pcall(L, 8, 6, NULL); //L, in, ut, NULL

	//sätt dem i c++
	this->hasAttacked = lua_toboolean(L, -1); //får sista
	this->lastMove = lua_tostring(L, -2);
	this->moved = lua_toboolean(L, -3);
	this->moveCD = lua_tonumber(L, -4);
	velocity.y = lua_tonumber(L, -5);
	velocity.x = lua_tonumber(L, -6);

	//ta bort alla
	lua_pop(L, 6);
}

void Character::luaAttack(lua_State* L, int moveCDChange, bool movedChange, bool attackingChange,
						  bool hasAttackedChange)
{
	int error = luaL_dofile(L, "character.lua");

	lua_getglobal(L, "attack");

	//de som ska ändras
	lua_pushnumber(L, this->moveCD);
	lua_pushboolean(L, this->moved);
	lua_pushboolean(L, this->attacking);
	lua_pushboolean(L, this->hasAttacked);

	//det som ska ändras med
	lua_pushnumber(L, moveCDChange);
	lua_pushboolean(L, movedChange);
	lua_pushboolean(L, attackingChange);
	lua_pushboolean(L, hasAttackedChange);

	//ta tillbaka svar
	error = lua_pcall(L, 8, 4, NULL);

	//sätt dem i c++
	this->hasAttacked = lua_toboolean(L, -1);
	this->attacking = lua_toboolean(L, -2);
	this->moved = lua_toboolean(L, -3);
	this->moveCD = lua_tonumber(L, -4);

	//ta bort alla
	lua_pop(L, 4);
}

void Character::move(float sec, lua_State * L)
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

	//hitbox
	this->hitbox.move(velocity);
	this->hitbox.setPosition(hitbox.getPosition());
	this->hitbox.updateHitboxDrawable();

	//hitbox
	this->hurtbox.move(velocity);
	this->hurtbox.setPosition(hurtbox.getPosition());
	this->hurtbox.updateHitboxDrawable();

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

sf::FloatRect Character::getHitboxBoundingBox()
{
	return this->hurtbox.getBoundingBox();
}

Hitbox Character::getHitbox()
{
	return this->hitbox;
}

Hitbox Character::getHurtbox()
{
	return this->hurtbox;
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

	//hitbox

	this->hitbox.move(velocity);
	this->hitbox.setPosition(hitbox.getPosition());
	this->hitbox.updateHitboxDrawable();

	this->hurtbox.move(velocity);
	this->hurtbox.setPosition(hurtbox.getPosition());
	this->hurtbox.updateHitboxDrawable();

	this->updateMiddlePoint();
}

void Character::setHasAttacked(bool state)
{
	this->hasAttacked = state;
}
