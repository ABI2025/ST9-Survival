#pragma once
#include <memory>
#include "Log.h"

#include "spdlog/spdlog.h"


namespace Utils
{
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& get_logger() { return s_Logger; }
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
#define LOG_TRACE(...)         ::Utils::Log::get_logger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)         ::Utils::Log::get_logger()->debug(__VA_ARGS__)
#define LOG_INFO(...)          ::Utils::Log::get_logger()->info(__VA_ARGS__)
#define LOG_WARN(...)          ::Utils::Log::get_logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         ::Utils::Log::get_logger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      ::Utils::Log::get_logger()->critical(__VA_ARGS__)
#endif

