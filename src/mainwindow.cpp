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

#include "../include/mainwindow.h"

MainWindow mainwindow;
FileManagerDataStruct datastruct;
std::string location_to_save;
std::string location_of_program_with_name;
bool unsaved_changes = false;
bool root_access;

void mainwindow_set_unsaved_changes()
{
    unsaved_changes = true;
}

void mainwindow_reload_fields()
{
    gtk_entry_set_text(mainwindow.entryfield["name"], datastruct.name.c_str());
    gtk_entry_set_text(mainwindow.entryfield["exec"], datastruct.exec.c_str());
    gtk_entry_set_text(mainwindow.entryfield["icon"], datastruct.icon.c_str());
    gtk_entry_set_text(mainwindow.entryfield["categories"], datastruct.categories.c_str());
    gtk_entry_set_text(mainwindow.entryfield["mimetypes"], datastruct.mimetypes.c_str());
    gtk_toggle_button_set_active(mainwindow.checkbutton["terminal"],
                                 [](bool data)->gboolean { return (data) ? TRUE : FALSE; } (datastruct.start_in_terminal));
    gtk_toggle_button_set_active(mainwindow.checkbutton["notify"],
                                 [](bool data)->gboolean { return (data) ? TRUE : FALSE; } (datastruct.notify_on_startup));
    gtk_toggle_button_set_active(mainwindow.checkbutton["hide"],
                                 [](bool data)->gboolean { return (data) ? TRUE : FALSE; } (datastruct.hidden));
    gtk_combo_box_set_active(GTK_COMBO_BOX(mainwindow.shortcuttypecombo), [](std::string data)->int { if (data == "Directory") return DIRECTORY;
                             else if (data == "Link") return LINK; else return APPLICATION; } (datastruct.shortcut_type));
}

void mainwindow_filepicker_exec_to_entry()
{
    std::string filename = filepicker_pick_path();
    gtk_entry_set_text(mainwindow.entryfield["exec"], filename.c_str());
}

void mainwindow_filepicker_icon_to_entry()
{
    std::string filename = filepicker_pick_path();
    gtk_entry_set_text(mainwindow.entryfield["icon"], filename.c_str());
}

void mainwindow_open_categories_editor()
{
    categorieseditor_show(&datastruct,mainwindow.entryfield["categories"]);
}

