#include "mainwindow.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <glibmm.h>

MainWindow::MainWindow() : m_VBox(Gtk::Orientation::VERTICAL),
                           m_Button_Quit("_Quit", true),
                           m_Button_Buffer1("Use buffer 1"),
                           m_Button_Buffer2("Use buffer 2"),
                           m_year_search_valid{false},
                           m_subject_search_valid{false},
                           m_instructor_search_valid{false}

{
    std::cout << "Opening the mavgrades file" << std::endl;
    // create a dataImporter
    std::string filename = "allgradedata.json";
    dataImporter DI(filename); // DI is Data Importer....
    DI.load(m_gradesVect);     // Copys Data into array of grade
    std::cout << m_gradesVect.size() << " records read." << std::endl;
    // the file is not going to be needed anymore

    // in the begining, the filtered file (in a vector)should be
    // the same as the original file (in a vector).  make it so.
    m_gradesVectFiltered = m_gradesVect;

    // figure out (and set) the contents of the drop downs
    BuildDropDowns(m_gradesVect);

    // set the labels

    m_original.set_text("  ");
    m_filtered.set_text("  ");

    // window
    set_default_size(200, 450);
    ////////////////////////
    set_title("Gtk::TextView example");
    set_default_size(400, 200);

    m_VBox.set_margin(5);
    set_child(m_VBox);

    // Add the TreeView, inside a ScrolledWindow, with the button underneath:
    m_ScrolledWindow.set_child(m_TextView);

    // Only show the scrollbars when they are necessary:
    m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindow.set_expand();

    m_VBox.append(m_DropDownBox);
    m_VBox.append(m_ScrolledWindow);
    m_VBox.append(m_ButtonBox);

    m_DropDownBox.append(m_YearDropDown);
    m_DropDownBox.append(m_SubjectDropDown);
    m_DropDownBox.append(m_CourseDropDown);
    m_DropDownBox.append(m_InstructorDropDown);

    m_Button_Buffer1.set_hexpand(true);
    m_Button_Buffer1.set_halign(Gtk::Align::END);

    m_ButtonBox.append(m_Button_Buffer1);
    m_ButtonBox.append(m_Button_Buffer2);
    m_ButtonBox.append(m_Button_Quit);
    m_ButtonBox.set_margin(5);
    m_ButtonBox.set_spacing(5);

     Filter();

    // Connect signal handler(s):

    m_YearDropDown.property_selected().signal_changed().connect(
        [this]()
        {
            const auto selected = m_YearDropDown.get_selected();
            std::cout << "DropDown changed: Row=" << selected << ", String="
                      << m_yearStringList->get_string(selected) << std::endl;
            m_year_search_valid = true;
            m_year_search_key = std::stoi(m_yearStringList->get_string(selected));
            std::cout << "year valid = " << m_year_search_valid << " year search key = " << m_year_search_key << std::endl;

            Filter();
        });

    m_SubjectDropDown.property_selected().signal_changed().connect(
        [this]()
        {
            const auto selected = m_SubjectDropDown.get_selected();
            std::cout << "DropDown changed: Row=" << selected << ", String="
                      << m_subjectStringList->get_string(selected) << std::endl;
            m_subject_search_valid = true;
            m_subject_search_key = m_subjectStringList->get_string(selected);
            std::cout << "subject valid = " << m_subject_search_valid << " subject search key = " << m_subject_search_key << std::endl;

            Filter();
        });
         m_InstructorDropDown.property_selected().signal_changed().connect(
        [this]()
        {
            const auto selected = m_InstructorDropDown.get_selected();
            std::cout << "DropDown changed: Row=" << selected << ", String="
                      << m_instructorStringList->get_string(selected) << std::endl;
            m_instructor_search_valid = true;
            m_instructor_search_key = m_subjectStringList->get_string(selected);
            std::cout << "instructor valid = " << m_instructor_search_valid << " instructor search key = " << m_instructor_search_key << std::endl;

            Filter();
        });
    /// Gtk::DropDown m_CourseDropDown;
    // Gtk::DropDown m_InstructorDropDown;
    // Gtk::DropDown m_YearDropDown;
    // Gtk::DropDown m_SubjectDropDown;
}

