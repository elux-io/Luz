#pragma once

#include "Level.hpp"

#include <source_location>
#include <string_view>

namespace lux::log
{
	class Logger
	{
	public:
		virtual ~Logger() = default;

		auto GetLevel() const { return m_level; }
		auto SetLevel(Level level) { m_level = level; }

		auto Log(Level level, std::source_location const& location, std::string_view str) -> void
		{
			if (level <= m_level)
				LogImpl(level, location, str);
		}

	private:
		virtual auto LogImpl(Level level, std::source_location const& location, std::string_view str) -> void = 0;

		Level m_level = static_cast<Level>(LUX_MAX_LOG_LEVEL);
	};
}
