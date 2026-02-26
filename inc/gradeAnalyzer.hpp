#pragma once

#include "dataImporter.hpp" // to use AllGradesArraySize
#include "grade.hpp"

#include <string>
#include <array>


struct gradeAnalyzer{

    gradeAnalyzer(const std::array<grade, AllGradesArraySize> &gradesArr);
    
    void printCourse(); //prints subjects
    void printCourse(std::string SubjectID); //prints course numbers within subjectID
    void printCourse(std::string SubjectID, std::string CourseNumber); //prints all sections within

    //the flunkers AKA <C grade
    void findWeedOuts(); //prints SubjectID list
    void findWeedOuts(std::string SubjectID); //prints CourseNumber list
    void findWeedOuts(std::string SubjectID, std::string CourseNumber);//prints section number and term list
    //opposite of weedOuts >=C
    void findExemplary(); //prints SubjectID list
    void findExemplary(std::string SubjectID); //prints CourseNumber list
    void findExemplary(std::string SubjectID, std::string CourseNumber);//prints section number and term list

    std::array<grade, AllGradesArraySize> m_gradesArray;
    std::array<bool, AllGradesArraySize> checked; //to prevent unnesscary checking
};
// there are 134 unique subject ids
// 3753 unique course numbers