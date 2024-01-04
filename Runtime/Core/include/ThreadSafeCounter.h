#pragma once

class ThreadSafeCounter
{
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
		return ++counter;
	}

	int32 Add(int32 amount)
	{

	}

	int32 Decrement()
	{
		return --counter;
	}

private:
	volatile uint32 counter;
};