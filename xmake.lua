set_languages("c++20")
set_warnings("allextra")

option("enable-examples", { default = false })
option("enable-tests", { default = false })

add_rules("mode.debug", "mode.release")
add_cxxflags("/Zc:preprocessor", "/Zc:templateScope", "/Zc:throwingNew", "/Zc:enumTypes", { tools = "cl" })

target("lux")
	set_kind("static")
	add_includedirs("src", { public = true })
	add_files("src/Lux/**.cpp")

if has_config("enable-examples") then
	includes("examples/*")
end

if has_config("enable-tests") then
	includes("tests")
end
