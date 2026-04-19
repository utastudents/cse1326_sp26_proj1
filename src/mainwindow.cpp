#include "mainwindow.hpp"
#include <iostream>

MainWindow::MainWindow()
{
    set_title("DropDown example");
    std::cout << "Opening the mavgrades file" << std::endl;
    // create a dataImporter
    std::string filename = "allgradedata.json";
    dataImporter DI(filename);  // DI is Data Importer....
    DI.load(m_gradesVect); // Copys Data into array of grade
    std::cout << m_gradesVect.size() << " records read." << std::endl;

    std::set < int > years;
    std::set < std::string > subjects;
    std::set < std::string > instructors;
    std::set < std::string > subjects_plus_course_number;
    // put them in a set, to get all the possibilities
    for (const auto &r : m_gradesVect)
    {
	years.insert(r.year);
        instructors.insert(r.instructor1);
        subjects.insert(r.subject_id);
        subjects_plus_course_number.insert(r.subject_id + r.course_number);
    }

    // convert from a set to a vector of Glib::ustring
    std::vector<Glib::ustring> strings;
    for (const auto &i : subjects_plus_course_number)
    {
	    strings.push_back(i);
    }

    std::vector<Glib::ustring> yearStrings;
    for (const auto &i : years)
    {
	    yearStrings.push_back( std::to_string(i) );  
    }

    std::vector<Glib::ustring> instructorStrings;
    for (const auto &i : instructors)
    {
	    instructorStrings.push_back( i );  
    }

    std::vector<Glib::ustring> subjectStrings;
    for (const auto &i : subjects)
    {
	    subjectStrings.push_back( i );  
    }


    // window 
    set_default_size(200, 400);
    set_child(m_box);
    m_box.append(m_CourseDropDown);

    //Gtk::Label m_YearTotalsLabel;
    //Gtk::Label m_SubjectTotalsLabel;
    //Gtk::Label m_CourseTotalsLabel;
    //Gtk::Label m_InstructorTotalsLabel;

    Gtk::Label m_YearTotalsLabel = Gtk::Label(std::to_string(years.size()));
    m_box.append(m_YearTotalsLabel);

    m_courseStringList = Gtk::StringList::create(strings);
    m_CourseDropDown.set_model(m_courseStringList);
    m_CourseDropDown.set_selected(0);

    // Connect signal handler:
    m_CourseDropDown.property_selected().signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));

    m_box.append(m_YearDropDown);
    m_yearStringList = Gtk::StringList::create(yearStrings);

    m_YearDropDown.set_model(m_yearStringList);
    m_YearDropDown.set_selected(0);
    m_YearDropDown.property_selected().signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));

    m_box.append(m_InstructorDropDown);
    m_instructorStringList = Gtk::StringList::create(instructorStrings);

    m_InstructorDropDown.set_model(m_instructorStringList);
    m_InstructorDropDown.set_selected(0);
    m_InstructorDropDown.property_selected().signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));

    m_box.append(m_SubjectDropDown);
    m_subjectStringList = Gtk::StringList::create(subjectStrings);

    m_SubjectDropDown.set_model(m_subjectStringList);
    m_SubjectDropDown.set_selected(0);
    m_SubjectDropDown.property_selected().signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));
}

MainWindow::~MainWindow()
{
}

void MainWindow::Select()
{
}

void MainWindow::on_dropdown_changed()
{
    const auto selected = m_CourseDropDown.get_selected();
    std::cout << "DropDown changed: Row=" << selected << ", String="
            << m_courseStringList->get_string(selected) << std::endl;
}
