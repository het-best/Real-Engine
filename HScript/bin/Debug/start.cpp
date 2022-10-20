#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>

void log_add(std::string log);
int set_position(sf::Vector2i position);
int set_size(sf::Vector2u size);
int set_title(sf::String name);
int set_cursor_visible(bool visisble);
int draw_text(sf::Color color, sf::String path, sf::String text, int size, sf::Text::Style type, sf::Text::Style type_two);
int draw_circle(sf::Color color, float size, int position[2]);
int draw_polygon(sf::Color color, float size[255][2], float position[2], int count);
int play_sound(sf::String path);
int play_music(sf::String path);
int draw_cube(float position[2], float size);

sf::RenderWindow sfml_window(sf::VideoMode(1920, 1080), "Real engine", sf::Style::Fullscreen);



int main()
{
    sfml_window.setVerticalSyncEnabled(true);
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    log_add("Engine has been loaded!");

    sf::Shader shader;
    shader.loadFromFile("Shader.frag", sf::Shader::Fragment);

    auto shape = sf::RectangleShape{ sf::Vector2f{ sfml_window.getSize() } };

    float time = 0;
    sf::Clock clock;
    while (sfml_window.isOpen())
    {
        sf::Event event;
        while (sfml_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                sfml_window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    sfml_window.close();
                }
            }
        }