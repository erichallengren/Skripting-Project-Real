#include "Game.h"

Game::Game()
{
	amountOfWalls = 0;
	this->character = Character();
	this->monster = Monster();
}

Game::Game(sf::Texture * texture)
{
	//120 lång, en för varje tile på banan	
	string map = "";//1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890ab
	string mapTile = "";
	ifstream myfile("../Maps/map1.txt");

	amountOfWalls = 0;
	this->character = Character(texture, 2, 2);
	this->monster = Monster(texture, 6, 6);
	

	if (myfile.is_open())
	{
		while (getline(myfile, map))
		{
			cout << map << '\n';
		}
		myfile.close();
	}
	else cout << "Unable to open file";

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
			if (mapTile == "1")
			{
				this->walls[(i * 15) + j] = list[(i * 15) + j];
			}
		}
	}
	
}

Game::~Game()
{

}

void Game::update(float sec)
{
	bool moved = false;

	this->character.update(sec);
	this->monster.update(this->character);
	this->checkCollision();
}

void Game::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);

	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 15; j++)
		{
			window.draw( * list[(i * 15) + j]);
		}
	}

	window.draw(character);

	window.draw(monster);

	window.display();
}

void Game::checkCollision()
{
	if (this->character.getBoundingBox().intersects(this->monster.getBoundingBox()))
	{
		if (character.getLastMoved() == "N")
		{
			character.setMove(0, 128);
		}
		else if (character.getLastMoved() == "S")
		{
			character.setMove(0, -128);
		}
		else if (character.getLastMoved() == "W")
		{
			character.setMove(128, 0);
		}
		else
		{
			character.setMove(-128, 0);
		}
	}

	for (int i = 0; i < 120; i++)
	{
		if (this->walls[i] != nullptr)
		{
			if (this->character.getBoundingBox().intersects(this->walls[i]->getBoundingBox()))
			{
				if (character.getLastMoved() == "N")
				{
					character.setMove(0, 128);
				}
				else if(character.getLastMoved() == "S")
				{
					character.setMove(0, -128);
				}
				else if (character.getLastMoved() == "W")
				{
					character.setMove(128, 0);
				}
				else
				{
					character.setMove(-128, 0);
				}
			}
		}
	}

	//if (this->character.getHitbox().intersect(this->monster.getHitbox()))
	//{
	////	this->character
	//	//this->character.getCharacter().setFillColor(sf::Color::Black);
	//}
}