#pragma once
#include "Events/Event.h"

class Layer
{
public:
	Layer(const std::string& name)
		: m_DebugName(name) {}
	~Layer() {}
	
	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(float timestep) {}
	virtual void OnEvent(Event& e) {}
	
	inline const std::string& GetName() const { return m_DebugName; }
private:
	std::string m_DebugName;
};