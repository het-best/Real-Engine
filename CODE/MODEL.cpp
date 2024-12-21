


#ifndef ENGINE_MODEL_CPP
#define ENGINE_MODEL_CPP

#include "CONFIG.hpp"

namespace ENGINE_MODEL {

    vector<model*> models;
    vector<polygon_model*> polygon_models;

    struct vector_hash {
        size_t operator()(const Vector3f& vec) const noexcept {
            size_t h1 = hash<float>()(vec.x);
            size_t h2 = hash<float>()(vec.y);
            size_t h3 = hash<float>()(vec.z);

            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };

    voxel::voxel(Vector3f position_, Vector3f rotation_, Color color_) : position(position_), rotation(rotation_), color(color_) {}
    void voxel::render()
    {
        glPushMatrix();

        glTranslatef(position.x, position.y, position.z);
        glRotatef(rotation.x, 1, 0, 0);
        glRotatef(rotation.y, 0, 1, 0);
        glRotatef(rotation.z, 0, 0, 1);
        ENGINE_RENDERING::draw_voxel(1, color);

        glPopMatrix();
    }

    void polygon_voxel::render()
    {
        ENGINE_RENDERING::draw_polygon_voxel(first_position, second_position, color);
    }

    polygon_model::polygon_model(model* model_to_copy_from)
    {
        position = model_to_copy_from->position;

        std::unordered_map<Vector3f, Color, vector_hash> voxel_map;
        for (const auto& voxel : model_to_copy_from->voxels) {
            voxel_map[voxel.position] = voxel.color;
        }

        std::unordered_set<Vector3f, vector_hash> visited;

        for (const auto& voxel : model_to_copy_from->voxels) {
            if (visited.count(voxel.position)) {
                continue;
            }

            polygon_voxel poly;
            poly.first_position = voxel.position;
            poly.color = voxel.color;

            Vector3f dimensions(1, 1, 1);

            while (voxel_map.count(poly.first_position + Vector3f(dimensions.x, 0, 0)) &&
                voxel_map[poly.first_position + Vector3f(dimensions.x, 0, 0)] == poly.color &&
                !visited.count(poly.first_position + Vector3f(dimensions.x, 0, 0))) {
                dimensions.x++;
            }

            bool valid_y = true;
            while (valid_y) {
                for (int dx = 0; dx < dimensions.x; dx++) {
                    Vector3f check_pos = poly.first_position + Vector3f(dx, dimensions.y, 0);
                    if (!voxel_map.count(check_pos) ||
                        voxel_map[check_pos] != poly.color ||
                        visited.count(check_pos)) {
                        valid_y = false;
                        break;
                    }
                }
                if (valid_y) {
                    dimensions.y++;
                }
            }

            bool valid_z = true;
            while (valid_z) {
                for (int dx = 0; dx < dimensions.x; dx++) {
                    for (int dy = 0; dy < dimensions.y; dy++) {
                        Vector3f check_pos = poly.first_position + Vector3f(dx, dy, dimensions.z);
                        if (!voxel_map.count(check_pos) ||
                            voxel_map[check_pos] != poly.color ||
                            visited.count(check_pos)) {
                            valid_z = false;
                            break;
                        }
                    }
                    if (!valid_z) break;
                }
                if (valid_z) {
                    dimensions.z++;
                }
            }

            for (int dx = 0; dx < dimensions.x; dx++) {
                for (int dy = 0; dy < dimensions.y; dy++) {
                    for (int dz = 0; dz < dimensions.z; dz++) {
                        visited.insert(poly.first_position + Vector3f(dx, dy, dz));
                    }
                }
            }

            poly.second_position = poly.first_position + dimensions;

            polygon_voxels.push_back(poly);
        }
    }
    polygon_model::polygon_model(model model_to_copy_from)
    {
        position = model_to_copy_from.position;

        std::unordered_map<Vector3f, Color, vector_hash> voxel_map;
        for (const auto& voxel : model_to_copy_from.voxels) {
            voxel_map[voxel.position] = voxel.color;
        }

        std::unordered_set<Vector3f, vector_hash> visited;

        for (const auto& voxel : model_to_copy_from.voxels) {
            if (visited.count(voxel.position)) {
                continue;
            }

            polygon_voxel poly;
            poly.first_position = voxel.position;
            poly.color = voxel.color;

            Vector3f dimensions(1, 1, 1);

            while (voxel_map.count(poly.first_position + Vector3f(dimensions.x, 0, 0)) &&
                voxel_map[poly.first_position + Vector3f(dimensions.x, 0, 0)] == poly.color &&
                !visited.count(poly.first_position + Vector3f(dimensions.x, 0, 0))) {
                dimensions.x++;
            }

            bool valid_y = true;
            while (valid_y) {
                for (int dx = 0; dx < dimensions.x; dx++) {
                    Vector3f check_pos = poly.first_position + Vector3f(dx, dimensions.y, 0);
                    if (!voxel_map.count(check_pos) ||
                        voxel_map[check_pos] != poly.color ||
                        visited.count(check_pos)) {
                        valid_y = false;
                        break;
                    }
                }
                if (valid_y) {
                    dimensions.y++;
                }
            }

            bool valid_z = true;
            while (valid_z) {
                for (int dx = 0; dx < dimensions.x; dx++) {
                    for (int dy = 0; dy < dimensions.y; dy++) {
                        Vector3f check_pos = poly.first_position + Vector3f(dx, dy, dimensions.z);
                        if (!voxel_map.count(check_pos) ||
                            voxel_map[check_pos] != poly.color ||
                            visited.count(check_pos)) {
                            valid_z = false;
                            break;
                        }
                    }
                    if (!valid_z) break;
                }
                if (valid_z) {
                    dimensions.z++;
                }
            }

            for (int dx = 0; dx < dimensions.x; dx++) {
                for (int dy = 0; dy < dimensions.y; dy++) {
                    for (int dz = 0; dz < dimensions.z; dz++) {
                        visited.insert(poly.first_position + Vector3f(dx, dy, dz));
                    }
                }
            }

            poly.second_position = poly.first_position + dimensions;

            polygon_voxels.push_back(poly);
        }
    }
    void polygon_model::render()
    {
        glPushMatrix();

        glTranslatef(position.x, position.y, position.z);

        for (int i = 0; i < polygon_voxels.size(); i++)
        {
            polygon_voxels.at(i).render();
        }

        glPopMatrix();
    }

