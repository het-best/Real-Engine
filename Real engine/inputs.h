#include <SFML/Graphics.hpp>
//#include "config.h"

namespace game_input {

	sf::String entered_text = "";

	sf::Vector2i mouse_position = { 0, 0 };

	bool is_key_pressed(sf::Keyboard::Key key)
	{
		if (sf::Keyboard::isKeyPressed(key))
		{
			return true;
		}
		return false;
	}

	bool is_joystick_connected(int number)
	{
		if (sf::Joystick::isConnected(number))
		{
			return true;
		}
		return false;
	}

	int get_joystick_buttons(int number)
	{
		if (sf::Joystick::isConnected(number))
		{
			return true;
		}
		return false;
	}
}