/* Copyright (C) 2017 blahax2g
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
 
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
