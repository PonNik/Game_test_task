#include "GameField.h"

GameField::GameField(sf::Vector2i pos, sf::Vector2i elem_by)
{
	Position = pos;
	elements_by = elem_by;
	elements = new TypesBlock* [elements_by.x];
	blocks = new Block * [elements_by.x];
	for (int i = 0; i < elements_by.x; i++)
	{
		elements[i] = new TypesBlock[elements_by.y];
		blocks[i] = new Block[elements_by.y];
	}
	std::srand(time(0));
	standartField(elements);

	for (int x = 0; x < elements_by.x; x++)
	{
		for (int y = 0; y < elements_by.y; y++)
		{
			blocks[x][y] = Block(Position.x + x * 50 + x * 5 + 25, Position.y + y * 50 + y * 5 + 25, 50, 50, elements[x][y]);
		}
	}
}	

GameField::~GameField()
{
	for (int x = 0; x < elements_by.x; x++)
	{
		delete[] elements[x];
		delete[] blocks[x];
	}
	delete[] elements;
	delete[] blocks;
}

void GameField::standartField(TypesBlock** elem)
{
	elem[0][0] = YELLOW;
	elem[0][1] = RED;
	elem[0][2] = GREEN;
	elem[0][3] = YELLOW;
	elem[0][4] = RED;

	elem[1][0] = BLOCKED;
	elem[1][1] = EMPTY;
	elem[1][2] = BLOCKED;
	elem[1][3] = EMPTY;
	elem[1][4] = BLOCKED;

	elem[2][0] = GREEN;
	elem[2][1] = GREEN;
	elem[2][2] = RED;
	elem[2][3] = YELLOW;
	elem[2][4] = RED;

	elem[3][0] = BLOCKED;
	elem[3][1] = EMPTY;
	elem[3][2] = BLOCKED;
	elem[3][3] = EMPTY;
	elem[3][4] = BLOCKED;

	elem[4][0] = YELLOW;
	elem[4][1] = YELLOW;
	elem[4][2] = RED;
	elem[4][3] = GREEN;
	elem[4][4] = GREEN;

}

void GameField::checkWIN()
{
	if (blocks[0][0].getType() == GREEN &&
		blocks[0][1].getType() == GREEN &&
		blocks[0][2].getType() == GREEN &&
		blocks[0][3].getType() == GREEN &&
		blocks[0][4].getType() == GREEN &&

		blocks[2][0].getType() == YELLOW &&
		blocks[2][1].getType() == YELLOW &&
		blocks[2][2].getType() == YELLOW &&
		blocks[2][3].getType() == YELLOW &&
		blocks[2][4].getType() == YELLOW &&

		blocks[4][0].getType() == RED &&
		blocks[4][1].getType() == RED &&
		blocks[4][2].getType() == RED &&
		blocks[4][3].getType() == RED &&
		blocks[4][4].getType() == RED)
		WIN = true;
}

void GameField::Input(sf::Event event, sf::RenderWindow* window)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Button::Left && !WIN)
		{
			block = search(sf::Mouse::getPosition(*window));
		}
	}
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.key.code == sf::Mouse::Button::Left)
		{
			if (!WIN && block->getType() != BLOCKED && block->getType() != EMPTY)
			{
				block->isSelected = false;
				block->setPosition(block->getPosition());
				Block* dop = nullptr;
				dop = search(sf::Mouse::getPosition(*window));
				if (Position.x <= sf::Mouse::getPosition(*window).x &&
					Position.y <= sf::Mouse::getPosition(*window).y &&
					Position.x + elements_by.x * 55 >= sf::Mouse::getPosition(*window).x &&
					Position.y + elements_by.y * 55 >= sf::Mouse::getPosition(*window).y) {
					if (dop != nullptr && dop->getType() == EMPTY && 
						dop->getPosition().y <= (block->getPosition().y + block->getSize().y * 3 / 2) &&
						dop->getPosition().y >= (block->getPosition().y - block->getSize().y * 3 / 2) &&
						dop->getPosition().x <= (block->getPosition().x + block->getSize().x * 3 / 2) &&
						dop->getPosition().x >= (block->getPosition().x - block->getSize().x * 3 / 2) && 
						!(dop->getPosition().y <= (block->getPosition().y - block->getSize().y) && dop->getPosition().x >= (block->getPosition().x + block->getSize().x))&&
						!(dop->getPosition().y <= (block->getPosition().y - block->getSize().y) && dop->getPosition().x <= (block->getPosition().x - block->getSize().x))&&
						!(dop->getPosition().y >= (block->getPosition().y + block->getSize().y) && dop->getPosition().x >= (block->getPosition().x + block->getSize().x))&&
						!(dop->getPosition().y >= (block->getPosition().y + block->getSize().y) && dop->getPosition().x <= (block->getPosition().x - block->getSize().x)))
					{
						dop->setType(block->getType());
						block->setType(EMPTY);
						checkWIN();
						if (WIN)
							window->setTitle("You Win!!!");
					}
					else
					{
						block->isSelected = false;
						block->setPosition(block->getPosition());
					}
				}
			}
		}
	}
	if (block != nullptr)
	{
		if (block->isSelected && event.type == sf::Event::MouseMoved)
		{
			if (Position.x <= sf::Mouse::getPosition(*window).x &&
				Position.y <= sf::Mouse::getPosition(*window).y &&
				Position.x + elements_by.x * 55 >= sf::Mouse::getPosition(*window).x &&
				Position.y + elements_by.y * 55 >= sf::Mouse::getPosition(*window).y) 
			{
				if (block->getType() != BLOCKED && block->getType() != EMPTY)
					block->setPosition(sf::Mouse::getPosition(*window));
			}
		}
	}

	
}

Block* GameField::search(sf::Vector2i mousePos)
{
	for (int x = 0; x < elements_by.x; x++)
	{
		for (int y = 0; y < elements_by.y; y++)
		{
			if (blocks[x][y].select(mousePos))
			{
				return &blocks[x][y];
			}
		}
	}
}

void GameField::draw(sf::RenderWindow* window)
{
	for (int x = 0; x < elements_by.x; x++)
	{
		for (int y = 0; y < elements_by.y; y++)
		{
			blocks[x][y].draw(window);
		}
	}
	if (block != nullptr)
	{
		block->draw(window);
	}
}
