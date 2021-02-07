workspace "Minecraft"
	configurations { "Debug", "Release", "Dist" }
	architecture "x64"
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.system}"
IncludeDir = {}
IncludeDir["GLFW"] = "Minecraft/vendor/GLFW/include"
IncludeDir["Glad"] = "Minecraft/vendor/Glad/include"

include "Minecraft/vendor/GLFW"
include "Minecraft/vendor/Glad"

project "Minecraft"
	kind "ConsoleApp"
	language "C++"
	location "Minecraft"
	targetdir ("bin/" .. outputdir.. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir.. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	
	defines
	{
		"GLFW_INCLUDE_NONE"
	}
	

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"
		
		links
		{
			"GLFW",
			"Glad",
			"opengl32.lib"
		}
		
	filter "system:linux"
		cppdialect "C++17"
		toolset "gcc"
		staticruntime "on"
		systemversion "latest"
		
		links
		{
			"GLFW",
			"Glad",
			"pthread",
			"dl"
		}

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "on"

	filter "configurations:Debug"
		defines {"NDEBUG"}
		optimize "on"
