# Werkzeugverwaltung für linuxCNC

Die Werkzeug-Verwaltung der linuxCNC-Werkzeuge gibt es in zwei unterschiedlichen
Ausführungen (je nachdem welche Maschine konfiguriert ist).
Die Felder können in der Tabelle bearbeitet werden. Die Liste wechselt dann in
Bearbeitungsmodus. **[F10]** speichert die Änderung, **[Esc]** verwirft die
Änderung.

## Werkzeug-Verwaltung für Drehmaschinen

![Lathe](images/LCToolMgr_L.jpg)

Die Felder im einzelnen:

  - *Platz* ist der Platz im Revolver
  - *Z* der Offset in Z-Richtung
  - *X* der Offset in X-Richtung
  - *Durchmesser* ist der Durchmesser an der Werkzeugspitze
  - *Q* ist der Quadrant der Werkzeug-Ausrichtung
  - *FW* ist der Front-Winkel
  - *RW* ist der Rück-Winkel


## Werkzeug-Verwaltung für Fräsen

![Mill](images/LCToolMgr_M.jpg)

Die Felder im einzelnen:

  - *Platz* ist der Platz im Werkzeugwechsler
  - *Länge* ist die Länge in Z-Richtung
  - *Durchm* ist der Werkzeug-Durchmesser
  - *S* ist das Symbol des Werkzeuges

## Bilder in Werkzeug-Tabelle und Werkzeug-Info
das letzte (optionale) Feld in der Werkzeugtablle von linuxCNC ist ein Kommentar bis Zeilenende. Wenn man dort nach einem senkrechten Strich "|" eine Kategorie für das Werkzeug einträgt, können Bilder passend zur Kategorie geladen und angezeigt werden.

Dazu muss in der INI-Datei von linuxCNC in der **DISPLAY**-Gruppe ein Eintrag für das Bilderverzeichnis erstellt werden.
```
TOOL_IMAGE_DIR = ~/linuxcnc/tools
```
Die Wellenlinie (~) steht für das Basisverzeichnis des aktuellen Benutzers.

### Beispiel:
in der Werkzeugtablle gibt es folgenden Eintrag:
```
T31 P25 Z105.000 D10.200 ;10,2mm Spiralbohrer  | Spiralbohrer
```
In der Ini-Datei wurde das Verzeichnis wie oben angelegt.
Gibt es dort eine Datei ```Spiralbohrer.jpg```, dann wird diese in der Übersicht und in der Werkzeuginfo angezeigt.
Die Bilddatei hat eine Größe von 150x150 Pixel. Für die Übersicht werden kleinere Bilder erzeugt.
