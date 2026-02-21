#include "grade.hpp"

int grade::NumOfGradeDatas = 0;

grade::grade()
{	
	NumOfGradeDatas++;
	// this is a highly sophisticated constructor
}

void grade::print()
{
	std::cout 	<< "Subject ID: " << subject_id
				<< "\nCourse number: " << course_number
				<< "\nCourse title: " << course_title
				<< "\nSection number: " << section_number
				<< "\nGrades:"
				<< "\nA: " << grades.A
				<< "\nB: " << grades.B
				<< "\nC: " << grades.C
				<< "\nD: " << grades.D
				<< "\nF: " << grades.F
				<< "\nI: " << grades.I
				<< "\nP: " << grades.P
				<< "\nQ: " << grades.Q
				<< "\nW: " << grades.W
				<< "\nZ: " << grades.Z
				<< "\nR: " << grades.R
				<< "\nGrades count: " << grades_count
				<< "\nYear: " << year
				<< "\nSemester: " << semester
				<< "\nCareer: " << career
				<< "\nInstructor 1: " << instructor1
				<< "\nInstructor 2: " << instructor2
				<< "\nInstructor 3: " << instructor3
				<< "\nInstructor 4: " << instructor4
				<< "\nInstructor 5: " << instructor5
				<< "\nCourse GPA: " << course_gpa
				<< "\nDrop Percent: " << drop_percent << std::endl;
	return;
}
