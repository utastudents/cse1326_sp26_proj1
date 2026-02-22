#pragma once

#include <array>

#include "grade.hpp"

// Define it as a MACRO
constexpr size_t MAX_DATA_RECORDS = 10000;

// Function to calculate and print Weed-out statistics
void printWeedoutStatistics(const std::array<grade, MAX_DATA_RECORDS>& Grades);
