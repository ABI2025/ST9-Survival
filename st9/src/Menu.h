#pragma once
#include "Utils/Log.h"
#include "Utils/Utils.h"

class Menu
{
public:
	Menu(const Menu&) = delete;
	//test
	static Menu& get()
	{
		return s_Instance;
	}

private:
	Menu() {}
	std::vector<std::vector<std::vector<Utils::Cell>>> m_map;
	static Menu s_Instance;
};

