#pragma once
#include <Platform.h>
#include "ThreadSafeCounter.h"

class IRefCountedObject
{
public:
	virtual ~IRefCountedObject() {}
	virtual uint32 AddRef()const = 0;
	virtual uint32 Release()const = 0;
	virtual uint32 GetRefCount()const = 0;
};

class RefCountBase
{
public :
	RefCountBase() = default;
	virtual ~RefCountBase() = default;
	RefCountBase(const RefCountBase&) = delete;
	RefCountBase& operator=(const RefCountBase&) = delete;
	inline uint32 AddRef()const
	{
	}

	uint32 GetRefCount()const
	{

	}
private:
	mutable uint32 numRefs = 0;
	void CheckRefCount()const
	{

	}
};

class RefCountedObject
{
public:
	RefCountedObject() :numRefs(0) {}
	virtual ~RefCountedObject() {}
	RefCountedObject(const RefCountedObject&) = delete;
	RefCountedObject& operator=(const RefCountedObject&) = delete;
	uint32 AddRef()
	{
		return uint32(++numRefs);
	}
	uint32 Release()const {
		uint32 refs = uint32(--numRefs);
		if (refs == 0) {
			delete this;
		}
		return refs;
	}

	uint32 GetRefCount()const {
		return uint32(numRefs);
	}
private:
	mutable uint32 numRefs;
};

class ThreadSafeRefCountedObject
{
public:
	ThreadSafeRefCountedObject() :numRefs(0) {}
	virtual ~ThreadSafeRefCountedObject()
	{
		
	}
	ThreadSafeRefCountedObject(const ThreadSafeRefCountedObject&) = delete;
	ThreadSafeRefCountedObject& operator=(const ThreadSafeRefCountedObject&) = delete;
	uint32 AddRef()const
	{
		return uint32(numRefs.Increament());
	}
	uint32 Release()const
	{
		uint32 refs = uint32(numRefs.Decrement());
		if (refs == 0) {
			delete this;
		}
		return refs;
	}
	uint32 GetRefCount()const
	{
		return uint32(numRefs.GetValue());
	}
private:
	mutable ThreadSafeCounter numRefs;
};

template<typename ReferencedType>
class TRefCountPtr
{
	typedef ReferencedType* ReferenceType;
public:
	inline TRefCountPtr() :reference{ nullptr }
	{}
	TRefCountPtr(ReferenceType inReference, bool addRef = true)
	{
		reference = inReference;
		if (reference) {
			reference->AddRef();
		}
	}
	
	TRefCountPtr(const TRefCountPtr& other) 
	{
		reference = other.reference;
		if (reference) {
			reference->AddRef();
		}
	}
	template<typename MoveReferencedType>
	explicit TRefCountPtr(TRefCountPtr<MoveReferencedType>& other)
	{
		reference = static_cast<ReferenceType*>(move.GetReference());
		if (reference) {
			reference.AddRef();
		}
	}
	explicit TRefCountPtr(TRefCountPtr&& move)
	{
		reference = move.reference;;
		move.reference = nullptr;
	}
	template<typename MoveReferencedType>
	explicit TRefCountPtr(TRefCountPtr<MoveReferencedType>&& move)
	{
		reference = static_cast<ReferenceType*>(move.GetReference());
		move.reference = nullptr;
	}

	~TRefCountPtr()
	{
		if (reference) {
			reference->Release();
		}
	}

	TRefCountPtr& operator=(ReferenceType inReference)
	{
		if (reference != inReference) {
			ReferenceType oldReference = reference;
			reference = inReference;
			if (reference) {
				reference->AddRef();
			}
			if (oldReference) {
				oldReference->Release();
			}
		}
		return *this;
	}

	template<typename CopyReferencedType>
	inline TRefCountPtr& operator=(const TRefCountPtr<CopyReferencedType>& inPtr)
	{
		return *this = inPtr.GetReference();
	}

	TRefCountPtr& operator=(TRefCountPtr &&inPtr)
	{
		if (this!= &inPtr) {
			ReferenceType oldReference = reference;
			inPtr.reference = nullptr;
			if (oldReference) {
				oldReference->Release();
			}
		}
		return *this;
	}

	inline ReferencedType* operator->()const {
		return reference;
	}

	inline operator ReferenceType()const
	{
		return reference;
	}

	inline ReferencedType** GetIntReference()
	{
		*this = nullptr;
		return &reference;
	}

	inline ReferencedType* GetReference()const
	{
		return reference;
	}
	
	inline friend bool IsValidRef(const TRefCountPtr& inReference)
	{
		return inReference.reference != nullptr;
	}

	inline bool IsValid()const
	{
		return reference != nullptr;
	}

	inline void SafeRelease()
	{
		*this = nullptr;
	}

	uint32 GetRefCount()
	{
		uint32 result = 0;
		if (reference) {
			result = reference->GetRefCount();
		}
		return result;
	}

	inline void Swap(TRefCountPtr& inPtr)
	{
		ReferenceType oldReference = reference;
		reference = inPtr.reference;
		inPtr.reference = oldReference;
	}

	public:
		inline bool operator==(const TRefCountPtr& other)
		{
			return GetReference() == other.GetReference();
		}

		inline bool operator==(const ReferencedType* other)
		{
			return GetReference() == other;
		}
private:
	ReferenceType reference;
	template<typename OtherType>
	friend class TRefCountPtr;

};