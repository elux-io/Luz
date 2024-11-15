#pragma once

#define LUX_LOG_LEVEL(level) LUX_PRIVATE_LOG_LEVEL_##level()
#define LUX_PRIVATE_LOG_LEVEL_OFF()   0
#define LUX_PRIVATE_LOG_LEVEL_ERROR() 1
#define LUX_PRIVATE_LOG_LEVEL_WARN()  2
#define LUX_PRIVATE_LOG_LEVEL_INFO()  3
#define LUX_PRIVATE_LOG_LEVEL_DEBUG() 4
#define LUX_PRIVATE_LOG_LEVEL_TRACE() 5
#define LUX_PRIVATE_LOG_LEVEL_ALL()   6

#if not defined(LUX_MAX_LOG_LEVEL)
	#define LUX_MAX_LOG_LEVEL LUX_LOG_LEVEL(ALL)
#endif

namespace lux::log
{
	enum class Level
	{
		Off   = LUX_LOG_LEVEL(OFF),
		Error = LUX_LOG_LEVEL(ERROR),
		Warn  = LUX_LOG_LEVEL(WARN),
		Info  = LUX_LOG_LEVEL(INFO),
		Debug = LUX_LOG_LEVEL(DEBUG),
		Trace = LUX_LOG_LEVEL(TRACE),
		All   = LUX_LOG_LEVEL(ALL)
	};
}
