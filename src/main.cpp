#include <gtk/gtk.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "../include/mainwindow.h"
#define UI_FILE "../data/ui/gnome-shortcut-manager.ui"
#define UI_FILE_MIRROR "data/ui/gnome-shortcut-manager.ui"
#define UI_CATSEDITOR "../data/ui/cats-editor.ui"
#define UI_CATSEDITOR_MIRROR "data/ui/cats-editor.ui"

int main(int argc, char* argv[])
{
    bool root_access;
	setreuid(0, getuid());

    // init gtk to use gtk
    gtk_init(&argc,&argv);

    // GtkBuilder initializers
    GtkBuilder* builder = gtk_builder_new();
    if(gtk_builder_add_from_file(builder, UI_FILE, NULL) == 0) // returned error
    {
        gtk_builder_add_from_file(builder, UI_FILE_MIRROR, NULL);
    }
    aboutwindow_init(builder);
    mainwindow_init(builder);
    if(gtk_builder_add_from_file(builder, UI_CATSEDITOR, NULL) == 0) // returned error
    {
        gtk_builder_add_from_file(builder, UI_CATSEDITOR_MIRROR, NULL);
    }
    categorieseditor_init(builder);
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
    mainwindow_show(root_access);

    // and start application
    gtk_main();

    return 0;
}
