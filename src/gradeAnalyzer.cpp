#include "gradeAnalyzer.hpp"

#include <iostream>
#include <string>
#include <array>
#include <algorithm>

//these sizes have been tested and set to their respective value
std::array<std::string, 134> subjectIDstrArr; //the string array correlates with the int array
std::array<int, 134> subjectIDintArr; //holds number of subjectID 
int subjectCount = 0; //next new subject index
std::array<std::string, 3753> courseNumberstrArr; 
std::array<int, 3753> courseNumberintArr;  
int courseCount = 0; //next new course index

gradeAnalyzer::gradeAnalyzer(const std::array<grade, AllGradesArraySize> &gradesArr){ 
    m_gradesArray = gradesArr;
    for(const grade& g: m_gradesArray) 
    {
        bool containsSubject = false;
        for(int i = 0; i < subjectCount; i++){
            if(g.subject_id == subjectIDstrArr[i])
                {
                    containsSubject = true;
                    subjectIDintArr[i]++;
                    break;
                }
            }
        if(!containsSubject || subjectCount == 0)
        {
            subjectIDstrArr[subjectCount] = g.subject_id;
            subjectIDintArr[subjectCount]++;
            subjectCount++;
        }
        
        bool containsCourse = false;
        for(int i = 0; i < courseCount; i++){
            if(g.subject_id + " " + g.course_number == courseNumberstrArr[i])
                {
                    containsCourse = true;
                    courseNumberintArr[i]++;
                    break;
                }
            }
        if(!containsCourse || courseCount == 0)
        {
            courseNumberstrArr[courseCount] = g.subject_id + " " + g.course_number;
            courseNumberintArr[courseCount]++;
            courseCount++;
        }
    }
 /*
    for(int i = 0; i < subjectCount; i++)//used to show totals
    {
        if(subjectIDstrArr[i].size() < 8)
            std::cout << subjectIDstrArr[i] << "\t\t" << subjectIDintArr[i] << "\n";
        else
            std::cout << subjectIDstrArr[i] << "\t" << subjectIDintArr[i] << "\n";

    }
    std::cout << "Unique Subjects " << subjectCount<<"\n";
*/

/*
    for(int i = 0; i < courseCount; i++)//used to show totals
    {
        if(courseNumberstrArr[i].size() < 8)
            std::cout << courseNumberstrArr[i] << "\t\t" << courseNumberintArr[i] << "\n";
        else
            std::cout << courseNumberstrArr[i] << "\t" << courseNumberintArr[i] << "\n";

    }
    std::cout << "Unique Courses " << courseCount<<"\n";
*/

}


void gradeAnalyzer::printCourse() //prints subjects
{

}
void gradeAnalyzer::printCourse(std::string SubjectID) //prints course numbers within subjectID
{

}
void gradeAnalyzer::printCourse(std::string SubjectID, std::string CourseNumber) //prints all sections within
{

}


//the flunkers
void gradeAnalyzer::findWeedOuts() //prints SubjectID list
{

}
void gradeAnalyzer::findWeedOuts(std::string SubjectID) //prints CourseNumber list
{

}
void gradeAnalyzer::findWeedOuts(std::string SubjectID, std::string CourseNumber)//prints section number and term list
{

}

//opposite of weedOuts
void gradeAnalyzer::findExemplary() //prints SubjectID list
{

}
void gradeAnalyzer::findExemplary(std::string SubjectID) //prints CourseNumber list
{

}
void gradeAnalyzer::findExemplary(std::string SubjectID, std::string CourseNumber)//prints section number and term list
{

}
