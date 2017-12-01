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

#include "../include/aboutwindow.h"

AboutWindow aboutwindow;

void aboutwindow_init(GtkBuilder *builder)
{
    // assigning widgets to variables
    aboutwindow.window = GTK_WIDGET(gtk_builder_get_object(builder, "about_window"));

    // connecting signals
    gtk_builder_connect_signals(builder, NULL);
    g_signal_connect(aboutwindow.window, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
}

void aboutwindow_show()
{
    gtk_widget_show_all(aboutwindow.window);
}
