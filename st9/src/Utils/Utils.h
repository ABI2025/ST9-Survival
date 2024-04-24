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
		DEFENSE,
		WALL,
		STAIR,
		TURRET,


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
		// warum zur hölle tut die funktion vecc3 almost equal nur die x und y checken?
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
	inline bool hitboxCollision(const glm::vec3& posA, const glm::vec3& hitboxA, // wird nicht genutzt, fix ich nochm wird noch schöner
		const glm::vec3& posB, const glm::vec3& hitboxB) {

		glm::vec3 minA = posA;
		glm::vec3 maxA = posA + hitboxA;


		glm::vec3 minB = posB;
		glm::vec3 maxB = posB + hitboxB;

		return maxA.x >= minB.x && minA.x <= maxB.x &&
			maxA.y >= minB.y && minA.y <= maxB.y &&
			maxA.z >= minB.z && minA.z <= maxB.z;
	}

}
