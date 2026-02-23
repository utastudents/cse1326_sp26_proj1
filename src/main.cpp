#include <iostream>
#include <string>
#include "grade.hpp"
#include "dataImporter.hpp"
#include "weedout.hpp"


Grades GradesArray;
int main(int argc, char* argv[])
{

	//grade G{}; // this is just done so that the compiler
		   // will read it and check for errors.  it is
		   // not needed for anything else.

	// create a dataImporter
	std::string filename = "allgradedata.json";
	dataImporter DI(filename);  // DI is Data Importer....
			    
	// actually import the data into the array
	//grade AOG[100];                  // this needs to be in the grade header...
	//unsigned int maxSizeOfArray=100; // as does this
        //unsigned int num = DI.readFromFile(filename,arrayOfgrades,maxSizeofArray);	

	DI.load(GradesArray);

	// perhaps here we need to do some processing.  or maybe it is done
	// after each command???


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
			int number;
			std::cin >> subject >> number;

			bool found = false;
			// go through all the grades and find matching ones
			for(int i = 0; i < 10000; i++)
			{
				// stop if we hit empty records
				if(GradesArray[i].subject_id.empty())
					break;

				if(GradesArray[i].subject_id == subject && GradesArray[i].course_number == number)
				{
					GradesArray[i].print();
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
			printWeedoutStatistics(GradesArray);
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
