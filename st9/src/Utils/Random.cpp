#include "Random.h"

#include "Log.h"

namespace Utils
{
	thread_local std::mt19937 Random::s_random_engine;  // NOLINT(cert-msc51-cpp)
	std::uniform_int_distribution<std::mt19937::result_type> Random::s_distribution;

	void Random::Init()
	{
		const auto random_val = std::random_device()();
		LOG_INFO("seed: {}", random_val);
		s_random_engine.seed(random_val);
	}

	void Random::set_seed(const uint32_t i_seed)
	{
		s_random_engine.seed(i_seed);
	}

	uint32_t Random::UInt()
	{
		return s_distribution(s_random_engine);
	}

	uint32_t Random::UInt(const uint32_t min, const uint32_t max)
	{
		return min + s_distribution(s_random_engine) % (max - min + 1);
	}

	float Random::Float()
	{
		return static_cast<float>(s_distribution(s_random_engine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
	}

	float Random::Float(const float min, const float max)
	{
		return Float() * (max - min) + min;
	}

	glm::vec3 Random::Vec3()
	{
		return { Float(), Float(), Float() };
	}

	glm::vec3 Random::Vec3(const float min, const float max)
	{
		return { Float(min,max),Float(min,max) ,Float(min,max) };
	}

	glm::vec3 Random::InUnitSphere()
	{
		return normalize(Vec3(-1.0f, 1.0f));
	}
}

