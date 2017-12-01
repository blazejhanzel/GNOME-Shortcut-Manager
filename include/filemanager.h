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
void filemanager_delete_file(std::string, bool);

#endif // FILEMANAGER_H
