
//WINDOWS LIBRARIES
#include <windows.h>
#include <iostream>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

//SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//GLUT
#include <GLUT/glut.h>

//SHA256
#include "sha256.h"

//GLM
#include <glm/gtc/quaternion.hpp>

//SFML LIBRARIES
#include <SFML/Libraries/Cornered/RoundRect.cpp>
#include <SFML/Libraries/Cornered/Squircle.cpp>

//REAL ENGINE FILES
#include "inputs.h"
#include "world.h"
#include "config.h"

//REAL ENGINE FUNCTIONS
void log_add(std::string log);
void log_add(float log);
int set_position(sf::Vector2i position);
int set_size(sf::Vector2u size);
int set_title(sf::String name);
int set_cursor_visible(bool visisble);
int draw_text(sf::Color color, sf::String path, sf::String text, int size, sf::Text::Style type, sf::Text::Style type_two, sf::Vector2i position);
int draw_circle(sf::Color color, float size, sf::Vector2i position);
int draw_square(sf::Color color, sf::Vector2f size, float rounding, sf::Vector2i position);
int draw_polygon(sf::Color color, float size[255][2], sf::Vector2i position, int count);
int play_sound(sf::String path);
int play_music(sf::String path);
int draw_cube(float size, sf::Vector3f color, sf::Int16 transparency);
int draw_light(sf::Vector3f position, sf::Vector3f direction, sf::Vector3f color);

//SFML WINDOW
sf::RenderWindow sfml_window(sf::VideoMode(config::window_resolution.x, config::window_resolution.y), config::window_name, sf::Style::Default, config::window_settings);

