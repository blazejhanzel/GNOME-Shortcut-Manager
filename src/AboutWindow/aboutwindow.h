#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <gtk/gtk.h>

struct AboutWindow
{
    GtkWidget *window = NULL;
};
void aboutwindow_init(GtkBuilder*);
void aboutwindow_show();

#endif // ABOUTWINDOW_H
