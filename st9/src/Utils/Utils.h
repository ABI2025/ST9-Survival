#pragma once
#include "Random.h"
#include "Log.h"
#include "Timer.h"
#include "Pathfinding.h"
#include <SFML/Graphics.hpp>

namespace Utils
{

	enum class Cell
	{
		NOTHING = 0,
		WALL,
		DEFENSE,
		STAIR,



	};
	enum class Priority
	{
		nothing, player, tower
	};
	inline void Init()
	{
		Log::Init();
		Random::Init();

	}
	//template<typename T,glm::qualifier P> sf::Vector2<T> convert_to_sf_vec2(glm::vec<2,T,P> vec)
	//{
	//	return { vec.x,vec.y };
	//}
	//template<typename T, glm::qualifier P> sf::Vector3<T> convert_to_sf_vec3(glm::vec<3, T, P> vec)
	//{
	//	return { vec.x,vec.y,vec.z };
	//}
}
