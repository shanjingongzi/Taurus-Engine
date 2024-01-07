#pragma once
#include "WindowsPlatformatomics.h"
class ThreadSafeCounter
{
	using Type =int32;
public:
	typedef int32 IntergerType;
	ThreadSafeCounter() :counter{ 0 }
	{
	}

	ThreadSafeCounter(const ThreadSafeCounter& other)
	{
		counter = other.GetValue();
	}

	ThreadSafeCounter(uint32 value) :counter{ value }
	{

	}

	IntergerType GetValue()const
	{
		return counter;
	}

	int32 Increament()
	{
		return WindowPlatformAtomics::InterlockedIncrement(&counter);
	}

	int32 Add(int32 amount)
	{
		return WindowPlatformAtomics::InterlockedAdd(&counter,amount);
	}

	int Substract(int32 amount)
	{
		return WindowPlatformAtomics::InterlockedAdd(&counter,-amount);	
	}

	int32 Decrement()
	{
		return WindowPlatformAtomics::InterlockedDecrement(&counter);
	}

	int32 Set(int32 value)
	{
		return WindowPlatformAtomics::InterlockedExchange(&counter,value);
	}

	int32 Reset()
	{
		return WindowPlatformAtomics::InterlockedExchange(&counter,0);
	}
private:
	volatile Type counter;
};