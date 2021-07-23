
project "SOIL"
	kind "SharedLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/*.c",
		"include/SOIL/**.h"
	}

	includedirs
	{
		"include/"
	}
		

	filter "system:linux"
		links { "GL" }
		pic "On"
	        toolset "gcc"
		systemversion "latest"
		staticruntime "On"

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"
		buildoptions {"/MP"}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
