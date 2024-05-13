#pragma once
#include <random>

#include <glm/glm.hpp>

#include "Log.h"

namespace Utils
{

	class Random
	{
	public:
		static void Init()
		{
			const auto random_val = std::random_device()();
			LOG_INFO("seed: {}", random_val);
			s_random_engine.seed(random_val);
		}

		static void set_seed(uint32_t i_seed)
		{
			s_random_engine.seed(i_seed);
		}

		static uint32_t UInt()
		{
			return s_distribution(s_random_engine);
		}

		static uint32_t UInt(uint32_t min, uint32_t max)
		{
			return min + (s_distribution(s_random_engine) % (max - min + 1));
		}

		static float Float()
		{
			return static_cast<float>(s_distribution(s_random_engine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
		}
		static float Float(float min, float max)
		{
			return Float() * (max - min) + min;
		}

		static glm::vec3 Vec3()
		{
			return {Float(), Float(), Float()};
		}

		static glm::vec3 Vec3(float min, float max)
		{
			return {Float(min,max),Float(min,max) ,Float(min,max) };
		}

		static glm::vec3 InUnitSphere()
		{
			return glm::normalize(Vec3(-1.0f, 1.0f));
		}
	private:
		thread_local static std::mt19937 s_random_engine;
		static std::uniform_int_distribution<std::mt19937::result_type> s_distribution;
	};

}

