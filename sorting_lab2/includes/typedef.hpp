#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP

#include <chrono>
#include <vector>
#include <map>
#include <String>
#include <limits>

namespace cor {

	namespace time {

		typedef std::chrono::nanoseconds nano;
		typedef std::chrono::microseconds micro;
		typedef std::chrono::milliseconds mili;
		typedef std::chrono::seconds sec;
		typedef std::chrono::steady_clock steadyClock;
		typedef std::chrono::system_clock systemClock;

		template<typename clock_t>
		using timePoint = std::chrono::time_point<clock_t>;
	}

	typedef std::numeric_limits<int> INF;
}

#endif // !TYPEDEF_HPP
