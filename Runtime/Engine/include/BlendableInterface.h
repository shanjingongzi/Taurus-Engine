#pragma once

class IBlendableInterface
{
	public:
		virtual void OverrdeBlendableSettings(class SceneView &view,float weight)const=0;
};
