#ifndef CATEGORIESEDITOR_H
#define CATEGORIESEDITOR_H

#include <gtk/gtk.h>
#include <map>
#include <cctype>
#define UI_FILE "categories-editor.ui"

struct CategoriesEditor
{
    GtkWidget* window = NULL;
    std::map <int, GtkToggleButton*> cat_main_checkbutton;
    std::map <int, GtkToggleButton*> cat_add_checkbutton;
    std::map <int, GtkToggleButton*> cat_sys_checkbutton;
};

//dicts – id – WidgetName
//eg:      1 – cat_main_audiovideo_checkbutton
std::map <int, std::string> cat_main_dictionary;
std::map <int, std::string> cat_add_dictionary;
std::map <int, std::string> cat_sys_dictionary;

void categorieseditor_init(GtkBuilder*);
void categorieseditor_show();

#endif // CATEGORIESEDITOR_H
