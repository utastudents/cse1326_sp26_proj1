#include "gradeAnalyzer.hpp"
#include "grade.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <algorithm>

const int MAX_GRADES = 45108; 
const int MAX_SUBJECT = 134; //number of subjects
const int MAX_SECTION = 761; //max number of sections within a course
const int MAX_COURSE = 3753; //number of unique courses

//these sizes have been tested and set to their respective value
std::array<std::string, MAX_SUBJECT> subjectIDstrArr; //the string array correlates with the int array
std::array<int, MAX_SUBJECT> subjectIDintArr; //holds number of subjectID 

int subjectCount = 0; //next new subject index

std::array<std::array<std::string, MAX_SECTION>,MAX_SUBJECT> coursesPerSubjectstrArr;  
std::array<std::array<int, MAX_SECTION>,MAX_SUBJECT> coursesPerSubjectintArr;  
std::array<int, MAX_SUBJECT> coursePerSubjectCount = {0};

std::array<std::array<grade*, MAX_SECTION>,MAX_SUBJECT> gradeReferenceArray;  

gradeAnalyzer::gradeAnalyzer( std::array<grade, AllGradesArraySize>& gradesArr):m_gradesArray(gradesArr) //using if(true) to show processes
{
    

    for( grade& g: m_gradesArray) 
    {
        //---------------------------------calculates total unique subjects
        int subjectIndex = -1;
        
        bool containsSubject = false;
        for(int i = 0; i < subjectCount; i++){
            if(g.subject_id == subjectIDstrArr[i])
                {
                    containsSubject = true;
                    subjectIDintArr[i]++;
                    subjectIndex = i;       //stashing for use in next
                    break;
                }
            }
        if(!containsSubject || subjectCount == 0)
        {
            subjectIndex = subjectCount;       //stashing for use in next
            
            subjectIDstrArr[subjectCount] = g.subject_id;
            subjectIDintArr[subjectCount]++;
            subjectCount++;
        }
        //---------------------------------------calculates unique course per subject
        bool containsCourseWithinSubject = false;
            for(int j = 0; j < coursePerSubjectCount[subjectIndex]; j++){
                if(g.subject_id + " " + g.course_number == coursesPerSubjectstrArr[subjectIndex][j])
                    {
                        containsCourseWithinSubject = true;
                        coursesPerSubjectintArr[subjectIndex][j]++;
                        break;
                    }
            }
        if(!containsCourseWithinSubject)
        {
            coursesPerSubjectstrArr[subjectIndex][coursePerSubjectCount[subjectIndex]] = g.subject_id + " " + g.course_number;
            gradeReferenceArray[subjectIndex][coursePerSubjectCount[subjectIndex]] = &g;
            coursesPerSubjectintArr[subjectIndex][coursePerSubjectCount[subjectIndex]]++;
            coursePerSubjectCount[subjectIndex]++;
        }
    }
    //now time to sort
    //sorting subjectIDS
    if(true)
    {
        for(int i = 0; i < MAX_SUBJECT - 1; i++)
            for(int j = 0; j < MAX_SUBJECT - i - 1; j++)
            {
                if(subjectIDstrArr[j] > subjectIDstrArr[j + 1])
                {
                    std::swap(subjectIDstrArr[j], subjectIDstrArr[j + 1]);
                    std::swap(subjectIDintArr[j], subjectIDintArr[j + 1]);
                    std::swap(coursesPerSubjectstrArr[j], coursesPerSubjectstrArr[j + 1]);
                    std::swap(coursesPerSubjectintArr[j], coursesPerSubjectintArr[j + 1]);
                    std::swap(coursePerSubjectCount[j], coursePerSubjectCount[j + 1]);
                    std::swap(gradeReferenceArray[j], gradeReferenceArray[j + 1]);
                }
                
            }
    }      

    //sorting courses within subject
    if(true)
    {
        for (int s = 0; s < subjectCount; s++)
        {
            int count = coursePerSubjectCount[s];

            for (int i = 0; i < count - 1; i++)
                for (int j = 0; j < count - i - 1; j++)
                {
                    if (coursesPerSubjectstrArr[s][j] > coursesPerSubjectstrArr[s][j + 1])
                    {
                        std::swap(coursesPerSubjectstrArr[s][j], coursesPerSubjectstrArr[s][j + 1]);
                        std::swap(coursesPerSubjectintArr[s][j], coursesPerSubjectintArr[s][j + 1]);
                        std::swap(gradeReferenceArray[s][j], gradeReferenceArray[s][j + 1]);
                    }
                }
        }
    }      //courses are now sorted alphabetically/numerically for printing

    //change to true to see output 
    if(false)
        printCourse();
    
}


