#include <iostream>
#include <SFML/Graphics.hpp>
#include<windows.h>

#include <cmath>                                

#define PI 3.14159265   

struct Point
{
    int x, y;
    sf::RectangleShape point;

    Point(int x_, int y_)
    {
        x = x_;
        y = y_;
        point.setOrigin(sf::Vector2f(0, 0));
        point.setSize(sf::Vector2f(4.5, 4.5));
        point.setPosition(sf::Vector2f(x, y));
    }

    void set_pos_point(int x_, int y_)
    {
        point.setPosition(sf::Vector2f(x_, y_));
    }    
};


struct Grid
{
    int x0, y0;
    int size_x, size_y;
    std::vector<Point> grid;

    Grid(int x0_, int y0_, int size_x_, int size_y_)
    {
        x0 = x0_;
        y0 = y0_;
        size_x = size_x_;
        size_y = size_y_;
        for (int i = 0; i < size_x; i++)
        {
            for (int j = 0; j < size_y; j++)
            {
                Point crt_p(x0 +i*5, y0+j*5);
                grid.push_back(crt_p);
            }
        }
    }
    void move_grid(int x_, int y_)
    {
        int x0_ = grid[0].x;
        int y0_ = grid[0].y;

        for (int i = 0; i < grid.size(); i++)
        {
            int dx = grid[i].x - x0_;
            int dy = grid[i].y - y0_;
            grid[i].x = x_ + dx;
            grid[i].y = y_ + dy;
            grid[i].set_pos_point(grid[i].x, grid[i].y);
        }

    }

    void render_grid(sf::RenderWindow &window)
    {
        for (int i = 0; i < grid.size(); i++)
        {
            window.draw(grid[i].point);
        }
    }
    void change_color()
    {
        for (int i = 0; i < grid.size(); i++)
        {
            grid[i].point.setFillColor(sf::Color::Green);
        }
    }

    void boolean_cut(Grid tool)
    {
        for (int i = 0; i < tool.grid.size(); i++)
        {
            for (int j = 0; j < grid.size(); j++)
            {
                if (tool.grid[i].x == grid[j].x && tool.grid[i].y == grid[j].y)
                {
                    grid[j].point.setSize(sf::Vector2f(0, 0));
                }
            }
        }
    }

};


int main()
{

    int x = 500;
    int y = 500;

    // Создаем главное окно приложения
    sf::RenderWindow window(sf::VideoMode(800, 640), "SFML Test");

    Grid blank(50, 50, 130, 70);
    
    Grid tool(x, y, 11, 11);
    tool.change_color();

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text_fps;
    text_fps.setFont(font);
    text_fps.setCharacterSize(20);
    text_fps.setFillColor(sf::Color::White);

    sf::Clock clock;
    float time_end = clock.getElapsedTime().asSeconds();

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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { x -= 5; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { x += 5; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { y -= 5;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { y += 5;}
            //std::cout << "x = " << x << "   y = " << y << std::endl;
        }
        
        window.clear();

      
        tool.move_grid(x, y);
        blank.boolean_cut(tool);

        blank.render_grid(window);
        tool.render_grid(window);

        time_end = clock.getElapsedTime().asSeconds();
        int FPS = (int)(1 / time_end);
        std::string str = std::to_string(FPS);
        text_fps.setString(str);
        window.draw(text_fps);
        //std::cout <<"FPS = " << (int)(1 / time_end) << std::endl;
        

        window.display();
        
    }


    return 0;
}
