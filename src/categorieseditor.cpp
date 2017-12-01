#include "../include/categorieseditor.h"

#define MAIN_CAT_DICT "../data/cat_dicts/cat_main.txt"
#define MAIN_CAT_DICT_MIRROR "data/cat_dicts/cat_main.txt"
#define SYS_CAT_DICT "../data/cat_dicts/cat_sys.txt"
#define SYS_CAT_DICT_MIRROR "data/cat_dicts/cat_sys.txt"
#define ADD_CAT_DICT "../data/cat_dicts/cat_add.txt"
#define ADD_CAT_DICT_MIRROR "data/cat_dicts/cat_add.txt"

#define MAIN_CATS 13
#define SYS_CATS 4
#define ADD_CATS 126

CategoriesEditor catseditor;

void categorieseditor_quit()
{
    // Clean all - uncheck every check
    for (int i=0; i<MAIN_CATS; i++) // for main
    {
        gtk_toggle_button_set_active(catseditor.cat_main_checkbutton[i], FALSE);
    }
    for (int i=0; i<SYS_CATS; i++) // for system-reserved
    {
        gtk_toggle_button_set_active(catseditor.cat_sys_checkbutton[i], FALSE);
    }
    for (int i=0; i<ADD_CATS; i++) // for additional
    {
        gtk_toggle_button_set_active(catseditor.cat_add_checkbutton[i], FALSE);
    }
    gtk_widget_hide_on_delete(catseditor.window);
    gtk_entry_set_text(catseditor.entry, catseditor.datastruct->categories.c_str());
}

void categorieseditor_throw_dictloadingerror(std::string filename)
{
    std::string text_to_display = "Couldn't load dictionary file: " + filename + "\n\
Some categories in Editor couldn't work properly!\n\
Your installation of GNOME-Shortcut-Manager is probably broken,\n\
Please reinstall application. Use GitHub to get the latest official version.";
    GtkWidget* dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK, "Couldn't load restricted files!");
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), text_to_display.c_str());
    g_signal_connect_swapped (dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
    g_signal_connect_swapped (dialog, "response", G_CALLBACK(categorieseditor_quit), NULL);
    gtk_dialog_run(GTK_DIALOG(dialog));
}

void categorieseditor_save_database()
{
    // first, clean all old tags
    catseditor.datastruct->categories.clear();

    for (int i=0; i<MAIN_CATS; i++) // for main
    {
        if (gtk_toggle_button_get_active(catseditor.cat_main_checkbutton[i]))
        {
            std::string data_to_append = catseditor.cat_main_dictionary[i] + ";";
            catseditor.datastruct->categories.append(data_to_append);
        }
    }
    for (int i=0; i<SYS_CATS; i++) // for system-reserved
    {
        if (gtk_toggle_button_get_active(catseditor.cat_sys_checkbutton[i]))
        {
            std::string data_to_append = catseditor.cat_sys_dictionary[i] + ";";
            catseditor.datastruct->categories.append(data_to_append);
        }
    }
    for (int i=0; i<ADD_CATS; i++) // for additional
    {
        if (gtk_toggle_button_get_active(catseditor.cat_add_checkbutton[i]))
        {
            std::string data_to_append = catseditor.cat_add_dictionary[i] + ";";
            catseditor.datastruct->categories.append(data_to_append);
        }
    }

    // and close
    categorieseditor_quit();
}

