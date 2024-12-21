


#ifndef ENGINE_INPUT_CPP
#define ENGINE_INPUT_CPP

#include "CONFIG.hpp"
#include "INPUT.hpp"

namespace ENGINE_INPUT {
	Vector2i mouse_position;

	/*
		0 - Front
		1 - Back
		2 - Left
		3 - Right
		4 - Up
		5 - Down
		6 - Exit
	*/
	std::unordered_set<Keyboard::Key> just_pressed_keys;

	vector<Keyboard::Key> input_keys = { 
		Keyboard::Key::W, 
		Keyboard::Key::S, 
		Keyboard::Key::A, 
		Keyboard::Key::D, 
		Keyboard::Key::Space,
		Keyboard::Key::LShift,
		Keyboard::Key::Escape,
		Keyboard::Key::Q,
		Keyboard::Key::E };

	bool is_key_pressed(Keyboard::Key key)
	{
		if (Keyboard::isKeyPressed(key))
		{
			return true;
		}
		return false;
	}

	bool is_key_just_pressed(Keyboard::Key key)
	{
		auto key_insert = just_pressed_keys.insert(key).second;
		just_pressed_keys.erase(key);
		if (!key_insert)
		{
			return true;
		}
		return false;
	}
}

#endif // ENGINE_INPUT_CPP