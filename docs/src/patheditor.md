# active editor ![Edit](images/SK_Edit.png)

When switching to the NC editor, the *Open* button is active. **[Space]**
is sufficient to execute the action. For file selection the
[File manager](filemanager) is used.

The active editor edits the NC file, which can be executed as current job. If the file is modified, execution cannot be started until the file is saved.

There are 2 NC editors in **FalconView**:
- one for the active NC file ![Edit](images/SK_Edit.png), i.e. the job that is to be executed
- an independent ![TestEdit](images/SK_TestEdit.png), to be able to make changes to other files even during job processing.

A special feature of the *active editor*: it is **connected** to the 3D preview, i.e. when the cursor is moved to a new line, the new line is also the current line in the 3D preview.
**When the line is changed in the editor, the corresponding toolpath is highlighted in the 3D preview.**

In addition to the usual key combinations for file editing, the following **key combinations** are supported:

- **[Ctrl + S]** saves modified files. The previous file is renamed as a backup.

- **[Ctrl + F]** opens an input dialog to search for a text.

![NC-Editor](images/NCEditor.jpg)
