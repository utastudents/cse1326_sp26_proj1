#include "gradeAnalyzer.hpp"
#include "grade.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <limits.h>
#include <cctype>

std::ofstream file("gradeAnalyzer.txt");


const int MAX_GRADES = 45108; 
const int MAX_SUBJECT = 134; //number of unique subjects
//const int MAX_COURSE_PER_SUBJECT = 141; //max number of courses within a subject
const int MAX_COURSE = 3753; // number of unique courses
//const int MAX_SECTION_PER_COURSE = 761; //max number of sections within a course

//these sizes have been tested and set to their respective value
std::array<std::string, MAX_SUBJECT> subjectName; //the string array correlates with the int array
std::array<int, MAX_SUBJECT> subjectSectionBegin; //an array to have number of sections within the subject


std::array<std::string, MAX_COURSE> courseName;
std::array<int, MAX_COURSE> courseSectionBegin;



int containsSubject(std::array<std::string, MAX_SUBJECT> subArr, std::string subject){
    for(int i = 0; i < MAX_SUBJECT; i++)
    {
        if(subArr[i] == subject)
            return i;
    }
    return -1;
}

int containsCourse(std::array<std::string, MAX_COURSE> courseArr, std::string course){
    for(int i = 0; i < MAX_COURSE; i++)
    {
        if(courseArr[i] == course)
            return i;
    }
    return -1;
}

gradeAnalyzer::gradeAnalyzer(std::array<grade, AllGradesArraySize>& gradesArr):m_gradesArray(gradesArr) //using if(true) to show processes
{   
    { // organizes subject names alphabeticly and collects array of how many sections per subject
        std::fill(subjectName.begin(), subjectName.end(), std::to_string(INT_MIN));
        std::fill(subjectSectionBegin.begin(), subjectSectionBegin.end(), 1);
        for(grade& g: m_gradesArray){
            std::string tempName = g.subject_id;
            int tempCount;
            int index = containsSubject(subjectName, tempName);
            if(index != -1)
                {
                    //std::cout << "subjectName arr contains " << tempName << "\n";
                    subjectSectionBegin[index]++;
                    continue;
                }
            for(int i = MAX_SUBJECT - 1; i >= 0; i--)
            {
                if(subjectName[i] < tempName){
                    //std::cout << "Swapping " << subjectName[i] << " and " << tempName << "\n";
                    std::swap(subjectName[i], tempName);
                    std::swap(subjectSectionBegin[i], tempCount);
                }
            }
        }

        //for(int i = 0; i < 10; i++)std::cout << i << ". " << subjectName[i] << "\t" << subjectSectionBegin[i] << "\n";// shows front
        //for(int i = MAX_SUBJECT-1; i > MAX_SUBJECT-10; i--)std::cout << i << ". " << subjectName[i] << "\t" << subjectSectionBegin[i] << "\n"; //shows end
        int temp = 33;
        int newtemp;
        subjectSectionBegin[0] = 0;
        for(int i = 1; i < MAX_SUBJECT; i++)     //using counts of each subject, were turning that into starting indexs of each
        {
            newtemp = subjectSectionBegin[i];
            subjectSectionBegin[i] = temp + subjectSectionBegin[i-1];
            temp = newtemp;
        }
        //for(int i = 0; i < 10; i++)std::cout << i << ". " << subjectName[i] << "\t" << subjectSectionBegin[i] << "\n"; //shows front
        //for(int i = MAX_SUBJECT-10; i < MAX_SUBJECT; i++)std::cout << i << ". " << subjectName[i] << "\t" << subjectSectionBegin[i] << "\n"; //shows end    

    }
    { // organizes course names alphabeticly and collects array of how many sections per course
        std::fill(courseName.begin(), courseName.end(), std::to_string(INT_MIN));
        std::fill(courseSectionBegin.begin(), courseSectionBegin.end(), 1);
        for(grade& g: m_gradesArray){
            std::string tempName = g.subCor;
            int tempCount;
            int index = containsCourse(courseName, tempName);
            if(index != -1)
                {
                    //std::cout << "subjectName arr contains " << tempName << "\n";
                    courseSectionBegin[index]++;
                    continue;
                }
            for(int i = MAX_COURSE - 1; i >= 0; i--)
            {
                if(courseName[i] < tempName){
                    //std::cout << "Swapping " << subjectName[i] << " and " << tempName << "\n";
                    std::swap(courseName[i], tempName);
                    std::swap(courseSectionBegin[i], tempCount);
                }
            }
        }
       
        //for(int i = 0; i < 100; i++)std::cout << i << ". " << courseName[i] << "\t" << courseSectionBegin[i] << "\n";// shows front
        //for(int i = MAX_COURSE-1; i > MAX_COURSE-100; i--)std::cout << i << ". " << courseName[i] << "\t" << courseSectionBegin[i] << "\n"; //shows end
        int temp = 10;
        int newtemp;
        courseSectionBegin[0] = 0;
        for(int i = 1; i < MAX_COURSE; i++)     //using counts of each course, were turning that into starting indexs of each
        {
            newtemp = courseSectionBegin[i];
            courseSectionBegin[i] = temp + courseSectionBegin[i-1];
            temp = newtemp;
        }
        //for(int i = 0; i < 100; i++)std::cout << i << ". " << courseName[i] << "\t" << courseSectionBegin[i] << "\n"; //shows front
        //for(int i = MAX_COURSE-100; i < MAX_COURSE; i++)std::cout << i << ". " << courseName[i] << "\t" << courseSectionBegin[i] << "\n"; //shows end
                    
    }
    //using bucket sort then bubble sort
        // we can do that later if needed -Johnny
    {   
        std::array<int, MAX_COURSE> counter;
        std::fill(counter.begin(), counter.end(), 0);
        for(grade& g: m_gradesArray)
        {
            for(int j = 0; j < MAX_COURSE; j++)
                if(g.subCor == courseName[j])
                {   
                    //std::cout << g.subCor << "      " << courseSectionBegin[j] << "   +  " << counter[j] <<"\n";
                    sortedGrades[courseSectionBegin[j] + counter[j]] = &g;
                    counter[j]++;
                    break;
                }
        }
        //for(grade* g : sortedGrades)std::cout << g->subCorSec << std::endl; 
            
    
        for(int i = 1; i < MAX_COURSE; i++){
            for(int j = courseSectionBegin[i - 1]; j < courseSectionBegin[i] && j < MAX_GRADES; j++)
            {
                for(int k = j; k < courseSectionBegin[i] && k < MAX_GRADES - j - 1; k++)
                {
                    if
                    ( 
                    sortedGrades[k]->subCorSec
                    + std::to_string(sortedGrades[k]->year)
                    + (sortedGrades[k]->semester == "Spring" ? "1" : sortedGrades[k]->semester == "Summer" ? "2" : sortedGrades[k]->semester == "Fall" ? "3" : "-1") 
                    > sortedGrades[k+1]->subCorSec
                    + std::to_string(sortedGrades[k+1]->year)
                    + (sortedGrades[k+1]->semester == "Spring" ? "1" : sortedGrades[k+1]->semester == "Summer" ? "2" : sortedGrades[k+1]->semester == "Fall" ? "3" : "-1")
                    )
                        std::swap(sortedGrades[k],  sortedGrades[k + 1]);
                }
            }
        }
        //for(int i = MAX_GRADES - 100; i < MAX_GRADES; i++)   std::cout << sortedGrades[i]->subCorSecTermYear << "\n";
    }
}


