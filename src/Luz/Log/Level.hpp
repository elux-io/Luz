#pragma once

#define LUZ_LOG_LEVEL(level) LUZ_PRIVATE_LOG_LEVEL_##level()
#define LUZ_PRIVATE_LOG_LEVEL_OFF()   0
#define LUZ_PRIVATE_LOG_LEVEL_ERROR() 1
#define LUZ_PRIVATE_LOG_LEVEL_WARN()  2
#define LUZ_PRIVATE_LOG_LEVEL_INFO()  3
#define LUZ_PRIVATE_LOG_LEVEL_DEBUG() 4
#define LUZ_PRIVATE_LOG_LEVEL_TRACE() 5
#define LUZ_PRIVATE_LOG_LEVEL_ALL()   6

#if not defined(LUZ_MAX_LOG_LEVEL)
	#define LUZ_MAX_LOG_LEVEL LUZ_LOG_LEVEL(ALL)
#endif

namespace luz::log
{
	enum class Level
	{
		Off   = LUZ_LOG_LEVEL(OFF),
		Error = LUZ_LOG_LEVEL(ERROR),
		Warn  = LUZ_LOG_LEVEL(WARN),
		Info  = LUZ_LOG_LEVEL(INFO),
		Debug = LUZ_LOG_LEVEL(DEBUG),
		Trace = LUZ_LOG_LEVEL(TRACE),
		All   = LUZ_LOG_LEVEL(ALL)
	};
}
