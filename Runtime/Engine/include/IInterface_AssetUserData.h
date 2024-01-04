#pragma once
#include <vector>
class AssetUserData;
class IInterface_AssetUserData
{
	public:
		virtual void AddAssetUserData(AssetUserData*userData){}
		virtual AssetUserData* GetAssetUserDataOfClass(AssetUserData* InUserDataClass) { return nullptr; }
		virtual const std::vector<AssetUserData*>* GetAssetUserDataArray()const { return nullptr; }
		template<typename T>
		T* GetAssetUserData()
		{
			return static_cast<T*>(GetAssetUserDataOfClass(T::StaticClass()));
		}

		template<typename T>
		T* GetAssetUserDataChecked()
		{
			return static_cast<T*>(GetAssetUserDataOfClass(T::StaticClass()));
		}

		virtual void RemoveUserDataOfClass(AssetUserData* InUserDataClass) {}
}; 