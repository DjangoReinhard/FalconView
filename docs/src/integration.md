# Integration in linuxCNC

*linuxCNC* consists of several background services, which are started by the utility program
"linuxcnc". The configuration of the machine is done via an
INI file, which contains several sections.

The section important for integration is **[DISPLAY]**. There is stored, which
application to be used/started to control *linuxCNC*.
The corresponding entry is **DISPLAY = ...**.

The value on the right side is the application linuxcnc wants to start. The
entry for **FalconView** looks in the simplest case like this:

```
DISPLAY = FalconView
```

For this to work, **FalconView** must be able to be called without path specification
(e.g. via softlink in */usr/local/bin*)

Otherwise the absolute path must be entered in the ini file, for example like this:

```
DISPLAY = /opt/FalconView/FalconView
```