int main()
{
    //VARIABLE FOR FOCUS
    bool focus = true;

    //ACTIVATE WINDOW
    sfml_window.setActive(true);

    //OPERATION WITH OPENGL
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    //glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //INITIALIZATION OBJECTS
    game_world::initialization_objects();

    auto image = sf::Image{};
    if (!image.loadFromFile(config::window_icon)) { log_add("ERROR TO LOAD FILE"); }

    sfml_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    //CLOCKS
    sf::Clock game_time;
    sf::Clock FPS;

    sf::Event event;
    while (sfml_window.pollEvent(event)) { sf::Mouse::setPosition(sf::Vector2i(config::window_resolution.x / 2, config::window_resolution.y / 2), sfml_window); }

    //MAIN CYCLE
    while (sfml_window.isOpen())
    {
        //EVENTS
        sf::Event event;
        while (sfml_window.pollEvent(event))
        {
            if (game_input::is_key_pressed(sf::Keyboard::Key::Escape)) { event.type = sf::Event::Closed; }
            if (event.type == sf::Event::Closed)
            {
                sfml_window.close();
            }
            else if (event.type == sf::Event::LostFocus)
            {
                focus = false;
            }
            else if (event.type == sf::Event::GainedFocus)
            {
                focus = true;
            }
            if (event.type == sf::Event::Resized)
            {
                glViewport(0, 0, event.size.width, event.size.height);
                config::window_resolution = { (int)event.size.width, (int)event.size.height };
            }
            if (event.type == sf::Event::MouseMoved)
            {
                game_input::mouse_position.x += event.mouseMove.x - config::window_resolution.x / 2;
                game_input::mouse_position.y += event.mouseMove.y - config::window_resolution.y / 2;
                sf::Mouse::setPosition(sf::Vector2i(config::window_resolution.x / 2, config::window_resolution.y / 2), sfml_window);
            }
        }
        if (focus)
        {
            //CLEARING BUFFERS
            //sfml_window.clear();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            //CLEARING OBJECTS
            game_world::clear_objects();

            //CLEAR MATRIX
            glLoadIdentity();

            //CHANGE CAMERA POSITION AND ROTAION 
            game_world::cam.degrees.x = -((float)game_input::mouse_position.x / config::window_resolution.x * 360 * game_world::cam.sensitivity / 50);
            game_world::cam.degrees.y = -((float)game_input::mouse_position.y / config::window_resolution.y * 360 * game_world::cam.sensitivity / 50);

            //CONVERTING THE DEGREES OF THE CAMERA INTO A POINT WHERE TO LOOK
            //game_world::cam.calculate_camera_physics(game_world::att);
            game_world::cam.degrees_into_point();

            //MOVING
            if (game_input::is_key_pressed(sf::Keyboard::W))
            {
                game_world::cam.position.x += game_world::cam.direction.x;
                game_world::cam.position.y += game_world::cam.direction.y;
                game_world::cam.position.z += game_world::cam.direction.z;
            }
            if (game_input::is_key_pressed(sf::Keyboard::S))
            {
                game_world::cam.position.x -= game_world::cam.direction.x;
                game_world::cam.position.y -= game_world::cam.direction.y;
                game_world::cam.position.z -= game_world::cam.direction.z;
            }
            if (game_input::is_key_pressed(sf::Keyboard::A))
            {
                game_world::cam.position.x -= game_world::cam.right.x;
                game_world::cam.position.y -= game_world::cam.right.y;
                game_world::cam.position.z -= game_world::cam.right.z;
            }
            if (game_input::is_key_pressed(sf::Keyboard::D))
            {
                game_world::cam.position.x += game_world::cam.right.x;
                game_world::cam.position.y += game_world::cam.right.y;
                game_world::cam.position.z += game_world::cam.right.z;
            }

            if (game_input::is_key_pressed(sf::Keyboard::Space))
            {
                game_world::cam.position.y += game_world::cam.speed;
            }
            if (game_input::is_key_pressed(sf::Keyboard::LShift))
            {
                game_world::cam.position.y -= game_world::cam.speed;
            }

            //CONVERTING THE DEGREES OF THE CAMERA INTO A POINT WHERE TO LOOK
            game_world::cam.rotation = { game_world::cam.position.x + game_world::cam.direction.x, game_world::cam.position.y + game_world::cam.direction.y, game_world::cam.position.z + game_world::cam.direction.z };

            game_world::current_camera = game_world::cam;

            //APPLY CAMERA POSITION, ROTAION AND PERSPECTIVE
            gluPerspective(game_world::current_camera.fov, (float)config::window_resolution.x / (float)config::window_resolution.y, 0.01, game_world::current_camera.max_distance);
            gluLookAt(
                game_world::current_camera.position.x, game_world::current_camera.position.y, game_world::current_camera.position.z,
                game_world::current_camera.rotation.x, game_world::current_camera.rotation.y, game_world::current_camera.rotation.z,
                game_world::current_camera.up.x, game_world::current_camera.up.y, game_world::current_camera.up.z);

            //DRAWING VOXELS
            game_world::obj.calculate_object_physics(game_world::att);
            int count = game_world::obj.update_objects(0);
            //game_world::att.strength = game_time.getElapsedTime().asSeconds() / 100.0;
            //game_world::att.position.x += game_time.getElapsedTime().asSeconds() / 100.0;

            for (int i = 0; i < game_world::objects_count; i++)
            {
                if (game_world::objects_position[i] != sf::Vector3f())
                {
                    glPushMatrix();
                    glTranslatef(game_world::objects_position[i].x, game_world::objects_position[i].y, game_world::objects_position[i].z);
                    glRotatef(game_world::objects_rotation[i].x, 1, 0, 0);
                    glRotatef(game_world::objects_rotation[i].y, 0, 1, 0);
                    glRotatef(game_world::objects_rotation[i].z, 0, 0, 1);

                    draw_cube(1.0, game_world::objects_color[i], game_world::objects_visible[i]);

                    glPopMatrix();
                }
            }

            sfml_window.pushGLStates();

            if (FPS.getElapsedTime().asMicroseconds() != 0)
                draw_text(sf::Color::White, "arial.ttf", std::to_string(1000000 / FPS.getElapsedTime().asMicroseconds()), 40, sf::Text::Style::Bold, sf::Text::Style::Bold, sf::Vector2i(0, 0));
            FPS.restart();

            sfml_window.popGLStates();

            sfml_window.display();
        }
    }

    return 0;
}

void log_add(std::string log)
{
    std::cout << log << "\n";
}

