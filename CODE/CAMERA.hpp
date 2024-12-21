


#ifndef ENGINE_CAMERA_HPP
#define ENGINE_CAMERA_HPP

namespace ENGINE_CAMERA {
    class fps_camera
    {
    public:
        vec3 direction = vec3();
        vec3 right = vec3();
        vec3 up = vec3();

        Vector3f position;
        Vector3f rotation;
        Vector3f velocity;
        Vector3f target_velocity;

        Vector2f degrees = Vector2f();

        float render_distance;
        float speed;
        float jump_speed;

        float fov;

        float rotation_sensitivity;

        void update(int delta_time);

        fps_camera(Vector3f position_, float render_distance_ = 256, float speed_ = 25, float jump_speed_ = 10, float fov_ = 60.0, float rotation_sensitivity_ = 0.9);
    };
}

#endif // ENGINE_CAMERA_HPP
