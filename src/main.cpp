#include "grade.hpp"
#include "dataImporter.hpp"
#include "gradeAnalyzer.hpp"

#include <iostream>
#include <string>

// ulimit -s unlimited
// ^ here just incase

std::array<grade, AllGradesArraySize> gradesArray;


int main(int argc, char* argv[])
{
	// create a dataImporter
	std::string filename = "allgradedata.json";
	dataImporter DI(filename);  // DI is Data Importer....
	DI.load(gradesArray); // Copys Data into array of grade
	gradeAnalyzer analyzer(gradesArray);
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

	// clean up
	return 0;
}
