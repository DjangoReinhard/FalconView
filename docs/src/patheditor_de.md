# aktiver Editor

Es gibt 2 NC-Editoren in **FalconView**:
- einen für die aktive NC-Datei ![Edit](images/SK_Edit.png), also der Job, der ausgeführt werden soll
- einen unabhängigen ![TestEdit](images/SK_TestEdit.png), um auch während der Job-Verarbeitung Änderungen an anderen
Dateien durchführen zu können.

Wenn zum NC-Editor gewechselt wird, dann ist der *Öffnen*-Knopf aktiv. **[Leertaste]**
reicht aus um die Aktion auszuführen. Zur Datei-Auswahl wird der
[Datei-Verwalter](filemanager) verwendet.

Der aktive Editor bearbeitet die NC-Datei, die als aktueller Job ausgeführt werden kann. Wurde die Datei verändert, kann die Ausführung nicht gestartet werden, bis die Datei gespeichert wurde.

Eine weitere Besonderheit des *aktiven Editors*: er ist **mit der 3D-Vorschau verbunden**, d.h. wenn der Cursor auf eine neue Zeile geführt wird, dann ist die neue Zeile auch in der 3D-Vorschau die aktuelle Zeile.
**Wenn im Editor die Zeile gewechselt wird, dann wird der entsprechende Werkzeugpfad in der 3D-Vorschau gekennzeichnet.**

Neben den übliche Tastenkombinationen zur Dateibearbeitung werden folgende **Tastenkombinationen** unterstützt:

- **[Strg + S]** speichert geänderte Dateien. Dabei wird die bisherige Datei als Backup umbenannt.

- **[Strg + F]** öffnet einen Eingabedialog um nach einem Text zu suchen.

![NC-Editor](images/NCEditor.jpg)
