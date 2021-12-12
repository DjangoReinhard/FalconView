# File manager

The file manager is used by the editors to select a file. By selecting first the directory and then selecting the file, the desired file is choosen. **[Enter]** completes the selection.

![File Manager](images/FileManager.jpg)

The file manager shows the directories in a tree structure on the left. As protection only directories below the specified directory are shown. No other directories or paths can be entered. The main directory can be seen as a folder for GCode files.

New directories can be created with **[Insert]** and **empty** folders can be deleted with **[Del]**. With **arrow keys** (up/down) the selected directory can be changed. *Right arrow* shows subdirectories (if any), *Left arrow* hides the subdirectories.

**[Tab]** switches between the directory view and the file list (top right). The file list shows the files of the selected directory. With arrow keys (up/down) the current file can be changed. In the lower area on the right side a preview of the current file is displayed. With **[Insert]** a new file can be created, with **[Delete]** a file can be deleted.
**[F5]** marks a file for *copying*, **[F6]** marks it for *moving*. *Copy* and *Move* are two-step operations. First a file must be **marked**. Then the destination directory must be selected in the directory tree. If **[Enter]** is pressed on the target directory, the operation is executed.
