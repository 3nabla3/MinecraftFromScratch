workspace "Minecraft"
	configurations { "Debug", "Release", "Dist" }
	architecture "x64"
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["spdlog"] = "Minecraft/vendor/spdlog/include"
IncludeDir["GLFW"] = "Minecraft/vendor/GLFW/include"
IncludeDir["Glad"] = "Minecraft/vendor/Glad/include"
IncludeDir["SOIL"] = "Minecraft/vendor/SOIL/include"
IncludeDir["glm"] = "Minecraft/vendor/glm/include"

include "Minecraft/vendor/GLFW"
include "Minecraft/vendor/Glad"
include "Minecraft/vendor/glm"

project "Minecraft"
	kind "ConsoleApp"
	language "C++"
	location "Minecraft"
	targetdir ("bin/" .. outputdir.. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir.. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/res/**",
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.SOIL}",
		"Minecraft/src"
	}

	pchheader "pch.h"
	pchsource ("%{prj.name}/src/pch.cpp")
	
	defines
	{
		"GLFW_INCLUDE_NONE"
	}
	

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"
		buildoptions {"/MP"}
		
		links
		{
			"GLFW",
			"Glad",
			 -- "SOIL",
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
			"SOIL",
			"pthread",
			"dl"
		}

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "on"

	filter "configurations:Release"
		defines {"RELEASE"}
		optimize "on"
		symbols "on"

	filter "configurations:Dist"
		defines {"DIST"}
		optimize "on"
