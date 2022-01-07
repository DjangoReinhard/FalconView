# Datei-Verwalter

Der Datei-Verwalter wird von den Editoren zur Wahl einer Datei verwendet. Über Wahl des Verzeichnisses und anschließender Auswahl der Datei kann die gewünschte Datei bestimmt werden. **[Enter]** schließt die Auswahl ab und lädt die Datei.

![Datei-Verwalter](images/FileManager.jpg)

Der Datei-Verwalter zeigt links die Verzeichnisse in einer Baumstruktur an. Als Schutz werden nur Verzeichnisse unterhalb des (bei linuxCNC in der Ini-Datei) angegebenen Verzeichnisses angezeigt. Es können keine anderen Verzeichnisse oder Pfade eingegeben werden. Das Hauptverzeichnis kann als Ordner für GCode-Dateien angesehen werden.

## Folgende Funktionen/Tastenkombinationen werden unterstützt:

- **[Einfg]** - im Verzeichnisbaum erstellt ein neues Verzeichnis. Der gleiche Tastendruck in der Dateiliste erzeugt eine neue Datei.

- **[Pfeiltasten]** - ändern aktuelles Verzeichnis bwz. aktuelle Datei.

- **[Tab]** wechselt zwischen der Verzeichnis-Ansicht und der Dateiliste (rechts oben). In der Dateiliste werden die Dateien des ausgewählten Verzeichnisses angezeigt.

- **[Entf]** - im Verzeichnisbaum löscht ein Verzeichnis (nur wenn es leer ist) und [Entf] in der Dateiliste löscht die Datei.

- **[F5]** - in der Dateiliste markiert eine Datei zum *Kopieren*

- **[F6]** - in der Dateiliste markiert eine Datei zum *Verschieben*.

 **Kopieren** und **Verschieben** sind zweistufige Vorgänge: Zuerst muss eine Datei **markiert** werden. Anschließend muss im Verzeichnisbaum das **Zielverzeichnis ausgewählt** werden. Wird auf dem Zielverzeichnis **[Enter]** betätigt, so wird der Vorgang ausgeführt.
