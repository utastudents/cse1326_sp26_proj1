#include "grade.hpp"
#include <fstream>
#include <string>
#include "json.hpp"
#include <array>

using json = nlohmann::json;
using Grades = std::array<grade,10000>;

struct dataImporter
{
    dataImporter(const std::string& _filename);
    void load(Grades& arr);

    std::string filename;
    std::ifstream file;
};
