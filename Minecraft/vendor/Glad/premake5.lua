project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"include/**.h",
		"src/**.c"
	}

	includedirs
	{
		"include"
	}
	
	filter "system:linux"
		toolset "gcc"
		systemversion "latest"
		staticruntime "On"
