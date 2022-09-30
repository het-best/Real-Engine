#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>

int log_add(std::string log);
int draw_circle(sf::Color color, float size, int position[2]);
int draw_polygon(sf::Color color, float size[255][2], int position[2]);
int set_title(std::string name);
int set_cursor_visible(bool visisble);

sf::ContextSettings settings;

sf::RenderWindow sfml_window(sf::VideoMode(1920, 1080), "Real engine", sf::Style::Fullscreen, settings);



int main()
{
    log_add("Engine has been loaded!");

    sfml_window.setFramerateLimit(60);
    settings.antialiasingLevel = 8;
    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    set_cursor_visible(false);
    while (sfml_window.isOpen())
    {
        sf::Event event;
        while (sfml_window.pollEvent(event))
        {
            // Закрываем окно если нажата кнопка закрытия
            if (event.type == sf::Event::Closed)
                sfml_window.close();

            if (event.type == sf::Event::KeyPressed) 
            {
                // обработка нажатия Escape
                if (event.key.code == sf::Keyboard::Escape)
                {
                    sfml_window.close();
                }
            }
        }


        int b[2] = { sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };
        draw_circle(sf::Color::Green,100.f , b);

        sfml_window.display();
    }

    return 0;
}

int log_add(std::string log)
{
    std::cout << log << "\n";
    return 0;
}

int set_cursor_visible(bool visisble)
{
    try
    {
        sfml_window.setMouseCursorVisible(visisble);
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}

int set_title(std::string name)
{
    try
    {
        sfml_window.setTitle(name);
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}

int draw_circle(sf::Color color, float size, int position[2])
{
    try
    {
        sf::CircleShape shape(size);
        shape.setPosition(position[0] - size, position[1] - size);
        shape.setFillColor(color);
        sfml_window.draw(shape);
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}

int draw_polygon(sf::Color color, float size[255][2], int position[2])
{
    try
    {
        float rec_size[255][2];
        for (int i = 0; i < sizeof(size) - 3; i++) rec_size[i][0] = size[i][0];
        for (int i = 0; i < sizeof(size) - 3; i++) rec_size[i][1] = size[i][1];
        size = new float[255][2];
        for (int i = 0; i < 255; i++)
        {
            size[i][0] = rec_size[i][0] + position[0];
            size[i][1] = rec_size[i][1] + position[1];
        }

        sf::ConvexShape shape;
        shape.setPointCount(sizeof(size) - 3);
        for (int i = 0; i < sizeof(size) - 3;i++)
        {
            shape.setPoint(i, sf::Vector2f(size[i][0], size[i][1]));
        }
        shape.setFillColor(color);
        sfml_window.draw(shape);
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}