    model::model(string path_to_vox)
    {
        ENGINE_FILE::read_vox_file(path_to_vox, *this);
    }
    void model::render()
    {
        glPushMatrix();

        glTranslatef(position.x, position.y, position.z);

        for (int i = 0; i < voxels.size(); i++)
        {
            voxels.at(i).render();
        }

        glPopMatrix();
    }
    void model::rotate_around_point(Vector3f point, Vector3f rotation_vector)
    {
    }

    collision::collision(Vector3f first_position_, Vector3f second_position_, Color color_) : first_position(first_position_), second_position(second_position_), color(color_) {}
    void collision::check(collision* coll)
    {
        if (coll->first_position.x < first_position.x && coll->first_position.x < second_position.x &&
            coll->first_position.y < first_position.y && coll->first_position.y < second_position.y &&
            coll->first_position.z < first_position.z && coll->first_position.z < second_position.z &&
            
            coll->second_position.x > first_position.x && coll->second_position.x > second_position.x &&
            coll->second_position.y > first_position.y && coll->second_position.y > second_position.y &&
            coll->second_position.z > first_position.z && coll->second_position.z > second_position.z)
        {
            on_collision(this, coll);
        }
        else
        {
            on_no_collision();
            ENGINE_RENDERING::draw_polygon_voxel(coll->first_position, coll->second_position, coll->color);
        }
    }

    void render()
    {
        for (int i = 0; i < models.size(); i++)
        {
            models.at(i)->render();
        }
    }
    void polygon_render()
    {
        for (int i = 0; i < polygon_models.size(); i++)
        {
            polygon_models.at(i)->render();
        }
    }
}

#endif // ENGINE_MODEL_CPP