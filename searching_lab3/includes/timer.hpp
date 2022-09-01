#ifndef TIMER_HPP
#define TIMER_HPP

#include "typedef.hpp"

namespace cor::time {

	template<typename duration_t, class clock_t>
	class Timer {
	private:
		timePoint<clock_t> startPoint;
		timePoint<clock_t> stopPoint;

	public:

		void start();

		void stop();

		double elapsedSec();
		double elapsedTime();
		double timeSinceStart();
	};

	template<typename duration_t, class clock_t>
	inline void Timer<duration_t, clock_t>::start()
	{
		startPoint = clock_t::now();
	}

	template<typename duration_t, class clock_t>
	inline void Timer<duration_t, clock_t>::stop()
	{
		stopPoint = clock_t::now();
	}

	template<typename duration_t, class clock_t>
	inline double Timer<duration_t, clock_t>::elapsedSec()
	{
		return std::chrono::duration<double>(stopPoint - startPoint).count();
	}

	template<typename duration_t, class clock_t>
	inline double Timer<duration_t, clock_t>::elapsedTime()
	{
		return double(std::chrono::duration_cast<duration_t>(stopPoint - startPoint).count());
	}

	template<typename duration_t, class clock_t>
	inline double Timer<duration_t, clock_t>::timeSinceStart()
	{
		return double(std::chrono::duration_cast<duration_t>(clock_t::now(); - startPoint).count());
	}
}

#endif // !TIMER_HPP