void gradeAnalyzer::printCourse() //prints subjects
{
    int grandTotal = 0;
    for (int i = 0; i < MAX_SUBJECT; i++) {
        int total = (i == MAX_SUBJECT - 1 ? MAX_GRADES : subjectSectionBegin[i + 1]) - subjectSectionBegin[i];    
        grandTotal += total;
        std::cout << subjectName[i] << (subjectName[i].size() < 8 ? "\t" : "\t\t") << total << "\n";
    }
    std::cout << "Subject" << "\t\t" << "Number of Sections\n\n";
    std::cout << "Total Subjects: " << MAX_SUBJECT <<"\n"; //should be 134
    std::cout << "Total Sections: " << grandTotal <<"\n\n"; //should be 134
}
void gradeAnalyzer::printCourse(std::string SubjectID) //prints course numbers within subjectID
{
    
    int start;
    int end;
    int totalSections = 0;
    for(int i = 0; i <= MAX_SUBJECT; i++)
    {
        if(i == MAX_SUBJECT)
        {
            std::cout << "No courses found within Subject ID: " << SubjectID << "\n\n"; 
            return;                
        }
        if(subjectName[i] == SubjectID)
        {
            start = subjectSectionBegin[i];
            end = subjectSectionBegin[i + 1];
            totalSections = ( i != MAX_SUBJECT - 1 ? end - start : 59);//handles the edge
            break; 
        }
    }
    int beginCourseIndex;
    int endCourseIndex;
    for(int i = 0; i < MAX_COURSE; i++)
    {
        if(courseSectionBegin[i] == start){
            beginCourseIndex = i;
        }
        if(courseSectionBegin[i] == end){
            endCourseIndex = i;
        }
    }
    int totalCourses = 0;
    for (int i = beginCourseIndex; courseName[i] != courseName[endCourseIndex] && i < MAX_COURSE; i++) {
    {
        totalCourses++;
        int total = (i == MAX_COURSE - 1 ? MAX_GRADES : courseSectionBegin[i + 1]) - courseSectionBegin[i]; 
        std::cout << courseName[i] << (courseName[i].size() < 8 ? "\t" : "\t\t") << total << "\n";
    }
    }
    std::cout << "Course" << "\t\t" << "Number of Sections\n" << SubjectID << "\n";
    std::cout << "Total Courses: " << totalCourses << "\n";    
    std::cout << "Total number of Sections: " << totalSections << "\n\n";
    
}
void gradeAnalyzer::printCourse(std::string SubjectID, std::string CourseNumber) //prints all sections within
{
    int start;
    int end;
    int totalSections = 0;
    std::string search = SubjectID + " " + CourseNumber; 
    for(int i = 0; i <= MAX_COURSE; i++)
    {
        if(i == MAX_COURSE)
        {
            std::cout << "No sections found within: " << SubjectID + " " + CourseNumber << "\n\n"; 
            return;                
        }
        if(courseName[i] == search)
        {
            start = courseSectionBegin[i];
            end = (i != MAX_COURSE - 1 ? courseSectionBegin[i + 1] : MAX_GRADES);
            totalSections = end - start;
            break; 
        }
    }
    for (int i = start; i < end; i++) {
        std::cout << sortedGrades[i]->section_number << "\t" <<  sortedGrades[i]->semester << " " << sortedGrades[i]->year << "\n";
    }
    std::cout << "Section"  << "\t" << "Term\n" << search << "\n";
    std::cout << "Total number of Sections: " << totalSections << "\n\n";
}


