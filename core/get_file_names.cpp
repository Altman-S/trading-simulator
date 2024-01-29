#include "header/get_file_names.h"

std::vector<std::string> get_file_names() {
    std::vector<std::string> file_names;

    DIR *dir_ptr = opendir("../data/");
    struct dirent *dir_entered_ptr;
    if (dir_ptr != nullptr) {
        dir_entered_ptr = readdir(dir_ptr);

        while (dir_entered_ptr != nullptr) {
            std::string cur_file_name = dir_entered_ptr->d_name;
            // Add the file name when it's not . or ..
            if (cur_file_name != "." && cur_file_name != ".." && cur_file_name != ".DS_Store") {
                file_names.push_back(cur_file_name);
            }
            dir_entered_ptr = readdir(dir_ptr);
        }

        closedir(dir_ptr);
    }
    else {
        std::cerr << "Could not open the data folder!" << std::endl;
    }
    
    return file_names;
}