void mainwindow_delete_active_file()
{
    if (location_to_save.length() > 0)
    {
        filemanager_delete_file(location_to_save, root_access);
    }
    else
    {
        GtkWidget* dialog;
		dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Nothing to delete!");
        g_signal_connect_swapped (dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
		gtk_dialog_run(GTK_DIALOG(dialog));
    }
}

void mainwindow_get_data_from_fields()
{
    datastruct.name = gtk_entry_get_text(mainwindow.entryfield["name"]);
    datastruct.exec = gtk_entry_get_text(mainwindow.entryfield["exec"]);
    datastruct.icon = gtk_entry_get_text(mainwindow.entryfield["icon"]);
    datastruct.categories = gtk_entry_get_text(mainwindow.entryfield["categories"]);
    datastruct.mimetypes = gtk_entry_get_text(mainwindow.entryfield["mimetypes"]);
    datastruct.start_in_terminal = gtk_toggle_button_get_active(mainwindow.checkbutton["terminal"]);
    datastruct.notify_on_startup = gtk_toggle_button_get_active(mainwindow.checkbutton["notify"]);
    datastruct.hidden = gtk_toggle_button_get_active(mainwindow.checkbutton["hide"]);
    datastruct.shortcut_type = gtk_combo_box_text_get_active_text(mainwindow.shortcuttypecombo);
}

void mainwindow_toolbar_new()
{
    // delete all info about opened file
    location_to_save.clear();
    filemanager_clear_file_info(&datastruct);
    mainwindow_reload_fields();
}

void mainwindow_toolbar_open()
{
    // sets variables up
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Choose .desktop file", GTK_WINDOW(mainwindow.window),
                                          action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    chooser = GTK_FILE_CHOOSER (dialog);
    if (root_access == true)
    {
        gtk_file_chooser_set_current_folder (chooser, "/usr/share/applications/"); // default run location for sudo
    }
    else
    {
        std::string path = getenv("HOME");
        path += "/.local/share/applications";
        gtk_file_chooser_set_current_folder (chooser, path.c_str()); // default run location for non-sudo
    }
    res = gtk_dialog_run (GTK_DIALOG (dialog));

    if (res == GTK_RESPONSE_ACCEPT)
    {
        std::string filename;
        filename = gtk_file_chooser_get_filename (chooser);
        datastruct = filemanager_load(filename);
        location_to_save = filename;
    }

    gtk_widget_destroy (dialog);
    mainwindow_reload_fields();
}

void mainwindow_toolbar_saveas()
{
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Save as .desktop file", GTK_WINDOW(mainwindow.window),
                                          action, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
    chooser = GTK_FILE_CHOOSER (dialog);
    if (root_access == true)
    {
        gtk_file_chooser_set_current_folder (chooser, "/usr/share/applications/"); // default run location for sudo
    }
    else
    {
        std::string path = getenv("HOME");
        path += "/.local/share/applications";
        gtk_file_chooser_set_current_folder (chooser, path.c_str()); // default run location for non-sudo
    }
    gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
    res = gtk_dialog_run (GTK_DIALOG (dialog));

    if (res == GTK_RESPONSE_ACCEPT)
    {
        std::string filename;
        std::string extension = ".desktop";
        filename = gtk_file_chooser_get_filename (chooser);
        if (filename.find(extension.c_str(),filename.size()-extension.size(),extension.size()) == std::string::npos)
        {
            filename.append(extension);
        }
        location_to_save = filename;

        mainwindow_get_data_from_fields();
        filemanager_save(filename, datastruct);
        unsaved_changes = false;
        filemanager_set_chmodx(location_to_save, root_access);
    }

    gtk_widget_destroy (dialog);
}

void mainwindow_toolbar_save()
{
    if (location_to_save.length() > 0)
    {
        mainwindow_get_data_from_fields();
        filemanager_save(location_to_save, datastruct);
        unsaved_changes = false;
        filemanager_set_chmodx(location_to_save, root_access);
    }
    else
    {
        mainwindow_toolbar_saveas();
    }
}

void mainwindow_toolbar_create_shortcut()
{
    filemanager_create_app_shortcuts(location_of_program_with_name);
}

void mainwindow_quit()
{
    if (unsaved_changes == true)
    {
        GtkWidget *dialog;
        gint res;

        dialog = gtk_dialog_new_with_buttons("Unsaved changes!", GTK_WINDOW(mainwindow.window), GTK_DIALOG_MODAL, "_Save", GTK_RESPONSE_ACCEPT,
                                             "_Don't save", GTK_RESPONSE_REJECT, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
        res = gtk_dialog_run (GTK_DIALOG (dialog));

        if (res == GTK_RESPONSE_ACCEPT)
        {
            mainwindow_toolbar_save();
            gtk_widget_destroy (dialog);
            gtk_main_quit();
        }
        else if (res == GTK_RESPONSE_REJECT)
        {
            gtk_widget_destroy (dialog);
            gtk_main_quit();
        }
        else
        {
            gtk_widget_destroy (dialog);
        }
    }
    else
    {
        gtk_main_quit();
    }
}

void mainwindow_init(GtkBuilder *builder)
{
    location_to_save.clear();

    // assigning widgets to variables
    mainwindow.window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    mainwindow.toolbar["item_new"] = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "toolbar_item_new"));
    mainwindow.toolbar["item_open"] = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "toolbar_item_open"));
    mainwindow.toolbar["item_save"] = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "toolbar_item_save"));
    mainwindow.toolbar["item_saveas"] = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "toolbar_item_saveas"));
    mainwindow.toolbar["item_delete"] = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "toolbar_item_delete"));
    mainwindow.toolbar["item_about"] = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "toolbar_item_about"));
    mainwindow.toolbar["item_shortcut_create"] = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "toolbar_item_shortcut_create"));
    mainwindow.toolbar["item_quit"] = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "toolbar_item_quit"));
    mainwindow.entryfield["name"] = GTK_ENTRY(gtk_builder_get_object(builder, "entryfield_name"));
    mainwindow.entryfield["exec"] = GTK_ENTRY(gtk_builder_get_object(builder, "entryfield_exec"));
    mainwindow.entryfield["icon"] = GTK_ENTRY(gtk_builder_get_object(builder, "entryfield_icon"));
    mainwindow.entryfield["categories"] = GTK_ENTRY(gtk_builder_get_object(builder, "entryfield_categories"));
    mainwindow.entryfield["mimetypes"] = GTK_ENTRY(gtk_builder_get_object(builder, "entryfield_mimetypes"));
    mainwindow.checkbutton["terminal"] = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "checkbutton_terminal"));
    mainwindow.checkbutton["notify"] = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "checkbutton_notify"));
    mainwindow.checkbutton["hide"] = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "checkbutton_hide"));
    mainwindow.shortcuttypecombo = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_type"));
    mainwindow.filechooserbutton["exec"] = GTK_BUTTON(gtk_builder_get_object(builder, "pick_execpath_button"));
    mainwindow.filechooserbutton["icon"] = GTK_BUTTON(gtk_builder_get_object(builder, "pick_iconpath_button"));
    mainwindow.catseditorbutton = GTK_BUTTON(gtk_builder_get_object(builder, "catseditor_open_button"));

    // connecting signals
    g_signal_connect(G_OBJECT(mainwindow.window), "delete-event", G_CALLBACK(mainwindow_quit), NULL);
    g_signal_connect(G_OBJECT(mainwindow.toolbar["item_new"]), "clicked", G_CALLBACK(mainwindow_toolbar_new), NULL);
    g_signal_connect(G_OBJECT(mainwindow.toolbar["item_open"]), "clicked", G_CALLBACK(mainwindow_toolbar_open), NULL);
    g_signal_connect(G_OBJECT(mainwindow.toolbar["item_save"]), "clicked", G_CALLBACK(mainwindow_toolbar_save), NULL);
    g_signal_connect(G_OBJECT(mainwindow.toolbar["item_saveas"]), "clicked", G_CALLBACK(mainwindow_toolbar_saveas), NULL);
    g_signal_connect(G_OBJECT(mainwindow.toolbar["item_delete"]), "clicked", G_CALLBACK(mainwindow_delete_active_file), NULL);
    g_signal_connect(G_OBJECT(mainwindow.toolbar["item_about"]), "clicked", G_CALLBACK(aboutwindow_show), NULL);
    g_signal_connect(G_OBJECT(mainwindow.toolbar["item_shortcut_create"]), "clicked", G_CALLBACK(mainwindow_toolbar_create_shortcut), NULL);
    g_signal_connect(G_OBJECT(mainwindow.toolbar["item_quit"]), "clicked", G_CALLBACK(mainwindow_quit), NULL);
    g_signal_connect(G_OBJECT(mainwindow.filechooserbutton["exec"]), "clicked", G_CALLBACK(mainwindow_filepicker_exec_to_entry), NULL);
    g_signal_connect(G_OBJECT(mainwindow.filechooserbutton["icon"]), "clicked", G_CALLBACK(mainwindow_filepicker_icon_to_entry), NULL);
    g_signal_connect(GTK_EDITABLE(mainwindow.entryfield["name"]), "changed", G_CALLBACK(mainwindow_set_unsaved_changes), NULL);
    g_signal_connect(GTK_EDITABLE(mainwindow.entryfield["exec"]), "changed", G_CALLBACK(mainwindow_set_unsaved_changes), NULL);
    g_signal_connect(GTK_EDITABLE(mainwindow.entryfield["icon"]), "changed", G_CALLBACK(mainwindow_set_unsaved_changes), NULL);
    g_signal_connect(GTK_EDITABLE(mainwindow.entryfield["categories"]), "changed", G_CALLBACK(mainwindow_set_unsaved_changes), NULL);
    g_signal_connect(GTK_EDITABLE(mainwindow.entryfield["mimetypes"]), "changed", G_CALLBACK(mainwindow_set_unsaved_changes), NULL);
    g_signal_connect(GTK_TOGGLE_BUTTON(mainwindow.checkbutton["terminal"]), "toggled", G_CALLBACK(mainwindow_set_unsaved_changes), NULL);
    g_signal_connect(GTK_TOGGLE_BUTTON(mainwindow.checkbutton["notify"]), "toggled", G_CALLBACK(mainwindow_set_unsaved_changes), NULL);
    g_signal_connect(GTK_TOGGLE_BUTTON(mainwindow.checkbutton["hide"]), "toggled", G_CALLBACK(mainwindow_set_unsaved_changes), NULL);
    g_signal_connect(GTK_EDITABLE(mainwindow.shortcuttypecombo), "changed", G_CALLBACK(mainwindow_set_unsaved_changes), NULL);
    g_signal_connect(G_OBJECT(mainwindow.catseditorbutton), "clicked", G_CALLBACK(mainwindow_open_categories_editor), NULL);
}

void mainwindow_show(bool root_acc, std::string program_location)
{
    location_of_program_with_name = program_location;
    root_access = root_acc;
    gtk_widget_show_all(mainwindow.window);
}
