#include "../include/filemanager.h"

void filemanager_save(std::string filename, FileManagerDataStruct data)
{
    std::fstream f;
    f.open(filename, std::ios::out | std::ios::trunc);
    if (f.is_open() == false)
        throw 1;

    f << "[Desktop Entry]" << std::endl;
    f << "Name=" << data.name << std::endl;
    f << "Type=" << data.shortcut_type << std::endl;
    if (data.shortcut_type == "Link")
    {
        f << "URL=" << data.exec << std::endl;
    }
    else
    {
        f << "Exec=" << data.exec << std::endl;
    }
    f << "Icon=" << data.icon << std::endl;
    f << "Terminal=" << [](bool data)->std::string { return (data) ? "true" : "false"; }(data.start_in_terminal) << std::endl;
    f << "StartupNotify=" << [](bool data)->std::string { return (data) ? "true" : "false"; }(data.notify_on_startup) << std::endl;
    f << "NoDisplay=" << [](bool data)->std::string { return (data) ? "true" : "false"; }(data.hidden) << std::endl;
    f << "Categories=" << data.categories << std::endl;
    f << "MimeType=" << data.mimetypes << std::endl;

    for (int i=0; i<data.unknown_data.size(); i++) // FIXME: Doesn't read data when int => size_t
    {
        f << data.unknown_data[i] << std::endl;
    }

    f.close();
}

FileManagerDataStruct filemanager_load(std::string filename)
{
    std::fstream f;
    f.open(filename, std::ios::in);
    if (f.is_open() == false)
        throw 1;
    FileManagerDataStruct datastruct;
    std::map <int, std::string> data_tags;

    // get new datastruct be clean
    filemanager_clear_file_info(&datastruct);

    // setting up data_tags map
    data_tags[INIT] = "[Desktop Entry]";
    data_tags[NAME] = "Name=";
    data_tags[TYPE] = "Type=";
    data_tags[EXEC] = "Exec=";
    data_tags[URL] = "URL=";
    data_tags[ICON] = "Icon=";
    data_tags[TERMINAL] = "Terminal=";
    data_tags[STARTUP_NOTIFY] = "StartupNotify=";
    data_tags[HIDDEN] = "NoDisplay=";
    data_tags[CATEGORIES] = "Categories=";
    data_tags[MIMETYPES] = "MimeType=";

    std::string data;
    while (!f.eof()) // if not on the end of file
    {
        getline(f,data);
        int str; // string temporary info variable // FIXME: Doesn't read data when int => unsigned int
        int i;

        for (i=0; i <= UNKNOWN; i++)
        {
            if (i != UNKNOWN)
                str = data.find(data_tags[i]);
            if (str != std::string::npos)
            {
                switch (i)
                {
                case INIT:
                    break;
                case NAME:
                {
                    datastruct.name = data;
                    if (data.find("GenericName=") != std::string::npos) // it can be Name or GenericName in some cases (especially in KDE-created apps)
                    {
                        datastruct.name.erase(str-7, data_tags[i].size()+7);
                    }
                    else
                    {
                        datastruct.name.erase(str, data_tags[i].size());
                    }
                    break;
                }
                case TYPE:
                {
                    if (data.find("MimeType=") == std::string::npos) // can be mistake with Type and MimeType, MimeType must be ignored
                    {
                        datastruct.shortcut_type = data;
                        datastruct.shortcut_type.erase(str, data_tags[i].size());
                    }
                    break;
                }
                case EXEC:
                case URL:
                    datastruct.exec = data;
                    datastruct.exec.erase(str, data_tags[i].size());
                    break;
                case ICON:
                    datastruct.icon = data;
                    datastruct.icon.erase(str, data_tags[i].size());
                    break;
                case TERMINAL:
                    datastruct.start_in_terminal = (data.find("true") != std::string::npos) ? true : false;
                    break;
                case STARTUP_NOTIFY:
                    datastruct.notify_on_startup = (data.find("true") != std::string::npos) ? true : false;
                    break;
                case HIDDEN:
                    datastruct.hidden = (data.find("true") != std::string::npos) ? true : false;
                    break;
                case CATEGORIES:
                    datastruct.categories = data;
                    datastruct.categories.erase(str, data_tags[i].size());
                    break;
                case MIMETYPES:
                    datastruct.mimetypes = data;
                    datastruct.mimetypes.erase(str, data_tags[i].size());
                    break;
                }
                break;
            }
            else if (i == UNKNOWN)
            {
                datastruct.unknown_data.push_back(data);
                break;
            }
        }
        data.clear();
    }

    f.close();

    return datastruct;
}

void filemanager_clear_file_info(FileManagerDataStruct* datastruct)
{
    datastruct->name.clear();
    datastruct->shortcut_type.clear();
    datastruct->exec.clear();
    datastruct->icon.clear();
    datastruct->start_in_terminal = false;
    datastruct->notify_on_startup = true;
    datastruct->hidden = false;
    datastruct->categories.clear();
    datastruct->mimetypes.clear();
}

void filemanager_set_chmodx(std::string filename, bool as_root)
{
    std::string command;
    if (as_root == true)
        command = "sudo chmod +x " + filename;
    else
        command = "chmod +x " + filename;
    system(command.c_str());
}

void filemanager_delete_file(std::string filename, bool as_root)
{
    std::string command;
    if (as_root == true)
        command = "sudo rm " + filename;
    else
        command = "rm " + filename;
    system(command.c_str());
}
