#pragma once
#include "MemoryLayout.h"
class ScriptName;
class MemoryImage;
class MemoryImageSection;
class PointerTableBase;

class MemoryImageWriter
{
	public:
		MemoryImageWriter(MemoryImage &inImage);
		MemoryImageWriter(MemoryImageSection*section);
		~MemoryImageWriter();
		MemoryImage &GetImage()const;
		const PlatformTypeLayoutParameters&GetHostLayoutParams();
		const PlatformTypeLayoutParameters&GetTargetLayoutParams();
		PointerTableBase&GetPointerTable()const;
		const PointerTableBase*TryGetPrevPointerTable()const;
		inline bool Is32BitTarget()const {return GetTargetLayoutParams().Is32Bit();}
	        inline bool Is64BitTargeit()const{return GetTargetLayoutParams().Is64Bit();}

		int AddTypeDependency(const TypeLayoutDesc &typeDesc);

		void WriteObject(const void *object,const TypeLayoutDesc &typeDesc);
		void WriteObjectArray(const void *object,const TypeLayoutDesc &typeDesc,uint32_t numArray);
		void WriteRootObject(const void *object,const TypeLayoutDesc &typeDesc);
		uint32 GetOffset()const;
		uint32 WriteAlignment(uint32 alignment);
		void WritePaddingToSize(uint32 offset);
		uint32 WriteBytes(const void *data,uint32 size);
		MemoryImageWriter WritePointer(const TypeLayoutDesc &staticTypeDesc,const TypeLayoutDesc DerivedTypeDesc,uint32 *outOffsetToBase=nullptr);
		MemoryImageWriter WritePointer(const TypeLayoutDesc &typeDesc);
		uint32 WriteNullPointer();
		uint32 WriterRawPointerSizeBytes(uint64 pointerValue);
		uint32 WriteVTable(const TypeLayoutDesc &typeDesc,const TypeLayoutDesc &derivedTypeDesc);
		uint32 WriteMemoryImageName(int32 numBytes,const Name &name);
		uint32 WriteScriptName(const ScriptName &name);

		template<typename T>
		void WriteObject(const T &object)
		{
			const TypeLayoutDesc &typeDesc=GetTypeLayoutDesc(TryGetPrevPointerTable(),object);
			WriteRootObject(object,TypeDesc);
		}

		template<typename T>
		void WriteAlignment()
		{
			return WriteAlignment(alignof(T));
		}

		template<typename T>
		uint32 WriteBytes(const T &data)
		{
			return WriteButes(&data,sizeof(T));
		}
		MemoryImageSectin *section;
};




