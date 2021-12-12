# coordinate systems

![FixtureMgr](images/FixtureMgr.jpg)

Under **Coordinate systems** the zero points for different coordinate systems can be stored. The *FixtureManager* offers 10 editors. The number of input fields
depends on the configured machine. For a machine with 3 axes
3 input fields are offered, for one with 9 axes 9 input fields.

The first editor is intended for fixtures, which are applied on every coordinate system.
**G54** is the first coordinate system and can be activated via the key combination
**[Ctrl+1]**. Correspondingly, **[Ctrl+2]** applies to **G55**, and so on.
**[Ctrl+0]** applies to the general fixtures. **[Tab]** switches between the input fields.

## Mode of operation

The machine is moved to the desired position (of an axis). Then
the desired display value can be entered here. Usually you will want to enter **0**. The editor converts the input into the machine coordinate system
and the display of the relative position then shows the desired value.

If, for example, you want to place the zero point at the center of the workpiece,
one side is probed and set to **0**. Then the opposite side is probed.
If the relative position display shows the value *184.6* - then you can
enter half in the corresponding input field. In this case *92,3*.
After doing so the zero point of this axis is at the center of the workpiece.
