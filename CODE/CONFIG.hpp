


#ifndef ENGINE_CONFIG_HPP
#define ENGINE_CONFIG_HPP

// WINDOWS LIBRARIES
#include <chrono>
#include <cmath>
#include <fstream> 
#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <unordered_map>
#include <unordered_set>

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

// GLUT
#include <GLUT/glut.h>

// GLM
#include <glm/gtc/type_ptr.hpp>

// SFML LIBRARIES
#include <SFML/Libraries/Cornered/RoundRect.cpp>
#include <SFML/Libraries/Cornered/Squircle.cpp>

using sf::Color;
using sf::Vector3i;
using sf::Vector3f;
using sf::Vector2i;
using sf::Vector2f;
using sf::RenderWindow;
using sf::ContextSettings;
using sf::Keyboard;
using sf::Event;
using sf::Clock;

using glm::vec3;
using glm::cross;

using std::endl;
using std::hash;
using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::to_string;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::remove;
using std::min;
using std::max;
using std::time_t;
using std::localtime;
using std::chrono::system_clock;

namespace ENGINE_CONFIG {
    extern const string ENGINE_VERSION;
    extern Vector2i WINDOW_RESOLUTION;
    extern string WINDOW_NAME;
    extern ContextSettings WINDOW_SETTINGS;
    extern RenderWindow SFML_WINDOW;

    extern uint WINDOW_NO_FOCUS_TIME;
}

#include "RENDERING.hpp"
#include "MATH.hpp"
#include "CAMERA.hpp"
#include "INPUT.hpp"
#include "MODEL.hpp"
#include "FILE.hpp"
#include "DEBUGGING.cpp"

#endif // ENGINE_CONFIG_HPP