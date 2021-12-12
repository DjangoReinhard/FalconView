# User Manual FalconView

**FalconView** is a client application for the operation of CNC machines, which are controlled by *linuxCNC*.

**FalconView** is designed for multiclient environment, which means that the application feels different than usual desktop applications. Specifically this means
that commands are sent to *linuxCNC* server and **FalconView** processes the
response. Likewise, a second client application can send commands to the *linuxCNC*-
server, which results in status changes which in turn causes **FalconView** to change visual states.

**Note:** see [integration of **FalconView** in linuxCNC](integration)

To make it easier to learn how to use **FalconView**, the corresponding help will be displayed on every page change. There the operation by keyboard shortcuts
is described. If you want to stop this kind of help to be displayed, you can disable it in the settings ![settings](images/SK_Settings.png).

Nevertheless help can be displayed at any time by hitting **[F1]**.

## Structure of the application

the default appearance of **FalconView** looks like this:

![Overview](images/FV006.jpg)

- the *red area* (1) is the [**main application area**](reference).
This can be an editor, the 3D preview or whatever is needed to process user input.

- the *blue area* (2-5) are the *command buttons* arranged in so-called [**toolbars**](toolbars). The individual toolbars can be arbitrarily moved or otherwise arranged around the *main application area*. They can also be placed anywhere on the desktop.

- the green area (6-9) are [**status information**](info) about the machine state.
These mini windows can (like the toolbars) be freely moved and placed around
the central *main application area*. If a mini window is placed on top of another, then a notebook with several tabs is created on the fly.

**If you select in the settings that status outputs are to be displayed within the
3D preview, the appearance changes as follows:** !

![Inline](images/FV007.jpg)
