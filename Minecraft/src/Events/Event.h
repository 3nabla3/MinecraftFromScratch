#pragma once
#include <string>

enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum class EventCategory
{
	None = 0,
	Application		= 1 << 0,
	Input			= 1 << 1,
	Keyboard		= 1 << 2,
	Mouse			= 1 << 3,
	MouseButton		= 1 << 4
};

class Event
{
public:
	bool Handled = false;

	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	inline bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags() & (int)category;
	}
};

class EventDispacher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;
};