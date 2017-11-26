#include "categorieseditor.h"

CategoriesEditor catseditor;

void categorieseditor_init(GtkBuilder* builder)
{
    // dictionaries init
    cat_main_dictionary[0] = "AudioVideo";
    cat_main_dictionary[1] = "Audio";
    cat_main_dictionary[2] = "Video";
    cat_main_dictionary[3] = "Development";
    cat_main_dictionary[4] = "Education";
    cat_main_dictionary[5] = "Game";
    cat_main_dictionary[6] = "Graphics";
    cat_main_dictionary[7] = "Network";
    cat_main_dictionary[8] = "Office";
    cat_main_dictionary[9] = "Science";
    cat_main_dictionary[10] = "Settings";
    cat_main_dictionary[11] = "System";
    cat_main_dictionary[12] = "Utility";
    cat_sys_dictionary[0] = "Screensaver";
    cat_sys_dictionary[1] = "TrayIcon";
    cat_sys_dictionary[2] = "Applet";
    cat_sys_dictionary[3] = "Shell";
    cat_add_dictionary[0] = "Building";
    cat_add_dictionary[1] = "Debugger";
    cat_add_dictionary[2] = "IDE";
    cat_add_dictionary[3] = "GUIDesigner";
    cat_add_dictionary[4] = "Profiling";
    cat_add_dictionary[5] = "RevisionControl";
    cat_add_dictionary[6] = "Translation";
    cat_add_dictionary[7] = "Calendar";
    cat_add_dictionary[8] = "ContactManagement";
    cat_add_dictionary[9] = "Database";
    cat_add_dictionary[10] = "Dictionary";
    cat_add_dictionary[11] = "Chart";
    cat_add_dictionary[12] = "Email";
    cat_add_dictionary[13] = "Finance";
    cat_add_dictionary[14] = "FlowChart";
    cat_add_dictionary[15] = "PDA";
    cat_add_dictionary[16] = "ProjectManagement";
    cat_add_dictionary[17] = "Presentation";
    cat_add_dictionary[18] = "Spreadsheet";
    cat_add_dictionary[19] = "WordProcessor";
    cat_add_dictionary[20] = "2DGraphics";
    cat_add_dictionary[21] = "VectorGraphics";
    cat_add_dictionary[22] = "RasterGraphics";
    cat_add_dictionary[23] = "3DGraphics";
    cat_add_dictionary[24] = "Scanning";
    cat_add_dictionary[25] = "OCR";
    cat_add_dictionary[26] = "Photography";
    cat_add_dictionary[27] = "Publishing";
    cat_add_dictionary[28] = "Viewer";
    cat_add_dictionary[29] = "TextTools";
    cat_add_dictionary[30] = "DesktopSettings";
    cat_add_dictionary[31] = "HardwareSettings";
    cat_add_dictionary[32] = "Printing";
    cat_add_dictionary[33] = "PackageManager";
    cat_add_dictionary[34] = "Dialup";
    cat_add_dictionary[35] = "InstantMessaging";
    cat_add_dictionary[36] = "Chat";
    cat_add_dictionary[37] = "IRCClient";
    cat_add_dictionary[38] = "Feed";
    cat_add_dictionary[39] = "FileTransfer";
    cat_add_dictionary[40] = "HamRadio";
    cat_add_dictionary[41] = "News";
    cat_add_dictionary[42] = "P2P";
    cat_add_dictionary[43] = "RemoteAccess";
    cat_add_dictionary[44] = "Telephony";
    cat_add_dictionary[45] = "TelephonyTools";
    cat_add_dictionary[46] = "VideoConference";
    cat_add_dictionary[47] = "WebBrowser";
    cat_add_dictionary[48] = "WebDevelopment";
    cat_add_dictionary[49] = "Midi";
    cat_add_dictionary[50] = "Mixer";
    cat_add_dictionary[51] = "Sequencer";
    cat_add_dictionary[52] = "Tuner";
    cat_add_dictionary[53] = "TV";
    cat_add_dictionary[54] = "AudioVideoEditing";
    cat_add_dictionary[55] = "Player";
    cat_add_dictionary[56] = "Recorder";
    cat_add_dictionary[57] = "DiscBurning";
    cat_add_dictionary[58] = "ActionGame";
    cat_add_dictionary[59] = "AdventureGame";
    cat_add_dictionary[60] = "ArcadeGame";
    cat_add_dictionary[61] = "BoardGame";
    cat_add_dictionary[62] = "BlocksGame";
    cat_add_dictionary[63] = "CardGame";
    cat_add_dictionary[64] = "KidsGame";
    cat_add_dictionary[65] = "LogicGame";
    cat_add_dictionary[66] = "RolePlaying";
    cat_add_dictionary[67] = "Shooter";
    cat_add_dictionary[68] = "Simulation";
    cat_add_dictionary[69] = "SportsGame";
    cat_add_dictionary[70] = "StrategyGame";
    cat_add_dictionary[71] = "Art";
    cat_add_dictionary[72] = "Construction";
    cat_add_dictionary[73] = "Music";
    cat_add_dictionary[74] = "Languages";
    cat_add_dictionary[75] = "ArtificialIntelligence";
    cat_add_dictionary[76] = "Astronomy";
    cat_add_dictionary[77] = "Biology";
    cat_add_dictionary[78] = "Chemistry";
    cat_add_dictionary[79] = "ComputerScience";
    cat_add_dictionary[80] = "DataVisualization";
    cat_add_dictionary[81] = "Economy";
    cat_add_dictionary[82] = "Electricity";
    cat_add_dictionary[83] = "Geography";
    cat_add_dictionary[84] = "Geology";
    cat_add_dictionary[85] = "Geoscience";
    cat_add_dictionary[86] = "History";
    cat_add_dictionary[87] = "Humanities";
    cat_add_dictionary[88] = "ImageProcessing";
    cat_add_dictionary[89] = "Literature";
    cat_add_dictionary[90] = "Maps";
    cat_add_dictionary[91] = "Math";
    cat_add_dictionary[92] = "NumericalAnalysis";
    cat_add_dictionary[93] = "MedicalSoftware";
    cat_add_dictionary[94] = "Physics";
    cat_add_dictionary[95] = "Robotics";
    cat_add_dictionary[96] = "Spirituality";
    cat_add_dictionary[97] = "Sports";
    cat_add_dictionary[98] = "ParallelComputing";
    cat_add_dictionary[99] = "Amusement";
    cat_add_dictionary[100] = "Archiving";
    cat_add_dictionary[101] = "Compression";
    cat_add_dictionary[102] = "Electronics";
    cat_add_dictionary[103] = "Emulator";
    cat_add_dictionary[104] = "Engineering";
    cat_add_dictionary[105] = "FileTools";
    cat_add_dictionary[106] = "FileManager";
    cat_add_dictionary[107] = "TerminalEmulator";
    cat_add_dictionary[108] = "Filesystem";
    cat_add_dictionary[109] = "Monitor";
    cat_add_dictionary[110] = "Security";
    cat_add_dictionary[111] = "Accessibility";
    cat_add_dictionary[112] = "Calculator";
    cat_add_dictionary[113] = "Clock";
    cat_add_dictionary[114] = "TextEditor";
    cat_add_dictionary[115] = "Documentation";
    cat_add_dictionary[116] = "Adult";
    cat_add_dictionary[117] = "Core";
    cat_add_dictionary[118] = "KDE";
    cat_add_dictionary[119] = "GNOME";
    cat_add_dictionary[120] = "XFCE";
    cat_add_dictionary[121] = "GTK";
    cat_add_dictionary[122] = "Qt";
    cat_add_dictionary[123] = "Motif";
    cat_add_dictionary[124] = "Java";
    cat_add_dictionary[125] = "ConsoleOnly";

    // Buttons Init
    for (int i=0; i<13; i++) // for main
    {
        // getting object from builder to variable
        std::string name = "cat_main_";
        for (size_t j=0; j<cat_main_dictionary[i].size(); j++)
        {
            name += tolower(cat_main_dictionary[i][j]);
        }
        name += "_checkbutton";

        catseditor.cat_main_checkbutton[i] = GTK_TOGGLE_BUTTON(gtk_builder_get_object
                                                               (builder, name.c_str()));

        // setting label
        gtk_button_set_label(catseditor.cat_main_checkbutton[i], cat_main_dictionary[i].c_str());
    }
    for (int i=0; i<4; i++) // for system-reserved
    {
        // getting object from builder to variable
        std::string name = "cat_sys_";
        for (size_t j=0; j<cat_sys_dictionary[i].size(); j++)
        {
            name += tolower(cat_sys_dictionary[i][j]);
        }
        name += "_checkbutton";

        catseditor.cat_sys_checkbutton[i] = GTK_TOGGLE_BUTTON(gtk_builder_get_object
                                                               (builder, name.c_str()));

        // setting label
        gtk_button_set_label(catseditor.cat_sys_checkbutton[i], cat_sys_dictionary[i].c_str());
    }
    for (int i=0; i<126; i++) // for additional
    {
        // getting object from builder to variable
        std::string name = "cat_add_";
        for (size_t j=0; j<cat_add_dictionary[i].size(); j++)
        {
            name += tolower(cat_add_dictionary[i][j]);
        }
        name += "_checkbutton";

        catseditor.cat_add_checkbutton[i] = GTK_TOGGLE_BUTTON(gtk_builder_get_object
                                                               (builder, name.c_str()));

        // setting label
        gtk_button_set_label(catseditor.cat_add_checkbutton[i], cat_add_dictionary[i].c_str());
    }
}