void categorieseditor_init(GtkBuilder* builder)
{
    // dictionaries init
    std::fstream f;
    f.open(MAIN_CAT_DICT, std::ios::in);
    if (f.is_open() == false)
    {
        f.open(MAIN_CAT_DICT_MIRROR, std::ios::in);
        if (f.is_open() == false)
            categorieseditor_throw_dictloadingerror(MAIN_CAT_DICT_MIRROR);
    }
    if (f.is_open() == true)
    {
        for (int i=0; i<MAIN_CATS; i++) // for main
        {
            f >> catseditor.cat_main_dictionary[i];
        }
        f.close();
    }

    f.open(SYS_CAT_DICT, std::ios::in);
    if (f.is_open() == false)
    {
        f.open(SYS_CAT_DICT_MIRROR, std::ios::in);
        if (f.is_open() == false)
            categorieseditor_throw_dictloadingerror(SYS_CAT_DICT_MIRROR);
    }
    if (f.is_open() == true)
    {
        for (int i=0; i<SYS_CATS; i++) // for system-reserved
        {
            f >> catseditor.cat_sys_dictionary[i];
        }
        f.close();
    }

    f.open(ADD_CAT_DICT, std::ios::in);
    if (f.is_open() == false)
    {
        f.open(ADD_CAT_DICT_MIRROR, std::ios::in);
        if (f.is_open() == false)
            categorieseditor_throw_dictloadingerror(ADD_CAT_DICT_MIRROR);
    }
    if (f.is_open() == true)
    {
        for (int i=0; i<ADD_CATS; i++) // for additional
        {
            f >> catseditor.cat_add_dictionary[i];
        }
        f.close();
    }

    // Window Init
    catseditor.window = GTK_WIDGET(gtk_builder_get_object(builder, "categories_editor"));

    // getting buttons
    catseditor.accept_button = GTK_BUTTON(gtk_builder_get_object(builder, "accept_button"));
    catseditor.reject_button = GTK_BUTTON(gtk_builder_get_object(builder, "reject_button"));

    // connecting signals
    gtk_builder_connect_signals(builder, NULL);
    g_signal_connect(G_OBJECT(catseditor.window), "delete-event", G_CALLBACK(categorieseditor_quit), NULL);
    g_signal_connect(G_OBJECT(catseditor.accept_button), "clicked", G_CALLBACK(categorieseditor_save_database), NULL);
    g_signal_connect(G_OBJECT(catseditor.reject_button), "clicked", G_CALLBACK(categorieseditor_quit), NULL);

    // Buttons Init
    for (int i=0; i<MAIN_CATS; i++) // for main
    {
        // getting object from builder to variable
        std::string name = "cat_main_";
        for (size_t j=0; j<catseditor.cat_main_dictionary[i].size(); j++)
        {
            name += tolower(catseditor.cat_main_dictionary[i][j]);
        }
        name += "_checkbutton";

        catseditor.cat_main_checkbutton[i] = GTK_TOGGLE_BUTTON(gtk_builder_get_object
                                                               (builder, name.c_str()));

        // setting label
        gtk_button_set_label(GTK_BUTTON(catseditor.cat_main_checkbutton[i]),
                             catseditor.cat_main_dictionary[i].c_str());
    }
    for (int i=0; i<SYS_CATS; i++) // for system-reserved
    {
        // getting object from builder to variable
        std::string name = "cat_sys_";
        for (size_t j=0; j<catseditor.cat_sys_dictionary[i].size(); j++)
        {
            name += tolower(catseditor.cat_sys_dictionary[i][j]);
        }
        name += "_checkbutton";

        catseditor.cat_sys_checkbutton[i] = GTK_TOGGLE_BUTTON(gtk_builder_get_object
                                                               (builder, name.c_str()));

        // setting label
        gtk_button_set_label(GTK_BUTTON(catseditor.cat_sys_checkbutton[i]),
                             catseditor.cat_sys_dictionary[i].c_str());
    }
    for (int i=0; i<ADD_CATS; i++) // for additional
    {
        // getting object from builder to variable
        std::string name = "cat_add_";
        for (size_t j=0; j<catseditor.cat_add_dictionary[i].size(); j++)
        {
            name += tolower(catseditor.cat_add_dictionary[i][j]);
        }
        name += "_checkbutton";

        catseditor.cat_add_checkbutton[i] = GTK_TOGGLE_BUTTON(gtk_builder_get_object
                                                               (builder, name.c_str()));

        // setting label
        gtk_button_set_label(GTK_BUTTON(catseditor.cat_add_checkbutton[i]),
                             catseditor.cat_add_dictionary[i].c_str());
    }
}

void categorieseditor_show(FileManagerDataStruct* datastruct_to_copy,
    GtkEntry* categories_entry)
{
    // Create local copy of catseditor.datastruct pointer
    catseditor.datastruct = datastruct_to_copy;
    catseditor.entry = categories_entry;

    // Load active categories
    for (int i=0; i<MAIN_CATS; i++) // for main
    {
        std::string text_to_search = catseditor.cat_main_dictionary[i] + ";";
            /* using semicolon fix bug with loading similiar
            categories e.g. loading Sports anstead of SportsGame
            doesn't work with some types, may be fixed: FIXME */
        if (catseditor.datastruct->categories.find(
            text_to_search) != std::string::npos) // if finded
        {
            gtk_toggle_button_set_active(catseditor.cat_main_checkbutton[i], TRUE);
        }
    }
    for (int i=0; i<SYS_CATS; i++) // for system-reserved
    {
        std::string text_to_search = catseditor.cat_sys_dictionary[i] + ";";
        if (catseditor.datastruct->categories.find(
            text_to_search) != std::string::npos) // if finded
        {
            gtk_toggle_button_set_active(catseditor.cat_sys_checkbutton[i], TRUE);
        }
    }
    for (int i=0; i<ADD_CATS; i++) // for additional
    {
        std::string text_to_search = catseditor.cat_add_dictionary[i] + ";";
        if (catseditor.datastruct->categories.find(
            text_to_search) != std::string::npos) // if finded
        {
            gtk_toggle_button_set_active(catseditor.cat_add_checkbutton[i], TRUE);
        }
    }

    // at the end… Display
    gtk_widget_show_all(catseditor.window);
}
