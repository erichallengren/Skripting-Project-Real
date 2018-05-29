#ifndef CHARACTER_H
#define CHARACTER_H
#include "Includes.h"
#include "Hitbox.h"
#include "AnimatedSprite.h"

class Character : public sf::Drawable
{
private:
	AnimatedSprite animatedCharacter;
	sf::CircleShape character;
	float characterSize;
	sf::Vector2f middlePoint;
	sf::Vector2f velocity;
	sf::Vector2f velocityh;

	int tileSize;
	float moveCD;
	bool moved;
	string lastMove;
	bool attacking;
	bool hasAttacked;

public:
	Character();
	Character(sf::Texture * texture);
	~Character();

	void update(float sec, lua_State * L);

	void setLua(lua_State * L);
	static int LuaRunner(lua_State * L);

	void luaMove(lua_State* L, int velocityXChange, int velocityYChange, float moveCDChange,
		bool movedChange, string lastMoveChange, bool hasAttackedChange);

	void luaAttack(lua_State* L, int moveCDChange, bool movedChange,
		bool attackingChange, bool hasAttackedChange);

	void move(lua_State * L, float sec);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	void updateMiddlePoint();


	sf::CircleShape getCharacter();
	sf::FloatRect getBoundingBox();
	bool getMoved();
	sf::Vector2f getMiddlePoint();
	string getLastMoved();
	bool getHasAttacked();


	void setPos(int x, int y);
	void setMoved(bool moved);
	void setMove(float x, float y);
	void setHasAttacked(bool state);
};

#endif // !