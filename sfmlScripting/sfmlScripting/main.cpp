#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include <SFML/Audio.hpp>

int main()
{	
	lua_State * L = luaL_newstate();
	luaL_openlibs(L);

	sf::Texture texture;
	if (!texture.loadFromFile("../Sprites/SpriteShetah.png"))
	{	/* error...*/	}

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("../Sprites/StarPlatinumAllSheet.png"))
		throw "somthing is schreecing";

	Game* game = new Game(&texture, &playerTexture);

	sf::Music battleMusic;
	battleMusic.openFromFile("mus_dance_of_dog.ogg");
	battleMusic.setLoop(true);
	battleMusic.play();


	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

	Menu menu(window.getSize().x, window.getSize().y);

	sf::Clock clock;

	int play = 1;
	bool gameStarted = false;
	while (window.isOpen())
	{
		if (play == 1)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu.MoveUp();
						break;

					case sf::Keyboard::Down:
						menu.MoveDown();
						break;

					case sf::Keyboard::W:
						play = menu.Select(*game);
						break;
					}
				}
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			menu.draw(window);
			window.display();
		}
		else if (play == 2 && gameStarted == false)
		{
			game->setupMap(&texture);
			gameStarted = true;
		}
		else if (play == 2)
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
		else if(play == 0)
		{
			window.close();
		}
	}
	return 0;
}