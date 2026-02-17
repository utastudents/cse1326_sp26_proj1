// This class holds the grade date for one course.
struct grade
{
	grade();
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