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

#include "../include/filepicker.h"

std::string filepicker_pick_path()
{
    // sets variables up
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    std::string filename = "";

    dialog = gtk_file_chooser_dialog_new ("Pick your file", NULL, action, "_Cancel", GTK_RESPONSE_CANCEL,
                                          "_Pick path", GTK_RESPONSE_ACCEPT, NULL);
    chooser = GTK_FILE_CHOOSER (dialog);
    res = gtk_dialog_run (GTK_DIALOG (dialog));

    if (res == GTK_RESPONSE_ACCEPT)
    {
        filename = gtk_file_chooser_get_filename (chooser);
    }
    gtk_widget_destroy (dialog);
    return filename;
}
