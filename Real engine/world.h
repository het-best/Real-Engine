#include <SFML/Graphics.hpp>

namespace game_world {

    float max_distance = 128.0f;

    sf::Vector3f camera_position = { 5.0f, 0.0f, 0.0f };

    sf::Vector3f camera_rotation = { 0.0f, 0.0f, 0.0f };
    sf::Vector2f camera_degrees = { 0.0f, 0.0f };

    float camera_speed = 0.15f;

    float camera_fov = 80.0f;

    float camera_sensitivity = 0.9f;
    float camera_accuracy = 15.0f;

    class object
    {
    public:
        sf::Vector3f *voxels_position = new sf::Vector3f[65535];
        sf::Vector3f *voxels_color = new sf::Vector3f[65535];
        sf::Vector3f *voxels_rotation = new sf::Vector3f[65535];
        sf::Int16*voxels_weight = new sf::Int16[65535];
        sf::Int16*voxels_strength = new sf::Int16[65535];
        sf::Int16*voxels_visible = new sf::Int16[65535];
        bool* voxels_destroyed = new bool[65535];
        void destroy_object()
        {
            for (int i = 0; i < sizeof(voxels_destroyed) / 12; i++)
            {
                voxels_destroyed[i] = true;
            }
        }
        void set_voxel(int voxel_count, sf::Vector3f voxel_position, sf::Vector3f voxel_color, sf::Vector3f voxel_rotation, sf::Int16 voxel_weight = 0, sf::Int16 voxel_strength = -1, sf::Int16 voxel_visible = 256)
        {
            voxels_position[voxel_count] = voxel_position;
            voxels_color[voxel_count] = voxel_color;
            voxels_rotation[voxel_count] = voxel_rotation;
            voxels_weight[voxel_count] = voxel_weight;
            voxels_strength[voxel_count] = voxel_strength;
            voxels_visible[voxel_count] = voxel_visible;
            voxels_destroyed[voxel_count] = false;
        }
        sf::Vector3f* get_voxels_position()
        {
            return voxels_position;
        }
        sf::Vector3f* get_voxels_color()
        {
            return voxels_color;
        }
        sf::Vector3f* get_voxels_rotation()
        {
            return voxels_rotation;
        }
        sf::Int16* get_voxels_weight()
        {
            return voxels_weight;
        }
        sf::Int16* get_voxels_strength()
        {
            return voxels_strength;
        }
        sf::Int16* get_voxels_visible()
        {
            return voxels_visible;
        }
        bool* get_voxels_destroyed()
        {
            return voxels_destroyed;
        }

    };

    object obj;

    sf::Vector3f objects_position[] = {
        sf::Vector3f(0, 0, 0),
        sf::Vector3f(0, 0, 0),
    };

    sf::Vector3f objects_color[] = {
        sf::Vector3f(0, 0, 0),
        sf::Vector3f(0, 0, 0),
    };

    sf::Vector3f objects_rotation[] = {
        sf::Vector3f(0, 0, 0),
        sf::Vector3f(0, 0, 0),
    };

    sf::Int16 objects_weight[] = {
        0,
        0,
    };

    sf::Int16 objects_strength[] = {
        -1,
        -1,
    };

    sf::Int16 objects_visible[] = {
        256,
        256,
    };

    bool objects_destroyed[] = {
        false,
        false,
    };

    void initialization_objects()
    {
        obj.set_voxel(0, sf::Vector3f(0, 0, 1), sf::Vector3f(1.0, 0.8, 0.1058824), sf::Vector3f(0, 0, 0), 0, -1, 256);
        obj.set_voxel(1, sf::Vector3f(-2, 0, 1), sf::Vector3f(0.8, 0.4784314, 0.03921569), sf::Vector3f(0, 0, 0), 0, -1, 256);
    }

    void clear_objects()
    {
        for (int i = 0; i < sizeof(objects_position) / 12; i++)
        {
            objects_position[i] = sf::Vector3f();
            objects_color[i] = sf::Vector3f();
            objects_rotation[i] = sf::Vector3f();
            objects_weight[i] = NULL;
            objects_strength[i] = NULL;
            objects_visible[i] = NULL;
            objects_destroyed[i] = NULL;
        }
    }

    int update_objects(object& object_, int count)
    {
        for (int i = 0; i < sizeof(objects_position) / 12 - count; i++) { objects_position[i] = object_.get_voxels_position()[i]; }
        for (int i = 0; i < sizeof(objects_color) / 12 - count; i++) { objects_color[i] = object_.get_voxels_color()[i]; }
        for (int i = 0; i < sizeof(objects_rotation) / 12 - count; i++) { objects_rotation[i] = object_.get_voxels_rotation()[i]; }
        for (int i = 0; i < sizeof(objects_weight) / 12 - count; i++) { objects_weight[i] = object_.get_voxels_weight()[i]; }
        for (int i = 0; i < sizeof(objects_strength) / 12 - count; i++) { objects_strength[i] = object_.get_voxels_strength()[i]; }
        for (int i = 0; i < sizeof(objects_visible) / 12 - count; i++) { objects_visible[i] = object_.get_voxels_visible()[i]; }
        for (int i = 0; i < sizeof(objects_destroyed) / 12 - count; i++) { objects_destroyed[i] = object_.get_voxels_destroyed()[i]; }
        return count;
    }
}