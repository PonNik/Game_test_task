#include <SFML/Graphics.hpp>
#include "GameField.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(290, 350), "Game!");
    
    GameField gm(sf::Vector2i(10, 70), sf::Vector2i(5, 5));
    Block red(35, 35, 50, 50, GREEN);
    Block green(145, 35, 50, 50, YELLOW);
    Block yellow(255, 35, 50, 50, RED);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                sf::View view(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Vector2f(window.getSize().x, window.getSize().y));
                window.setView(view);
            }
            gm.Input(event, &window);
        }

        window.clear();
        gm.draw(&window);
        red.draw(&window);
        green.draw(&window);
        yellow.draw(&window);

        window.display();
    }

    return 0;
}