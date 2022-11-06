#pragma once
#include "Block.h"

class GameField
{
private:
	sf::Vector2i Position;
	sf::Vector2i elements_by;
	TypesBlock** elements;
	Block** blocks;
	Block* block;
	bool bottonPressed = false;
	bool WIN = false;
public:
	GameField(sf::Vector2i pos, sf::Vector2i elem_by);
	~GameField();

	void standartField(TypesBlock** elem);

	void checkWIN();
	
	void Input(sf::Event event, sf::RenderWindow* window);
	Block* search(sf::Vector2i pos);
	void draw(sf::RenderWindow* window);
};