const int MAXLIST = 100; //can be edited for how many YOU want printed
const std::string CAREER = "UGRD"; 

//the flunkers
void gradeAnalyzer::findPercents(bool findLowest) //prints lowest overall
{
    std::array<double, MAXLIST> percent; //will hold lowest scores
    std::array<std::string, MAXLIST> percentName; //will hold name correlating w/ lowest scores
    if(findLowest)
        std::fill(percent.begin(), percent.end(), 1000); //sets to high number for comparisons
    else
        std::fill(percent.begin(), percent.end(), -1); //sets to low number for comparisons    
    int totalCounted = 0; //pervents calling to array with empty slots in case of MAXLIST being higher than valid scans
    for (int i = 0; i < MAX_COURSE; i++)
    {
        if (sortedGrades[courseSectionBegin[i]]->career != CAREER)
            continue;
        double denominator = 0; //grade count total
        double numerator = 0;  //total num of As,Bs,Cs
        for (int j = courseSectionBegin[i]; j < (j != MAX_GRADES - 1 ? courseSectionBegin[i + 1] : MAX_GRADES); j++) 
        {
            denominator += sortedGrades[j]->grades_count;
            numerator   += sortedGrades[j]->grades.A + sortedGrades[j]->grades.B + sortedGrades[j]->grades.C;
        }    
        if (denominator == 0)
            continue;
        totalCounted++;
        double temp = (numerator * 100) / denominator;
        std::string strTemp = sortedGrades[courseSectionBegin[i]]->subCor;
        for(int i = 0; i < MAXLIST; i++)
        {   
            if(temp < percent[i] && findLowest) //swap and carry
                {
                    std::swap(temp, percent[i]);
                    std::swap(strTemp, percentName[i]);
                }  
                else if(temp > percent[i] && ! findLowest) //swap and carry
                {
                    std::swap(temp, percent[i]);
                    std::swap(strTemp, percentName[i]);
                }   
        }   
    }
    for(int i = 0; i < MAXLIST && i < totalCounted; i++) //done time to print
    {
        if(percentName[i].size() < 8)
                std::cout << percentName[i] << "\t\t" << percent[i] << "%\n";
        else
            std::cout << percentName[i] << "\t" << percent[i] << "%\n";
    }
    std::cout << "Course\t\tPassing Rate\n\n";
}

