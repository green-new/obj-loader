#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

enum TYPE {
    VERTEX, 
    VERTEX_NORMAL,
    TEXTURE,
    FACE,
    LINES
};

std::map<std::string, enum TYPE> dataTypeMap {
    {"vn", VERTEX_NORMAL},
    {"v", VERTEX},
    {"f", FACE}
};

namespace loader {
    template<int N>
    class obj {
        private:
            char* filename;
            std::vector<float> vertices;
            std::vector<float> vertices_normal;
            std::vector<std::string> faces;
        public:
            /* Constructor */
            obj(std::string _filename) {
                std::ifstream file(_filename);
                std::string line = "";
                while (std::getline(file, line)) {
                    if (line[0] == '#' || line.empty()) {
                        continue;
                    }
                    std::string elements[N];
                    std::string dataType;
                    std::stringstream ss;
                    ss << line;
                    ss >> dataType;
                    for (auto& i : elements) {
                        ss >> i;
                    }
                    enum TYPE t = dataTypeMap[dataType];
                    switch(t) {
                        case VERTEX:
                            for (auto& i : elements) {
                                vertices.push_back(std::stof(i));
                            }
                            if (N == 3)
                                vertices.push_back(1.0f);
                        break;
                        case VERTEX_NORMAL:
                            for (auto& i : elements) {
                                vertices_normal.push_back(std::stof(i));
                            }
                        break;
                        case FACE:
                            for (auto& i : elements) {
                                faces.push_back(i);
                            }
                        break;
                        default:

                        break;
                    }
                }
            }

            float* vertex_data() {
                return vertices.data();
            }
    };
}