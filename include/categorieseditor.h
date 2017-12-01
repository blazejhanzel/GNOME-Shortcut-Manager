#ifndef CATEGORIESEDITOR_H
#define CATEGORIESEDITOR_H

#include <gtk/gtk.h>
#include <string>
#include <map>
#include <fstream>
#include <cctype>
#include <iostream>
#include "filemanager.h"

struct CategoriesEditor
{
    GtkWidget* window = NULL;
    FileManagerDataStruct* datastruct;
    GtkEntry* entry;
    std::map <int, GtkToggleButton*> cat_main_checkbutton;
    std::map <int, GtkToggleButton*> cat_add_checkbutton;
    std::map <int, GtkToggleButton*> cat_sys_checkbutton;
    GtkButton* accept_button;
    GtkButton* reject_button;

    //dicts – id – WidgetName
    //eg:      1 – cat_main_audiovideo_checkbutton
    std::map <int, std::string> cat_main_dictionary;
    std::map <int, std::string> cat_add_dictionary;
    std::map <int, std::string> cat_sys_dictionary;
};

void categorieseditor_init(GtkBuilder*);
void categorieseditor_show(FileManagerDataStruct*, GtkEntry*);

#endif // CATEGORIESEDITOR_H
