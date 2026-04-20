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

    // the file is not going to be needed anymore
    std::set<int> years;
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

    // window 
    set_default_size(200, 400);

    m_YearTotalsLabel = Gtk::Label(std::to_string(years.size()));
    m_SubjectTotalsLabel = Gtk::Label(std::to_string(subjects.size()));
    m_InstructorTotalsLabel = Gtk::Label(std::to_string(instructors.size()));
    m_CourseTotalsLabel = Gtk::Label(
            std::to_string(subjects_plus_course_number.size()));

    m_grid.set_halign(Gtk::Align::START);
    m_grid.set_valign(Gtk::Align::START);
    m_grid.set_hexpand(true);
    m_grid.set_vexpand(true);

    set_child(m_grid);
    m_grid.attach(m_YearTotalsLabel, 0, 0);
    m_grid.attach(m_SubjectTotalsLabel, 1, 0);
    m_grid.attach(m_CourseTotalsLabel, 2, 0);
    m_grid.attach(m_InstructorTotalsLabel, 3, 0);
    m_grid.attach(m_YearDropDown, 0, 1);
    m_grid.attach(m_SubjectDropDown, 1, 1);
    m_grid.attach(m_CourseDropDown, 2, 1);
    m_grid.attach(m_InstructorDropDown, 3, 1);

    //m_YearTotalsLabel = Gtk::Label(std::to_string(years.size()));

    m_courseStringList = Gtk::StringList::create(strings);
    m_CourseDropDown.set_model(m_courseStringList);
    m_CourseDropDown.set_selected(0);

    // Connect signal handler:
    m_CourseDropDown.property_selected().signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));

    m_yearStringList = Gtk::StringList::create(yearStrings);

    m_YearDropDown.set_model(m_yearStringList);
    m_YearDropDown.set_selected(0);
    m_YearDropDown.property_selected().signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));

    m_instructorStringList = Gtk::StringList::create(instructorStrings);

    m_InstructorDropDown.set_model(m_instructorStringList);
    m_InstructorDropDown.set_selected(0);
    m_InstructorDropDown.property_selected().signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));

    m_subjectStringList = Gtk::StringList::create(subjectStrings);

    m_SubjectDropDown.set_model(m_subjectStringList);
    m_SubjectDropDown.set_selected(0);
    m_SubjectDropDown.property_selected().signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_dropdown_changed));
#if 0
       // 1. Create a ScrolledWindow to handle long text
        m_scrolled_window.set_child(m_text_view);
        m_scrolled_window.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        m_scrolled_window.set_expand();

        // 2. Access the TextBuffer to set initial content
        auto buffer = m_text_view.get_buffer();
        buffer->set_text("Hello, this is a GTK4 TextView in C++!");

        // 3. Set properties like wrapping
        //m_text_view.set_wrap_mode(Gtk::WrapMode::WORD);
        m_grid.attach(m_text_view,0,2);
#endif
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
    for (const auto &r : m_gradesVect)
    {
        if ((r.subject_id == "CSE") && (r.course_number == "3310"))
        {
            m_gradesVectFiltered.push_back(r);
        }
    }

}

std::vector<int> CalculateTotals(std::vector<grade> v)
{
	std::vector<int> t;
	return t;
}

void MainWindow::Select()
{
}

void MainWindow::on_dropdown_changed()
{
	static int x=0;
	x++;
    m_YearTotalsLabel.set_text(std::to_string(x));
    std::cout << "the label value is " << std::to_string(x) << std::endl;
    const auto selected = m_CourseDropDown.get_selected();
    std::cout << "DropDown changed: Row=" << selected << ", String="
            << m_courseStringList->get_string(selected) << std::endl;
}
