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
	void print();
	
	std::string subject_id;
	int course_number;
    std::string course_title;
	std::string section_number;
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
