#include <SFML/Window.hpp>

namespace config {

	extern sf::Vector2i window_resolution = { 1920, 1080 };
	extern sf::String window_name = "Real Engine";
	extern sf::ContextSettings window_settings = sf::ContextSettings(24, 8, 16, 4, 6);
	extern sf::String window_icon = "icon.png";
}