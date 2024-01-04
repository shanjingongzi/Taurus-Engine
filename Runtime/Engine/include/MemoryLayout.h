#pragma once
#include "Platform.h"
#include "MemeroyImageWriter.h"

class HashedName;
class SHA1;
class MemoryImageWriter;
class MemoryUnfreezeContent;
class PointerTableBase;
class TargetPlatform;
struct  TypeLayoutDesc;
struct PlatformTypeLayoutParameters;

namespace EFieldLayoutFlags
{
	enum Type :uint8 {
		None = 0u,
		WithEditorOnly = (1u << 0),
		WithRayTracing = (1u << 1),
		Transient = (1u << 2),
		UseIntanceWithProperty = (1u << 3),
	};
	inline Type MakeFlags(uint32 flags=None){return (Type)flags;}
	inline Type MakeFlagsEditorOnly(uint32 flags=None){return (Type)(WithEditorOnly);}
	inline Type MakeFlagsRayTracing(uint32 flags=None){return (Type)(WithRayTracing);}
}

namespace ETypeLayoutInterface
{
	enum Type :uint8
	{
		NonVirtual,
		Virtual,
		Abstract
	};
	inline bool HasVTable(Type type) { return type != NonVirtual; }
}

struct  CORE_API FieldLayoutDesc
{
	typedef void(WriterFrozenMemoryImageFunc)(MemoryImageWriter& writer, const void* object,const void *fieldObject, const TypeLayoutDewsc& typeDesc, const TypeLayoutDesc& derivedTypeDesc);
	const TCHAR *name;
	const struct TypeLayoutDesc *type;
	const FieldLayoutDesc*next;
	WriterFrozenMemoryImageFunc*writerFrozonMemoryImageFunc;
	uint32 offset;
	uint32 munArray;
	EFieldLayoutFlags::Type flags;
	uint8 bitFieldSize;
	uint8 fieldNameLenght;
};

struct CORE_API TypeLayoutDesc
{
	typedef void (DestroyFunc)(void *onject,const TypeLayoutDesc &typeDesc,const PointerTableBase *ptrTable,bool isFrozen);
	typedef void (WriteFrozenMemoryImageFunc)(MemoryImageWriter &writer,const void*object,const TypeLayoutDesc &typeDesc,cosnt TypeLayoutDesc &derivedTypeDesc);
	typedef uint32(UnfrozenCopyFunc)(const MemoryUnfreezeContent &context,const void *object,const TypeLayoutDesc &typeDesc,void *outDst);
	typedef uint32(AppendHashFunc)(const TypeLayoutDesc &TypeLayoutDesc &typeDesc,const PlatformTypeLayoutParameters&layoutParams,SHA1&haser);
	typedef uint32(GetTargetAlignmentFunc)(const TypeLayoutDesc &typeDesc,const PlatformTypeLayoutParameters &layoutParams);
	typedef void(ToStringFunc)(const void *object,const TypeLayoutDesc&typeDesc,const PlatformTypeLayoutParamters &layoutParams,MemoryToString &outContext O&outContext);

	static const TypeLayoutDesc &GetInvalidTypeLayout();
	static void Initialize(TypeLayoutDesc &typeDesc);
	static void Register(TypeLayoutDesc &typedesc);
	static const TypeLayoutDesc *Find(uint64 nameHash);

	uint32 GetOffsetToBase(const TypeLayoutDesc &baseTypeDesc)const;
	bool IsDerivedFrom(const TypeLayoutDesc &baseTypeDesc)const;

	typedef const void *(GetDefaultFunc)();
	const TypeLayoutDesc* hashNext;
	const TCHAR* name;
	const FieldLayoutDesc* fields;
	DestroyFunc* destroyFunc;
	WriteFrozenMemoryImageFunc *writeFrozenMemoryImageFunc;
	UnfrozenCopyFunc*unfrozenCopyFunc;
	AppendHashFunc *appendHashFunc;
	GetTargetAlignmentFunc *GetTargetAlignmentFunc;
	ToStringFunc*toStringFunc;
	GetDefaultFunc *GetDefaultOhbjectFunc;

	uint64 nameHash;
	uint32 size;
	uint32 sizeFromFields;
	uint32 Alignment;
	ETypeLayoutInterface::Type interface;
	uint8 numBases;
	uint8 numVirtualBases;
	uint8 isIntrinsic:1;
	uint8 IsInitialized:1;
};

struct RegisterTypeLayoutDesc
{
	explicit CORE_API RegisterTypeLayoutDesc(TypeLayoutDesc& typeDesc);
	CORE_API RegisterTypeLayoutDesc(const TCHAR* name, TypeLayoutDesc& typedesc);
};

template<typename T,typename Base>
inline uint32 GetBaseOffset()
{
	alignas(T) char dunmy[sizeof(T)];
	T* Derived = reinterpret_cast<T*>(dummy);
	return (uint32)((uint64)static_cast<Base*>(derived) - (uint64)derived);
}



