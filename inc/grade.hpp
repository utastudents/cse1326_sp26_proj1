// This class holds the grade date for one course.
#pragma once

#include <string>
#include <iostream>

struct GradeCounts
{
	int A,B,C,D,F,I,P,Q,W,Z,R;
};

struct grade
{
	static int NumOfGradeDatas;
	
	grade();
	grade(bool NEW);
	~grade();
	
	void print();
	
	std::string subject_id;
	std::string course_number; //changed to string
    std::string course_title;
	std::string section_number;
	std::string subCor;
	std::string subCorSec; //got tired of typing the whole thing 
	std::string subCorSecTermYear;
	GradeCounts grades;
	int grades_count;
	int year;
	std::string semester;
	std::string career;
	std::string instructor1;
	std::string instructor2;
	std::string instructor3;
	std::string instructor4;
	std::string instructor5;
	double course_gpa;
	double drop_percent;
};

// Scoped Enumeration that could be used to discern the indecies in
// the grades array?? 
enum class LetterGrade {A, B, C, D, F, I, P, Q, W, Z, R};
enum class Semester {FALL, WINTER, SPRING, SUMMER};

// Created a rough outline for the class to hold data, probably incorrect - [Noah Chiarelli - February 17th 9:54AM]
class baseClass{

	char* subjectID;
	int courseNumber;
	char* courseTitle;
	int sectionNumber;
	int grades[11]; // Index 0 = # of A's index 1 = # of B's etc...
	
	int gradesCount;
	int year;

	// Maybe have linked list of instructors??

	float courseGPA; // Include method to calculate GPA? Unless it's already included in JSON
	float drop_percent; 

};