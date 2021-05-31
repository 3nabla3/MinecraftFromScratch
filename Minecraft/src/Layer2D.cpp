#include "pch.h"

#include "Layer2D.h"

Layer2D::Layer2D(const std::string& name)
	:Layer(name)
{
	spdlog::trace("Created Layer {}", name);
	
	
}

void Layer2D::OnAttach()
{
	spdlog::trace("Layer {} was attached", m_DebugName);
}

void Layer2D::OnDetach()
{
	spdlog::trace("Layer {} was detached", m_DebugName);
}

void Layer2D::OnEvent(Event& e)
{
}

void Layer2D::OnUpdate(float timestep)
{
}