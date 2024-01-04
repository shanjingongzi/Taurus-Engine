#pragma once
#include "PrimitiveComponent.h"
#include <MaterialInterface.h>
#include <string>
#include <vector>
class MeshComponent:public PrimitiveComponent
{
public:
	std::vector<MaterialInterface*>overrideMaterials;
	virtual std::vector<MaterialInterface*>GetMaterials()const;
	virtual int GetMaterialIndex(const std::string& name)const;
	virtual std::vector<std::string>GetMaterialSlotNames()const;
	virtual bool IsMaterialSlotNameValid(const std::string& name)const;
	virtual bool UseNaniteOverrideMaterials()const { return false; }
	virtual int GetNumberOverrideMaterials()const;
	MaterialInterface* overlayMaterial;
	float overlayMaterialMaxDrawDistance;
	MaterialInterface* GetOverlayMaterial()const;
	void SetOverlayMaterial(MaterialInterface* newOverlayMaterial);
	void CleanUpOverrideMaterials();
	void EmptyOverrideMaterials();
	bool HasOverrideMaterials();
	virtual int GetNumMaterials()const ;
	virtual MaterialInterface* GetMaterial(int elementIndex)const ;
private:
};
