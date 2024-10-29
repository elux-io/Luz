includes("**/xmake.lua")
add_rules("mode.debug", "mode.release")

set_languages("c++20")
set_warnings("allextra")

add_cxxflags("/Zc:preprocessor", "/Zc:templateScope", "/Zc:throwingNew", "/Zc:enumTypes", { tools = "cl" })

target("luz")
	set_kind("static")
	add_includedirs("src", { public = true })
	add_files("src/Luz/**.cpp")

target("main")
	set_kind("binary")
	add_deps("luz")
	add_files("src/main.cpp")
