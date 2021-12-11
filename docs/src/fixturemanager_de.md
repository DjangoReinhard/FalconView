# Koordinatensysteme

![FixtureMgr](images/FixtureMgr.jpg)

Unter **Koordinatensysteme** können die Nullpunkte für verschiedene Koordinatensysteme
hinterlegt werden. Der Verwalter bietet 10 Editoren an. Die Anzahl der Eingabefelder
hängt von der konfigurierten Maschine ab. Bei einer Maschine mit 3 Achsen werden
3 Eingabefelder angeboten, bei einer mit 9 Achsen eben 9 Eingabefelder.

Der erste Editor ist für Korrekturen vorgesehen, welche für alle Koordinatensysteme
gelten. **G54** ist das erste Koordinatensystem und kann über die Tastenkombination
**[Strg+1]** aktiviert werden. Entsprechend gilt **[Strg+2]** für **G55**, usw.
**[Strg+0]** gilt für die Korrektur-Werte. **[Tab]** wechselt zwischen den Eingabefeldern.

## Arbeitsweise

Die Maschine wird zur gewünschten Position (einer Achse) gefahren. Anschließend
kann hier der gewünschte Anzeigewert eingegeben werden. Üblicherweise wird man **0**
eingeben wollen. Der Editor rechnet die Eingabe in das Maschinenkoordinatensystem
um und die Anzeige der relativen Position zeigt danach den gewünschten Wert.

Will man beispielsweise den Nullpunkt in die Mitte des Werkstückes legen, wird
eine Seite angetastet und auf **0** gesetzt. Anschließend wird die gegenüberliegende
Seite angetastet. Zeigt die relative Positionsanzeige den Wert *184,6* - dann kann
im entsprechenden Eingabefeld die Hälfte davon eingegeben werden. Also *92,3*
Danach liegt der Nullpunkt dieser Achse in der Mitte des Werkstückes.
