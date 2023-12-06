#pragma once
#include <vector>
#include "Utils/Utils.h"
class Game
{
public:
	static Game* erstelleGame();
	void setMap(Utils::Cell& , int , int , int ); // Cell x,y,z
	std::vector<std::vector<std::vector<Utils::Cell>>>& get_map();
private:
	inline static Game* s_game;
	Game() = default;
	Game(Game&) = delete;
	std::vector<std::vector<std::vector<Utils::Cell>>> m_map;
};

