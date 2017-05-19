#include "Game.h"

Game::Game()
{
	amountOfWalls = 0;
	this->character = Character();
	this->monster = Monster();
	this->nextTo = false;
}

Game::Game(sf::Texture * texture, sf::Texture * playerTexture)
{
	score = 0;
	//120 lång, en för varje tile på banan	
	string map = "";
	string mapTile = "";
	ifstream myfile("../Maps/map1.txt");

	if (!font.loadFromFile("arial.ttf"))
	{
		//error
	}
	scoreDisplay.setFont(font);
	scoreDisplay.setString("Score: " + std::to_string(score));
	scoreDisplay.setCharacterSize(24);
	scoreDisplay.setFillColor(sf::Color::Red);


	amountOfWalls = 0;
	this->character = Character(playerTexture, 2, 2);
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
			if (mapTile == "8")
			{
				this->walls[(i * 15) + j] = list[(i * 15) + j];
			}
		}
	}
	
}

Game::~Game()
{

}

void Game::update(float sec, lua_State * L)
{


	scoreDisplay.setString("Score: " + std::to_string(score));

	this->character.update(sec, L);
	this->checkCollision(); //collision med väggen
	this->monster.update(this->character, this->nextTo, L, this->score);
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

	window.draw(scoreDisplay);

	window.display();
}

void Game::checkCollision()
{
	/*this->nextTo = false;

	sf::Vector2f distance = (this->character.getMiddlePoint() - this->monster.getMiddlePoint());

	if (distance.x == 128 && distance.y == 0 || distance.x == 0 && distance.y == 128)
	{
		nextTo = true;
		score++;
	}

	if (distance.x == -128 && distance.y == 0 || distance.x == 0 && distance.y == -128)
	{
		nextTo = true;
		score++;
	}*/

	//Collosion med väggar
	for (int i = 0; i < 120; i++)
	{
		if (this->walls[i] != nullptr && i != 0 && i != 14 && i != 105 && i != 119 )
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