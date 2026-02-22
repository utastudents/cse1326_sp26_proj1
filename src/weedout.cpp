#include <iostream>
#include <string>
#include "weedout.hpp"
#include <map>
#include <iomanip>

//tracking student stats
struct Student_stat {
	int student_total{0};
	int student_success{0};
};

void printWeedoutStatistics(const std::array <grade, MAX_DATA_RECORDS> &Grades) {

	//create a map to group section.[Has a key we use to access the elements instead of integers for indicies in array, also sorts itself]
	std::map<std::string, Student_stat> groupedCourses;

	//loop through Grades up to the 
	for(size_t i = 0; i < MAX_DATA_RECORDS; i++){
		const grade &g = Grades[i];

		// Stop processing once we hit empty uninitialized array slots
		if(g.subject_id.empty()){
			break;
		}

		//only stop when u see CSE class
		if(g.subject_id != "CSE"){
			continue;
		}

		//now create key: format of "YEAR_CSE CourseNumber" :: 2024 CSE 1320 
		std::string key = std::to_string(g.year) + " CSE " + std::to_string(g.course_number);

		// Calculate total participants and successful students for this section
		int success = g.grades.A + g.grades.B + g.grades.C;	//students that passed
		int total = g.grades.A + g.grades.B + g.grades.C + g.grades.D + g.grades.F + 
					g.grades.I + g.grades.P + g.grades.Q + g.grades.W + g.grades.Z + g.grades.R;

		// Add to running totals in the Map does this for each it has counted
		if (total > 0) { // Safety check against empty data, if >= 0 , we will be dividing by 0
			groupedCourses[key].student_total += total;
			groupedCourses[key].student_success += success;
		}
	}

	std::cout << "========================================" << std::endl;
	std::cout << "   CSE WEED-OUT CLASS STATISTICS        " << std::endl;
	std::cout << "========================================" << std::endl;
	
	// 4. Print the grouped data
	for (const auto& pair : groupedCourses) {
		const std::string& courseName = pair.first;
		const Student_stat& stats = pair.second;
		int weedout_students = stats.student_total - stats.student_success;	//total number of weedout students in that year for all profs
		double weedout_percentage = 0.0;
		
		if (stats.student_total > 0) {
			weedout_percentage = (static_cast<double>(weedout_students) / stats.student_total) * 100.0;
		}
		
		std::cout << courseName << " -> " << std::fixed << std::setprecision(2) << weedout_percentage << "%" << std::endl;
	}
}
