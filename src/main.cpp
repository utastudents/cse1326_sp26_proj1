#include "grade.hpp"
#include "dataImporter.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

std::vector<grade> gradesVect;

int main(int argc, char* argv[])
{
        // create a dataImporter
        std::string filename = "allgradedata.json";
        dataImporter DI(filename);  // DI is Data Importer....
        DI.load(gradesVect); // Copys Data into array of grade
        std::cout << gradesVect.size() << " records read." << std::endl;


        std::set<std::string> subjects;
        std::set<std::string> instructors;
	std::set<std::string> subjects_plus_course_number;
	// put them in a set, to get all the possibilities
        for (const auto& r : gradesVect) 
        {
		instructors.insert(r.instructor1);
		subjects.insert(r.subject_id);
		subjects_plus_course_number.insert(r.subject_id+r.course_number);
	}
#if 0
        std::cout << "the number of subjects is " << subjects.size() << std::endl;

        for (const auto& i : subjects_plus_course_number ) 
	{
                std::cout << i << " " << std::endl;
        }
#endif
        std::vector<grade> filteredResults;
        for (const auto& r : gradesVect) 
        {
           if ((r.subject_id == "CSE") && (r.course_number == "3310")) 
           { 
               filteredResults.push_back(r);
           }
        }

	// want to sort based on pass percentage
        std::sort(filteredResults.begin(), filteredResults.end(), [](const grade& a, const grade& b) {
                                                   return float(a.grades.A+a.grades.B+a.grades.C) / a.grades_count < float(b.grades.A+b.grades.B+b.grades.C) / b.grades_count;});
	// A,B,C,D,F,I,P,Q,W,Z,R;
        std::cout << "found " << filteredResults.size() << " matches" << std::endl;
        for (auto &i : filteredResults)
        {
           std::cout << i.subject_id << i.course_number << '\t' << i.course_title;
           std::cout << i.semester << '\t'  << i.year << '\t' << i.instructor1.substr(0,15) << '\t';
	   std::cout << '\t' << i.grades_count ;
	   std::cout << std::fixed << std::setprecision(4);
	   std::cout << '\t' << float(i.grades.A+i.grades.B+i.grades.C) / i.grades_count << '%';
           std::cout << '\t' << float(i.grades.A) / i.grades_count;
           std::cout << '\t' << float(i.grades.B) / i.grades_count;
           std::cout << '\t' << float(i.grades.C) / i.grades_count;
           std::cout << '\t' << float(i.grades.D) / i.grades_count;
           std::cout << '\t' << float(i.grades.F) / i.grades_count;
           std::cout << std::endl;
           //i.print();
        }

#if 0	
	gradeAnalyzer analyzer(gradesArray);
	simple_find(gradesArray, 1973);
	// command processor
	std::cout << "Welcome to the command line MavGrades" << std::endl;
	std::string cmd;
	// keep looping until user wants to quit
	while(true)
	{
		std::cout << "> ";
		std::cin >> cmd;

		// check if user wants to exit
		if(cmd == "quit" || cmd == "exit")
		{
			break;
		}
		// course command - search for a course // weedout command
	else if (cmd == "course" || cmd == "weedout" || cmd == "superior")
	{
		std::string subjectID;
		std::string courseNumber;

		// Try to read the next token, but only if it isn't another command
		if (std::cin.peek() != '\n')
			std::cin >> subjectID;

		if (std::cin.peek() != '\n')
			std::cin >> courseNumber;

		if (cmd == "course")
		{
			if (!subjectID.empty() && !courseNumber.empty())
				analyzer.printCourse(subjectID, courseNumber);
			else if (!subjectID.empty())
				analyzer.printCourse(subjectID);
			else
				analyzer.printCourse();
		}
		else if(cmd == "weedout") // weedout
		{
			if (!subjectID.empty() && !courseNumber.empty())
				analyzer.findPercents(subjectID, courseNumber, 1);
			else if (!subjectID.empty())
				analyzer.findPercents(subjectID, 1);
			else
				analyzer.findPercents(1);
		}
		else{
			if (!subjectID.empty() && !courseNumber.empty())
				analyzer.findPercents(subjectID, courseNumber, 0);
			else if (!subjectID.empty())
				analyzer.findPercents(subjectID, 0);
			else
				analyzer.findPercents(0);
		}
	}

		// help command
		else if(cmd == "help")
		{
			std::cout << "Commands:" << std::endl;
			std::cout << "  course <SUBJECT> <NUMBER>  - search for a section  (ex: course CSE 1320)" << std::endl;
			std::cout << "  weedout                    - show weedout statistics" << std::endl;
			std::cout << "  superior				   - show exemplary statistics" << std::endl;
			std::cout << "  help                       - show this help message" << std::endl;
			std::cout << "  quit                       - exit the program" << std::endl;
		}
		else
		{
			std::cout << "Unknown command. Type 'help' for a list of commands." << std::endl;
		}
	}
#endif
	// clean up
	return 0;
}
