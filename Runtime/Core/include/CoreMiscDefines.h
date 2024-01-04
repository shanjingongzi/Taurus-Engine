#pragma once
#include "PreprocessorHelpers.h"

#define WARNING_LOCATION(Line) __FILE__ "(" PREPROCESSOR_TO_STRING(Line) ")"

enum {INDEX_NONE =-1};
enum { UNICODE_BOM = 0xfeff };

enum EForceInit
{
	ForceInit,
	ForceInitToZero
};


enum ENoInit { NoInit };
enum EInPlace { InPlace };
