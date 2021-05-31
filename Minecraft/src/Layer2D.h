#include "Layer.h"

class Layer2D : public Layer
{
public:
	Layer2D(const std::string& name);
	~Layer2D();
	
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnEvent(Event& e);
	virtual void OnUpdate(float timestep);
};