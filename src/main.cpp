#include <gtk/gtk.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "MainWindow/mainwindow.h"
#define UI_FILE "gnome-shortcut-manager.ui"

int main(int argc, char* argv[])
{
    bool root_access;
	setreuid(0, getuid());

    // init gtk to use gtk
    gtk_init(&argc,&argv);

    // GtkBuilder initializers
    GtkBuilder* builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, UI_FILE, NULL);
    aboutwindow_init(builder);
    mainwindow_init(builder);
    g_object_unref(builder);

    // root is needed
    if (getuid() != 0)
	{
	    GtkWidget* dialog;
		dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
                                        "Root privileges are recommended for running this program!");
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog),"You don't need root to open or save into \"home\" directory. \n\
Read about running application with root access.");
        g_signal_connect_swapped (dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
		gtk_dialog_run(GTK_DIALOG(dialog));
		root_access = false;
	}
	else
    {
        root_access = true;
    }

    // display main window
    mainwindow_show();

    // and start application
    gtk_main();

    return 0;
}
