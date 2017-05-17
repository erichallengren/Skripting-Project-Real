#ifndef HITBOX_H
#define HITBOX_H
#include "Includes.h"

class Hitbox : public sf::Drawable
{
private:
	sf::FloatRect box;
	sf::RectangleShape hitboxDrawable;
	sf::Vector2f origin;
	sf::Vector2f position;
public:
	Hitbox();
	~Hitbox();
	void setOrigin(sf::Vector2f origin);
	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);

	bool intersect(const Hitbox &other);
	void move(sf::Vector2f velocity);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

	void updateHitboxDrawable();
	sf::FloatRect getBox();
	sf::Vector2f getPosition();
	sf::FloatRect getBoundingBox();
};

#endif // !HITBOX_H