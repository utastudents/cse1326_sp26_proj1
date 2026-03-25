#pragma once

#include "dataImporter.hpp" // to use AllGradesArraySize
#include "grade.hpp"

#include <string>
#include <array>


struct gradeAnalyzer{

    gradeAnalyzer(std::array<grade, AllGradesArraySize>& gradesArr);
    
    void printCourse(); //prints subjects
    void printCourse(std::string SubjectID); //prints course numbers within subjectID
    void printCourse(std::string SubjectID, std::string CourseNumber); //prints all sections within

    //the flunkers AKA <C grade                                         //if 1 -> find weedouts else find best
    void findPercents(bool findLowest); //prints overall lowest
    void findPercents(std::string SubjectID, bool findLowest); //prints lowest within Subject
    void findPercents(std::string SubjectID, std::string CourseNumber, bool findLowest);//prints lowest within course
   
    std::array<grade, AllGradesArraySize>& m_gradesArray; //reference to main grade array
    std::array<grade*, AllGradesArraySize> sortedGrades; //a new ptr array that we have sorted 

    //no need for checked boolean array with the way were processing stuff
};
// there are 134 unique subject ids
// 3753 unique course numbers
// there's a max of 761 sections within a course