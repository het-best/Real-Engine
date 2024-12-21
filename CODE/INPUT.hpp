


#ifndef ENGINE_INPUT_HPP
#define ENGINE_INPUT_HPP

namespace ENGINE_INPUT {
	extern Vector2i mouse_position;

	extern std::unordered_set<Keyboard::Key> just_pressed_keys;

	extern vector<Keyboard::Key> input_keys;

	extern bool is_key_pressed(Keyboard::Key key);
	extern bool is_key_just_pressed(Keyboard::Key key);
}

#endif // ENGINE_INPUT_HPP