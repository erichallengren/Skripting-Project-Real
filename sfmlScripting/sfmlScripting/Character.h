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
	sf::CircleShape debugMidPoint;

	int tileSize;
	float moveCD;
	bool moved;
	string lastMove;

	Hitbox hitbox;
public:
	Character();
	Character(sf::Texture * texture, int x = 0, int y = 0);
	~Character();

	void update(float sec);
	void move(float sec);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	void updateMiddlePoint();

	sf::CircleShape getCharacter();
	sf::FloatRect getBoundingBox();
	Hitbox getHitbox();
	bool getMoved();
	sf::Vector2f getMiddlePoint();
	string getLastMoved();


	void setPosition(int x, int y);
	void setMoved(bool moved);
	void setMove(float x, float y);
};

#endif // !