#include "pch.h"

#include "Application.h"

int main()
{
	spdlog::set_level(spdlog::level::trace);
	
	{
		Application app = Application();
		app.Run();
	}
	spdlog::info("Press enter to continue: ");
	std::cin.get();
}