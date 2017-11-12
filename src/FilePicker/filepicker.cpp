#include "filepicker.h"

std::string filepicker_pick_path()
{
    // sets variables up
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    std::string filename;

    dialog = gtk_file_chooser_dialog_new ("Pick your file", NULL, action, "_Cancel", GTK_RESPONSE_CANCEL,
                                          "_Pick path", GTK_RESPONSE_ACCEPT, NULL);
    chooser = GTK_FILE_CHOOSER (dialog);
    res = gtk_dialog_run (GTK_DIALOG (dialog));

    if (res == GTK_RESPONSE_ACCEPT)
    {
        filename = gtk_file_chooser_get_filename (chooser);
        gtk_widget_destroy (dialog);
        return filename;
    }
    else
    {
        gtk_widget_destroy (dialog);
    }
}
