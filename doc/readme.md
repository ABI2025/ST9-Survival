
- [log](#Log)
    - [how it works](#how-it-works)
    - [usage](#usage)
- [Random](#Random)  
    - [how it works](#how-it-works-1)
    - [usage](#usage-1)
- [Timer](#Timer)
    - [how it works](#how-it-works-2)
    - [usage](#usage-2)
- [Pathfinding](#pathfinding)
    - [how it works](#how-it-works-3)
    - [usage](#usage-3)

# Log

### how it works


### usage
![when to use which log](res/log.png)

```c++
LOG_DEBUG("");

```
# Random

### how it works


### usage

# Timer

### how it works


### usage

# Pathfinding

### how it works
Immer wenn sich was an der Karte und/oder der Position des Sielers geäntert wurde wird der Dijkstra Algorithmus genutzt um vom Spieler und/oder Türmen aus Kosten und Pfad zu jeder Zelle auszurechnen


```c++				
while (!q_vector.empty())
{
    std::ranges::sort(q_vector, comp); // Sortiere den q_Vector nach Distanz absteigend.

	cell* current = q_vector.back(); // Nehme das letzte Element aus dem q_Vector.
    q_vector.pop_back(); // Loesche das letzte Element aus dem q_Vector.

    for (cell* v : get_neighbours(current, cellmap)) // Hole die Nachbarn von current.
    {
	    // Berechne die Distanz zwischen current und v.
	    const double dist = current->dist + get_dist(current, v);

		// Vergleiche die berechnete Distanz mit der in v gespeicherten Distanz.
	    if (dist < v->dist)
		{
			// Aktualisiere die Distanz und den Parent von v.
			v->dist = dist;
		    v->parent = current;
		}
	}
}
```




### usage
```c++
Utils::Pathfinding* instance = Utils::Pathfinding::get_instance();
glm::vec3 start = entity->get_pos(); //position vom entity
std::vector<glm::vec3> path = instance->find_path(start, );
```
