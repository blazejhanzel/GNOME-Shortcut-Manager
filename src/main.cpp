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

#include <gtk/gtk.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "../include/mainwindow.h"
#define APP_NAME "GNOME-Shortcut-Manager"
#define UI_FILE "../data/ui/gnome-shortcut-manager.ui"
#define UI_FILE_MIRROR "data/ui/gnome-shortcut-manager.ui"
#define UI_CATSEDITOR "../data/ui/cats-editor.ui"
#define UI_CATSEDITOR_MIRROR "data/ui/cats-editor.ui"

std::string get_working_directory()
{
  char buff[FILENAME_MAX];
  getcwd( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}

int main(int argc, char* argv[])
{
    std::string app_path;
    std::string path;

    // set app_path
    std::string app_name = APP_NAME;
    app_path = argv[0];
    app_path.erase(app_path.size()-app_name.size(),app_name.size());

    bool root_access;
	setreuid(0, getuid());

    // init gtk to use gtk
    gtk_init(&argc,&argv);

    // GtkBuilder initializers
    GtkBuilder* builder = gtk_builder_new();
    path = app_path + UI_FILE;
    if(gtk_builder_add_from_file(builder, path.c_str(), NULL) == 0) // returned error
    {
        path = app_path + UI_FILE_MIRROR;
        gtk_builder_add_from_file(builder, path.c_str(), NULL);
    }
    aboutwindow_init(builder);
    mainwindow_init(builder);
    path = app_path + UI_CATSEDITOR;
    if(gtk_builder_add_from_file(builder, path.c_str(), NULL) == 0) // returned error
    {
        path = app_path + UI_CATSEDITOR_MIRROR;
        gtk_builder_add_from_file(builder, path.c_str(), NULL);
    }
    categorieseditor_init(builder, app_path);
    g_object_unref(builder);

    // root is needed
    if (getuid() != 0)
	{
	    GtkWidget* dialog;
		dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Root privileges – Inactive!");
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog),"Without root you still can change shortcuts for this user.\n\
If you want to change shortcuts for all users, run this program as sudo.");
        g_signal_connect_swapped (dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
		gtk_dialog_run(GTK_DIALOG(dialog));
		root_access = false;
	}
	else
    {
        root_access = true;
    }

    // display main window
    mainwindow_show(root_access, get_working_directory());

    // and start application
    gtk_main();

    return 0;
}
