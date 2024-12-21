


#ifndef ENGINE_RENDERING_CPP
#define ENGINE_RENDERING_CPP

#include "CONFIG.hpp"
#include "RENDERING.hpp"

namespace ENGINE_RENDERING {
    void draw_voxel(float size, Color color)
    {
        size /= 2.0f;

        const GLfloat vertices[8][3] = {
            {-size, -size, -size},
            { size, -size, -size},
            { size,  size, -size},
            {-size,  size, -size},
            {-size, -size,  size},
            { size, -size,  size},
            { size,  size,  size},
            {-size,  size,  size}
        };

        const GLuint faces[6][4] = {
            {0, 3, 2, 1},
            {4, 5, 6, 7},
            {0, 1, 5, 4},
            {3, 7, 6, 2},
            {0, 4, 7, 3},
            {1, 2, 6, 5}
        };

        glColor4f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);

        glBegin(GL_QUADS);
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 4; ++j) {
                const GLfloat* vertex = vertices[faces[i][j]];
                glVertex3f(vertex[0], vertex[1], vertex[2]);
            }
        }
        glEnd();
    }

    void draw_polygon_voxel(Vector3f first_position, Vector3f second_position, Color color)
    {
        Vector3f minimum = Vector3f(min(first_position.x, second_position.x), min(first_position.y, second_position.y), min(first_position.z, second_position.z));
        Vector3f maximum = Vector3f(max(first_position.x, second_position.x), max(first_position.y, second_position.y), max(first_position.z, second_position.z));

        Vector3f vertices[8] = {
            minimum, {minimum.x, minimum.y, maximum.z}, {minimum.x, maximum.y, minimum.z}, {minimum.x, maximum.y, maximum.z},
            {maximum.x, minimum.y, minimum.z}, {maximum.x, minimum.y, maximum.z}, {maximum.x, maximum.y, minimum.z}, maximum
        };

        int faces[6][4] = {
            {0, 1, 3, 2},
            {4, 5, 7, 6},
            {0, 1, 5, 4},
            {2, 3, 7, 6},
            {0, 2, 6, 4},
            {1, 3, 7, 5}
        };

        glColor4f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);

        glBegin(GL_QUADS);
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                Vector3f& v = vertices[faces[i][j]];
                glVertex3f(v.x, v.y, v.z);
            }
        }
        glEnd();
    }

    void draw_coordinates()
    {
        glColor3f(0.5, 0.5, 0.5);
        for (int i = 0; i < 8; ++i) {
            float phi1 = 3.14 * i / 8;
            float phi2 = 3.14 * (i + 1) / 8;

            glBegin(GL_TRIANGLE_STRIP);
            for (int j = 0; j <= 8; ++j) {
                float theta = 2 * 3.14 * j / 8;

                glVertex3f(sin(phi1) * cos(theta), cos(phi1), sin(phi1) * sin(theta));

                glVertex3f(sin(phi2) * cos(theta), cos(phi2), sin(phi2) * sin(theta));
            }
            glEnd();
        }



        glLineWidth(10);

        glColor3f(1, 0, 0);

        glBegin(GL_LINES);
        glVertex3f(-4096, 0, 0);
        glVertex3f(4096, 0, 0);
        glEnd();



        glColor3f(0, 1, 0);

        glBegin(GL_LINES);
        glVertex3f(0, -4096, 0);
        glVertex3f(0, 4096, 0);
        glEnd();



        glColor3f(0, 0, 1);

        glBegin(GL_LINES);
        glVertex3f(0, 0, -4096);
        glVertex3f(0, 0, 4096);
        glEnd();
    }
}

#endif // ENGINE_RENDERING_CPP