#include "../include/categorieseditor.h"

CategoriesEditor catseditor;

void categorieseditor_quit()
{
    // Clean all - uncheck every check
    for (int i=0; i<13; i++) // for main
    {
        gtk_toggle_button_set_active(catseditor.cat_main_checkbutton[i], FALSE);
    }
    for (int i=0; i<4; i++) // for system-reserved
    {
        gtk_toggle_button_set_active(catseditor.cat_sys_checkbutton[i], FALSE);
    }
    for (int i=0; i<126; i++) // for additional
    {
        gtk_toggle_button_set_active(catseditor.cat_add_checkbutton[i], FALSE);
    }
    gtk_widget_hide_on_delete(catseditor.window);
    gtk_entry_set_text(catseditor.entry, catseditor.datastruct->categories.c_str());
}

void categorieseditor_save_database()
{
    // first, clean all old tags
    catseditor.datastruct->categories.clear();

    for (int i=0; i<13; i++) // for main
    {
        if (gtk_toggle_button_get_active(catseditor.cat_main_checkbutton[i]))
        {
            std::string data_to_append = catseditor.cat_main_dictionary[i] + ";";
            catseditor.datastruct->categories.append(data_to_append);
        }
    }
    for (int i=0; i<4; i++) // for system-reserved
    {
        if (gtk_toggle_button_get_active(catseditor.cat_sys_checkbutton[i]))
        {
            std::string data_to_append = catseditor.cat_sys_dictionary[i] + ";";
            catseditor.datastruct->categories.append(data_to_append);
        }
    }
    for (int i=0; i<126; i++) // for additional
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
    catseditor.cat_main_dictionary[0] = "AudioVideo";
    catseditor.cat_main_dictionary[1] = "Audio";
    catseditor.cat_main_dictionary[2] = "Video";
    catseditor.cat_main_dictionary[3] = "Development";
    catseditor.cat_main_dictionary[4] = "Education";
    catseditor.cat_main_dictionary[5] = "Game";
    catseditor.cat_main_dictionary[6] = "Graphics";
    catseditor.cat_main_dictionary[7] = "Network";
    catseditor.cat_main_dictionary[8] = "Office";
    catseditor.cat_main_dictionary[9] = "Science";
    catseditor.cat_main_dictionary[10] = "Settings";
    catseditor.cat_main_dictionary[11] = "System";
    catseditor.cat_main_dictionary[12] = "Utility";
    catseditor.cat_sys_dictionary[0] = "Screensaver";
    catseditor.cat_sys_dictionary[1] = "TrayIcon";
    catseditor.cat_sys_dictionary[2] = "Applet";
    catseditor.cat_sys_dictionary[3] = "Shell";
    catseditor.cat_add_dictionary[0] = "Building";
    catseditor.cat_add_dictionary[1] = "Debugger";
    catseditor.cat_add_dictionary[2] = "IDE";
    catseditor.cat_add_dictionary[3] = "GUIDesigner";
    catseditor.cat_add_dictionary[4] = "Profiling";
    catseditor.cat_add_dictionary[5] = "RevisionControl";
    catseditor.cat_add_dictionary[6] = "Translation";
    catseditor.cat_add_dictionary[7] = "Calendar";
    catseditor.cat_add_dictionary[8] = "ContactManagement";
    catseditor.cat_add_dictionary[9] = "Database";
    catseditor.cat_add_dictionary[10] = "Dictionary";
    catseditor.cat_add_dictionary[11] = "Chart";
    catseditor.cat_add_dictionary[12] = "Email";
    catseditor.cat_add_dictionary[13] = "Finance";
    catseditor.cat_add_dictionary[14] = "FlowChart";
    catseditor.cat_add_dictionary[15] = "PDA";
    catseditor.cat_add_dictionary[16] = "ProjectManagement";
    catseditor.cat_add_dictionary[17] = "Presentation";
    catseditor.cat_add_dictionary[18] = "Spreadsheet";
    catseditor.cat_add_dictionary[19] = "WordProcessor";
    catseditor.cat_add_dictionary[20] = "2DGraphics";
    catseditor.cat_add_dictionary[21] = "VectorGraphics";
    catseditor.cat_add_dictionary[22] = "RasterGraphics";
    catseditor.cat_add_dictionary[23] = "3DGraphics";
    catseditor.cat_add_dictionary[24] = "Scanning";
    catseditor.cat_add_dictionary[25] = "OCR";
    catseditor.cat_add_dictionary[26] = "Photography";
    catseditor.cat_add_dictionary[27] = "Publishing";
    catseditor.cat_add_dictionary[28] = "Viewer";
    catseditor.cat_add_dictionary[29] = "TextTools";
    catseditor.cat_add_dictionary[30] = "DesktopSettings";
    catseditor.cat_add_dictionary[31] = "HardwareSettings";
    catseditor.cat_add_dictionary[32] = "Printing";
    catseditor.cat_add_dictionary[33] = "PackageManager";
    catseditor.cat_add_dictionary[34] = "Dialup";
    catseditor.cat_add_dictionary[35] = "InstantMessaging";
    catseditor.cat_add_dictionary[36] = "Chat";
    catseditor.cat_add_dictionary[37] = "IRCClient";
    catseditor.cat_add_dictionary[38] = "Feed";
    catseditor.cat_add_dictionary[39] = "FileTransfer";
    catseditor.cat_add_dictionary[40] = "HamRadio";
    catseditor.cat_add_dictionary[41] = "News";
    catseditor.cat_add_dictionary[42] = "P2P";
    catseditor.cat_add_dictionary[43] = "RemoteAccess";
    catseditor.cat_add_dictionary[44] = "Telephony";
    catseditor.cat_add_dictionary[45] = "TelephonyTools";
    catseditor.cat_add_dictionary[46] = "VideoConference";
    catseditor.cat_add_dictionary[47] = "WebBrowser";
    catseditor.cat_add_dictionary[48] = "WebDevelopment";
    catseditor.cat_add_dictionary[49] = "Midi";
    catseditor.cat_add_dictionary[50] = "Mixer";
    catseditor.cat_add_dictionary[51] = "Sequencer";
    catseditor.cat_add_dictionary[52] = "Tuner";
    catseditor.cat_add_dictionary[53] = "TV";
    catseditor.cat_add_dictionary[54] = "AudioVideoEditing";
    catseditor.cat_add_dictionary[55] = "Player";
    catseditor.cat_add_dictionary[56] = "Recorder";
    catseditor.cat_add_dictionary[57] = "DiscBurning";
    catseditor.cat_add_dictionary[58] = "ActionGame";
    catseditor.cat_add_dictionary[59] = "AdventureGame";
    catseditor.cat_add_dictionary[60] = "ArcadeGame";
    catseditor.cat_add_dictionary[61] = "BoardGame";
    catseditor.cat_add_dictionary[62] = "BlocksGame";
    catseditor.cat_add_dictionary[63] = "CardGame";
    catseditor.cat_add_dictionary[64] = "KidsGame";
    catseditor.cat_add_dictionary[65] = "LogicGame";
    catseditor.cat_add_dictionary[66] = "RolePlaying";
    catseditor.cat_add_dictionary[67] = "Shooter";
    catseditor.cat_add_dictionary[68] = "Simulation";
    catseditor.cat_add_dictionary[69] = "SportsGame";
    catseditor.cat_add_dictionary[70] = "StrategyGame";
    catseditor.cat_add_dictionary[71] = "Art";
    catseditor.cat_add_dictionary[72] = "Construction";
    catseditor.cat_add_dictionary[73] = "Music";
    catseditor.cat_add_dictionary[74] = "Languages";
    catseditor.cat_add_dictionary[75] = "ArtificialIntelligence";
    catseditor.cat_add_dictionary[76] = "Astronomy";
    catseditor.cat_add_dictionary[77] = "Biology";
    catseditor.cat_add_dictionary[78] = "Chemistry";
    catseditor.cat_add_dictionary[79] = "ComputerScience";
    catseditor.cat_add_dictionary[80] = "DataVisualization";
    catseditor.cat_add_dictionary[81] = "Economy";
    catseditor.cat_add_dictionary[82] = "Electricity";
    catseditor.cat_add_dictionary[83] = "Geography";
    catseditor.cat_add_dictionary[84] = "Geology";
    catseditor.cat_add_dictionary[85] = "Geoscience";
    catseditor.cat_add_dictionary[86] = "History";
    catseditor.cat_add_dictionary[87] = "Humanities";
    catseditor.cat_add_dictionary[88] = "ImageProcessing";
    catseditor.cat_add_dictionary[89] = "Literature";
    catseditor.cat_add_dictionary[90] = "Maps";
    catseditor.cat_add_dictionary[91] = "Math";
    catseditor.cat_add_dictionary[92] = "NumericalAnalysis";
    catseditor.cat_add_dictionary[93] = "MedicalSoftware";
    catseditor.cat_add_dictionary[94] = "Physics";
    catseditor.cat_add_dictionary[95] = "Robotics";
    catseditor.cat_add_dictionary[96] = "Spirituality";
    catseditor.cat_add_dictionary[97] = "Sports";
    catseditor.cat_add_dictionary[98] = "ParallelComputing";
    catseditor.cat_add_dictionary[99] = "Amusement";
    catseditor.cat_add_dictionary[100] = "Archiving";
    catseditor.cat_add_dictionary[101] = "Compression";
    catseditor.cat_add_dictionary[102] = "Electronics";
    catseditor.cat_add_dictionary[103] = "Emulator";
    catseditor.cat_add_dictionary[104] = "Engineering";
    catseditor.cat_add_dictionary[105] = "FileTools";
    catseditor.cat_add_dictionary[106] = "FileManager";
    catseditor.cat_add_dictionary[107] = "TerminalEmulator";
    catseditor.cat_add_dictionary[108] = "Filesystem";
    catseditor.cat_add_dictionary[109] = "Monitor";
    catseditor.cat_add_dictionary[110] = "Security";
    catseditor.cat_add_dictionary[111] = "Accessibility";
    catseditor.cat_add_dictionary[112] = "Calculator";
    catseditor.cat_add_dictionary[113] = "Clock";
    catseditor.cat_add_dictionary[114] = "TextEditor";
    catseditor.cat_add_dictionary[115] = "Documentation";
    catseditor.cat_add_dictionary[116] = "Adult";
    catseditor.cat_add_dictionary[117] = "Core";
    catseditor.cat_add_dictionary[118] = "KDE";
    catseditor.cat_add_dictionary[119] = "GNOME";
    catseditor.cat_add_dictionary[120] = "XFCE";
    catseditor.cat_add_dictionary[121] = "GTK";
    catseditor.cat_add_dictionary[122] = "Qt";
    catseditor.cat_add_dictionary[123] = "Motif";
    catseditor.cat_add_dictionary[124] = "Java";
    catseditor.cat_add_dictionary[125] = "ConsoleOnly";

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
    for (int i=0; i<13; i++) // for main
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
    for (int i=0; i<4; i++) // for system-reserved
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
    for (int i=0; i<126; i++) // for additional
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
    for (int i=0; i<13; i++) // for main
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
    for (int i=0; i<4; i++) // for system-reserved
    {
        std::string text_to_search = catseditor.cat_sys_dictionary[i] + ";";
        if (catseditor.datastruct->categories.find(
            text_to_search) != std::string::npos) // if finded
        {
            gtk_toggle_button_set_active(catseditor.cat_sys_checkbutton[i], TRUE);
        }
    }
    for (int i=0; i<126; i++) // for additional
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
