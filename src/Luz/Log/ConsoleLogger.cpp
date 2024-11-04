#include "ConsoleLogger.hpp"

#include <Luz/Core/Debug.hpp>
#include <cstdio>
#include <format>

namespace luz::log
{
	auto ConsoleLogger::LogImpl(Level level, [[maybe_unused]] std::source_location const& location, std::string_view str) -> void
	{
		auto levelStr = [&] {
			switch (level)
			{
				case Level::Error: return "[ERROR]";
				case Level::Warn:  return "[WARN]";
				case Level::Info:  return "[INFO]";
				case Level::Debug: return "[DEBUG]";
				case Level::Trace: return "[TRACE]";
			}

			Unreachable();
		}();

		auto message = std::format("{} {}\n", levelStr, str);
		std::fwrite(message.data(), sizeof(char), message.size(), stdout);
	}
}
