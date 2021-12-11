# Einbindung in linuxCNC

*linuxCNC* besteht aus mehreren Hintergrund-Diensten, die über das Hilfsprogramm
"linuxcnc" gestartet werden. Die Konfiguration der Maschine erfolgt über eine
INI-Datei, die mehrere Sektionen enthält.

Die zur Integration wichtige Sektion ist **[DISPLAY]**. Dort ist hinterlegt, welche
Anwendung zur Steuerung von *linuxCNC* verwendet/gestartet werden soll.
Der entsprechende Eintrag lautet **DISPLAY = ...**

Der Wert auf der rechten Seite ist die Anwendung, die linuxcnc starten will. Der
Eintrag für **FalconView** sieht im einfachsten Falle so aus:

```
DISPLAY = FalconView
```

Damit das funktioniert, muss **FalconView** ohne Pfadangabe aufgerufen werden können
(z.B. via softlink in */usr/local/bin*)

Ansonsten muss in der Ini-Datei der absolute Pfad eingetragen werden, beispielsweise so:

```
DISPLAY = /opt/FalconView/FalconView
```
