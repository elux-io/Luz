#include "Log.hpp"
#include "ConsoleLogger.hpp"

#include <Lux/Core/Debug.hpp>

namespace lux::log
{
	static constinit auto s_defaultLogger = ConsoleLogger();
	static constinit auto s_logger = static_cast<Logger*>(&s_defaultLogger);

	auto GetLogger() -> Logger&
	{
		return *s_logger;
	}

	auto SetLogger(Logger* logger) -> void
	{
		s_logger = logger;
	}
}
