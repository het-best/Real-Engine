


#ifndef ENGINE_RENDERING_HPP
#define ENGINE_RENDERING_HPP

namespace ENGINE_RENDERING {
    extern void draw_voxel(float size, Color color);
    extern void draw_polygon_voxel(Vector3f first_position, Vector3f second_position, Color color);
    extern void draw_coordinates();
}

#endif // ENGINE_RENDERING_HPP