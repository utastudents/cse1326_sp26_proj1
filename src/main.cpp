#include <iostream>
#include <string>
#include "grade.hpp"
#include "dataImporter.hpp"
#include "gradeAnalyzer.hpp"

// ulimit -s unlimited
// ^ here just incase
// probably have to use it for now until we get Prof Davis' diagnosis

std::array<grade, AllGradesArraySize> gradesArray;

int main(int argc, char* argv[])
{
	// create a dataImporter
	std::string filename = "allgradedata.json";
	dataImporter DI(filename);  // DI is Data Importer....
	DI.load(gradesArray); // Copys Data into array of grade

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
		// course command - search for a course
		else if(cmd == "course")
		{
			std::string subject;
			std::string number;
			std::cin >> subject >> number;

			bool found = false;
			// go through all the grades and find matching ones
			for(int i = 0; i < 10000; i++)
			{
				// stop if we hit empty records
				if(gradesArray[i].subject_id.empty())
					break;

				if(gradesArray[i].subject_id == subject && gradesArray[i].course_number == number)
				{
					gradesArray[i].print();
					std::cout << "-------------------" << std::endl;
					found = true;
				}
			}
			if(!found)
				std::cout << "No results found for " << subject << " " << number << std::endl;
		}
		// weedout command
		else if(cmd == "weedout")
		{
			gradeAnalyzer a(gradesArray);
		}
		// help command
		else if(cmd == "help")
		{
			std::cout << "Commands:" << std::endl;
			std::cout << "  course <SUBJECT> <NUMBER>  - search for a course (ex: course CSE 1320)" << std::endl;
			std::cout << "  weedout                    - show weedout statistics" << std::endl;
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
