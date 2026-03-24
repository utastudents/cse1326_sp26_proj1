#pragma once

#include "json.hpp"
#include "grade.hpp"

#include <array>
#include <fstream>
#include <string>


using json = nlohmann::json;
using AllGradesArray = std::array<grade,45108>;
const int AllGradesArraySize  = 45108; //renamed to a more defined, to prevent mix ups

struct dataImporter
{
    dataImporter(const std::string& _filename);
    void load(std::array<grade, AllGradesArraySize> &arr);

    std::string filename;
    std::ifstream file;
};
