#pragma once
#include <vector>
#include "src/Utils/Utils.h"
class Game
{
	static Game* erstelleGame();
	inline static Game *game;
	void setMap(Utils::Cell& , int , int , int ); // Cell x,y,z
	std::vector<std::vector<std::vector<Utils::Cell>>>& getMap();
private:
	Game() = default;
	Game(Game&) = delete;
	std::vector<std::vector<std::vector<Utils::Cell>>> map;
};

