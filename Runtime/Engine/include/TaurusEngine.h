#pragma once

class IEngineLoop
{
public:
	virtual int Init() = 0;
	virtual void Tick() = 0;
	virtual void ClearPendingCleanupObjects() = 0;
};
