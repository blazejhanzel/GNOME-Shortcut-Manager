#include "../include/aboutwindow.h"

AboutWindow aboutwindow;

void aboutwindow_init(GtkBuilder *builder)
{
    // assigning widgets to variables
    aboutwindow.window = GTK_WIDGET(gtk_builder_get_object(builder, "about_window"));

    // connecting signals
    gtk_builder_connect_signals(builder, NULL);
    g_signal_connect (aboutwindow.window, "delete-event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
}

void aboutwindow_show()
{
    gtk_widget_show_all(aboutwindow.window);
}
