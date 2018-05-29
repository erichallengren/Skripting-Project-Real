#include "Game.h"

Game::Game()
{
}

Game::Game(sf::Texture * texture, sf::Texture * playerTexture)
{
	score = 0;

	//120 l�ng, en f�r varje tile p� banan	
	map = "";
	mapTile = "";
	ifstream myfile("../Maps/map1.txt");

	if (!font.loadFromFile("arial.ttf"))
	{
		//error
	}
	scoreDisplay.setFont(font);
	scoreDisplay.setString("Score: " + std::to_string(score));
	scoreDisplay.setCharacterSize(36);
	scoreDisplay.setFillColor(sf::Color::White);


	amountOfWalls = 0;
	this->character = Character(playerTexture);
	this->monster = Monster(texture);


	if (myfile.is_open())
	{
		while (getline(myfile, map))
		{
			cout << map << '\n';
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	setupMap(texture);
	setupSelectionList(texture);
}

Game::~Game()
{

}

void Game::setupMap(sf::Texture * texture)
{
	for (int i = 0; i < 120; i++)
	{
		this->walls[i] = nullptr;
	}

	//map tiles
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			mapTile = map.substr((i * 15) + j, 1);

			this->list[(i * 15) + j] = new Tile(texture, mapTile, j * 128, i * 128);
			this->smallList[(i * 15) + j] = new Tile(texture, mapTile, j * 64, i * 64, true);
			if (mapTile == "6" || mapTile == "7" || mapTile == "8")
			{
				this->walls[(i * 15) + j] = list[(i * 15) + j];
			}
		}
	}
}

void Game::setupSelectionList(sf::Texture * texture)
{
	for (int i = 0; i < 8; i++)
	{
		selectList[i] = new Tile(texture, i, i * 128, 600, false, true);
	}
}

void Game::update(float sec, lua_State * L, lua_State * LU)
{
	scoreDisplay.setString("Score: " + std::to_string(score));

	this->character.update(sec, L);
	this->checkCollision(); //collision med v�ggen
	this->monster.update(this->character, this->nextTo, L, this->score);
}

void Game::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			window.draw(*list[(i * 15) + j]);
		}
	}

	window.draw(character);

	window.draw(monster);

	window.draw(scoreDisplay);

	window.display();
}

void Game::drawMap(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);

	for (int i = 0; i < 120; i++)
	{
		window.draw(*list[i]);
	}
}

void Game::drawSmallMap(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);

	for (int i = 0; i < 120; i++)
	{
		window.draw(*smallList[i]);
	}
}

void Game::drawSelectList(sf::RenderWindow & window)
{
	for (int i = 0; i < 8; i++)
	{
		window.draw(*selectList[i]);
	}
}

void Game::checkCollision()
{
	//Collosion med v�ggar
	for (int i = 0; i < 120; i++)
	{
		if (this->walls[i] != nullptr && i != 0 && i != 14 && i != 105 && i != 119)
		{
			if (this->character.getBoundingBox().intersects(this->walls[i]->getBoundingBox()))
			{
				if (character.getLastMoved() == "N")
				{
					character.setMove(0, 128);
				}
				else if (character.getLastMoved() == "S")
				{
					character.setMove(0, -128);
				}
				else if (character.getLastMoved() == "A")
				{
					character.setMove(128, 0);
				}
				else
				{
					character.setMove(-128, 0);
				}
			}
		}
		if (this->character.getBoundingBox().intersects(this->walls[0]->getBoundingBox()))
		{
			character.setMove(128, 128);
		}
		if (this->character.getBoundingBox().intersects(this->walls[14]->getBoundingBox()))
		{
			character.setMove(-128, 128);
		}
		if (this->character.getBoundingBox().intersects(this->walls[105]->getBoundingBox()))
		{
			character.setMove(128, -128);
		}
		if (this->character.getBoundingBox().intersects(this->walls[119]->getBoundingBox()))
		{
			character.setMove(-128, -128);
		}
	}
}

string Game::getMap()
{
	return this->map;
}

void Game::setMap(string m)
{
	this->map = m;
}

void Game::setTile(int place, int tile, sf::Texture * texture)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (place == ((i * 15) + j))
			{
				this->list[place] = new Tile(texture, tile, j * 128, i * 128);
				this->smallList[place] = new Tile(texture, tile, j * 64, i * 64, true);
				if (tile == 6 || tile == 7 || tile == 8)
				{
					this->walls[place] = list[place];
				}
				else
				{
					this->walls[place] = nullptr;
				}
			}
		}
	}
}

int Game::getScore()
{
	return this->score;
}
