#include <windows.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


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

sf::RenderWindow sfml_window(sf::VideoMode(1920, 1080), "Real engine", sf::Style::Default);

int main()
{
    bool focus = true;
    int mouse_position_int[2] = { sfml_window.getSize().x / 2, sfml_window.getSize().y / 2 };
    float mouse_position[2] = { 0, 0 };
    float mouse_sensitivity = 3.0f;

    bool keyboard_buttons[98] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
    bool joysticks_buttons[4][9] = {
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false
    };
    bool joysticks_axes[4][7] = {
        false, false, false, false, false, false, false,
        false, false, false, false, false, false, false,
        false, false, false, false, false, false, false,
        false, false, false, false, false, false, false
    };
    bool joysticks_connect[4] = { false, false, false, false };

    sf::Vector3f light_position = { -5.0f, 0.0f, 0.0f };

    float max_distance = 100.0f;
    float fov = 1.0;
    sf::Vector3f camera_position = sf::Vector3f(-5.0f, 0.0f, 0.0f);
    float camera_speed = 0.15f;

    sf::Vector3f objects[64] = {
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0),
        sf::Vector3f(1.0, 2.0, 0.0)
    };

    sfml_window.setVerticalSyncEnabled(true);
    //ShowWindow(GetConsoleWindow(), SW_HIDE);

    sf::RenderTexture shader_placeholder_;
    shader_placeholder_.create(sfml_window.getSize().x, sfml_window.getSize().y);
    sf::Sprite shader_placeholder = sf::Sprite(shader_placeholder_.getTexture());

    sf::Shader shader;
    shader.loadFromFile("Shader.frag", sf::Shader::Fragment);

    sf::Clock game_time;
    sf::Clock FPS;

    set_cursor_visible(false);
    log_add("Engine has been loaded!");

	while (sfml_window.isOpen())
	{
		sf::Event event;
		while (sfml_window.pollEvent(event))
		{
            if (event.type == sf::Event::LostFocus)
            {
                focus = false;
            }
            else if (event.type == sf::Event::GainedFocus)
            {
                focus = true;
            }
			else if (event.type == sf::Event::Closed)
			{
				sfml_window.close();
			}
			else if (event.type == sf::Event::MouseMoved)
			{
                mouse_position_int[0] += event.mouseMove.x - sfml_window.getSize().x / 2;
                mouse_position_int[1] += event.mouseMove.y - sfml_window.getSize().y / 2;
				sf::Mouse::setPosition(sf::Vector2i(sfml_window.getSize().x / 2, sfml_window.getSize().y / 2), sfml_window);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
                    sfml_window.close();
				}
				else if (event.key.code == sf::Keyboard::Unknown) keyboard_buttons[0] = true;
                else if (event.key.code == sf::Keyboard::Q) keyboard_buttons[1] = true;
                else if (event.key.code == sf::Keyboard::W) keyboard_buttons[2] = true;
                else if (event.key.code == sf::Keyboard::E) keyboard_buttons[3] = true;
                else if (event.key.code == sf::Keyboard::R) keyboard_buttons[4] = true;
                else if (event.key.code == sf::Keyboard::T) keyboard_buttons[5] = true;
                else if (event.key.code == sf::Keyboard::Y) keyboard_buttons[6] = true;
                else if (event.key.code == sf::Keyboard::U) keyboard_buttons[7] = true;
                else if (event.key.code == sf::Keyboard::I) keyboard_buttons[8] = true;
                else if (event.key.code == sf::Keyboard::O) keyboard_buttons[9] = true;
                else if (event.key.code == sf::Keyboard::P) keyboard_buttons[10] = true;
                else if (event.key.code == sf::Keyboard::A) keyboard_buttons[11] = true;
                else if (event.key.code == sf::Keyboard::S) keyboard_buttons[12] = true;
                else if (event.key.code == sf::Keyboard::D) keyboard_buttons[13] = true;
                else if (event.key.code == sf::Keyboard::F) keyboard_buttons[14] = true;
                else if (event.key.code == sf::Keyboard::G) keyboard_buttons[15] = true;
                else if (event.key.code == sf::Keyboard::H) keyboard_buttons[16] = true;
                else if (event.key.code == sf::Keyboard::J) keyboard_buttons[17] = true;
                else if (event.key.code == sf::Keyboard::K) keyboard_buttons[18] = true;
                else if (event.key.code == sf::Keyboard::L) keyboard_buttons[19] = true;
                else if (event.key.code == sf::Keyboard::Z) keyboard_buttons[20] = true;
                else if (event.key.code == sf::Keyboard::X) keyboard_buttons[21] = true;
                else if (event.key.code == sf::Keyboard::C) keyboard_buttons[22] = true;
                else if (event.key.code == sf::Keyboard::V) keyboard_buttons[23] = true;
                else if (event.key.code == sf::Keyboard::B) keyboard_buttons[24] = true;
                else if (event.key.code == sf::Keyboard::N) keyboard_buttons[25] = true;
                else if (event.key.code == sf::Keyboard::M) keyboard_buttons[26] = true;
                else if (event.key.code == sf::Keyboard::Num1) keyboard_buttons[27] = true;
                else if (event.key.code == sf::Keyboard::Num2) keyboard_buttons[28] = true;
                else if (event.key.code == sf::Keyboard::Num3) keyboard_buttons[29] = true;
                else if (event.key.code == sf::Keyboard::Num4) keyboard_buttons[30] = true;
                else if (event.key.code == sf::Keyboard::Num5) keyboard_buttons[31] = true;
                else if (event.key.code == sf::Keyboard::Num6) keyboard_buttons[32] = true;
                else if (event.key.code == sf::Keyboard::Num7) keyboard_buttons[33] = true;
                else if (event.key.code == sf::Keyboard::Num8) keyboard_buttons[34] = true;
                else if (event.key.code == sf::Keyboard::Num9) keyboard_buttons[35] = true;
                else if (event.key.code == sf::Keyboard::Num0) keyboard_buttons[36] = true;
                else if (event.key.code == sf::Keyboard::Numpad1) keyboard_buttons[37] = true;
                else if (event.key.code == sf::Keyboard::Numpad2) keyboard_buttons[38] = true;
                else if (event.key.code == sf::Keyboard::Numpad3) keyboard_buttons[39] = true;
                else if (event.key.code == sf::Keyboard::Numpad4) keyboard_buttons[40] = true;
                else if (event.key.code == sf::Keyboard::Numpad5) keyboard_buttons[41] = true;
                else if (event.key.code == sf::Keyboard::Numpad6) keyboard_buttons[41] = true;
                else if (event.key.code == sf::Keyboard::Numpad7) keyboard_buttons[42] = true;
                else if (event.key.code == sf::Keyboard::Numpad8) keyboard_buttons[43] = true;
                else if (event.key.code == sf::Keyboard::Numpad9) keyboard_buttons[44] = true;
                else if (event.key.code == sf::Keyboard::Numpad0) keyboard_buttons[45] = true;
                else if (event.key.code == sf::Keyboard::LControl) keyboard_buttons[46] = true;
                else if (event.key.code == sf::Keyboard::RControl) keyboard_buttons[47] = true;
                else if (event.key.code == sf::Keyboard::LShift) keyboard_buttons[48] = true;
                else if (event.key.code == sf::Keyboard::RShift) keyboard_buttons[49] = true;
                else if (event.key.code == sf::Keyboard::LAlt) keyboard_buttons[50] = true;
                else if (event.key.code == sf::Keyboard::RAlt) keyboard_buttons[51] = true;
                else if (event.key.code == sf::Keyboard::LSystem) keyboard_buttons[52] = true;
                else if (event.key.code == sf::Keyboard::RSystem) keyboard_buttons[53] = true;
                else if (event.key.code == sf::Keyboard::Escape) keyboard_buttons[54] = true;
                else if (event.key.code == sf::Keyboard::F1) keyboard_buttons[55] = true;
                else if (event.key.code == sf::Keyboard::F2) keyboard_buttons[56] = true;
                else if (event.key.code == sf::Keyboard::F3) keyboard_buttons[57] = true;
                else if (event.key.code == sf::Keyboard::F4) keyboard_buttons[58] = true;
                else if (event.key.code == sf::Keyboard::F5) keyboard_buttons[59] = true;
                else if (event.key.code == sf::Keyboard::F6) keyboard_buttons[60] = true;
                else if (event.key.code == sf::Keyboard::F7) keyboard_buttons[61] = true;
                else if (event.key.code == sf::Keyboard::F8) keyboard_buttons[62] = true;
                else if (event.key.code == sf::Keyboard::F9) keyboard_buttons[63] = true;
                else if (event.key.code == sf::Keyboard::F10) keyboard_buttons[64] = true;
                else if (event.key.code == sf::Keyboard::F11) keyboard_buttons[65] = true;
                else if (event.key.code == sf::Keyboard::F12) keyboard_buttons[66] = true;
                else if (event.key.code == sf::Keyboard::F13) keyboard_buttons[67] = true;
                else if (event.key.code == sf::Keyboard::F14) keyboard_buttons[68] = true;
                else if (event.key.code == sf::Keyboard::F15) keyboard_buttons[69] = true;
                else if (event.key.code == sf::Keyboard::Tab) keyboard_buttons[70] = true;
                else if (event.key.code == sf::Keyboard::Backspace) keyboard_buttons[71] = true;
                else if (event.key.code == sf::Keyboard::Delete) keyboard_buttons[72] = true;
                else if (event.key.code == sf::Keyboard::Insert) keyboard_buttons[73] = true;
                else if (event.key.code == sf::Keyboard::Menu) keyboard_buttons[74] = true;
                else if (event.key.code == sf::Keyboard::Left) keyboard_buttons[75] = true;
                else if (event.key.code == sf::Keyboard::Right) keyboard_buttons[76] = true;
                else if (event.key.code == sf::Keyboard::Up) keyboard_buttons[77] = true;
                else if (event.key.code == sf::Keyboard::Down) keyboard_buttons[78] = true;
                else if (event.key.code == sf::Keyboard::Enter) keyboard_buttons[79] = true;
                else if (event.key.code == sf::Keyboard::PageUp) keyboard_buttons[80] = true;
                else if (event.key.code == sf::Keyboard::PageDown) keyboard_buttons[81] = true;
                else if (event.key.code == sf::Keyboard::Home) keyboard_buttons[82] = true;
                else if (event.key.code == sf::Keyboard::End) keyboard_buttons[83] = true;
                else if (event.key.code == sf::Keyboard::Space) keyboard_buttons[84] = true;
                else if (event.key.code == sf::Keyboard::Add) keyboard_buttons[85] = true;
                else if (event.key.code == sf::Keyboard::Hyphen) keyboard_buttons[86] = true;
                else if (event.key.code == sf::Keyboard::Multiply) keyboard_buttons[87] = true;
                else if (event.key.code == sf::Keyboard::Tilde) keyboard_buttons[88] = true;
                else if (event.key.code == sf::Keyboard::Equal) keyboard_buttons[89] = true;
                else if (event.key.code == sf::Keyboard::LBracket) keyboard_buttons[90] = true;
                else if (event.key.code == sf::Keyboard::RBracket) keyboard_buttons[91] = true;
                else if (event.key.code == sf::Keyboard::Semicolon) keyboard_buttons[92] = true;
                else if (event.key.code == sf::Keyboard::Comma) keyboard_buttons[93] = true;
                else if (event.key.code == sf::Keyboard::Period) keyboard_buttons[94] = true;
                else if (event.key.code == sf::Keyboard::Quote) keyboard_buttons[95] = true;
                else if (event.key.code == sf::Keyboard::Slash) keyboard_buttons[96] = true;
                else if (event.key.code == sf::Keyboard::Backslash) keyboard_buttons[97] = true;
			}
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Unknown) keyboard_buttons[0] = false;
                else if (event.key.code == sf::Keyboard::Q) keyboard_buttons[1] = false;
                else if (event.key.code == sf::Keyboard::W) keyboard_buttons[2] = false;
                else if (event.key.code == sf::Keyboard::E) keyboard_buttons[3] = false;
                else if (event.key.code == sf::Keyboard::R) keyboard_buttons[4] = false;
                else if (event.key.code == sf::Keyboard::T) keyboard_buttons[5] = false;
                else if (event.key.code == sf::Keyboard::Y) keyboard_buttons[6] = false;
                else if (event.key.code == sf::Keyboard::U) keyboard_buttons[7] = false;
                else if (event.key.code == sf::Keyboard::I) keyboard_buttons[8] = false;
                else if (event.key.code == sf::Keyboard::O) keyboard_buttons[9] = false;
                else if (event.key.code == sf::Keyboard::P) keyboard_buttons[10] = false;
                else if (event.key.code == sf::Keyboard::A) keyboard_buttons[11] = false;
                else if (event.key.code == sf::Keyboard::S) keyboard_buttons[12] = false;
                else if (event.key.code == sf::Keyboard::D) keyboard_buttons[13] = false;
                else if (event.key.code == sf::Keyboard::F) keyboard_buttons[14] = false;
                else if (event.key.code == sf::Keyboard::G) keyboard_buttons[15] = false;
                else if (event.key.code == sf::Keyboard::H) keyboard_buttons[16] = false;
                else if (event.key.code == sf::Keyboard::J) keyboard_buttons[17] = false;
                else if (event.key.code == sf::Keyboard::K) keyboard_buttons[18] = false;
                else if (event.key.code == sf::Keyboard::L) keyboard_buttons[19] = false;
                else if (event.key.code == sf::Keyboard::Z) keyboard_buttons[20] = false;
                else if (event.key.code == sf::Keyboard::X) keyboard_buttons[21] = false;
                else if (event.key.code == sf::Keyboard::C) keyboard_buttons[22] = false;
                else if (event.key.code == sf::Keyboard::V) keyboard_buttons[23] = false;
                else if (event.key.code == sf::Keyboard::B) keyboard_buttons[24] = false;
                else if (event.key.code == sf::Keyboard::N) keyboard_buttons[25] = false;
                else if (event.key.code == sf::Keyboard::M) keyboard_buttons[26] = false;
                else if (event.key.code == sf::Keyboard::Num1) keyboard_buttons[27] = false;
                else if (event.key.code == sf::Keyboard::Num2) keyboard_buttons[28] = false;
                else if (event.key.code == sf::Keyboard::Num3) keyboard_buttons[29] = false;
                else if (event.key.code == sf::Keyboard::Num4) keyboard_buttons[30] = false;
                else if (event.key.code == sf::Keyboard::Num5) keyboard_buttons[31] = false;
                else if (event.key.code == sf::Keyboard::Num6) keyboard_buttons[32] = false;
                else if (event.key.code == sf::Keyboard::Num7) keyboard_buttons[33] = false;
                else if (event.key.code == sf::Keyboard::Num8) keyboard_buttons[34] = false;
                else if (event.key.code == sf::Keyboard::Num9) keyboard_buttons[35] = false;
                else if (event.key.code == sf::Keyboard::Num0) keyboard_buttons[36] = false;
                else if (event.key.code == sf::Keyboard::Numpad1) keyboard_buttons[37] = false;
                else if (event.key.code == sf::Keyboard::Numpad2) keyboard_buttons[38] = false;
                else if (event.key.code == sf::Keyboard::Numpad3) keyboard_buttons[39] = false;
                else if (event.key.code == sf::Keyboard::Numpad4) keyboard_buttons[40] = false;
                else if (event.key.code == sf::Keyboard::Numpad5) keyboard_buttons[41] = false;
                else if (event.key.code == sf::Keyboard::Numpad6) keyboard_buttons[41] = false;
                else if (event.key.code == sf::Keyboard::Numpad7) keyboard_buttons[42] = false;
                else if (event.key.code == sf::Keyboard::Numpad8) keyboard_buttons[43] = false;
                else if (event.key.code == sf::Keyboard::Numpad9) keyboard_buttons[44] = false;
                else if (event.key.code == sf::Keyboard::Numpad0) keyboard_buttons[45] = false;
                else if (event.key.code == sf::Keyboard::LControl) keyboard_buttons[46] = false;
                else if (event.key.code == sf::Keyboard::RControl) keyboard_buttons[47] = false;
                else if (event.key.code == sf::Keyboard::LShift) keyboard_buttons[48] = false;
                else if (event.key.code == sf::Keyboard::RShift) keyboard_buttons[49] = false;
                else if (event.key.code == sf::Keyboard::LAlt) keyboard_buttons[50] = false;
                else if (event.key.code == sf::Keyboard::RAlt) keyboard_buttons[51] = false;
                else if (event.key.code == sf::Keyboard::LSystem) keyboard_buttons[52] = false;
                else if (event.key.code == sf::Keyboard::RSystem) keyboard_buttons[53] = false;
                else if (event.key.code == sf::Keyboard::Escape) keyboard_buttons[54] = false;
                else if (event.key.code == sf::Keyboard::F1) keyboard_buttons[55] = false;
                else if (event.key.code == sf::Keyboard::F2) keyboard_buttons[56] = false;
                else if (event.key.code == sf::Keyboard::F3) keyboard_buttons[57] = false;
                else if (event.key.code == sf::Keyboard::F4) keyboard_buttons[58] = false;
                else if (event.key.code == sf::Keyboard::F5) keyboard_buttons[59] = false;
                else if (event.key.code == sf::Keyboard::F6) keyboard_buttons[60] = false;
                else if (event.key.code == sf::Keyboard::F7) keyboard_buttons[61] = false;
                else if (event.key.code == sf::Keyboard::F8) keyboard_buttons[62] = false;
                else if (event.key.code == sf::Keyboard::F9) keyboard_buttons[63] = false;
                else if (event.key.code == sf::Keyboard::F10) keyboard_buttons[64] = false;
                else if (event.key.code == sf::Keyboard::F11) keyboard_buttons[65] = false;
                else if (event.key.code == sf::Keyboard::F12) keyboard_buttons[66] = false;
                else if (event.key.code == sf::Keyboard::F13) keyboard_buttons[67] = false;
                else if (event.key.code == sf::Keyboard::F14) keyboard_buttons[68] = false;
                else if (event.key.code == sf::Keyboard::F15) keyboard_buttons[69] = false;
                else if (event.key.code == sf::Keyboard::Tab) keyboard_buttons[70] = false;
                else if (event.key.code == sf::Keyboard::Backspace) keyboard_buttons[71] = false;
                else if (event.key.code == sf::Keyboard::Delete) keyboard_buttons[72] = false;
                else if (event.key.code == sf::Keyboard::Insert) keyboard_buttons[73] = false;
                else if (event.key.code == sf::Keyboard::Menu) keyboard_buttons[74] = false;
                else if (event.key.code == sf::Keyboard::Left) keyboard_buttons[75] = false;
                else if (event.key.code == sf::Keyboard::Right) keyboard_buttons[76] = false;
                else if (event.key.code == sf::Keyboard::Up) keyboard_buttons[77] = false;
                else if (event.key.code == sf::Keyboard::Down) keyboard_buttons[78] = false;
                else if (event.key.code == sf::Keyboard::Enter) keyboard_buttons[79] = false;
                else if (event.key.code == sf::Keyboard::PageUp) keyboard_buttons[80] = false;
                else if (event.key.code == sf::Keyboard::PageDown) keyboard_buttons[81] = false;
                else if (event.key.code == sf::Keyboard::Home) keyboard_buttons[82] = false;
                else if (event.key.code == sf::Keyboard::End) keyboard_buttons[83] = false;
                else if (event.key.code == sf::Keyboard::Space) keyboard_buttons[84] = false;
                else if (event.key.code == sf::Keyboard::Add) keyboard_buttons[85] = false;
                else if (event.key.code == sf::Keyboard::Hyphen) keyboard_buttons[86] = false;
                else if (event.key.code == sf::Keyboard::Multiply) keyboard_buttons[87] = false;
                else if (event.key.code == sf::Keyboard::Tilde) keyboard_buttons[88] = false;
                else if (event.key.code == sf::Keyboard::Equal) keyboard_buttons[89] = false;
                else if (event.key.code == sf::Keyboard::LBracket) keyboard_buttons[90] = false;
                else if (event.key.code == sf::Keyboard::RBracket) keyboard_buttons[91] = false;
                else if (event.key.code == sf::Keyboard::Semicolon) keyboard_buttons[92] = false;
                else if (event.key.code == sf::Keyboard::Comma) keyboard_buttons[93] = false;
                else if (event.key.code == sf::Keyboard::Period) keyboard_buttons[94] = false;
                else if (event.key.code == sf::Keyboard::Quote) keyboard_buttons[95] = false;
                else if (event.key.code == sf::Keyboard::Slash) keyboard_buttons[96] = false;
                else if (event.key.code == sf::Keyboard::Backslash) keyboard_buttons[97] = false;
            }

            else if (event.type == sf::Event::JoystickMoved) 
            {
                if (joysticks_connect[0])
                {
                    joysticks_axes[0][0] = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                    joysticks_axes[0][1] = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
                    joysticks_axes[0][2] = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
                    joysticks_axes[0][3] = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
                    joysticks_axes[0][4] = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
                    joysticks_axes[0][5] = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
                    joysticks_axes[0][6] = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
                }
                else if (joysticks_connect[1])
                {
                    joysticks_axes[1][0] = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
                    joysticks_axes[1][1] = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
                    joysticks_axes[1][2] = sf::Joystick::getAxisPosition(1, sf::Joystick::U);
                    joysticks_axes[1][3] = sf::Joystick::getAxisPosition(1, sf::Joystick::V);
                    joysticks_axes[1][4] = sf::Joystick::getAxisPosition(1, sf::Joystick::PovX);
                    joysticks_axes[1][5] = sf::Joystick::getAxisPosition(1, sf::Joystick::PovY);
                    joysticks_axes[1][6] = sf::Joystick::getAxisPosition(1, sf::Joystick::Z);
                }
                else if (joysticks_connect[2])
                {
                    joysticks_axes[2][0] = sf::Joystick::getAxisPosition(2, sf::Joystick::X);
                    joysticks_axes[2][1] = sf::Joystick::getAxisPosition(2, sf::Joystick::Y);
                    joysticks_axes[2][2] = sf::Joystick::getAxisPosition(2, sf::Joystick::U);
                    joysticks_axes[2][3] = sf::Joystick::getAxisPosition(2, sf::Joystick::V);
                    joysticks_axes[2][4] = sf::Joystick::getAxisPosition(2, sf::Joystick::PovX);
                    joysticks_axes[2][5] = sf::Joystick::getAxisPosition(2, sf::Joystick::PovY);
                    joysticks_axes[2][6] = sf::Joystick::getAxisPosition(2, sf::Joystick::Z);
                }
                else if (joysticks_connect[3])
                {
                    joysticks_axes[3][0] = sf::Joystick::getAxisPosition(3, sf::Joystick::X);
                    joysticks_axes[3][1] = sf::Joystick::getAxisPosition(3, sf::Joystick::Y);
                    joysticks_axes[3][2] = sf::Joystick::getAxisPosition(3, sf::Joystick::U);
                    joysticks_axes[3][3] = sf::Joystick::getAxisPosition(3, sf::Joystick::V);
                    joysticks_axes[3][4] = sf::Joystick::getAxisPosition(3, sf::Joystick::PovX);
                    joysticks_axes[3][5] = sf::Joystick::getAxisPosition(3, sf::Joystick::PovY);
                    joysticks_axes[3][6] = sf::Joystick::getAxisPosition(3, sf::Joystick::Z);
                }
            }
            else if (event.type == sf::Event::JoystickButtonPressed)
            {
                if (joysticks_connect[0])
                {
                    if (sf::Joystick::isButtonPressed(0, 0)) { joysticks_buttons[0][0] = true; }
                    else if (sf::Joystick::isButtonPressed(0, 1)) { joysticks_buttons[0][1] = true; }
                    else if (sf::Joystick::isButtonPressed(0, 2)) { joysticks_buttons[0][2] = true; }
                    else if (sf::Joystick::isButtonPressed(0, 3)) { joysticks_buttons[0][3] = true; }
                    else if (sf::Joystick::isButtonPressed(0, 4)) { joysticks_buttons[0][4] = true; }
                    else if (sf::Joystick::isButtonPressed(0, 5)) { joysticks_buttons[0][5] = true; }
                    else if (sf::Joystick::isButtonPressed(0, 6)) { joysticks_buttons[0][6] = true; }
                    else if (sf::Joystick::isButtonPressed(0, 7)) { joysticks_buttons[0][7] = true; }
                    else if (sf::Joystick::isButtonPressed(0, 8)) { joysticks_buttons[0][8] = true; }
                    else if (sf::Joystick::isButtonPressed(0, 9)) { joysticks_buttons[0][9] = true; }
                }
                if (joysticks_connect[1])
                {
                    if (sf::Joystick::isButtonPressed(1, 0)) { joysticks_buttons[1][0] = true; }
                    else if (sf::Joystick::isButtonPressed(1, 1)) { joysticks_buttons[1][1] = true; }
                    else if (sf::Joystick::isButtonPressed(1, 2)) { joysticks_buttons[1][2] = true; }
                    else if (sf::Joystick::isButtonPressed(1, 3)) { joysticks_buttons[1][3] = true; }
                    else if (sf::Joystick::isButtonPressed(1, 4)) { joysticks_buttons[1][4] = true; }
                    else if (sf::Joystick::isButtonPressed(1, 5)) { joysticks_buttons[1][5] = true; }
                    else if (sf::Joystick::isButtonPressed(1, 6)) { joysticks_buttons[1][6] = true; }
                    else if (sf::Joystick::isButtonPressed(1, 7)) { joysticks_buttons[1][7] = true; }
                    else if (sf::Joystick::isButtonPressed(1, 8)) { joysticks_buttons[1][8] = true; }
                    else if (sf::Joystick::isButtonPressed(1, 9)) { joysticks_buttons[1][9] = true; }
                }
                if (joysticks_connect[2])
                {
                    if (sf::Joystick::isButtonPressed(2, 0)) { joysticks_buttons[2][0] = true; }
                    else if (sf::Joystick::isButtonPressed(2, 1)) { joysticks_buttons[2][1] = true; }
                    else if (sf::Joystick::isButtonPressed(2, 2)) { joysticks_buttons[2][2] = true; }
                    else if (sf::Joystick::isButtonPressed(2, 3)) { joysticks_buttons[2][3] = true; }
                    else if (sf::Joystick::isButtonPressed(2, 4)) { joysticks_buttons[2][4] = true; }
                    else if (sf::Joystick::isButtonPressed(2, 5)) { joysticks_buttons[2][5] = true; }
                    else if (sf::Joystick::isButtonPressed(2, 6)) { joysticks_buttons[2][6] = true; }
                    else if (sf::Joystick::isButtonPressed(2, 7)) { joysticks_buttons[2][7] = true; }
                    else if (sf::Joystick::isButtonPressed(2, 8)) { joysticks_buttons[2][8] = true; }
                    else if (sf::Joystick::isButtonPressed(2, 9)) { joysticks_buttons[2][9] = true; }
                }
                if (joysticks_connect[3])
                {
                    if (sf::Joystick::isButtonPressed(3, 0)) { joysticks_buttons[3][0] = true; }
                    else if (sf::Joystick::isButtonPressed(3, 1)) { joysticks_buttons[3][1] = true; }
                    else if (sf::Joystick::isButtonPressed(3, 2)) { joysticks_buttons[3][2] = true; }
                    else if (sf::Joystick::isButtonPressed(3, 3)) { joysticks_buttons[3][3] = true; }
                    else if (sf::Joystick::isButtonPressed(3, 4)) { joysticks_buttons[3][4] = true; }
                    else if (sf::Joystick::isButtonPressed(3, 5)) { joysticks_buttons[3][5] = true; }
                    else if (sf::Joystick::isButtonPressed(3, 6)) { joysticks_buttons[3][6] = true; }
                    else if (sf::Joystick::isButtonPressed(3, 7)) { joysticks_buttons[3][7] = true; }
                    else if (sf::Joystick::isButtonPressed(3, 8)) { joysticks_buttons[3][8] = true; }
                    else if (sf::Joystick::isButtonPressed(3, 9)) { joysticks_buttons[3][9] = true; }
                }
            }
            else if (event.type == sf::Event::JoystickButtonReleased)
            {
                if (joysticks_connect[0])
                {
                    if (!sf::Joystick::isButtonPressed(0, 0)) { joysticks_buttons[0][0] = false; }
                    if (!sf::Joystick::isButtonPressed(0, 1)) { joysticks_buttons[0][1] = false; }
                    if (!sf::Joystick::isButtonPressed(0, 2)) { joysticks_buttons[0][2] = false; }
                    if (!sf::Joystick::isButtonPressed(0, 3)) { joysticks_buttons[0][3] = false; }
                    if (!sf::Joystick::isButtonPressed(0, 4)) { joysticks_buttons[0][4] = false; }
                    if (!sf::Joystick::isButtonPressed(0, 5)) { joysticks_buttons[0][5] = false; }
                    if (!sf::Joystick::isButtonPressed(0, 6)) { joysticks_buttons[0][6] = false; }
                    if (!sf::Joystick::isButtonPressed(0, 7)) { joysticks_buttons[0][7] = false; }
                    if (!sf::Joystick::isButtonPressed(0, 8)) { joysticks_buttons[0][8] = false; }
                    if (!sf::Joystick::isButtonPressed(0, 9)) { joysticks_buttons[0][9] = false; }
                }
                if (joysticks_connect[1])
                {
                    if (!sf::Joystick::isButtonPressed(1, 0)) { joysticks_buttons[1][0] = false; }
                    if (!sf::Joystick::isButtonPressed(1, 1)) { joysticks_buttons[1][1] = false; }
                    if (!sf::Joystick::isButtonPressed(1, 2)) { joysticks_buttons[1][2] = false; }
                    if (!sf::Joystick::isButtonPressed(1, 3)) { joysticks_buttons[1][3] = false; }
                    if (!sf::Joystick::isButtonPressed(1, 4)) { joysticks_buttons[1][4] = false; }
                    if (!sf::Joystick::isButtonPressed(1, 5)) { joysticks_buttons[1][5] = false; }
                    if (!sf::Joystick::isButtonPressed(1, 6)) { joysticks_buttons[1][6] = false; }
                    if (!sf::Joystick::isButtonPressed(1, 7)) { joysticks_buttons[1][7] = false; }
                    if (!sf::Joystick::isButtonPressed(1, 8)) { joysticks_buttons[1][8] = false; }
                    if (!sf::Joystick::isButtonPressed(1, 9)) { joysticks_buttons[1][9] = false; }
                }
                if (joysticks_connect[2])
                {
                    if (!sf::Joystick::isButtonPressed(2, 0)) { joysticks_buttons[2][0] = false; }
                    if (!sf::Joystick::isButtonPressed(2, 1)) { joysticks_buttons[2][1] = false; }
                    if (!sf::Joystick::isButtonPressed(2, 2)) { joysticks_buttons[2][2] = false; }
                    if (!sf::Joystick::isButtonPressed(2, 3)) { joysticks_buttons[2][3] = false; }
                    if (!sf::Joystick::isButtonPressed(2, 4)) { joysticks_buttons[2][4] = false; }
                    if (!sf::Joystick::isButtonPressed(2, 5)) { joysticks_buttons[2][5] = false; }
                    if (!sf::Joystick::isButtonPressed(2, 6)) { joysticks_buttons[2][6] = false; }
                    if (!sf::Joystick::isButtonPressed(2, 7)) { joysticks_buttons[2][7] = false; }
                    if (!sf::Joystick::isButtonPressed(2, 8)) { joysticks_buttons[2][8] = false; }
                    if (!sf::Joystick::isButtonPressed(2, 9)) { joysticks_buttons[2][9] = false; }
                }
                if (joysticks_connect[3])
                {
                    if (!sf::Joystick::isButtonPressed(3, 0)) { joysticks_buttons[3][0] = false; }
                    if (!sf::Joystick::isButtonPressed(3, 1)) { joysticks_buttons[3][1] = false; }
                    if (!sf::Joystick::isButtonPressed(3, 2)) { joysticks_buttons[3][2] = false; }
                    if (!sf::Joystick::isButtonPressed(3, 3)) { joysticks_buttons[3][3] = false; }
                    if (!sf::Joystick::isButtonPressed(3, 4)) { joysticks_buttons[3][4] = false; }
                    if (!sf::Joystick::isButtonPressed(3, 5)) { joysticks_buttons[3][5] = false; }
                    if (!sf::Joystick::isButtonPressed(3, 6)) { joysticks_buttons[3][6] = false; }
                    if (!sf::Joystick::isButtonPressed(3, 7)) { joysticks_buttons[3][7] = false; }
                    if (!sf::Joystick::isButtonPressed(3, 8)) { joysticks_buttons[3][8] = false; }
                    if (!sf::Joystick::isButtonPressed(3, 9)) { joysticks_buttons[3][9] = false; }
                }
            }
            else if (event.type = sf::Event::JoystickConnected)
            {
                if (sf::Joystick::isConnected(0))
                {
                    joysticks_connect[0] = true;
                }
                if (sf::Joystick::isConnected(1))
                {
                    joysticks_connect[1] = true;
                }
                if (sf::Joystick::isConnected(2))
                {
                    joysticks_connect[2] = true;
                }
                if (sf::Joystick::isConnected(3))
                {
                    joysticks_connect[3] = true;
                }
            }
            else if (event.type = sf::Event::JoystickDisconnected)
            {
                if (!sf::Joystick::isConnected(0))
                {
                    joysticks_connect[0] = false;
                }
                else if (!sf::Joystick::isConnected(1))
                {
                    joysticks_connect[1] = false;
                }
                else if (!sf::Joystick::isConnected(2))
                {
                    joysticks_connect[2] = false;
                }
                else if (!sf::Joystick::isConnected(3))
                {
                    joysticks_connect[3] = false;
                }
            }
		}
        
        if (focus)
        {
            mouse_position[0] = ((float)mouse_position_int[0] / sfml_window.getSize().x - 0.5f) * mouse_sensitivity;
            mouse_position[1] = ((float)mouse_position_int[1] / sfml_window.getSize().y - 0.5f) * mouse_sensitivity;
            sf::Vector3f dir = sf::Vector3f(0.0f, 0.0f, 0.0f);
            sf::Vector3f dirTemp;
            if (keyboard_buttons[2]) dir = sf::Vector3f(1.0f, 0.0f, 0.0f);
            else if (keyboard_buttons[12]) dir = sf::Vector3f(-1.0f, 0.0f, 0.0f);
            if (keyboard_buttons[11]) dir += sf::Vector3f(0.0f, -1.0f, 0.0f);
            else if (keyboard_buttons[13]) dir += sf::Vector3f(0.0f, 1.0f, 0.0f);
            dirTemp.z = dir.z * cos(-mouse_position[1]) - dir.x * sin(-mouse_position[1]);
            dirTemp.x = dir.z * sin(-mouse_position[1]) + dir.x * cos(-mouse_position[1]);
            dirTemp.y = dir.y;
            dir.x = dirTemp.x * cos(mouse_position[0]) - dirTemp.y * sin(mouse_position[0]);
            dir.y = dirTemp.x * sin(mouse_position[0]) + dirTemp.y * cos(mouse_position[0]);
            dir.z = dirTemp.z;
            camera_position += dir * camera_speed;
            if (keyboard_buttons[84]) camera_position.z -= camera_speed;
            else if (keyboard_buttons[48]) camera_position.z += camera_speed;

            shader.setUniform("uResolution", sf::Vector2f(sfml_window.getSize().x, sfml_window.getSize().y));
            shader.setUniform("uMouse", sf::Vector2f(mouse_position[0], mouse_position[1]));
            shader.setUniform("uTime", game_time.getElapsedTime().asSeconds());
            shader.setUniform("uMaxDistance", max_distance);
            shader.setUniform("uFov", fov);
            shader.setUniform("uCameraPosition", camera_position);
            shader.setUniform("uLightPosition", sf::Vector3f(-0.5, 0.75, -1.0));
            shader.setUniform("uObjects", objects);

            sfml_window.draw(shader_placeholder, &shader);
            /*
            int position[] = { 100, 100 };
            log_add("Test log");
            set_cursor_visible(false);
            set_position(sf::Vector2i{100, 100});
            set_size(sf::Vector2u{ 1080, 720 });
            set_title("Test name");
            draw_text(sf::Color::Cyan, "test_font.ttf", "Test text", 50, position, sf::Text::Bold, sf::Text::Italic);
            draw_circle(sf::Color::Magenta, 100.f, position);
            float size[][2] = {
                0.f, 0.f,
                100.f, 100.f
            };
            draw_polygon(sf::Color::Yellow, size, position, 2);
            play_music("music.ogg");
            play_sound("sound.ogg");
            */
            try
            {
                draw_text(sf::Color::Black, "test_font.ttf", std::to_string(1000 / FPS.getElapsedTime().asMilliseconds()), 50, sf::Text::Bold, sf::Text::Bold);
            }
            catch (char* error) {}
            sfml_window.display();
            FPS.restart();
            Sleep(1);
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