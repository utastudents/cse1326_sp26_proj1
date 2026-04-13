#pragma once

#include "json.hpp"
#include "grade.hpp"

#include <vector>
#include <array>
#include <fstream>
#include <string>


struct dataImporter
{
    dataImporter(const std::string& _filename);
    void load(std::vector<grade> &v);

    std::string filename;
    std::ifstream file;
};
