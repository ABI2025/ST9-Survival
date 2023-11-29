#pragma once
#include "Random.h"
#include "Log.h"
#include "Timer.h"
#include "Pathfinding.h"
namespace Utils
{
	enum class Priority
	{
		nothing, player, tower
	};
	inline void Init()
	{
		Log::Init();
		Random::Init();

	}



}
