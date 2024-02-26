#pragma once
#include <memory>
#include "Log.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"



namespace Utils
{
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};
}
#ifdef DIST
#define LOG_TRACE(...)
#define LOG_DEBUG(...)         
#define LOG_INFO(...)       
#define LOG_WARN(...)       
#define LOG_ERROR(...)      
#define LOG_CRITICAL(...)   
#else
#define LOG_TRACE(...)         ::Utils::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)         ::Utils::Log::GetLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)          ::Utils::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          ::Utils::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         ::Utils::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      ::Utils::Log::GetLogger()->critical(__VA_ARGS__)
#define LOG_LEVEL(...)         ::Utils::Log::GetLogger()->set_level(__VA_ARGS__)
#endif