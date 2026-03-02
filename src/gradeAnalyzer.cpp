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
std::array<std::string, MAX_SUBJECT> subjectStrArr; //the string array correlates with the int array
std::array<int, MAX_SUBJECT> subjectIntArr; //holds number of subjectID 
int subjectCount = 0; //next new subject index

std::array<std::array<std::string, MAX_SECTION>,MAX_SUBJECT> courseStrArr;  
std::array<std::array<int, MAX_SECTION>,MAX_SUBJECT> courseIntArr;  
std::array<int, MAX_SUBJECT> courseCountArr = {0};

std::array<std::array<grade*, MAX_SECTION>,MAX_SUBJECT> gradeReferenceArray; //grade reference array syncs with the others

gradeAnalyzer::gradeAnalyzer(std::array<grade, AllGradesArraySize>& gradesArr):m_gradesArray(gradesArr) //using if(true) to show processes
{
    for(grade& g: m_gradesArray) 
    {
        //---------------------------------calculates total unique subjects
        int subjectIndex = -1;
        
        bool containsSubject = false;
        for(int i = 0; i < subjectCount; i++){
            if(g.subject_id == subjectStrArr[i])
                {
                    containsSubject = true;
                    subjectIntArr[i]++;
                    subjectIndex = i;       //stashing for use in next
                    break;
                }
            }
        if(!containsSubject || subjectCount == 0)
        {
            subjectIndex = subjectCount;       //stashing for use in next
            
            subjectStrArr[subjectCount] = g.subject_id;
            subjectIntArr[subjectCount]++;
            subjectCount++;
        }
        //---------------------------------------calculates unique course per subject
        bool containsCourseWithinSubject = false;
            for(int j = 0; j < courseCountArr[subjectIndex]; j++){
                if(g.subject_id + " " + g.course_number == courseStrArr[subjectIndex][j])
                    {
                        containsCourseWithinSubject = true;
                        courseIntArr[subjectIndex][j]++;
                        break;
                    }
            }
        if(!containsCourseWithinSubject)
        {
            courseStrArr[subjectIndex][courseCountArr[subjectIndex]] = g.subject_id + " " + g.course_number;
            gradeReferenceArray[subjectIndex][courseCountArr[subjectIndex]] = &g;
            courseIntArr[subjectIndex][courseCountArr[subjectIndex]]++;
            courseCountArr[subjectIndex]++;
        }
    }
    //now time to sort
    //sorting subjectIDS
    if(true) //bubble sort
    {
        for(int i = 0; i < MAX_SUBJECT - 1; i++)
            for(int j = 0; j < MAX_SUBJECT - i - 1; j++)
            {
                if(subjectStrArr[j] > subjectStrArr[j + 1])
                {
                    std::swap(subjectStrArr[j], subjectStrArr[j + 1]);
                    std::swap(subjectIntArr[j], subjectIntArr[j + 1]);
                    std::swap(courseStrArr[j], courseStrArr[j + 1]);
                    std::swap(courseIntArr[j], courseIntArr[j + 1]);
                    std::swap(courseCountArr[j], courseCountArr[j + 1]);
                    std::swap(gradeReferenceArray[j], gradeReferenceArray[j + 1]); 
                }
                
            }
    }      

    //sorting courses within subject
    if(true)
    {
        for (int s = 0; s < subjectCount; s++)
        {
            int count = courseCountArr[s];

            for (int i = 0; i < count - 1; i++)
                for (int j = 0; j < count - i - 1; j++)
                {
                    if (courseStrArr[s][j] > courseStrArr[s][j + 1])
                    {
                        std::swap(courseStrArr[s][j], courseStrArr[s][j + 1]);
                        std::swap(courseIntArr[s][j], courseIntArr[s][j + 1]);
                        std::swap(gradeReferenceArray[s][j], gradeReferenceArray[s][j + 1]);
                    }
                }
        }
    }      //courses are now sorted alphabetically/numerically for printing
    
    
}

