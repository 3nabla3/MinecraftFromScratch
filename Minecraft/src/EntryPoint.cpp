#include "pch.h"

#include "Application.h"

int main()
{
#ifdef DEBUG
	spdlog::set_level(spdlog::level::trace);
#elif RELEASE
	spdlog::set_level(spdlog::level::info);
#elif DIST
	spdlog::set_level(spdlog::level::off);
#endif

	{
		Application app = Application();
		app.Run();
	}

#ifndef DIST
	spdlog::info("Press enter to continue: ");
	std::cin.get();
#endif
}