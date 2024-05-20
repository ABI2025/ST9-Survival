# st9

[Documentation](doc/readme.md)

# Tower Defense Spiel

Dieses Projekt ist ein Tower Defense Spiel, das in C++ mit der SFML-Bibliothek entwickelt wurde. Das Spiel beinhaltet den Bau von Türmen zur Verteidigung gegen Wellen von Gegnern. Das Spiel umfasst mehrere Komponenten wie die Hauptspielschleife, ein Bausystem zum Platzieren von Türmen, ein Soundsystem, ein Kamerasystem und verschiedene Spielelemente einschließlich Türmen, Mauern und Gegnern.

## Projektübersicht

### Hauptdateien

- **main.cpp**: Einstiegspunkt des Spiels. Initialisiert das Menü und behandelt plattformspezifische Einstiegspunkte für Windows und andere Plattformen.
- **Game.cpp/h**: Verwaltet den allgemeinen Spielzustand, einschließlich Rendering der Karte, Spiellogik und Verwaltung von Ressourcen wie Geld.

### GUI und Menü

- **Gui.cpp/h**: Verwaltet die grafische Benutzeroberfläche mit ImGui und SFML. Beinhaltet Initialisierungsfunktionen und die Verwaltung von GUI-Elementen.
- **Menu.cpp/h**: Verwaltet das Hauptmenü des Spiels, einschließlich Optionen zum Starten des Spiels, Ändern von Einstellungen und Anzeigen der Geschichte.

### Gameplay-Komponenten

- **BuildSystem.cpp/h**: Verwaltet das Bausystem im Spiel. Ermöglicht es den Spielern, Türme zu bauen und zu platzieren.
- **Tower.cpp/h**: Definiert die Türme, ihre Eigenschaften und ihr Verhalten im Spiel.
- **Wall.cpp/h**: Definiert die Mauern, die gebaut werden können, um den Weg der Gegner zu blockieren.
- **Projectile.cpp/h**: Definiert die Projektile, die von den Türmen abgefeuert werden.
- **EnemyManager.cpp/h**: Verwaltet die Gegner im Spiel, einschließlich ihrer Erstellung, Bewegung und Angriffslogik.
- **Wave.cpp/h**: Verwaltet die Wellen von Gegnern, die das Spielfeld angreifen.

### Spieler und Gebäude

- **Player.cpp/h**: Definiert den Spielercharakter und seine Interaktionen im Spiel.
- **MainBuilding.cpp/h**: Definiert das Hauptgebäude, das der Spieler verteidigen muss.
- **healthbar.cpp/h**: Verwaltet die Gesundheitsleiste des Spielers und anderer Einheiten.

### Soundsystem

- **Sounds.cpp/h**: Verwaltet das Soundsystem im Spiel, einschließlich Hintergrundmusik und Soundeffekten.

### Kamera

- **camera.cpp/h**: Verwaltet die Kamerasteuerung im Spiel, einschließlich Bewegungen und Anpassungen an die Fenstergröße.

### Zusätzliche Dateien

- **Optionen.cpp/h**: Verwaltet die Optionen und Einstellungen des Spiels, einschließlich Lautstärkeregelung und grafischen Einstellungen.
- **GameWindow.cpp/h**: Platzhalter für das GameWindow, das das Hauptfenster des Spiels darstellt.
- **Utils/Utils.h**: Hilfsfunktionen und -klassen, die im gesamten Projekt verwendet werden.

