#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>

namespace mol {
    class loader {
        class obj {
        private:
            enum TYPE {
                VERTEX, 
                VERTEX_NORMAL,
                VERTEX_TEXTURE,
                TEXTURE,
                FACE,
                GROUP_NAME,
                USE_MATERIAL,
                SMOOTHING_GROUP
            };

            std::map<std::string, enum TYPE> strTypeMap {
                {"v", VERTEX},
                {"vn", VERTEX_NORMAL},
                {"vt", VERTEX_TEXTURE},
                {"f", FACE},
                {"g", GROUP_NAME},
                {"usemtl", USE_MATERIAL},
                {"s", SMOOTHING_GROUP}
            };
        public:
            std::vector<float> vertices;
            std::vector<float> vertices_normal;
            std::vector<std::string> faces;

            /* Constructor */
            obj(const std::string _filename) {
                std::ifstream file(_filename);
                if (file.is_open()) {
                    std::string line = "";
                    while (std::getline(file, line)) {
                        if (line[0] == '#' || line.empty()) {
                            continue;
                        }
                        std::string elements[3];
                        std::string dataType;
                        std::stringstream ss;
                        ss << line;
                        ss >> dataType;
                        for (auto& i : elements) {
                            ss >> i;
                        }
                        enum TYPE t = strTypeMap[dataType];
                        switch(t) {
                            case VERTEX:
                                for (auto& i : elements) {
                                    vertices.push_back(std::stof(i));
                                }
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
                            case GROUP_NAME:

                            break;
                            case USE_MATERIAL:

                            break;
                            case SMOOTHING_GROUP:

                            break;
                            default:

                            break;
                        }
                    }
                }
            }        
            public:
                obj() = default;
        };

    private:
        std::unordered_map<std::string, const obj> loaded;
        const obj blank_obj;

    public:
        bool obj_load(const std::string& _filename) {
            return loaded.insert({_filename, obj(_filename)}).second;
        }
        bool obj_unload(const std::string& _filename) {
            return loaded.erase(_filename) == 1;
        }
        void all_unload() {
            loaded.clear();
        }
        const obj& get_loaded_obj(const std::string& _filename) {
            auto it = this->loaded.find(_filename);
            return (it != this->loaded.end() ? (it->second) : (blank_obj));
        }
        const std::vector<float>& get_vertex_data(const std::string & _filename) {
            const obj& object = this->get_loaded_obj(_filename);
            return object.vertices;
        }
    };
}