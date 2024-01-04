#include <VarRange.h>

VarRange::iterator::iterator(ObjectTree::iterator typeiter,CVRefMode cvref_mode,FieldFlag flag)
	:typeiter{ typeiter }, cvref_mode{ cvref_mode }, flag{ flag }, mode{ typeiter.Vaild() ? 0 : -1 }
{
	if (typeiter.Vaild()) {
		update();
	}
}

void VarRange::iterator::update()
{
}

VarRange::iterator& VarRange::iterator::operator++() {
	update();
	return *this;
}

VarRange::iterator VarRange::iterator::operator++(int) {
	VarRange::iterator iter = *this;
	(void)operator++();
	return iter;
}

bool operator==(const VarRange::iterator& lhs, const VarRange::iterator& rhs) {
	assert(lhs.flag == rhs.flag);
	assert(lhs.cvref_mode == rhs.cvref_mode);
	if (lhs.Valid()) {
		if (rhs.Valid()) {
			if (lhs.typeiter == rhs.typeiter)
				return lhs.curfield == rhs.curfield;
			else
				return false;
		}
		else
			return false;
	}
	else if (rhs.Valid())
		return false;
	else
		return lhs.typeiter == rhs.typeiter;
}

bool operator!=(const VarRange::iterator& lhs, const VarRange::iterator& rhs) 
{
	return !(lhs == rhs);
}