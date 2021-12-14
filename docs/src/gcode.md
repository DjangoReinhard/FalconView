# LinuxCNC "G-Code" Quick Reference

## Motion
**(X Y Z A B C U V W apply to all motions)**

| Code | Parameters | Description |
| --- | --- | --- |
| [G0](gcode/g-code.html#gcode:g0) | | Rapid Move |
| [G1](gcode/g-code.html#gcode:g1) | | Linear Move |
| [G2](gcode/g-code.html#gcode:g2-g3) | I J K or R, P | Arc Move clockwise |
| [G3](gcode/g-code.html#gcode:g2-g3) | I J K or R, P | Arc Move counterclockwise |
| [G4](gcode/g-code.html#gcode:g4) | P | Dwell |
| [G5](gcode/g-code.html#gcode:g5) | I J P Q | Cubic Spline |
| [G5.1](gcode/g-code.html#gcode:g5.1) | I J | Quadratic Spline |
| [G5.2](gcode/g-code.html#gcode:g5.2-g5.3) | P L | NURBS |
| [G38.2 - G38.5](gcode/g-code.html#gcode:g38) | | Straight Probe |
| [G33](gcode/g-code.html#gcode:g33) | K ($) | Spindle Synchronized Motion |
| [G33.1](gcode/g-code.html#gcode:g33.1) | K ($) | Rigid Tapping |

## Canned cycles
**(X Y Z or U V W apply to canned cycles, depending on active plane)**

| Code | Parameters | Description |
| --- | --- | --- |
| [G80](gcode/g-code.html#gcode:g80) | | Cancel Canned Cycle |
| [G81](gcode/g-code.html#gcode:g81) | R L (P) | Drilling Cycle |
| [G82](gcode/g-code.html#gcode:g82) | R L (P) | Drilling Cycle, Dwell |
| [G83](gcode/g-code.html#gcode:g83) | R L Q | Drilling Cycle, Peck |
| [G84](gcode/g-code.html#gcode:g84) | R L (P) ($) | Right-hand Tapping Cycle, Dwell |
| [G73](gcode/g-code.html#gcode:g73) | R L Q | Drilling Cycle, Chip Breaking |
| [G74](gcode/g-code.html#gcode:g74) | R L (P) ($) | Left-hand Tapping Cycle, Dwell |
| [G85](gcode/g-code.html#gcode:g85) | R L (P) | Boring Cycle, Feed Out |
| [G89](gcode/g-code.html#gcode:g89) | R L (P) | Boring Cycle, Dwell, Feed Out |
| [G76](gcode/g-code.html#gcode:g76) | P Z I J R K Q H L E ($) | Threading Cycle |

## Tool Length Offset

| Code | Parameters | Description |
| --- | --- | --- |
| [G43](gcode/g-code.html#gcode:g43) | H | Tool Length Offset |
| [G43.1](gcode/g-code.html#gcode:g43.1) | | Dynamic Tool Length Offset |
| [G43.2](gcode/g-code.html#gcode:g43.2) | H | Apply additional Tool Length Offset |
| [G49](gcode/g-code.html#gcode:g49) | | Cancel Tool Length Compensation |

## Cutter Radius Compensation

| Code | Parameters | Description |
| --- | --- | --- |
| [G40](gcode/g-code.html#gcode:g40) | | Compensation Off |
| [G41,G42](gcode/g-code.html#gcode:g41-g42) | D | Cutter Compensation |
| [G41.1, G42.1](gcode/g-code.html#gcode:g41.1-g42.1) | D L | Dynamic Cutter Compensation |

## Distance Mode

| Code | Parameters | Description |
| --- | --- | --- |
| [G90, G91](gcode/g-code.html#gcode:g90-g91) | | Distance Mode |
| [G90.1, G91.1](gcode/g-code.html#gcode:g90.1-g91.1) | | Arc Distance Mode |
| [G7](gcode/g-code.html#gcode:g7) | | Lathe Diameter Mode |
| [G8](gcode/g-code.html#gcode:g8) | | Lathe Radius Mode |

## Feed Rate Mode

| Code | Parameters | Description |
| --- | --- | --- |
| [G93, G94, G95](gcode/g-code.html#gcode:g93-g94-g95) | S ($) | Feed Rate Mode |

## Spindle Control

| Code | Parameters | Description |
| --- | --- | --- |
| [M3, M4, M5](gcode/m-code.html#mcode:m3-m4-m5) | S ($) | Spindle Control |
| [M19](gcode/m-code.html#mcode:m19) | R Q (P) ($) | Orient Spindle |
| [G96, G97](gcode/g-code.html#gcode:g96-g97) | S D ($) | Spindle Control Mode |

## Coolant

| Code | Parameters | Description |
| --- | --- | --- |
| [M7, M8, M9](gcode/m-code.html#mcode:m7-m8-m9) | | Coolant Control |


## Stopping

| Code | Parameters | Description |
| --- | --- | --- |
| [M0, M1](gcode/m-code.html#mcode:m0-m1) | | Program Pause |
| [M2, M30](gcode/m-code.html#mcode:m2-m30) | | Program End |
| [M60](gcode/m-code.html#mcode:m60) | | Pallet Change Pause |

## Units

| Code | Parameters | Description |
| --- | --- | --- |
| [G20, G21](gcode/g-code.html#gcode:g20-g21) | | Units (inch, mm) |
| Plane Selection | (affects G2, G3, G81…G89, G40…G42) |
| [G17 - G19.1](gcode/g-code.html#gcode:g17-g19.1) | | Plane Select |

## Path Control Mode

| Code | Parameters | Description |
| --- | --- | --- |
| [G61 G61.1](gcode/g-code.html#gcode:g61) | | Exact Path Mode |
| [G61.1](gcode/g-code.html#gcode:g61.1) | | Exact Stop Mode |
| [G64](gcode/g-code.html#gcode:g64) | P Q | Path Blending |
| | --- |
| [G98, G99](gcode/g-code.html#gcode:g98-g99) | | Canned Cycle Return Level |

## Other Modal Codes

| Code | Parameters | Description |
| --- | --- | --- |
| [F](gcode/other-code.html#sec:set-feed-rate) | | Set Feed Rate |
| [S](gcode/other-code.html#sec:set-spindle-speed) | ($) | Set Spindle Speed |
| [T](gcode/other-code.html#sec:select-tool) | | Select Tool) |
| [M48, M49](gcode/m-code.html#mcode:m48-m49) | | Speed and Feed Override Control |
| [M50](gcode/m-code.html#mcode:m50) | P0 (off) or P1 (on) | Feed Override Control |
| [M51](gcode/m-code.html#mcode:m51) | P0 (off) or P1 (on) ($) | Spindle Speed Override Control |
| [M52](gcode/m-code.html#mcode:m52) | P0 (off) or P1 (on) | Adaptive Feed Control |
| [M53](gcode/m-code.html#mcode:m53) | P0 (off) or P1 (on) | Feed Stop Control |
| [G54-G59.3](gcode/g-code.html#gcode:g54-g59.3) | | Select Coordinate System |


## Flow-control Codes

| Code | Parameters | Description |
| --- | --- | --- |
| [o sub](gcode/o-code.html#ocode:subroutines) | | Subroutines, sub/endsub call |
| [o while](gcode/o-code.html#ocode:looping) | | Looping, while/endwhile do/while |
| [o if](gcode/o-code.html#ocode:conditional) | | Conditional, if/else/endif |
| [o repeat](gcode/o-code.html#ocode:repeat) | | Repeat a loop of code |
| [[]](gcode/o-code.html#ocode:indirection) | | Indirection |
| [o call](gcode/o-code.html#ocode:calling-files) | | Call named file |
| [M70](gcode/m-code.html#mcode:m70) | | Save modal state |
| [M71](gcode/m-code.html#mcode:m71) | | Invalidate stored state |
| [M72](gcode/m-code.html#mcode:m72) | | Restore modal state |
| [M73](gcode/m-code.html#mcode:m73) | | Save and Auto-restore modal state |

## Input/Output Codes

| Code | Parameters | Description |
| --- | --- | --- |
| [M62 - M65](gcode/m-code.html#mcode:m62-m65) | P | Digital Output Control |
| [M66](gcode/m-code.html#mcode:m66) | P E L Q | Wait on Input |
| [M67](gcode/m-code.html#mcode:m67) | T | Analog Output,Synchronized |
| [M68](gcode/m-code.html#mcode:m68) | T | Analog Output, Immediate |

## Non-modal Codes

| Code | Parameters | Description |
| --- | --- | --- |
| [M6](gcode/m-code.html#mcode:m6) | T | Tool Change |
| [M61](gcode/m-code.html#mcode:m61) | Q | Set Current Tool |
| [G10 L0](gcode/g-code.html#gcode:g10-l0) | | Reload Tool Table Data |
| [G10 L1](gcode/g-code.html#gcode:g10-l1) | P Q R | Set Tool Table |
| [G10 L10](gcode/g-code.html#gcode:g10-l10) | P | Set Tool Table |
| [G10 L11](gcode/g-code.html#gcode:g10-l11) | P | Set Tool Table |
| [G10 L2](gcode/g-code.html#gcode:g10-l2) | P R | Set Coordinate System |
| [G10 L20](gcode/g-code.html#gcode:g10-l20) | P | Set Coordinate System |
| [G28, G28.1](gcode/g-code.html#gcode:g28-g28.1) | | Go/Set Predefined Position |
| [G30, G30.1](gcode/g-code.html#gcode:g30-g30.1) | | Go/Set Predefined Position |
| [G53](gcode/g-code.html#gcode:g53) | | Move in Machine Coordinates |
| [G52, G92](gcode/g-code.html#gcode:g92) | | Coordinate System Offset |
| [G92.1, G92.2](gcode/g-code.html#gcode:g92.1-g92.2) | | Reset G92 Offsets |
| [G92.3](gcode/g-code.html#gcode:g92.3) | | Restore G92 Offsets |
| [M101 - M199](gcode/m-code.html#mcode:m100-m199) | P Q | User Defined Commands |


## Comments & Messages

| Code | Parameters | Description |
| --- | --- | --- |
| [; (…)](gcode/overview.html#gcode:comments) | | Comments |
| [(MSG,…)](gcode/overview.html#gcode:messages) | | Messages |
| [(DEBUG,…)](gcode/overview.html#gcode:debug) | | Debug Messages |
| [(PRINT,…)](gcode/overview.html#gcode:print) | | Print Messages |
