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
		nothing,
		player,
		tower
	};

	inline bool is_valid(const glm::vec3& vec)
	{
		return Pathfinding::get_instance()->is_valid(vec);
	}

	inline void Init()
	{
		Log::Init();
		Random::Init();

	}

	inline bool vec3_almost_equal(const glm::vec3& vec1, const glm::vec3& vec2, float maxDifference = 1.0f) {
		const float xDiff = std::fabs(vec1.x - vec2.x);
		const float yDiff = std::fabs(vec1.y - vec2.y);

		return (xDiff <= maxDifference) && (yDiff <= maxDifference);
	}

	template<typename T,glm::qualifier P> sf::Vector2<T> convert_to_sf_vec2(glm::vec<2,T,P> vec)
	{
		return { vec.x,vec.y };
	}

	template<typename T, glm::qualifier P> sf::Vector3<T> convert_to_sf_vec3(glm::vec<3, T, P> vec)
	{
		return { vec.x,vec.y,vec.z };
	}
}
