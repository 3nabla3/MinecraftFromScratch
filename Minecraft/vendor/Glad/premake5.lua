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
	
	systemversion "latest"
	staticruntime "On"
	
	filter "system:linux"
		toolset "gcc"

