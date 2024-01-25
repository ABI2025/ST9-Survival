#pragma once
#include <string>
#include <chrono>
#include "Log.h"

namespace Utils
{

	class Timer
	{
	public:
		
		Timer()
		{
			Reset();
		}
		//resets the timer to 0
		void Reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		//returns the amount of time passed since the last time reset has been called in seconds
		float Elapsed()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
		}

		//returns the amount of time passed since the last time reset has been called in seconds
		float ElapsedMillis()
		{
			return Elapsed() * 1000.0f;
		}
	private:
		//zeitpunkt
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};

	//timer der in einer funktion verwendet werden soll um zu gucken wie lange die funktion dauert 
	class ScopedTimer
	{
	public:
		ScopedTimer(const std::string& name)
			: m_Name(name) {}
		~ScopedTimer()
		{
			float time = m_Timer.ElapsedMillis();
			LOG_INFO("[TIMER] {} - {} ms",m_Name, time);
		}
	private:
		std::string m_Name;
		Timer m_Timer;
	};
}