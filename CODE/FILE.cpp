


#ifndef ENGINE_FILE_CPP
#define ENGINE_FILE_CPP

#include "CONFIG.hpp"
#include "MODEL.hpp"
#include "FILE.hpp"

namespace ENGINE_FILE {
    void read_vox_file(string filename, ENGINE_MODEL::model& model)
    {
        char palette[256][4];



        ifstream file(filename, ios::binary);
        file.ignore(8);

        while (file)
        {
            char chunk_id[4];
            file.read(chunk_id, 4);
            if (!file) break;

            uint32_t chunk_size;
            uint32_t child_chunk_size;
            file.read(reinterpret_cast<char*>(&chunk_size), sizeof(chunk_size));
            file.read(reinterpret_cast<char*>(&child_chunk_size), sizeof(child_chunk_size));

            string chunk_name(chunk_id, 4);

            if (chunk_name == "RGBA")
            {
                for (int i = 0; i < 256; ++i)
                {
                    uint8_t r, g, b, a;
                    if (file.read(reinterpret_cast<char*>(&r), 1) &&
                        file.read(reinterpret_cast<char*>(&g), 1) &&
                        file.read(reinterpret_cast<char*>(&b), 1) &&
                        file.read(reinterpret_cast<char*>(&a), 1))
                    {
                        palette[i][0] = r;
                        palette[i][1] = g;
                        palette[i][2] = b;
                        palette[i][3] = a;
                    }
                }
            }
            else
            {
                file.ignore(chunk_size);
            }
        }
        file.close();



        file.open(filename, ios::binary);
        file.ignore(8);

        while (file)
        {
            char chunk_id[4];
            file.read(chunk_id, 4);
            if (!file) break;

            uint32_t chunk_size;
            uint32_t child_chunk_size;
            file.read(reinterpret_cast<char*>(&chunk_size), sizeof(chunk_size));
            file.read(reinterpret_cast<char*>(&child_chunk_size), sizeof(child_chunk_size));

            string chunk_name(chunk_id, 4);

            if (chunk_name == "XYZI")
            {
                uint32_t voxels_number;
                file.read(reinterpret_cast<char*>(&voxels_number), sizeof(voxels_number));

                for (uint32_t i = 0; i < voxels_number; ++i)
                {
                    uint8_t x, y, z, color_index;
                    file.read(reinterpret_cast<char*>(&x), 1);
                    file.read(reinterpret_cast<char*>(&y), 1);
                    file.read(reinterpret_cast<char*>(&z), 1);
                    file.read(reinterpret_cast<char*>(&color_index), 1);

                    color_index--;

                    Color color(palette[color_index][0],
                        palette[color_index][1],
                        palette[color_index][2],
                        palette[color_index][3]);

                    model.voxels.push_back(ENGINE_MODEL::voxel(
                        Vector3f(x, y, z),
                        Vector3f(0, 0, 0),
                        color
                    ));
                }
            }
            else
            {
                file.ignore(chunk_size);
            }
        }
        file.close();
    }
    void save_in_log(string filename, string text)
    {
        time_t current_time = system_clock::to_time_t(system_clock::now());

        ofstream file(filename, ios::app);
        file << std::put_time(localtime(&current_time), "%Y-%m-%d %H:%M:%S") << "   -   ";
        file << text;
        file << endl;

        file.close();
    }
}

#endif // ENGINE_FILE_CPP