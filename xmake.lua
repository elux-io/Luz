add_rules("mode.debug", "mode.release")

set_languages("c++20")
set_warnings("allextra")

add_cxxflags("/Zc:preprocessor", "/Zc:templateScope", "/Zc:throwingNew", "/Zc:enumTypes", { tools = "cl" })

add_includedirs("src")

target("main")
	set_kind("binary")
	add_files("src/**.cpp")