void gradeAnalyzer::printCourse() //prints subjects
{

    if(true){
        for(int i = 0; i < subjectCount; i++) //used find total subjects
        {
            if(subjectStrArr[i].size() < 8)
                std::cout << subjectStrArr[i] << "\t\t" << subjectIntArr[i] << "\n";
            else
                std::cout << subjectStrArr[i] << "\t" << subjectIntArr[i] << "\n";

        }
        std::cout << "Subject" << "\t\t" << "Number of Courses\n\n";
        std::cout << "Total Subjects: " << subjectCount <<"\n\n"; //should be 134

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
            for(int j = 0; j < courseCountArr[i]; j++)
            {
                std::string name = gradeReferenceArray[i][j]->subject_id + "  " + gradeReferenceArray[i][j]->course_number;
                if(true){
                
                    if(name.size() < 8)
                        file << name << "\t\t\t" << courseIntArr[i][j] << "\n";
                    else if(name.size() < 12)
                        file << name << "\t\t" << courseIntArr[i][j] << "\n";
                    else
                        file << name << "\t" << courseIntArr[i][j] << "\n";
                }
                if(false){
                    if(name.size() < 8)
                        std::cout << name << "\t\t" << courseIntArr[i][j] << "\n";
                    else
                        std::cout << name << "\t" << courseIntArr[i][j] << "\n";
                }
                uniqueCourses++;
                totalCourses += courseIntArr[i][j]; 
                if(maxSizeCoursePerSubject < courseIntArr[i][j])
                    maxSizeCoursePerSubject = courseIntArr[i][j];
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
    bool subjectFound = false;
    for(int i = 0; i < subjectCount; i++)//used to num of classes per course and sorted by section
    {
        if(subjectStrArr[i] == SubjectID){
            subjectFound = true;
            for(int j = 0; j < courseCountArr[i]; j++)
            {
                std::string name = gradeReferenceArray[i][j]->subject_id + "  " + gradeReferenceArray[i][j]->course_number;
                
                if(name.size() < 8)
                    std::cout << name << "\t\t" << courseIntArr[i][j] << "\n";
                else
                    std::cout << name << "\t" << courseIntArr[i][j] << "\n";
                
                totalCourses++;
                totalSections += courseIntArr[i][j]; 
                if(maxSizeCoursePerSubject < courseIntArr[i][j])
                    maxSizeCoursePerSubject = courseIntArr[i][j];
            }
        }
    }
    if(subjectFound){
        std::cout << "Course" << "\t\t" << "Number of Sections\n\n";
        std::cout << "Max number of sections within a course listed: " << maxSizeCoursePerSubject << "\n"; 
        std::cout << "Total Courses: " << totalCourses << "\n";    
        std::cout << "Total number of Sections: " << totalSections << "\n\n";
    }
    else
        std::cout << "No courses found within Subject ID: " << SubjectID << "\n\n"; 
}
void gradeAnalyzer::printCourse(std::string SubjectID, std::string CourseNumber) //prints all sections within
{
    int totalSections = 0;
    bool subjectFound = false;
    bool courseFound = false;
    for(int i = 0; i < subjectCount; i++)//used to num of classes per course and sorted by section
    {
        if(subjectStrArr[i] == SubjectID){
            subjectFound = true;
            for(int j = 0; j < courseCountArr[i]; j++)
            {
                if(gradeReferenceArray[i][j]->course_number == CourseNumber)
                {
                    courseFound = true;
                    gradeReferenceArray[i][j]->print();
                }
            }
        }
    }
    if(subjectFound && courseFound) 
        std::cout << "Total number of Sections: " << totalSections << "\n\n";
    else if(subjectFound)
        std::cout << "Course: " << CourseNumber << " not found within Subject ID: " << SubjectID << "\n\n";
    else 
        std::cout << "No Subject ID or Course Number found.\n\n";
}









const int MAXLIST = 100; //can be edited for how many YOU want printed
const std::string CAREER = "UGRD"; 

//the flunkers
void gradeAnalyzer::findWeedOuts() //prints lowest overall
{
    
    std::array<double, MAXLIST> weedOutsPercent; //will hold lowest scores
    std::array<std::string, MAXLIST> weedOutsName; //will hold name correlating w/ lowest scores
    std::fill(weedOutsPercent.begin(), weedOutsPercent.end(), 1000); //sets weedouts to high number for comparisons
    
    int totalCounted = 0; //pervents calling to array with empty slots in case of MAXLIST being higher than valid scans
    
    for (int subject = 0; subject < MAX_SUBJECT; subject++)
    {
        int courseCount = courseCountArr[subject];
        if (courseCount == 0)
            continue;

        for (int course = 0; course < courseCount; course++) //scan through every course array
        {
            grade* g0 = gradeReferenceArray[subject][course];
            if (!g0)
                continue;
            if (g0->career != CAREER)
                continue;

            double denominator = 0; //grade count total
            double numerator = 0;  //total num of As,Bs,Cs
            std::string targetCourse = g0->course_number;


            for (int i = 0; i < courseCount; i++)
            {
                grade* g = gradeReferenceArray[subject][i];
                if (!g)
                    continue;

                // Only include sections of the SAME course number
                if (g->course_number != targetCourse)
                    continue;

                denominator += g->grades_count;
                numerator   += g->grades.A + g->grades.B + g->grades.C;
            }


            if (denominator == 0)
                continue;

            totalCounted++;

            double temp = (numerator * 100) / denominator;
            std::string strTemp = g0->subject_id + " " + g0->course_number;

            for(int i = 0; i < MAXLIST; i++)
            {   
                if(temp < weedOutsPercent[i]) //swap and carry
                    {
                        std::swap(temp, weedOutsPercent[i]);
                        std::swap(strTemp, weedOutsName[i]);
                    }   
            }   
        }    
    }
    for(int i = 0; i < MAXLIST && i < totalCounted; i++) //done time to print
    {
        
        if(weedOutsName[i].size() < 8)
                std::cout << weedOutsName[i] << "\t\t" << weedOutsPercent[i] << "%\n";
        else
            std::cout << weedOutsName[i] << "\t" << weedOutsPercent[i] << "%\n";
    }
    std::cout << "Course\t\tPassing Rate\n\n";
    
}

void gradeAnalyzer::findWeedOuts(std::string SubjectID) //prints lowest within subject
{
    
    
    std::array<double, MAXLIST> weedOutsPercent; //will hold lowest scores
    std::array<std::string, MAXLIST> weedOutsName; //will hold name correlating w/ lowest scores
    std::fill(weedOutsPercent.begin(), weedOutsPercent.end(), 1000); //sets weedouts to high number for comparisons
    
    int totalCounted = 0; //pervents calling to array with empty slots in case of MAXLIST being higher than valid scans
    
    for (int subject = 0; subject < MAX_SUBJECT; subject++)
    {
        int courseCount = courseCountArr[subject];
        if (courseCount == 0 || gradeReferenceArray[subject][0]->subject_id != SubjectID)
            continue;
        
        for (int course = 0; course < courseCount; course++) //scan through every course array
        {
            grade* g0 = gradeReferenceArray[subject][course];
            if (!g0)
                continue;
            if (g0->career != CAREER)
                continue;

            double denominator = 0; //grade count total
            double numerator = 0;  //total num of As,Bs,Cs
            std::string targetCourse = g0->course_number;


            for (int i = 0; i < courseCount; i++)
            {
                grade* g = gradeReferenceArray[subject][i];
                if (!g)
                    continue;

                // Only include sections of the SAME course number
                if (g->course_number != targetCourse)
                    continue;

                denominator += g->grades_count;
                numerator   += g->grades.A + g->grades.B + g->grades.C;
            }


            if (denominator == 0)
                continue;

            totalCounted++;

            double temp = (numerator * 100) / denominator;
            std::string strTemp = g0->subject_id + " " + g0->course_number;

            for(int i = 0; i < MAXLIST; i++)
            {   
                if(temp < weedOutsPercent[i]) //swap and carry
                    {
                        std::swap(temp, weedOutsPercent[i]);
                        std::swap(strTemp, weedOutsName[i]);
                    }   
            }   
        }    
    }
    for(int i = 0; i < MAXLIST && i < totalCounted; i++) //done time to print
    {
        
        if(weedOutsName[i].size() < 8)
                std::cout << weedOutsName[i] << "\t\t" << weedOutsPercent[i] << "%\n";
        else
            std::cout << weedOutsName[i] << "\t" << weedOutsPercent[i] << "%\n";
    }
    std::cout << "Course\t\tPassing Rate\n\n";
    
}
void gradeAnalyzer::findWeedOuts(std::string SubjectID, std::string CourseNumber)
{
    std::array<double, MAXLIST> weedOutsPercent;
    std::array<std::string, MAXLIST> weedOutsName;
    std::fill(weedOutsPercent.begin(), weedOutsPercent.end(), 1000);

    int totalCounted = 0;

    // Loop through all grades in the original array to find matching sections
    for (const grade& g : m_gradesArray)
    {
        if (g.subject_id != SubjectID)
            continue;

        if (g.course_number != CourseNumber)
            continue;

        if (g.career != CAREER)
            continue;

        // Compute pass rate for THIS section
        double numerator = g.grades.A + g.grades.B + g.grades.C;
        double denominator = g.grades_count;

        if (denominator == 0)
            continue;

        double passRate = (numerator * 100.0) / denominator;

        // Label: "001 2024 Fall"
        std::string label =
            g.section_number + " " +
            std::to_string(g.year) + " " +
            g.semester;

        totalCounted++;

        // Insert into sorted list
        for (int k = 0; k < MAXLIST; k++)
        {
            if (passRate < weedOutsPercent[k])
            {
                std::swap(passRate, weedOutsPercent[k]);
                std::swap(label, weedOutsName[k]);
            }
        }
    }

    // Print header
    std::cout << "Section\t\t" << "Passing Rate\n\n";

    // Print results
    for (int i = 0; i < MAXLIST && i < totalCounted; i++)
    {
        if (weedOutsName[i].size() < 8)
            std::cout << weedOutsName[i] << "\t\t" << weedOutsPercent[i] << "%\n";
        else
            std::cout << weedOutsName[i] << "\t" << weedOutsPercent[i] << "%\n";
    }

    std::cout << "\n";
}



//opposite of weedOuts
void gradeAnalyzer::findExemplary() //prints highest overall
{
    
    std::array<double, MAXLIST> weedOutsPercent; //will hold lowest scores
    std::array<std::string, MAXLIST> weedOutsName; //will hold name correlating w/ lowest scores
    std::fill(weedOutsPercent.begin(), weedOutsPercent.end(), -1); //sets weedouts to high number for comparisons
    
    int totalCounted = 0; //pervents calling to array with empty slots in case of MAXLIST being higher than valid scans
    
    for (int subject = 0; subject < MAX_SUBJECT; subject++)
    {
        int courseCount = courseCountArr[subject];
        if (courseCount == 0)
            continue;

        for (int course = 0; course < courseCount; course++) //scan through every course array
        {
            grade* g0 = gradeReferenceArray[subject][course];
            if (!g0)
                continue;
            if (g0->career != CAREER)
                continue;

            double denominator = 0; //grade count total
            double numerator = 0;  //total num of As,Bs,Cs
            std::string targetCourse = g0->course_number;


            for (int i = 0; i < courseCount; i++)
            {
                grade* g = gradeReferenceArray[subject][i];
                if (!g)
                    continue;

                // Only include sections of the SAME course number
                if (g->course_number != targetCourse)
                    continue;

                denominator += g->grades_count;
                numerator   += g->grades.A + g->grades.B + g->grades.C;
            }


            if (denominator == 0)
                continue;

            totalCounted++;

            double temp = (numerator * 100) / denominator;
            std::string strTemp = g0->subject_id + " " + g0->course_number;

            for(int i = 0; i < MAXLIST; i++)
            {   
                if(temp > weedOutsPercent[i]) //swap and carry
                    {
                        std::swap(temp, weedOutsPercent[i]);
                        std::swap(strTemp, weedOutsName[i]);
                    }   
            }   
        }    
    }
    for(int i = 0; i < MAXLIST && i < totalCounted; i++) //done time to print
    {
        
        if(weedOutsName[i].size() < 8)
                std::cout << weedOutsName[i] << "\t\t" << weedOutsPercent[i] << "%\n";
        else
            std::cout << weedOutsName[i] << "\t" << weedOutsPercent[i] << "%\n";
    }
    std::cout << "Course\t\tPassing Rate\n\n";
    
}
void gradeAnalyzer::findExemplary(std::string SubjectID) //prints highest within subject
{
    
    
    std::array<double, MAXLIST> weedOutsPercent; //will hold lowest scores
    std::array<std::string, MAXLIST> weedOutsName; //will hold name correlating w/ lowest scores
    std::fill(weedOutsPercent.begin(), weedOutsPercent.end(), -1); //sets weedouts to high number for comparisons
    
    int totalCounted = 0; //pervents calling to array with empty slots in case of MAXLIST being higher than valid scans
    
    for (int subject = 0; subject < MAX_SUBJECT; subject++)
    {
        int courseCount = courseCountArr[subject];
        if (courseCount == 0 || gradeReferenceArray[subject][0]->subject_id != SubjectID)
            continue;
        
        for (int course = 0; course < courseCount; course++) //scan through every course array
        {
            grade* g0 = gradeReferenceArray[subject][course];
            if (!g0)
                continue;
            if (g0->career != CAREER)
                continue;

            double denominator = 0; //grade count total
            double numerator = 0;  //total num of As,Bs,Cs
            std::string targetCourse = g0->course_number;


            for (int i = 0; i < courseCount; i++)
            {
                grade* g = gradeReferenceArray[subject][i];
                if (!g)
                    continue;

                // Only include sections of the SAME course number
                if (g->course_number != targetCourse)
                    continue;

                denominator += g->grades_count;
                numerator   += g->grades.A + g->grades.B + g->grades.C;
            }


            if (denominator == 0)
                continue;

            totalCounted++;

            double temp = (numerator * 100) / denominator;
            std::string strTemp = g0->subject_id + " " + g0->course_number;

            for(int i = 0; i < MAXLIST; i++)
            {   
                if(temp > weedOutsPercent[i]) //swap and carry
                    {
                        std::swap(temp, weedOutsPercent[i]);
                        std::swap(strTemp, weedOutsName[i]);
                    }   
            }   
        }    
    }
    for(int i = 0; i < MAXLIST && i < totalCounted; i++) //done time to print
    {
        
        if(weedOutsName[i].size() < 8)
                std::cout << weedOutsName[i] << "\t\t" << weedOutsPercent[i] << "%\n";
        else
            std::cout << weedOutsName[i] << "\t" << weedOutsPercent[i] << "%\n";
    }
    std::cout << "Course\t\tPassing Rate\n\n";
    
}
void gradeAnalyzer::findExemplary(std::string SubjectID, std::string CourseNumber)//prints highest within course 
{
    std::array<double, MAXLIST> exemplaryPercent;
    std::array<std::string, MAXLIST> exemplaryName;
    std::fill(exemplaryPercent.begin(), exemplaryPercent.end(), -1);

    int totalCounted = 0;

    // Loop through all grades in the original array to find matching sections
    for (const grade& g : m_gradesArray)
    {
        if (g.subject_id != SubjectID)
            continue;

        if (g.course_number != CourseNumber)
            continue;

        if (g.career != CAREER)
            continue;

        // Compute pass rate for THIS section
        double numerator = g.grades.A + g.grades.B + g.grades.C;
        double denominator = g.grades_count;

        if (denominator == 0)
            continue;

        double passRate = (numerator * 100.0) / denominator;

        // Label: "001 2024 Fall"
        std::string label =
            g.section_number + " " +
            std::to_string(g.year) + " " +
            g.semester;

        totalCounted++;

        // Insert into sorted list (highest first)
        for (int k = 0; k < MAXLIST; k++)
        {
            if (passRate > exemplaryPercent[k])
            {
                std::swap(passRate, exemplaryPercent[k]);
                std::swap(label, exemplaryName[k]);
            }
        }
    }

    // Print header
    std::cout << "Section\t\t" << "Passing Rate\n\n";

    // Print results
    for (int i = 0; i < MAXLIST && i < totalCounted; i++)
    {
        if (exemplaryName[i].size() < 8)
            std::cout << exemplaryName[i] << "\t\t" << exemplaryPercent[i] << "%\n";
        else
            std::cout << exemplaryName[i] << "\t" << exemplaryPercent[i] << "%\n";
    }

    std::cout << "\n";
}
