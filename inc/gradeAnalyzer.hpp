#pragma once

#include "dataImporter.hpp" // to use AllGradesArraySize
#include "grade.hpp"

#include <string>
#include <array>


struct gradeAnalyzer{

    gradeAnalyzer( std::array<grade, AllGradesArraySize>& gradesArr);
    
    void printCourse(); //prints subjects
    void printCourse(std::string SubjectID); //prints course numbers within subjectID
    void printCourse(std::string SubjectID, std::string CourseNumber); //prints all sections within

    //the flunkers AKA <C grade
    void findWeedOuts(); //prints overall lowest
    void findWeedOuts(std::string SubjectID); //prints lowest within Subject
    void findWeedOuts(std::string SubjectID, std::string CourseNumber);//prints lowest within course
    //opposite of weedOuts >=C
    void findExemplary(); //prints highest overall
    void findExemplary(std::string SubjectID); //prints highest within subject
    void findExemplary(std::string SubjectID, std::string CourseNumber);//prints highest within course 

    std::array<grade, AllGradesArraySize>& m_gradesArray; //reference to main grade array
    //no need for checked boolean array with the way were processing stuff
};
// there are 134 unique subject ids
// 3753 unique course numbers