void log_add(float log)
{
    std::cout << std::to_string(log) << "\n";
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
        config::window_resolution = sf::Vector2i(size);
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}

int set_title(sf::String name)
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

int draw_text(sf::Color color, sf::String path, sf::String text, int size, sf::Text::Style type, sf::Text::Style type_two, sf::Vector2i position)
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
        text_.setPosition(position.x, position.y);

        sfml_window.draw(text_);
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}

int draw_circle(sf::Color color, float size, sf::Vector2i position)
{
    try
    {
        sf::CircleShape shape(size);
        shape.setPosition(position.x - size, position.y - size);
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

int draw_square(sf::Color color, sf::Vector2f size, float rounding, sf::Vector2i position)
{
    try
    {
        crd::RoundRect shape({ size.x, size.y }, rounding);
        shape.setFillColor(color);
        shape.setPosition(position.x, position.y);
        sfml_window.draw(shape);
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}

int draw_polygon(sf::Color color, float size[255][2], sf::Vector2i position, int count)
{
    try
    {
        float rec_size[255][2];
        for (int i = 0; i < 255 - 3; i++) rec_size[i][0] = size[i][0];
        for (int i = 0; i < 255 - 3; i++) rec_size[i][1] = size[i][1];
        size = new float[255][2];
        for (int i = 0; i < 255; i++)
        {
            size[i][0] = rec_size[i][0] + position.x;
            size[i][1] = rec_size[i][1] + position.y;
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

int play_music(sf::String path)
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

int play_sound(sf::String path)
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

int draw_cube(float size, sf::Vector3f color, sf::Int16 transparency)
{
    try
    {
        glColor4f(color.x, color.y, color.z, transparency / 256.0);

        glBegin(GL_QUADS);

        //glColor3f(1, 0, 0);
        glVertex3f(-size / 2, -size / 2, -size / 2);
        glVertex3f(-size / 2, size / 2, -size / 2);
        glVertex3f(-size / 2, size / 2, size / 2);
        glVertex3f(-size / 2, -size / 2, size / 2);

        //glColor3f(0, 1, 0);
        glVertex3f(size / 2, -size / 2, -size / 2);
        glVertex3f(size / 2, -size / 2, size / 2);
        glVertex3f(size / 2, size / 2, size / 2);
        glVertex3f(size / 2, size / 2, -size / 2);

        //glColor3f(0, 0, 1);
        glVertex3f(-size / 2, -size / 2, -size / 2);
        glVertex3f(-size / 2, -size / 2, size / 2);
        glVertex3f(size / 2, -size / 2, size / 2);
        glVertex3f(size / 2, -size / 2, -size / 2);

        //glColor3f(1, 1, 0);
        glVertex3f(-size / 2, size / 2, -size / 2);
        glVertex3f(-size / 2, size / 2, size / 2);
        glVertex3f(size / 2, size / 2, size / 2);
        glVertex3f(size / 2, size / 2, -size / 2);

        //glColor3f(0, 1, 1);
        glVertex3f(-size / 2, -size / 2, -size / 2);
        glVertex3f(size / 2, -size / 2, -size / 2);
        glVertex3f(size / 2, size / 2, -size / 2);
        glVertex3f(-size / 2, size / 2, -size / 2);

        //glColor3f(1, 0, 1);
        glVertex3f(-size / 2, -size / 2, size / 2);
        glVertex3f(size / 2, -size / 2, size / 2);
        glVertex3f(size / 2, size / 2, size / 2);
        glVertex3f(-size / 2, size / 2, size / 2);
        glEnd();
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}

//In developing
int draw_light(sf::Vector3f position, sf::Vector3f direction, sf::Vector3f color)
{
    try
    {
        float pos[4] = { position.x, position.y, position.z, 0 };
        float dir[3] = { direction.x, direction.y, direction.z };
        float col[4] = { color.x, color.y, color.z, 1 };

        glLightfv(GL_LIGHT0, GL_POSITION, pos);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
        return 0;
    }
    catch (char* error)
    {
        log_add(error);
        return 1;
    }
}