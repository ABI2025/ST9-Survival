// ReSharper disable CppInconsistentNaming
#pragma once
#include <random>

#include <glm/glm.hpp>

#include "Log.h"

namespace Utils
{

	class Random
	{
	public:
		static void Init();

		static void set_seed(uint32_t i_seed);

		static uint32_t UInt();

		static uint32_t UInt(uint32_t min, uint32_t max);

		static float Float();

		static float Float(float min, float max);

		static glm::vec3 Vec3();

		static glm::vec3 Vec3(float min, float max);

		static glm::vec3 InUnitSphere();

	private:
		thread_local static std::mt19937 s_random_engine;
		static std::uniform_int_distribution<std::mt19937::result_type> s_distribution;
	};

}

