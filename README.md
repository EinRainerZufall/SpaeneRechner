![GitHub](https://img.shields.io/github/license/EinRainerZufall/SpaeneRechner)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/EinRainerZufall/SpaeneRechner)
![GitHub branch checks state](https://img.shields.io/github/checks-status/EinRainerZufall/SpaeneRechner/main)
![GitHub all releases](https://img.shields.io/github/downloads/EinRainerZufall/SpaeneRechner/total)
![GitHub repo size](https://img.shields.io/github/repo-size/EinRainerZufall/SpaeneRechner)

# SpaeneRechner

Das ist ein Schnittdaten Rechner zum Berechnen aller wichtigen Daten beim Fräsen und Drehen,
sowie weitere nützliche Features.


---
zum selber Compilieren:
- Windows
  - min Win 10 x64
  - [Ms Visual C++ Redistributable x64](https://support.microsoft.com/de-de/topic/aktuelle-unterst%C3%BCtzte-downloads-f%C3%BCr-visual-c-2647da03-1eea-4433-9aff-95f26a218cc0)
  - [qt Creator](https://www.qt.io/)
  - kein Shadow build
  - KIT: Desktop Qt 6.2.2 MSVC2019 64bit
  - [xlnt lib](https://github.com/tfussell/xlnt)
  - nach dem Release build in der MSVC Konsole `windeployqt` eingeben
- macOS
  - git clone git@github.com:EinRainerZufall/SpaeneRechner.github
  - cd SpaeneRechner
  - ./build-xlnt.sh (This builds the current master, 1.5.0 doesn't work on macOS)
  - qmake -o Makefile .
  - make
- linux
