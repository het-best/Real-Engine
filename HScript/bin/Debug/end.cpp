        shader.setUniform("uTime", time);
		shader.setUniform("uResolution", sf::Vector2f{ sfml_window.getSize() });
		shader.setUniform("uMouse", sf::Vector2f{ float(sf::Mouse::getPosition().x), float(sf::Mouse::getPosition().y) });
		sfml_window.clear();
		//sfml_window.draw(shape, &shader);
		sfml_window.display();
		try
		{
			time += 0.01;
		}
		catch (char* error)
		{
			time = 0;
		}
    }

    return 0;
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

int draw_text(sf::Color color, sf::String path, sf::String text, int size, sf::Text::Style type, sf::Text::Style type_two)
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

