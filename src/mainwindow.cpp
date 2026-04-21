#include "mainwindow.hpp"
#include <iostream>

MainWindow::MainWindow()
{
    std::cout << "Opening the mavgrades file" << std::endl;
    // create a dataImporter
    std::string filename = "allgradedata.json";
    dataImporter DI(filename);  // DI is Data Importer....
    DI.load(m_gradesVect); // Copys Data into array of grade
    std::cout << m_gradesVect.size() << " records read." << std::endl;
    // the file is not going to be needed anymore

    // calculate totals for original file.
    m_origFileTotals = CalculateTotals(m_gradesVect);

    // in the begining, the filtered file (in a vector)should be
    // the same as the original file (in a vector).  make it so.
    m_gradesVectFiltered = m_gradesVect;
    m_filteredFileTotals = CalculateTotals(m_gradesVectFiltered);

    // set the labels
    SetFileTotals(m_origFileTotals);
    SetFilteredTotals(m_filteredFileTotals);

    m_original.set_text("original #");
    m_filtered.set_text("filtered #");

    // window 
    set_default_size(200, 450);

    m_grid.set_halign(Gtk::Align::START);
    m_grid.set_valign(Gtk::Align::START);
    m_grid.set_hexpand(true);
    m_grid.set_vexpand(true);

    set_child(m_grid);
    m_grid.attach(m_original, 0, 0);
    m_grid.attach(m_FileYearTotalsLabel, 1, 0);
    m_grid.attach(m_FileSubjectTotalsLabel, 2, 0);
    m_grid.attach(m_FileCourseTotalsLabel, 3, 0);
    m_grid.attach(m_FileInstructorTotalsLabel, 4, 0);
    m_grid.attach(m_YearDropDown, 1, 1);
    m_grid.attach(m_SubjectDropDown, 2, 1);
    m_grid.attach(m_CourseDropDown, 3, 1);
    m_grid.attach(m_InstructorDropDown, 4, 1);
    m_grid.attach(m_filtered, 0, 2);
    m_grid.attach(m_YearTotalsLabel, 1, 2);
    m_grid.attach(m_SubjectTotalsLabel, 2, 2);
    m_grid.attach(m_CourseTotalsLabel, 3, 2);
    m_grid.attach(m_InstructorTotalsLabel, 4, 2);


    // Connect signal handler:
 m_conobj1 = m_CourseDropDown.property_selected().signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));

 //m_conobj2 = m_YearDropDown.property_selected().signal_changed().connect(
 //           sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));

 //m_conobj3 = m_InstructorDropDown.property_selected().signal_changed().connect(
 //           sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));

 //m_conobj4 = m_SubjectDropDown.property_selected().signal_changed().connect(
 //           sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));
}

MainWindow::~MainWindow()
{
}

void MainWindow::Filter()
{
    // this method will filter m_gradesVect into m_gradesVectFiltered
    //  required order
    //       first year
    //       then subj
    //       then course
    //       then instructor
    m_gradesVectFiltered.clear();
    for (const auto &r : m_gradesVect)
    {
        if ((r.subject_id == "CSE") && (r.course_number == "3310"))
        {
            m_gradesVectFiltered.push_back(r);
        }
    }
    std::cout << "the number in the filtered list is " << m_gradesVectFiltered.size() << std::endl;


          for (auto &i :m_gradesVectFiltered )
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

    m_filteredFileTotals = CalculateTotals(m_gradesVectFiltered);
    std::cout << "after calculate totals " << std::endl;
    std::cout << "filtered file totals "; 
    for (auto i:m_filteredFileTotals)
	    std::cout << i << " ";
    std::cout << std::endl;
    SetFilteredTotals(m_filteredFileTotals);
}

totalVec  MainWindow::CalculateTotals(std::vector<grade> v)
{
    std::set<int> years;
    std::set < std::string > subjects;
    std::set < std::string > instructors;
    std::set < std::string > subjects_plus_course_number;
    // put them in a set, to get all the possibilities
    for (const auto &r : v)
    {
        years.insert(r.year);
        instructors.insert(r.instructor1);
        subjects.insert(r.subject_id);
        subjects_plus_course_number.insert(r.subject_id + r.course_number);
    }

    // convert from a set to a vector of Glib::ustring
    std::vector < Glib::ustring > strings;
    for (const auto &i : subjects_plus_course_number)
    {
        strings.push_back(i);
    }

    std::vector < Glib::ustring > yearStrings;
    for (const auto &i : years)
    {
        yearStrings.push_back(std::to_string(i));
    }

    std::vector < Glib::ustring > instructorStrings;
    for (const auto &i : instructors)
    {
        instructorStrings.push_back(i);
    }

    std::vector < Glib::ustring > subjectStrings;
    for (const auto &i : subjects)
    {
        subjectStrings.push_back(i);
    }

    m_conobj1.block();
    // this is a problem
    //if (m_courseStringList==nullptr)
    {
       //m_courseStringList->splice(0, m_courseStringList->get_n_items(), {});
       m_courseStringList=nullptr;
       m_courseStringList = Gtk::StringList::create(strings);
       m_CourseDropDown.set_model(m_courseStringList);
       m_CourseDropDown.set_selected(0);
    }
    m_conobj1.unblock();
#if 0
    if (m_yearStringList)
         m_yearStringList->splice(0, m_yearStringList->get_n_items(), {});
    m_yearStringList = Gtk::StringList::create(yearStrings);
    m_YearDropDown.set_model(m_yearStringList);
    m_YearDropDown.set_selected(0);

    if (m_instructorStringList)
        m_instructorStringList->splice(0, m_instructorStringList->get_n_items(), {});
    m_instructorStringList = Gtk::StringList::create(instructorStrings);
    m_InstructorDropDown.set_model(m_instructorStringList);
    m_InstructorDropDown.set_selected(0);

    if (m_subjectStringList)
     m_subjectStringList->splice(0, m_subjectStringList->get_n_items(), {});
    m_subjectStringList = Gtk::StringList::create(subjectStrings);
    m_SubjectDropDown.set_model(m_subjectStringList);
    m_SubjectDropDown.set_selected(0);
#endif

    std::vector<int> t;
    t.push_back(years.size());
    t.push_back(subjects.size());
    t.push_back(instructors.size());
    t.push_back(subjects_plus_course_number.size());
    return t;
}

void MainWindow::SetFileTotals(totalVec v)
{
    m_FileYearTotalsLabel.set_text(std::to_string(v[0]));
    m_FileSubjectTotalsLabel.set_text(std::to_string(v[1]));
    m_FileInstructorTotalsLabel.set_text(std::to_string(v[2]));
    m_FileCourseTotalsLabel.set_text(std::to_string(v[3]));

}

void MainWindow::SetFilteredTotals(totalVec v)
{
	std::cout << "setting labels " <<  std::to_string(v[3]) <<  std::endl;
    m_YearTotalsLabel.set_text(std::to_string(v[0]));
    m_SubjectTotalsLabel.set_text(std::to_string(v[1]));
    m_InstructorTotalsLabel.set_text(std::to_string(v[2]));
    m_CourseTotalsLabel.set_text(std::to_string(v[3]));
}

void MainWindow::Select()
{

}

int count=0;
void MainWindow::on_dropdown_changed()
{
	count++;
    //const auto selected = m_CourseDropDown.get_selected();
    //std::cout << "DropDown changed: Row=" << selected << ", String="
    //        << m_courseStringList->get_string(selected) << std::endl;
    Filter();
    std::cout << "leaving the signal handler " << count << std::endl;
    return; 
}
