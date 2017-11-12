#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>

struct FileManagerDataStruct
{
    std::string name;
    std::string shortcut_type;
    std::string exec;
    std::string icon;
    bool start_in_terminal;
    bool notify_on_startup;
    bool hidden;
    std::string categories;
    std::string mimetypes;
    std::vector <std::string> unknown_data;
};

enum DataTags
{
    INIT,
    NAME,
    TYPE,
    EXEC,
    URL,
    ICON,
    TERMINAL,
    STARTUP_NOTIFY,
    HIDDEN,
    CATEGORIES,
    MIMETYPES,
    UNKNOWN /* UNKNOWN must be at the end of enum */
};

void filemanager_save(std::string, FileManagerDataStruct);
FileManagerDataStruct filemanager_load(std::string);
void filemanager_clear_file_info(FileManagerDataStruct*);
void filemanager_set_chmodx(std::string, bool);

#endif // FILEMANAGER_H
