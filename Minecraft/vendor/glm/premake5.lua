project "glm"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"include/glm/**.h",
		"include/glm/**hpp",
		"include/glm/**inl"
	}

	includedirs
	{
		"include"
	}

	
	systemversion "latest"
	staticruntime "On"
	
	filter "system:linux"
		toolset "gcc"
