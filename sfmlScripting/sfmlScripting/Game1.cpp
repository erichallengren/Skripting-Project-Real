#include "Game.h"

Game::Game()
{
	amountOfWalls = 0;
	this->character = Character();
	this->monster = Monster();
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

void Game::update(float sec, lua_State * L)
{
	bool moved = false;
	bool nextTo = false;
	sf::Vector2f distance = this->character.getMiddlePoint() - this->monster.getMiddlePoint();
	if(distance.x == 128 && distance.y == 0 || distance.x == 0 && distance.y == 128 )
	{
		nextTo = true;
	}
	this->character.update(sec, L);
	distance = this->character.getMiddlePoint() - this->monster.getMiddlePoint();
	if (distance.x == 128 && distance.y == 0 || distance.x == 0 && distance.y == 128)
	{
		nextTo = true;
	}
	this->monster.update(this->character, nextTo, L);
	this->checkCollision();

	scoreDisplay.setString("Score: " + std::to_string(score));
	nextTo = false;
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
	bool nextTo = false;
	sf::Vector2f distance = this->character.getMiddlePoint() - this->monster.getMiddlePoint();
	if (distance.x == 128 && distance.y == 0 || distance.x == 0 && distance.y == 128)
	{
		nextTo = true;
	}
	else if (distance.x == -128 && distance.y == 0 || distance.x == 0 && distance.y == -128)
	{
		nextTo = true;
	}
	bool caracterAtt = this->character.getHasAttacked();
	bool monsterAtt = this->monster.getHasAttacked();
	if (caracterAtt && !monsterAtt)
	{
		score++;
		this->character.setHasAttacked(false);
	}
	else if (!caracterAtt && monsterAtt)
	{
		score--;
		this->monster.setHasAttacked(false);
	}

	//if (this->character.getBoundingBox().intersects(this->monster.getBoundingBox())/* || this->character.getBoundingBox().intersects(this->monster.getHurtboxBoundingBox())*/)
	//{
	//	if (character.getLastMoved() == "N")
	//	{
	//		character.setMove(0, 128);
	//	}
	//	else if (character.getLastMoved() == "S")
	//	{
	//		character.setMove(0, -128);
	//	}
	//	else if (character.getLastMoved() == "W")
	//	{
	//		character.setMove(128, 0);
	//	}
	//	else
	//	{
	//		character.setMove(-128, 0);
	//	}
	//	this->score--;
	//}
	//if (this->monster.getBoundingBox().intersects(this->character.getHitboxBoundingBox()))
	//{
	//	if (character.getLastMoved() == "N")
	//	{
	//		monster.setMove(0, -128);
	//	}
	//	else if (character.getLastMoved() == "S")
	//	{
	//		monster.setMove(0, 128);
	//	}
	//	else if (character.getLastMoved() == "W")
	//	{
	//		monster.setMove(-128, 0);
	//	}
	//	else
	//	{
	//		monster.setMove(128, 0);
	//	}
	//	this->score++;
	//}

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