void gradeAnalyzer::printCourse() //prints subjects
{

    if(true){
        for(int i = 0; i < subjectCount; i++) //used find total subjects
        {
            if(subjectIDstrArr[i].size() < 8)
                std::cout << subjectIDstrArr[i] << "\t\t" << subjectIDintArr[i] << "\n";
            else
                std::cout << subjectIDstrArr[i] << "\t" << subjectIDintArr[i] << "\n";

        }
        std::cout << "Subject" << "\t\t" << "Number of Courses\n\n";
        std::cout << "Total Subjects: " << subjectCount <<"\n\n~"; //should be 134

    }

    /*if(false){
        std::ofstream file("gradeAnalyzer.txt"); //writing to txt file to view entire output(for checking)
        if(!file.is_open())
            std::cerr << "Failed to open gradeAnalyzer.txt\n";
        int maxSizeCoursePerSubject = 0;
        int uniqueCourses = 0;
        int totalSections = 0;
        for(int i = 0; i < subjectCount; i++)//used to num of classes per course and sorted by section
        {
            for(int j = 0; j < coursePerSubjectCount[i]; j++)
            {
                std::string name = gradeReferenceArray[i][j]->subject_id + "  " + gradeReferenceArray[i][j]->course_number;
                if(true){
                
                    if(name.size() < 8)
                        file << name << "\t\t\t" << coursesPerSubjectintArr[i][j] << "\n";
                    else if(name.size() < 12)
                        file << name << "\t\t" << coursesPerSubjectintArr[i][j] << "\n";
                    else
                        file << name << "\t" << coursesPerSubjectintArr[i][j] << "\n";
                }
                if(false){
                    if(name.size() < 8)
                        std::cout << name << "\t\t" << coursesPerSubjectintArr[i][j] << "\n";
                    else
                        std::cout << name << "\t" << coursesPerSubjectintArr[i][j] << "\n";
                }
                uniqueCourses++;
                totalCourses += coursesPerSubjectintArr[i][j]; 
                if(maxSizeCoursePerSubject < coursesPerSubjectintArr[i][j])
                    maxSizeCoursePerSubject = coursesPerSubjectintArr[i][j];
            }
        }
        std::cout << "Course" << "\t\t" << "Number of Sections\n\n";
        std::cout << "Max number of sections within a course: " << maxSizeCoursePerSubject << "\n"; //should be 761 //ENGL1301(the class nobody wants to take)
        std::cout << "Unique Courses: " << uniqueCourses << "\n";         //should be 3753
        std::cout << "Total number of : " << totalSections << "\n"; //should be 45108
    }*/
}
void gradeAnalyzer::printCourse(std::string SubjectID) //prints course numbers within subjectID
{
    int maxSizeCoursePerSubject = 0;
    int totalCourses = 0;
    int totalSections = 0;
    for(int i = 0; i < subjectCount; i++)//used to num of classes per course and sorted by section
    {
        if(subjectIDstrArr[i] == SubjectID){
            for(int j = 0; j < coursePerSubjectCount[i]; j++)
            {
                std::string name = gradeReferenceArray[i][j]->subject_id + "  " + gradeReferenceArray[i][j]->course_number;
                
                if(name.size() < 8)
                    std::cout << name << "\t\t" << coursesPerSubjectintArr[i][j] << "\n";
                else
                    std::cout << name << "\t" << coursesPerSubjectintArr[i][j] << "\n";
                
                totalCourses++;
                totalSections += coursesPerSubjectintArr[i][j]; 
                if(maxSizeCoursePerSubject < coursesPerSubjectintArr[i][j])
                    maxSizeCoursePerSubject = coursesPerSubjectintArr[i][j];
            }
        }
    }
    std::cout << "Course" << "\t\t" << "Number of Sections\n\n";
    std::cout << "Max number of sections within a course listed: " << maxSizeCoursePerSubject << "\n"; 
    std::cout << "Total Courses: " << totalCourses << "\n";    
    std::cout << "Total number of Sections: " << totalSections << "\n\n";
}
void gradeAnalyzer::printCourse(std::string SubjectID, std::string CourseNumber) //prints all sections within
{
    int totalSections = 0;
    for(int i = 0; i < subjectCount; i++)//used to num of classes per course and sorted by section
    {
        if(subjectIDstrArr[i] == SubjectID){
            for(int j = 0; j < coursePerSubjectCount[i]; j++)
            {
                if(gradeReferenceArray[i][j]->course_number == CourseNumber)
                {
                    gradeReferenceArray[i][j]->print();
                }
            }
        }
    }
    std::cout << "Total number of Sections: " << totalSections << "\n\n";
}

const std::string CAREER = "UGRD"; 

//the flunkers
/*void gradeAnalyzer::findWeedOuts() //prints overall lowest
{
    const int MAXLIST = 10;
    double low[MAXLIST];

    std::string lowest_grades[10];

    for (int i = 0; i < MAXLIST; i++)
        lowest_gpas[i] = 9999.0;

    for (int i = 0; i < MAX_SECTION; i++)

    for (const grade& g : m_gradesArray)
    {
        if (g.career == CAREER)
        {

        }
    }
}

void gradeAnalyzer::findWeedOuts(std::string SubjectID) //prints CourseNumber list
{
    const int MAXLIST = 10;
    int listSize = 0; //if maxlist is too high this is a catch, incase there's not enough sections within parameter
     
    double lowest_gpas[MAXLIST];
    grade lowest_grades[MAXLIST];
    for (int i = 0; i < MAXLIST; i++)
        lowest_gpas[i] = 9999.0;
   
    for (const grade& g : m_gradesArray)
    {
        if (g.career == CAREER && g.subject_id == SubjectID)
        {
            double val = g.course_gpa / 4.0;
            listSize++;
            // find where it fits
            for (int i = 0; i < MAXLIST; i++)
            {
                if (val < lowest_gpas[i])
                {
                    // shift everything down
                    for (int j = 9; j > i; j--){
                        lowest_gpas[j] = lowest_gpas[j - 1];
                        lowest_grades[j] = lowest_grades[j - 1];
                    }
                    // insert new value
                    lowest_gpas[i] = val;
                    lowest_grades[i] = g;
                    break;
                }
            }
        }
    }
    // print results
    for (int i = 0; i < MAXLIST && i < listSize; i++)
        {
            lowest_grades[i].print();
            std::cout << "\n--------------------\n";
        }
        
}
void gradeAnalyzer::findWeedOuts(std::string SubjectID, std::string CourseNumber)//
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
*/