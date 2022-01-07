# General tool management

was developed for machines with changer spindle to manage tool data independent of NC jobs and/or Cam system. For machines with conventional spindle, where the tool has to be recalibrated after each change, the general tool management can be switched off in the system settings ![Settings](images/SK_Settings.png).

To manage tools well-arranged, tool categories can be created. Every user can create categories according to his own ideas and wishes. There are no defaults for this.

In the left area the hierarchy of the tool categories is displayed as a tree.
On the top right, the tool list corresponds to the selected category. The exception is the tree root, which is predefined by the system. If this is selected, all tools are displayed in the right list.

In the lower right area, on overview of tool properties is displayed, i.e. with readable identifiers. **[Enter]** on a tool in the list starts the [edit mode](tooleditor). In the edit mode, **[Tab]** can be used to switch between the input fields. **[Escape]** cancels the editing, **[F10]** saves the changes.

Further key combinations after the image.

![ToolManager](images/ToolManager.jpg)

## Key combinations for the tool manager

- **[Tab]** - switch between tree and tool list

- **[Enter]** - in the tool list switches to the edit mode for the tool properties. In the category tree [Enter] is used to complete a copy or move action.

- **[Insert]** pressed in the category overview creates a new category, pressed in the tool overview creates a new tool.

- **[Del]** pressed in the category overview it deletes the category (if it does not contain any tools), pressed in the tool list it deletes the tool.

- **[Esc]** - exits the tool properties editing mode without saving the changes.

- **[F6]** - pressed in the category overview it is used to rename a category.

- **[F9]** starts the export of the selected tools. Currently only the LinuxCNC format is supported and the current tool file is overwritten. The previous tool list is of course saved before.

- **[F10]** - exits the editing mode of the tool properties and saves the changes.

- **[Space]** in the category overview it opens/closes the child view, in the tool list it is used to select a tool for the export
