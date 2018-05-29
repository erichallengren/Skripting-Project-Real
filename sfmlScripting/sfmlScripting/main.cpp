#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include <SFML/Audio.hpp>
//hej
int main()
{
	lua_State * L = luaL_newstate();
	luaL_openlibs(L);

	lua_State * LU = luaL_newstate();
	luaL_openlibs(LU);

	sf::Texture texture;
	if (!texture.loadFromFile("../Sprites/SpriteShetah.png"))
	{	/* error...*/
	}

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
	int menuEditIndex = 0;

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

					case sf::Keyboard::Right:
						play = menu.Select(*game, window.getSize().x, window.getSize().y, play);

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
		else if (play == 3)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Left:
						play = 1;
						break;

					case sf::Keyboard::Num1:
						game->setTile(menuEditIndex++, 0, &texture);
						break;
					case sf::Keyboard::Num2:
						game->setTile(menuEditIndex++, 1, &texture);
						break;
					case sf::Keyboard::Num3:
						game->setTile(menuEditIndex++, 2, &texture);
						break;
					case sf::Keyboard::Num4:
						game->setTile(menuEditIndex++, 3, &texture);
						break;
					case sf::Keyboard::Num5:
						game->setTile(menuEditIndex++, 4, &texture);
						break;
					case sf::Keyboard::Num6:
						game->setTile(menuEditIndex++, 5, &texture);
						break;
					case sf::Keyboard::Num7:
						game->setTile(menuEditIndex++, 6, &texture);
						break;
					case sf::Keyboard::Num8:
						game->setTile(menuEditIndex++, 7, &texture);
						break;
					}
				}
				if (event.type == sf::Event::Closed)
					window.close();
			}

			//game->drawMap(window);
			game->drawSmallMap(window);
			game->drawSelectList(window);
			menu.draw(window);
			window.display();
		}
		else if (play == 2 && gameStarted == false)
		{
			//game->setupMap(&texture);
			gameStarted = true;
		}
		else if (play == 2)		// köras spelet
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			sf::Time elapsed = clock.restart();
			float sec = elapsed.asSeconds();
			game->update(sec, L, LU);

			game->draw(window);
			if (game->getScore() > 9 || game->getScore() < -9)
			{
				game->getScore();
				play = 4;
			}
		}
		else if (play == 4)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:

					break;
				}
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			int score = game->getScore();
			if (score >= 10)
			{
				menu.drawEnd(window, true);
			}
			else if (score < 10)
			{
				menu.drawEnd(window, false);
			}
			window.display();
		}
		else if (play == 0)
		{
			window.close();
		}
	}
	return 0;
}