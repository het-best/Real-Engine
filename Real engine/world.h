#include <SFML/Graphics.hpp>

namespace game_world {

    sf::Vector3f objects_position[65535];

    sf::Vector3f objects_color[65535];

    sf::Vector3f objects_rotation[65535];

    sf::Int16 objects_weight[65535];

    sf::Int16 objects_strength[65535];

    sf::Int16 objects_visible[65535];

    bool objects_destroyed[65535];

    int objects_count = 0;

    class attraction_point
    {
    public:
        sf::Vector3f position = sf::Vector3f();
        float strength = 1.0;
    };

    class object
    {
    public:
        sf::Vector3f* voxels_position = new sf::Vector3f[65535];
        sf::Vector3f* voxels_color = new sf::Vector3f[65535];
        sf::Vector3f* voxels_rotation = new sf::Vector3f[65535];
        sf::Vector3f* voxels_attraction_direction = new sf::Vector3f[65535];

        sf::Int16* voxels_strength = new sf::Int16[65535];
        sf::Int16* voxels_visible = new sf::Int16[65535];

        bool* voxels_destroyed = new bool[65535];
        float* voxels_weight = new float[65535];
        int voxels_count = 0;

        void destroy_object()
        {
            for (int i = 0; i < voxels_count; i++)
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

        int update_objects(int count)
        {
            voxels_count = 0;
            for (int i = 0; i < sizeof(objects_position) / 12 - count; i++) 
            {
                if (voxels_position[i] != sf::Vector3f())
                {
                    objects_position[i] = voxels_position[i];
                    objects_color[i] = voxels_color[i];
                    objects_rotation[i] = voxels_rotation[i];
                    objects_weight[i] = voxels_weight[i];
                    objects_strength[i] = voxels_strength[i];
                    objects_visible[i] = voxels_visible[i];
                    objects_destroyed[i] = voxels_destroyed[i];
                    objects_count++; 
                    voxels_count++;
                }
                else
                {
                    i = sizeof(objects_position);
                }

            }
            return count;
        }

        void calculate_object_physics(attraction_point attraction)
        {
            for (int i = 0; i < voxels_count; i++)
            {
                if (voxels_weight[i] != 0)
                {
                    sf::Vector3f direction = attraction.position - voxels_position[i];
                    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

                    direction /= distance;
                    float force = attraction.strength * voxels_weight[i];

                    voxels_attraction_direction[i] += force * direction;

                    float angle = distance * 10.0;

                    voxels_rotation[i] = direction * angle;

                    voxels_position[i] += voxels_attraction_direction[i];
                }
            }
        }
    };

    class camera
    {
    public:
        sf::Vector3f position = sf::Vector3f();

        sf::Vector3f rotation = sf::Vector3f();
        sf::Vector2f degrees = sf::Vector2f();

        glm::vec3 direction = glm::vec3();
        glm::vec3 right = glm::vec3();
        glm::vec3 up = glm::vec3();

        sf::Vector3f attraction_direction = sf::Vector3f();

        float weight = 1.0;

        float max_distance = 128.0;
        float speed = 0.15;

        float fov = 90.0;

        float sensitivity = 0.9;

        void set(sf::Vector3f pos = sf::Vector3f(), sf::Vector3f rot = sf::Vector3f(), float weight = 0.1)
        {
            position = pos;
            rotation = rot;
        }

        void degrees_into_point()
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

            up = glm::cross(right, direction);

            direction *= sensitivity;
            right *= sensitivity;
        }

        void calculate_camera_physics(attraction_point attraction)
        {
            sf::Vector3f direction = attraction.position - position;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

            direction /= distance;
            float force = attraction.strength * weight;

            attraction_direction += force * direction;

            float angle = distance * 10.0;

            rotation = direction * angle;

            position += attraction_direction;
        }
    };

    camera current_camera;

    object obj;
    camera cam;

    attraction_point att;

    void initialization_objects()
    {
        obj.set_voxel(0, sf::Vector3f(2, -4, 1), sf::Vector3f(1.0, 0.8, 0.1058824), sf::Vector3f(0, 0, 0), 0, -1, 256);
        obj.set_voxel(1, sf::Vector3f(5, 5, 5), sf::Vector3f(0.8, 0.4784314, 0.03921569), sf::Vector3f(0, 0, 0), 1, -1, 256);
        obj.set_voxel(2, sf::Vector3f(-5, -5, -5), sf::Vector3f(0.8, 0.14, 0), sf::Vector3f(0, 0, 0), 3, -1, 256);
        obj.set_voxel(3, sf::Vector3f(2, 8, 15), sf::Vector3f(0.81960784, 0.6039215, 0.60392156), sf::Vector3f(0, 0, 0), 1.5, -1, 256);
        obj.set_voxel(4, sf::Vector3f(-12, 1, -2), sf::Vector3f(0.1960784, 0.5450980, 0.6), sf::Vector3f(0, 0, 0), 2, -1, 256);

        att.position = sf::Vector3f(2, -4, 1);
        att.strength = 0.01;
    }

    void clear_objects()
    {
        objects_count = 0;
        for (int i = 0; i < objects_count; i++)
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
}