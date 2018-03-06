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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtk/gtk.h>
#include <string>
#include <map>
#include <iostream>
#include "aboutwindow.h"
#include "categorieseditor.h"
#include "filemanager.h"
#include "filepicker.h"

struct MainWindow
{
    GtkWidget *window;
    std::map <std::string, GtkToolButton*> toolbar;
    std::map <std::string, GtkEntry*> entryfield;
    std::map <std::string, GtkToggleButton*> checkbutton;
    GtkComboBoxText *shortcuttypecombo;
    std::map <std::string, GtkButton*> filechooserbutton;
    std::map <std::string, GtkRadioButton*> radiobutton;
    GtkButton* catseditorbutton;
};
enum ApplicationTypes { APPLICATION, LINK, DIRECTORY };
void mainwindow_init(GtkBuilder*);
void mainwindow_show(bool, std::string);

#endif // MAINWINDOW_H
