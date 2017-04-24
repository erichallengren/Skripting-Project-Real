#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{	
	sf::Texture texture;
	if (!texture.loadFromFile("../Sprites/Stone.png"))
	{	/* error...*/	}

	Game* game = new Game(&texture);

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time elapsed = clock.restart();
		float sec = elapsed.asSeconds();
		game->update(sec);
		game->draw(window);
	}
	return 0;
}