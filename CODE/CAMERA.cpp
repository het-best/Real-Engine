


#ifndef ENGINE_CAMERA_CPP
#define ENGINE_CAMERA_CPP

#include "CONFIG.hpp"
#include "CAMERA.hpp"

namespace ENGINE_CAMERA {
    void fps_camera::update(int delta_time)
    {
        direction = {
            cos(degrees.y) * sin(degrees.x),
            sin(degrees.y),
            cos(degrees.y) * cos(degrees.x)
        };

        right = {
            sin(degrees.x - 3.14f / 2.0),
            0,
            cos(degrees.x - 3.14f / 2.0)
        };

        up = cross(right, direction);

        direction *= rotation_sensitivity;
        direction *= speed;
        right *= rotation_sensitivity;
        right *= speed;

        target_velocity.x -= target_velocity.x / 100;
        target_velocity.y -= target_velocity.y / 100;
        target_velocity.z -= target_velocity.z / 100;

        velocity.x += (target_velocity.x - velocity.x) / 10;
        velocity.y += (target_velocity.y - velocity.y) / 10;
        velocity.z += (target_velocity.z - velocity.z) / 10;

        position += velocity;
    }

    fps_camera::fps_camera(Vector3f position_, float render_distance_, float speed_, float jump_speed_, float fov_, float rotation_sensitivity_)
        : position(position_), render_distance(render_distance_), speed(speed_), jump_speed(jump_speed_), fov(fov_), rotation_sensitivity(rotation_sensitivity_) {}
}

#endif // ENGINE_CAMERA_CPP