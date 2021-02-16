#pragma once
#include "GLFW/glfw3.h"
#include "Events/Event.h"

class Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	Window(unsigned int width=640, unsigned int height=480, const std::string& label = std::string("GLFW"));

	inline unsigned int GetWidth() const { return m_Data.Width; }
	inline unsigned int GetHeight() const { return m_Data.Height; }
	inline bool IsVSync() const { return m_Data.VSync; }
	inline bool IsCursorEnabled() const { return m_Data.CursorEnabled; }

	inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
	inline void SetVSync(bool enable);
	inline void EnableCursor(bool enable);

	GLFWwindow* GetRawWindow() const { return m_Window; }

private:
	GLFWwindow* m_Window = nullptr;
	
	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
		bool CursorEnabled;

		EventCallbackFn EventCallback;
	} m_Data;
};

