#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{	
	lua_State * L = luaL_newstate();
	luaL_openlibs(L);

	sf::Texture texture;
	if (!texture.loadFromFile("../Sprites/SpriteSheet.png"))
	{	/* error...*/	}

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("../Sprites/StarPlatinum-sheet.png"))
		throw "autistic schreecing";

	Game* game = new Game(&texture, &playerTexture);

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
		game->update(sec, L);
		game->draw(window);
	}
	return 0;
}