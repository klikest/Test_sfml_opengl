#include <iostream>
#include <SFML/Graphics.hpp>

#include<windows.h>



int main()
{

    const int grid_x = 10;
    const int grid_y = 10;

    int x = 500;
    int y = 500;


    sf::RectangleShape move_rec;
    move_rec.setSize(sf::Vector2f(10, 10));
    move_rec.setOrigin(sf::Vector2f(0, 0));
    move_rec.setPosition(sf::Vector2f(x, y));

    sf::RectangleShape grid[grid_x][grid_y];

    for (int i = 0; i < grid_x; i++)
    {
        for (int j = 0; j < grid_y; j++)
        {
            grid[i][j].setSize(sf::Vector2f(10, 10));
            grid[i][j].setOrigin(sf::Vector2f(0, 0));
            grid[i][j].setPosition(sf::Vector2f(100 + 20*i, 100 + 20*j));
        }
    }

    // Создаем главное окно приложения
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");
    sf::RectangleShape rectangle;
    
    sf::Text message;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    message.setFont(font);
    message.setString("0");
    message.setCharacterSize(40);
    message.setFillColor(sf::Color::White);


    sf::Clock clock;
    float time_end = clock.getElapsedTime().asMilliseconds();

    // Главный цикл приложения
    while (window.isOpen())
    {
        clock.restart();
        // Обрабатываем события в цикле
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Кроме обычного способа наше окно будет закрываться по нажатию на Escape
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                x -= 10;
                move_rec.setPosition(sf::Vector2f(x, y));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                x += 10;
                move_rec.setPosition(sf::Vector2f(x, y));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                y -= 10;
                move_rec.setPosition(sf::Vector2f(x, y));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                y += 10;
                move_rec.setPosition(sf::Vector2f(x, y));
            }
        }
        
        Sleep(21);

        // Очистка
        window.clear();
        // Тут будут вызываться функции обновления и отрисовки объектов
        // Отрисовка
        window.draw(message);
        for (int i = 0; i < grid_x; i++)
        {
            for (int j = 0; j < grid_y; j++)
            {
                window.draw(grid[i][j]);
            }
        }
        window.draw(move_rec);
        window.display();
        time_end = clock.getElapsedTime().asSeconds();
        message.setString(std::to_string((int) round(1/time_end)));
    }

    return 0;
}
