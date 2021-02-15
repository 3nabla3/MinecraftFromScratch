#include "spdlog/spdlog.h"
#include "Application.h"
#include <iostream>

int main()
{
	spdlog::info("Hello world");
	Application app = Application();
	app.Run();
}