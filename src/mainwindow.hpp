#pragma once

#include "grade.hpp"
#include "dataImporter.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

#include <gtkmm/window.h>
#include <gtkmm/dropdown.h>
#include <gtkmm/box.h>
#include <gtkmm/stringlist.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>

class MainWindow: public Gtk::Window
{
public:
    MainWindow();
    ~MainWindow() override;

protected:
    // Signal handler:
    void on_dropdown_changed();

    Gtk::Grid m_grid;

    Gtk::TextView m_text_view;
    Gtk::ScrolledWindow m_scrolled_window;
    Gtk::Box m_box;

    // Child widgets:
    Gtk::Label m_YearTotalsLabel;
    Gtk::Label m_SubjectTotalsLabel;
    Gtk::Label m_CourseTotalsLabel;
    Gtk::Label m_InstructorTotalsLabel;

    Gtk::DropDown m_CourseDropDown;
    Gtk::DropDown m_InstructorDropDown;
    Gtk::DropDown m_YearDropDown;
    Gtk::DropDown m_SubjectDropDown;

    void Select();
    void Filter();
    Glib::RefPtr<Gtk::StringList> m_courseStringList;
    Glib::RefPtr<Gtk::StringList> m_yearStringList;
    Glib::RefPtr<Gtk::StringList> m_instructorStringList;
    Glib::RefPtr<Gtk::StringList> m_subjectStringList;
    std::vector<grade> m_gradesVect;
    std::vector<grade> m_gradesVectFiltered;

};

