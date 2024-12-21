


#ifndef ENGINE_MODEL_HPP
#define ENGINE_MODEL_HPP

namespace ENGINE_MODEL {
    extern class voxel
    {
    public:
        Vector3f position;
        Vector3f rotation;
        Color color;

        voxel(Vector3f position_, Vector3f rotation_, Color color_);

        void render();
    };
    extern class polygon_voxel
    {
    public:
        Vector3f first_position;
        Vector3f second_position;
        Color color;

        void render();
    };

    extern class model
    {
    public:
        Vector3f position;

        vector<voxel> voxels;

        model(string path_to_vox);
        void render();
        void rotate_around_point(Vector3f point, Vector3f rotation_vector);
    };
    extern class polygon_model
    {
    public:
        Vector3f position;

        vector<polygon_voxel> polygon_voxels;

        polygon_model(model* model_to_copy_from);
        polygon_model(model model_to_copy_from);
        void render();
    };

    extern class collision
    {
    public:
        Vector3f first_position;
        Vector3f second_position;
        Color color;
        void (*on_collision)(collision*, collision*);
        void (*on_no_collision)();

        collision(Vector3f first_position_, Vector3f second_position_, Color color_);

        void check(collision* coll);
    };

    extern vector<model*> models;
    extern vector<polygon_model*> polygon_models;

    void render();
    void polygon_render();
}

#endif // ENGINE_MODEL_HPP