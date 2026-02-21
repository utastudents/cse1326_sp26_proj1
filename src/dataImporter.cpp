#include "dataImporter.hpp"
#include <string>
#include <iostream>
#include <fstream>

auto to_int = [](const json& v)
{
    if (v.is_number()) 
        return v.get<int>();
    if (v.is_string()) 
        return std::stoi(v.get<std::string>());
    return 0;
};

auto to_double = [](const json& v)
{
    if (v.is_number()) 
    {
        return v.get<double>();
    }
    if (v.is_string())
    { 
        return std::stod(v.get<std::string>());
    }
    return 0.0;
};


dataImporter::dataImporter(const std::string& _filename): 
filename(_filename), file(_filename)
{
    if(!file.is_open())
        std::cerr << "Failed to open file: " << filename << "\n";
}

void dataImporter::load(Grades& arr)
{
    json j;
    if(!file.is_open())
    {
        std::cerr << "File not open\n";
        return;
    }
    try
    {
        file >> j;
    }
    catch(const std::exception& e)
    {
        std::cerr << "JSON parse error:" << e.what() << "\n";
        return;
    }

    int count = 0;
    if(!j.is_array())
    {
        std::cerr << "Top-level JSON is not an array\n";
    }
    for (const auto& group : j)
    {
        if (!group.is_array())
        {
            std::cerr << "Group is not an array\n";
            continue;
        }
        for (const auto& item : group)
        {
            grade g;  // constructor increments static counter

            g.subject_id = item["subject_id"].get<std::string>();
            g.course_number = to_int(item["course_number"]);
            g.grades_count  = to_int(item["grades_count"]);
            g.year          = to_int(item["year"]);
            const auto& gr = item["grades"];

            g.grades = {
                to_int(gr["A"]),
                to_int(gr["B"]),
                to_int(gr["C"]),
                to_int(gr["D"]),
                to_int(gr["F"]),
                to_int(gr["I"]),
                to_int(gr["P"]),
                to_int(gr["Q"]),
                to_int(gr["W"]),
                to_int(gr["Z"]),
                to_int(gr["R"])
            };

            g.semester = item["semester"].get<std::string>();
            g.career = item["career"].get<std::string>();
            g.instructor1 = item["instructor1"].get<std::string>();
            g.instructor2 = item["instructor2"].get<std::string>();
            g.instructor3 = item["instructor3"].get<std::string>();
            g.instructor4 = item["instructor4"].get<std::string>();
            g.instructor5 = item["instructor5"].get<std::string>();
            g.course_gpa   = to_double(item["course_gpa"]);
            g.drop_percent = to_double(item["drop_percent"]);
            
            arr[count] = g;   // copy into array
            count++;

            if (count >= 100){
            std::cout << "overflow prevented\n";
                return;       // prevent overflow
            }
        }
    }

   return;
}