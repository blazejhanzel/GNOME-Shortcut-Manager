#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtk/gtk.h>
#include <string>
#include <map>
#include <iostream>
#include "aboutwindow.h"
#include "filemanager.h"
#include "filepicker.h"

struct MainWindow
{
    GtkWidget *window;
    std::map <std::string, GtkToolButton*> toolbar;
    std::map <std::string, GtkEntry*> entryfield;
    std::map <std::string, GtkToggleButton*> checkbutton;
    GtkComboBoxText *shortcut_type_combo;
    std::map <std::string, GtkButton*> filechooserbutton;
    std::map <std::string, GtkRadioButton*> radiobutton;
};
enum ApplicationTypes { APPLICATION, LINK, DIRECTORY };
void mainwindow_init(GtkBuilder*);
void mainwindow_show(bool);

#endif // MAINWINDOW_H
