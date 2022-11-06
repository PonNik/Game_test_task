#include "Block.h"

Block::Block(int coord_x, int coord_y, int _width, int _height, TypesBlock _type) 
	:coordX(coord_x), coordY(coord_y), width(_width), height(_height), type(_type)
{
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(coordX, coordY);
	
	shape.setOutlineColor(sf::Color::Yellow);
	shape.setOrigin(sf::Vector2f(width / 2, height / 2));

	setType(type);
}

TypesBlock Block::getType()
{
	return type;
}

sf::Vector2i Block::getPosition()
{
	return sf::Vector2i(coordX, coordY);
}

sf::Vector2i Block::getSize()
{
	return sf::Vector2i(width, height);
}

void Block::setType(TypesBlock _type)
{
	type = _type;
	switch (type)
	{
	case EMPTY:
		shape.setFillColor(sf::Color(66, 66, 66, 255));
		break;
	case BLOCKED:
		shape.setFillColor(sf::Color(33, 33, 33, 255));
		break;
	case RED:
		shape.setFillColor(sf::Color::Red);
		break;
	case GREEN:
		shape.setFillColor(sf::Color::Green);
		break;
	case YELLOW:
		shape.setFillColor(sf::Color::Yellow);
		break;
	default:
		shape.setFillColor(sf::Color::White);
		break;
	}
}

void Block::setPosition(sf::Vector2i vecPosition)
{
	shape.setPosition(vecPosition.x, vecPosition.y);
}

void Block::BlockSelected()
{
	if (isSelected && type != EMPTY && type != BLOCKED)
		shape.setOutlineThickness(5);
	else
		shape.setOutlineThickness(0);
}

bool Block::select(sf::Vector2i mousePos)
{
	if (mousePos.x >= coordX - width / 2 - 3 && mousePos.x <= coordX + width / 2 + 3 &&
		mousePos.y >= coordY - height / 2 - 3 && mousePos.y <= coordY + height / 2 + 3)
	{
		isSelected = true;
		return true;
	}
	else
		return false;

}

void Block::swapBlock(Block* block)
{
	if (block->getType() == EMPTY && isSelected)
	{
		if (block->getPosition().x >= coordX - width - 5 &&  block->getPosition().x <= coordX + 2 * width + 5 &&
			block->getPosition().y >= coordY - height - 5 && block->getPosition().y <= coordY + 2 * height + 5)
		{
			sf::Vector2i vec(coordX, coordY);
			setPosition(block->getPosition());
			block->setPosition(vec);
		}

	}
}

void Block::draw(sf::RenderWindow* window)
{
	window->draw(shape);
}