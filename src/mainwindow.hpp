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

class MainWindow: public Gtk::Window
{
public:
    MainWindow();
    ~MainWindow() override;

protected:
    // Signal handler:
    void on_dropdown_changed();

    Gtk::Box m_box;
    // Child widget:
    Gtk::DropDown m_CourseDropDown;
    Gtk::DropDown m_InstructorDropDown;
    Gtk::DropDown m_YearDropDown;
    Gtk::DropDown m_SubjectDropDown;

    void Select();
    Glib::RefPtr<Gtk::StringList> m_courseStringList;
    Glib::RefPtr<Gtk::StringList> m_yearStringList;
    Glib::RefPtr<Gtk::StringList> m_instructorStringList;
    Glib::RefPtr<Gtk::StringList> m_subjectStringList;
    std::vector<grade> gradesVect;

};

