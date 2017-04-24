#ifndef CHARACTER_H
#define CHARACTER_H
#include "Includes.h"
#include "Hitbox.h"

class Character : public sf::Drawable
{
private:
	sf::CircleShape character;
	sf::Vector2f velocity;

	int tileSize;
	float moveCD;

	Hitbox hitbox;
public:
	Character();
	~Character();

	void update(float sec);
	void move(float sec);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

	sf::CircleShape getCharacter();
};

#endif // !