#pragma once

#include "MacroUtils.hpp"

#include <utility>
#include <concepts>

#define LUX_DEFER(...) auto LUX_CONCAT(luxDeferrer, __LINE__) = ::lux::Deferrer([&] { __VA_ARGS__; })

namespace lux
{
	template<std::invocable F>
	class Deferrer
	{
	public:
		constexpr explicit Deferrer(F&& fn) : m_fn(std::move(fn)) {}
		constexpr Deferrer(Deferrer const&) = delete;
		constexpr Deferrer(Deferrer&&) = delete;
		constexpr ~Deferrer() { m_fn(); }

		constexpr auto operator=(Deferrer const&) -> Deferrer& = delete;
		constexpr auto operator=(Deferrer&&) -> Deferrer& = delete;

	private:
		F m_fn;
	};
}
