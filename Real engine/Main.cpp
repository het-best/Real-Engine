#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>

void log_add(std::string log);
int set_position(sf::Vector2i position);
int set_size(sf::Vector2u size);
int set_title(std::string name);
int set_cursor_visible(bool visisble);
int draw_text(sf::Color color, std::string path, std::string text, int size, sf::Text::Style type, sf::Text::Style type_two);
int draw_circle(sf::Color color, float size, int position[2]);
int draw_polygon(sf::Color color, float size[255][2], float position[2], int count);
int play_sound(std::string path);
int play_music(std::string path);
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
        //draw_text(sf::Color::Black, "font.ttf", "Привет", 50.f, sf::Text::Bold, sf::Text::Regular);

        shader.setUniform("uTime", time);
        shader.setUniform("uResolution", sf::Vector2f{ sfml_window.getSize() });
        shader.setUniform("uMouse", sf::Vector2f{ float(sf::Mouse::getPosition().x), float(sf::Mouse::getPosition().y) });
        sfml_window.clear();
        sfml_window.draw(shape, &shader);
        sfml_window.display();
        try 
        {
            time += 0.01;
        }
        catch(char* error)
        {
            time = 0;
        }
    }

    return 0;
}

int draw_cube(float position[2], float size)
{
    try
    {
        float sizing[255][2] = {
            {0.f * size, 0.f * size},
            {100.f * size, 50.f * size},
            {100.f * size, 150.f * size},
            {0.f * size, 100.f * size}
        };
        draw_polygon(sf::Color(24, 24, 24), sizing, position, 4);
        float sizing2[255][2] = {
            {100.f * size, 50.f * size},
            {200.f * size, 0.f * size},
            {200.f * size, 100.f * size},
            {100.f * size, 150.f * size}
        };
        draw_polygon(sf::Color::Black, sizing2, position, 4);
        float sizing3[255][2] = {
            {100.f * size, -50.f * size},
            {200.f * size, 0.f * size},
            {100.f * size, 50.f * size},
            {0.f * size, 0.f * size}
        };
        draw_polygon(sf::Color(40, 40, 40), sizing3, position, 4);
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}

void log_add(std::string log)
{
    std::cout << log << "\n";
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

int set_position(sf::Vector2i position)
{
    try
    {
        sfml_window.setPosition(position);
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}

int set_size(sf::Vector2u size)
{
    try
    {
        sfml_window.setSize(size);
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

int draw_text(sf::Color color, std::string path, std::string text, int size, sf::Text::Style type, sf::Text::Style type_two)
{
    try
    {
        sf::Font font;
        font.loadFromFile(path);

        sf::Text text_;
        text_.setFont(font);
        text_.setString(text);
        text_.setCharacterSize(size);
        text_.setFillColor(color);
        text_.setStyle(type | type_two);

        sfml_window.draw(text_);
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

int draw_polygon(sf::Color color, float size[255][2], float position[2], int count)
{
    try
    {
        float rec_size[255][2];
        for (int i = 0; i < 255 - 3; i++) rec_size[i][0] = size[i][0];
        for (int i = 0; i < 255 - 3; i++) rec_size[i][1] = size[i][1];
        size = new float[255][2];
        for (int i = 0; i < 255; i++)
        {
            size[i][0] = rec_size[i][0] + position[0];
            size[i][1] = rec_size[i][1] + position[1];
        }

        sf::ConvexShape shape;
        shape.setPointCount(count);
        for (int i = 0; i < count; i++)
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

int play_music(std::string path)
{
    try
    {
        sf::Music music;
        music.openFromFile(path);
        music.play();
        Sleep(music.getDuration().asMilliseconds());
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}

int play_sound(std::string path)
{
    try
    {
        sf::SoundBuffer buffer;
        buffer.loadFromFile(path);
        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();
        Sleep(5000);
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}