


#ifndef ENGINE_CONFIG_CPP
#define ENGINE_CONFIG_CPP

#include "CONFIG.hpp"

namespace ENGINE_CONFIG {
    const string ENGINE_VERSION = "0.14.12.2024";
    Vector2i WINDOW_RESOLUTION = Vector2i(1920, 1080);
    string WINDOW_NAME = "HET BEST ENGINE v" + ENGINE_VERSION;
    ContextSettings WINDOW_SETTINGS = sf::ContextSettings(24, 8, 0, 4, 6);
    RenderWindow SFML_WINDOW(
        sf::VideoMode(WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y),
        WINDOW_NAME,
        sf::Style::Default,
        WINDOW_SETTINGS
    );

    uint WINDOW_NO_FOCUS_TIME = 1000;
}

#endif // ENGINE_CONFIG_CPP