void MainWindow::LoadText(std::vector<grade> &v)
{
    std::stringstream S;

    for (auto &i : m_gradesVectFiltered)
    {
        S << std::setw(5) << i.subject_id << "\t" << i.course_number << '\t' << i.course_title;
        S << i.semester << '\t' << std::to_string(i.year)<< '\t' << i.instructor1.substr(0, 15) << '\t';
        S << '\t' << i.grades_count;
        S << std::fixed << std::setprecision(4);
        S << '\t' << float(i.grades.A + i.grades.B + i.grades.C) / i.grades_count << '%';
        S << '\t' << float(i.grades.A) / i.grades_count;
        S << '\t' << float(i.grades.B) / i.grades_count;
        S << '\t' << float(i.grades.C) / i.grades_count;
        S << '\t' << float(i.grades.D) / i.grades_count;
        S << '\t' << float(i.grades.F) / i.grades_count;
        S << std::endl;
    }
    m_refTextBuffer1 = Gtk::TextBuffer::create();
    m_refTextBuffer1->set_text(S.str());
    m_TextView.set_buffer(m_refTextBuffer1);
}
MainWindow::~MainWindow()
{
}

bool MainWindow::Filter()
{
    std::cout << "filter started. " << std::endl;
    // this method will filter m_gradesVect into m_gradesVectFiltered
    //  required order
    //       first year
    //       then subj
    //       then course
    //       then instructor

    m_gradesVectFiltered.clear();
    for (const auto &r : m_gradesVect)
    {
        if (
            ((!m_year_search_valid) || r.year == m_year_search_key) &&
            ((!m_subject_search_valid) || r.subject_id == m_subject_search_key) &&
            ((!m_instructor_search_valid) || r.instructor1 == m_instructor_search_key))
        // if (   (r.subject_id == "CSE") && (r.course_number == "3310"))
        {
            m_gradesVectFiltered.push_back(r);
        }
    }
    std::cout << "the number in the filtered list is " << m_gradesVectFiltered.size() << std::endl;
    LoadText(m_gradesVectFiltered);
#if 0

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
           
        }
#endif
    std::cout << "filter done." << std::endl;
    return false;
}

void MainWindow::BuildDropDowns(std::vector<grade> &v)
{
    std::set<int> years;
    std::set<std::string> subjects;
    std::set<std::string> instructors;
    std::set<std::string> subjects_plus_course_number;
    // put them in a set, to get all the possibilities
    for (const auto &r : v)
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
        yearStrings.push_back(std::to_string(i));
    }

    std::vector<Glib::ustring> instructorStrings;
    for (const auto &i : instructors)
    {
        instructorStrings.push_back(i);
    }

    std::vector<Glib::ustring> subjectStrings;
    for (const auto &i : subjects)
    {
        subjectStrings.push_back(i);
    }

    m_courseStringList = Gtk::StringList::create(strings);
    m_CourseDropDown.set_model(m_courseStringList);
    m_CourseDropDown.set_selected(0);

    m_yearStringList = Gtk::StringList::create(yearStrings);
    m_YearDropDown.set_model(m_yearStringList);
    m_YearDropDown.set_selected(0);

    m_instructorStringList = Gtk::StringList::create(instructorStrings);
    m_InstructorDropDown.set_model(m_instructorStringList);
    m_InstructorDropDown.set_selected(0);

    m_subjectStringList = Gtk::StringList::create(subjectStrings);
    m_SubjectDropDown.set_model(m_subjectStringList);
    m_SubjectDropDown.set_selected(0);
}

int count = 0;
#if 0
void MainWindow::on_dropdown_changed()
{
    count++;
    const auto selected = m_CourseDropDown.get_selected();
    std::cout << "DropDown changed: Row=" << selected << ", String="
              << m_courseStringList->get_string(selected) << std::endl;
    // Filter();
    // m_CourseDropDown.set_selected(GTK_INVALID_LIST_POSITION);
    Glib::signal_idle().connect(sigc::mem_fun(*this, &MainWindow::Filter));
    std::cout << "leaving the signal handler " << count << std::endl;
    return;
}
#endif
