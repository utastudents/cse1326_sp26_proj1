#pragma once

#include "grade.hpp"
#include "dataImporter.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

#include <gtkmm.h>

class MainWindow : public Gtk::Window
{
public:
    MainWindow();
    ~MainWindow() override;

protected:
    Gtk::Box m_VBox;
    Gtk::Box m_DropDownBox;

    Gtk::Box m_ButtonBox;
    Gtk::Button m_Button_Quit, m_Button_Buffer1, m_Button_Buffer2;

    Gtk::Box m_main_box;
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::TextView m_TextView;

    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer1, m_refTextBuffer2;

    // Child widgets:
    Gtk::Label m_YearTotalsLabel;
    Gtk::Label m_SubjectTotalsLabel;
    Gtk::Label m_CourseTotalsLabel;
    Gtk::Label m_InstructorTotalsLabel;

    Gtk::Label m_FileYearTotalsLabel;
    Gtk::Label m_FileSubjectTotalsLabel;
    Gtk::Label m_FileCourseTotalsLabel;
    Gtk::Label m_FileInstructorTotalsLabel;

    Gtk::Label m_original;
    Gtk::Label m_filtered;

    Gtk::DropDown m_CourseDropDown;
    Gtk::DropDown m_InstructorDropDown;
    Gtk::DropDown m_YearDropDown;
    Gtk::DropDown m_SubjectDropDown;

    bool m_year_search_valid;
    bool m_subject_search_valid;
    bool m_instructor_search_valid;
    int m_year_search_key;
    std::string m_subject_search_key;
    std::string m_instructor_search_key;

    bool Filter();

    void BuildDropDowns(std::vector<grade> &v);
    void LoadText(std::vector<grade> &v);

    Glib::RefPtr<Gtk::StringList> m_courseStringList;
    Glib::RefPtr<Gtk::StringList> m_yearStringList;
    Glib::RefPtr<Gtk::StringList> m_instructorStringList;
    Glib::RefPtr<Gtk::StringList> m_subjectStringList;
    std::vector<grade> m_gradesVect;
    std::vector<grade> m_gradesVectFiltered;
};
