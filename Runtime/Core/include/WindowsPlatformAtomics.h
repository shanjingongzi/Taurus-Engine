#pragma once
#include "Platform.h"
#include <intrin.h>

class WindowPlatformAtomics
{
public:
//Increment
    static inline int8 InterlockedIncrement(volatile int8 *value)
    {
        return (int8)::_InterlockedExchange8((char*)value,1)+1;
    }
    static inline int16 InterlockedIncrement(volatile int16 *value)
    {
        return (int16)::_InterlockedIncrement16((short*)value);
    }
    
    static inline int32 InterlockedIncrement(volatile int32 *value)
    {
        return (int32)::_InterlockedIncrement((long*)value);
    }

    static inline int64 InterlockedIncrement(volatile int64 *value)
    {
        return (int64)::_InterlockedIncrement64((long long*)value);
    }

//Decrement
    static inline int8 InterlockedDecrement( volatile int8* Value )
	{
		return (int8)::_InterlockedExchangeAdd8((char*)Value, -1) - 1;
	}
	static inline int16 InterlockedDecrement( volatile int16* Value )
	{
		return (int16)::_InterlockedDecrement16((short*)Value);
	}

	static inline int32 InterlockedDecrement( volatile int32* Value )
	{
		return (int32)::_InterlockedDecrement((long*)Value);
	}

	static inline  int64 InterlockedDecrement( volatile int64* Value )
	{
        return (int64)::_InterlockedDecrement64((long long*)Value);
	}
    //Add
    static inline int8 InterlockedAdd(volatile int8* value,int8 amount)
    {
        return (int8) ::_InterlockedExchangeAdd8((char*)value,(char)amount);
    }
    static inline int16 InterlockedAdd(volatile int16* value,int16 amount)
    {
        return (int16) ::_InterlockedExchangeAdd16((short*)value,(short)amount);
    }
    static inline int32 InterlockedAdd(volatile int32* value,int32 amount)
    {
        return (int32) ::_InterlockedExchangeAdd32((long*)value,(long)amount);
    }

    static inline int64 InterlockedAdd(volatile int64* value,int64 amount)
    {
        return (int64) ::_InterlockedExchangeAdd64((long long*)value,(long long)amount);
    }
//Exchange
    static inline int8 InterlockedExchange(volatile int8*value,int8 exchange)
    {
        return (int8)::_InterlockedExchange8((char*)value,(char)exchange);
    }
    static inline int16 InterlockedExchange(volatile int16*value,int16 exchange)
    {
        return (int16)::_InterlockedExchange16((short*)value,(short)exchange);
    }
    static inline int32 InterlockedExchange(volatile int32*value,int32 exchange)
    {
        return (int32)::_InterlockedExchange8((long*)value,(long)exchange);
    }
    static inline int64 InterlockedExchange(volatile int64*value,64 exchange)
    {
        return (long)::_InterlockedExchange8((long long*)value,(long long)exchange);
    }
};