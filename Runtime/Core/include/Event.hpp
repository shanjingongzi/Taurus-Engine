#ifndef EVENT_HPP
#define EVENT_HPP
#include <functional>
#include <vector>
template<typename Return,typename ...Args>
class Event
{
public:
	void Invoke(Args...arg)
	{
		for (auto& iter : handles) {
			iter(std::forward<Args>(arg)...);
		}
	}

	bool Empty()const
	{
		return handles.size() == 0;
	}

	void operator +=(std::function<Return(Args...)>func)
	{
		handles.emplace_back(func);
	}
private:
	std::vector<std::function<Return(Args...)>>handles;
};
#endif