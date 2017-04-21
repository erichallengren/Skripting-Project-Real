#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game* game = new Game();

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

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
		game->draw(&window);
	}
	return 0;
}