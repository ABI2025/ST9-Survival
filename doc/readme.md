- [log](#Log)
    - [usage](#usage)
- [Random](#Random)  
    - [how it works](#how-it-works)
    - [usage](#usage-1)
- [Timer](#Timer)
    - [how it works](#how-it-works-1)
    - [usage](#usage-2)
- [Pathfinding](#pathfinding)
    - [how it works](#how-it-works-2)
    - [usage](#usage-3)

# Log

## usage
![when to use which log](res/log.png)
So loggt man eine Nachricht
```c++
LOG_DEBUG("test");

```
So loggt man eine variable
```c++
int ausgabe = 0;
LOG_DEBUG("ausgabe : {}", ausgabe);
```

# Random

## how it works
Wir nutzten eine Mersenne-Twister engine und eine uniform distribution um Zufällige zahlen zu erstellen.
Für die Float Variante wird einfach der zufalswert durch das unsigned 32 bit integer limit geteilt für eine zahl zwischen 1 und 0.
Für die Float Variante mit nem min und max wird einfach ein zufälliger float von oben genommen mal die differenz zwischen min und max genommen und plus min gerechnet.
Für die Unsigned Int Variante wird einfach nur die Mersenne Twister enginer genutzt um eine Zufalls zahl zwischen 0 und unsigned 32 bit integer limit erstellt.
Fur die Unsigned Int Variant mit nem min und max wird einfach eine zufälliger unsigned Int modulo differenz zwischen min und max plus 1 genommen und plus min gerechnet.

## usage
als aller erstes Muss Random Initialisiert werden.
```c++
Utils::Random::Init();
```
Dann kann man mittels `Utils::Random::UInt();` einen zufälligen Unsigned int bekommen alternativ mit einem min und max.
Und man kann mittles `Utils::Random::Float()` einen zufälligen float zwischen 0 und 1 erstellen lassen alternativ auch mit min und max.

# Timer

## how it works
Timer nutzt std::chrono für die Zeit.
mittels `std::chrono::high_resolution_clock::now()` wird der momentane zeitpunkt geholt und gespeichert und bei Elapsed wird die momentane Zeit also `std::chrono::high_resolution_clock::now()` mit der gespeicherten verglichen und so multipliziert, dass man eine Zeit in sekunden bekommt.
bei elapsed millis wird der wert von elapsed mal 1000 genommen weil 1000 millisekunden eine sekunde sind.
Zusätzlich gibt es noch einen ScopedTimer der einen Timer speichert und im konstruktor den Timer startet und im destruktor Wird dann mittels Ellapsed Millis die vergangenen Millisekunden seit erstellung des Scoped Timers auf der Konsole ausgegeben.
## usage

```
Utils::Timer delta_timer;
while(window.is_open())
{
	float deltatime = delta_timer.Elapsed();
	delta_timer.Reset();
	/*restlicher code hier*/
}


```


```
void bar()
{
Utils::ScopedTimer timer("bar timer");

do_something();

}
```
# Pathfinding

## how it works
Immer wenn sich was an der Karte und/oder der Position des Sielers verändert hat wird der Dijkstra Algorithmus genutzt um vom Spieler und/oder Türmen aus Kosten und Pfad zu jeder Zelle auszurechnen, anschließend wird dann mittels Backtracking ein Pfad genneriert.


```c++
// Initialisierung eines Vektors, der alle Zellen enthaelt
// Eine PriorityQueue waere eigentlich besser, aber es gibt Probleme damit.
// Ein Vektor wird verwendet, und Sortierung fuehrt zum gleichen Ergebnis wie mit einer PriorityQueue.
std::vector<cell*> cells;
```
<!---
Hierzwischen sind noch ein par Checks um undefiniertes verhalten zu verhindern
--->

```c++
{// Setze die Distanz der Startpunkte auf 0 und deren Eltern auf nullptr
    size_t amount_valid = start_points.size();
	for (const auto start : start_points)
	{
	    if (!is_valid(start))
		{
		amount_valid--;
	    }
	    else
	    {
	        cellmap[start.z][start.y][start.x].dist = 0; // Distanz am Startpunkt auf 0 setzen
			cellmap[start.z][start.y][start.x].parent = nullptr; // Elternknoten auf nullptr setzen
	    }
	}
	if (amount_valid <= 0) //falls es keien gueltigen Start punkte gibt wird das pathfinden abgebrochen
	{
		LOG_ERROR("keine gueltigen start punkte verfuegbar");
	    return;
	}
}
```



```c++
while (!cells.empty())
{
    std::ranges::sort(cells, comp); // Sortiere den q_Vector nach Distanz absteigend.

    cell* current = cells.back(); // Nehme das letzte Element aus dem q_Vector.
    cells.pop_back(); // Loesche das letzte Element aus dem q_Vector.

    for (cell* neighbor : get_neighbors(current, cellmap)) // Hole die Nachbarn von current.
    {
		// Berechne die Distanz zwischen current und v.
		const double dist = current->dist + get_dist(current, neighbor);

		// Vergleiche die berechnete Distanz mit der in v gespeicherten Distanz.
		if (dist < neighbor->dist)
		{
	    	// Aktualisiere die Distanz und den Parent von v.
 	    	neighbor->dist = dist;
	    	neighbor->parent = current;
		}
    }
}
```




## usage
```c++
Utils::Pathfinding* instance = Utils::Pathfinding::get_instance();
instance->calculate_paths(); //wenn die pfade vorher noch nicht berechnet worden
glm::vec3 start = entity->get_pos(); //position vom entity
std::vector<glm::vec3> path = instance->find_path(start,entity->get_priority());
entity->set_path(path);
```

Bei mehreren entities macht man einmal calculate paths und ruft dann in einer schleife immer wieder die Funktion find_path auf.

```c++
Utils::Pathfinding* instance = Utils::Pathfinding::get_instance();
instance->calculate_paths(); //wenn die pfade vorher noch nicht berechnet worden
for(auto& entity : entities)
{
    glm::vec3 start = entity->get_pos(); //position vom entity
    std::vector<glm::vec3> path = instance->find_path(start, entity->get_priority());
    entity->set_path(path);
}

```