void gradeAnalyzer::findPercents(std::string SubjectID, bool findLowest) //prints lowest within subject
{
    std::array<double, MAXLIST> percent; //will hold lowest scores
    std::array<std::string, MAXLIST> percentName; //will hold name correlating w/ lowest scores
    if(findLowest)
        std::fill(percent.begin(), percent.end(), 1000); //sets to high number for comparisons
    else
        std::fill(percent.begin(), percent.end(), -1); //sets to low number for comparisons    
    int totalCounted = 0; //pervents calling to array with empty slots in case of MAXLIST being higher than valid scans
    bool found = false;
    for (int i = 0; i < MAX_COURSE; i++)
    {
        if (sortedGrades[courseSectionBegin[i]]->career != CAREER || sortedGrades[courseSectionBegin[i]]->subject_id != SubjectID){
            if(found)
                break;
            continue;
        }
        found = true;
        double denominator = 0; //grade count total
        double numerator = 0;  //total num of As,Bs,Cs
        for (int j = courseSectionBegin[i]; j < (j != MAX_GRADES - 1 ? courseSectionBegin[i + 1] : MAX_GRADES); j++) 
        {
            denominator += sortedGrades[j]->grades_count;
            numerator   += sortedGrades[j]->grades.A + sortedGrades[j]->grades.B + sortedGrades[j]->grades.C;
        }    
        if (denominator == 0)
            continue;
        totalCounted++;
        double temp = (numerator * 100) / denominator;
        std::string strTemp = sortedGrades[courseSectionBegin[i]]->subCor;
        for(int i = 0; i < MAXLIST; i++)
        {   
            if(temp < percent[i] && findLowest) //swap and carry
                {
                    std::swap(temp, percent[i]);
                    std::swap(strTemp, percentName[i]);
                }  
                else if(temp > percent[i] && ! findLowest) //swap and carry
                {
                    std::swap(temp, percent[i]);
                    std::swap(strTemp, percentName[i]);
                }    
        }   
    }
    for(int i = 0; i < MAXLIST && i < totalCounted; i++) //done time to print
    {
        if(percentName[i].size() < 8)
                std::cout << percentName[i] << "\t\t" << percent[i] << "%\n";
        else
            std::cout << percentName[i] << "\t" << percent[i] << "%\n";
    }
    std::cout << "Course\t\tPassing Rate\n" << SubjectID << "\n";
}
void gradeAnalyzer::findPercents(std::string SubjectID, std::string CourseNumber, bool findLowest)
{
    std::array<double, MAXLIST> percent; //will hold lowest scores
    std::array<std::string, MAXLIST> percentName; //will hold name correlating w/ lowest scores
    if(findLowest)
        std::fill(percent.begin(), percent.end(), 1000); //sets to high number for comparisons
    else
        std::fill(percent.begin(), percent.end(), -1); //sets to low number for comparisons
    int totalCounted = 0; //pervents calling to array with empty slots in case of MAXLIST being higher than valid scans
    bool found = false;
    for (int i = 0; i < MAX_COURSE; i++)
    {
        if (sortedGrades[courseSectionBegin[i]]->career != CAREER || sortedGrades[courseSectionBegin[i]]->subCor != SubjectID + " " + CourseNumber){
            if(found)
                break;
            continue;
        }
        found = true;
        double denominator = 0; //grade count total
        double numerator = 0;  //total num of As,Bs,Cs
        for (int j = courseSectionBegin[i]; j < (j != MAX_GRADES - 1 ? courseSectionBegin[i + 1] : MAX_GRADES); j++) 
        {
            denominator += sortedGrades[j]->grades_count;
            numerator   += sortedGrades[j]->grades.A + sortedGrades[j]->grades.B + sortedGrades[j]->grades.C;
            if (denominator == 0)
                continue;
            totalCounted++;
            double temp = (numerator * 100) / denominator;
            std::string strTemp = sortedGrades[j]->section_number + "\t" + 
            sortedGrades[j]->semester + " " +  std::to_string(sortedGrades[j]->year);

            for(int i = 0; i < MAXLIST; i++)
            {   
                if(temp < percent[i] && findLowest) //swap and carry
                {
                    std::swap(temp, percent[i]);
                    std::swap(strTemp, percentName[i]);
                }  
                else if(temp > percent[i] && ! findLowest) //swap and carry
                {
                    std::swap(temp, percent[i]);
                    std::swap(strTemp, percentName[i]);
                }  
            }
        }   
    }
    for(int i = 0; i < MAXLIST && i < totalCounted; i++) //done time to print
    {
         std::cout << percentName[i] << "\t" << percent[i] << "%\n";
    }
    std::cout << "Section\t\t\tPassing Rate\n" << SubjectID << " " << CourseNumber << "\n";
}