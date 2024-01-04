#pragma once

class NonCopyable
{
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
	NonCopyable& operator=(const NonCopyable&) {}
};