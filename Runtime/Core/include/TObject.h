#ifndef T_OBJECT_H
#define T_OBJECT_H
#include <string>
#include "Core.h"
#include <vector>
#include "Platform.h"
class TObject
{
public:
	virtual ~TObject() {}
	inline bool IsEmpty()const
	{
		return true;
	}
	int32 GetUniqueID()
	{
		return 1;
	}
};


#endif
