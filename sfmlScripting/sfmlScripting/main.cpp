#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::Clock time;
	float deltaTime;
	Game* game = new Game();

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	while (window.isOpen())
	{
		deltaTime = time.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		game->update(deltaTime);
		game->draw(&window);
	}
	return 0;
}