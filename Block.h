#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

enum TypesBlock
{
	EMPTY = 0,
	BLOCKED = 1,
	RED = 2,
	GREEN = 3,
	YELLOW = 4
};

class Block
{
private:
	int coordX, coordY;
	int width, height;
	TypesBlock type;
	sf::RectangleShape shape;
public:
	bool isSelected = false;
	Block(int coord_x = 0, int coord_y = 0, int width = 50, int height = 50, TypesBlock type = EMPTY);
	
	void setType(TypesBlock type);
	void setPosition(sf::Vector2i vecPos);

	TypesBlock getType();
	sf::Vector2i getPosition();
	sf::Vector2i getSize();
	
	void BlockSelected();
	bool select(sf::Vector2i mousePos);
	void swapBlock(Block* block);

	void draw(sf::RenderWindow* window);
};

