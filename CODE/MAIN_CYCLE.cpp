


#ifndef ENGINE_MAIN_CYCLE
#define ENGINE_MAIN_CYCLE

#include "CONFIG.hpp"

namespace ENGINE_MAIN_CYCLE
{
    void close(string game_time, int code)
    {
        ENGINE_FILE::save_in_log("exit.log", "Current game time: " + game_time + "s");
        exit(code);
    }

	int MAIN_CYCLE()
	{
        //OPERATION WITH OPENGL
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_ALPHA_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL);



        //LOAD GAME DATA
        ENGINE_CAMERA::fps_camera camera(Vector3f(0, 0, 0));
        ENGINE_MODEL::polygon_model pmod(ENGINE_MODEL::model("objects/test.vox"));
        ENGINE_MODEL::polygon_models.push_back(&pmod);



        //VARIABLES
        ENGINE_INPUT::just_pressed_keys.reserve(Keyboard::Key::KeyCount);

        Clock main_time;

        Clock delta_time_clock;
        float delta_time = 0.0f;

        bool window_focus = true;
        Event event{};



        remove("exit.log");
        ENGINE_FILE::save_in_log("exit.log", "Current engine version: v" + ENGINE_CONFIG::ENGINE_VERSION);
        #ifdef DEBUGGING

            ENGINE_FILE::save_in_log("exit.log", "Current engine configuration: DEBUG");

        #else
            ENGINE_FILE::save_in_log("exit.log", "Current engine configuration: RELEASE");
        #endif // DEBUGGING

        
        
        while (ENGINE_CONFIG::SFML_WINDOW.isOpen())
        {
            //EVENTS
            sf::Event event;
            while (ENGINE_CONFIG::SFML_WINDOW.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    close(to_string(main_time.getElapsedTime().asSeconds()), 101);
                }
                if (event.type == sf::Event::KeyPressed && ENGINE_INPUT::is_key_pressed(ENGINE_INPUT::input_keys[6]))
                {
                    close(to_string(main_time.getElapsedTime().asSeconds()), 102);
                }

                //CONTROL
                if (event.type == sf::Event::MouseMoved)
                {
                    ENGINE_INPUT::mouse_position.x += event.mouseMove.x - ENGINE_CONFIG::WINDOW_RESOLUTION.x / 2;
                    ENGINE_INPUT::mouse_position.y += event.mouseMove.y - ENGINE_CONFIG::WINDOW_RESOLUTION.y / 2;
                    sf::Mouse::setPosition(sf::Vector2i(ENGINE_CONFIG::WINDOW_RESOLUTION.x / 2, ENGINE_CONFIG::WINDOW_RESOLUTION.y / 2), ENGINE_CONFIG::SFML_WINDOW);
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    if (!ENGINE_INPUT::just_pressed_keys.insert(event.key.code).second) {
                        ENGINE_INPUT::just_pressed_keys.erase(event.key.code);
                    }
                }

                //WINDOW
                if (event.type == sf::Event::Resized)
                {
                    glViewport(0, 0, event.size.width, event.size.height);
                    ENGINE_CONFIG::WINDOW_RESOLUTION = { (int)event.size.width, (int)event.size.height };
                }
                if (event.type == sf::Event::GainedFocus)
                {
                    window_focus = true;
                }
                else if (event.type == sf::Event::LostFocus)
                {
                    window_focus = false;
                }
            }
            if (window_focus)
            {
                delta_time = delta_time_clock.restart().asSeconds();

                //CLEARING BUFFERS
                ENGINE_CONFIG::SFML_WINDOW.clear(Color::Cyan);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

                //CLEAR MATRIX
                glLoadIdentity();

                //CHANGE CAMERA POSITION AND ROTAION 
                camera.degrees.x = -((float)ENGINE_INPUT::mouse_position.x / ENGINE_CONFIG::WINDOW_RESOLUTION.x * 360 * camera.rotation_sensitivity / 50);
                camera.degrees.y = -((float)ENGINE_INPUT::mouse_position.y / ENGINE_CONFIG::WINDOW_RESOLUTION.y * 360 * camera.rotation_sensitivity / 50);

                camera.update(delta_time);

                //MOVING
                if (ENGINE_INPUT::is_key_pressed(ENGINE_INPUT::input_keys.at(0)))
                {
                    camera.position.x += camera.direction.x * delta_time;
                    camera.position.z += camera.direction.z * delta_time;
                }
                if (ENGINE_INPUT::is_key_pressed(ENGINE_INPUT::input_keys.at(1)))
                {
                    camera.position.x -= camera.direction.x * delta_time;
                    camera.position.z -= camera.direction.z * delta_time;
                }
                if (ENGINE_INPUT::is_key_pressed(ENGINE_INPUT::input_keys.at(2)))
                {
                    camera.position.x -= camera.right.x * delta_time;
                    camera.position.z -= camera.right.z * delta_time;
                }
                if (ENGINE_INPUT::is_key_pressed(ENGINE_INPUT::input_keys.at(3)))
                {
                    camera.position.x += camera.right.x * delta_time;
                    camera.position.z += camera.right.z * delta_time;
                }

                if (ENGINE_INPUT::is_key_just_pressed(ENGINE_INPUT::input_keys.at(4)))
                {
                    camera.target_velocity.y += camera.jump_speed * delta_time;
                }

                //CONVERTING THE DEGREES OF THE CAMERA INTO A POINT WHERE TO LOOK
                camera.rotation = { camera.position.x + camera.direction.x, camera.position.y + camera.direction.y, camera.position.z + camera.direction.z };

                gluPerspective(camera.fov, (float)ENGINE_CONFIG::WINDOW_RESOLUTION.x / (float)ENGINE_CONFIG::WINDOW_RESOLUTION.y, 1, camera.render_distance);
                gluLookAt(
                    camera.position.x, camera.position.y, camera.position.z,
                    camera.rotation.x, camera.rotation.y, camera.rotation.z,
                    camera.up.x, camera.up.y, camera.up.z);

                ENGINE_RENDERING::draw_coordinates();

                ENGINE_MODEL::render();
                ENGINE_MODEL::polygon_render();

                ENGINE_CONFIG::SFML_WINDOW.display();
            }
            else
            {
                Sleep(ENGINE_CONFIG::WINDOW_NO_FOCUS_TIME);
            }
        }
	}
}

#endif // !ENGINE_MAIN_CYCLE
