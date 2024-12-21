


#ifndef ENGINE_FILE_HPP
#define ENGINE_FILE_HPP

namespace ENGINE_FILE {
    void read_vox_file(string filename, ENGINE_MODEL::model& mod);
    void save_in_log(string filename, string text);
}

#endif // ENGINE_FILE_HPP