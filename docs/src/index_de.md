# Benutzerhandbuch FalconView

**FalconView** ist eine Client-Anwendung zur Bedienung von CNC-Maschinen, welche mit
*linuxCNC* gesteuert werden.

**FalconView** wurde für eine Multiclient-Umgebung entworfen, was bedeutet, dass sich
die Anwendung möglicherweise anders anfühlt, als übliche Desktop-Anwendungen. Konkret bedeutet das,
dass Befehle zum *linuxCNC*-Server geschickt werden und **FalconView** die Antwort vom Server
verarbeitet. Genauso kann eine zweite Client-Anwendung Befehle an den *linuxCNC*-
Server schicken, welches Statusänderungen zur Folge hat, die in **FalconView**
angezeigt werden.

**Hinweis:** siehe [Einbindung von **FalconView** in linuxCNC](integration)

Zum leichteren Erlernen der Bedienung von **FalconView** wird bei jedem Seitenwechsel
die dazugehörige Hilfe eingeblendet. Dort wird die Bedienung per Tastaturkürzel
beschrieben.

Soll die Hilfe nicht mehr bei jedem Seitenwechsel angezeigt werden, kann dies in den Einstellungen
![Einstellungen](images/SK_Settings.png) abgestellt werden.

Natürlich kann zu jedem Zeitpunkt die Hilfe mit **[F1]** angezeigt werden.

## Aufbau der Anwendung

das Standard-Erscheinungsbild von **FalconView** sieht folgendermaßen aus:

![Übersicht](images/FV006.jpg)

- der *rote Bereich* (1) ist der feste [**Hauptanwendungbereich**](reference).
Dies kann ein Editor, die 3D-Vorschau oder sonst ein Gebilde sein, welches Benutzereingaben verarbeitet.

- der *blaue Bereich* (2-5) sind die *Befehlstasten* in sogenannten [**Werkzeugleisten**](toolbars) angeordnet. Die einzelnen Werkzeugleisten können **beliebig verschoben** oder anderweitig rund um den *Hauptanwendungsbereich*
angeordnet werden. Sie können aber auch frei auf dem Bildschirm platziert werden.

- der grüne Bereich (6-9) sind [**Status-Informationen**](info) zum Maschinenzustand.
Diese Minifenster können (wie die Werkzeugleisten) **frei verschoben** und rund um den zentralen "Hauptanwendungbereich" angeordnet werden. Werden zwei Minifenster übereinander platziert, dann entsteht automatisch ein Notebook mit mehreren
Reitern.

## Variante 1

Wird in den Einstellungen ausgewählt, dass **Statusausgaben innerhalb der
3D-Vorschau** angezeigt werden sollen, dann ändert sich das Erscheinungsbild wie folgt. Die Einstellung kann bei kleinen Bildschirmen von Vorteil sein.

![Inline](images/FV007.jpg)

## Variante 2

In den Einstellungen kann ausgewählt werden, dass nur die 3D-Vorschau das Anwendungszentrum darstellt. Dann werden die Editoren und anderen Hauptfenster in einem verschiebbaren Hilfsfenster angezeigt, welches **beliebig verschoben** werden kann.

![Inline](images/FVV3.jpg)
