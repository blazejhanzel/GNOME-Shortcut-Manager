# GNOME Shortcut Manager

[![GitHub release](https://img.shields.io/github/release/blahax2g/GNOME-Shortcut-Manager.svg?style=flat-square)](https://github.com/blahax2g/GNOME-Shortcut-Manager/releases)
![GitHub Release Date](https://img.shields.io/github/release-date/blahax2g/GNOME-Shortcut-Manager.svg?style=flat-square)
![Github Releases](https://img.shields.io/github/downloads/blahax2g/GNOME-Shortcut-Manager/total.svg?style=flat-square)
![GitHub repo size in bytes](https://img.shields.io/github/repo-size/blahax2g/GNOME-Shortcut-Manager.svg?style=flat-square)
[![license](https://img.shields.io/github/license/blahax2g/GNOME-Shortcut-Manager.svg?style=flat-square)](https://github.com/blahax2g/GNOME-Shortcut-Manager/blob/master/LICENSE)

GNOME Shortcut Manager is simple and free (GPL3 licensed) application that help you creates or edit shortcuts
for applications in GNOME Dash (application browser).

## How to use GNOME Shortcut Manager?
1. Download version you want from "Release" section (I recommend the newest version for you, but it's your choose).
2. Run "GNOME Shortcut Manager" file with sudo access and executable permissions.
3. On the toolbar at the top of application you have options, in sequence:
New, Open, Save, Save As, Delete, About, Quit (this is too simple to explain how it works :P)

![](https://raw.githubusercontent.com/blahax2g/GNOME-Shortcut-Manager/master/docs/img/menu_editor_v1-1.png)

### Editing / Creating shorcut
1. Open existing file using "Open" toolbar button or just type text into fields to create new file.
2. Regardless you open existing file or create new one, you have some fields to fill, in sequence:
* *Display name* - This name will be shown in GNOME Dash
* *Shortcut type* - You can choose: Application, Link or Directory; This is to what is shortcut connected.
* *Executable file/path* - This is what will be run, when you click this shortcut.
* *Icon file/path* - You can set whatever image you want, this will be displayed in GNOME Dash.
* *Start in terminal?* - Default is false; Set this true, if application should be started from terminal.
* *Notify on startup?* - Default is true; You will have notification if application start in background.
* *Hide shortcut in dash?* - Default is false; You can turn it on if you don't want to remove shortcut, but you don't want to have it in dash.
* *Categories [Special option]* - You can manually write categories there, separate them with ";"
or you can use Categories Editor. Just click "..." button at the right of entry field.
* *Mimetypes [Special option]* - Use it only if you know system-defined mimetypes, separate them with ";".
I'm going to add simple editor for this field in the future.
3. Save file using "Save" or "Save as" button from toolbar.

### Deleting shortcut
To delete shortcut:
1. Open shortcut file using "Open" button (second from left on toolbar).
2. Click Delete button (fifth from left, looks like trash bin).
3. If you have permissions to edit this file, it was removed.
