#include "Object.h"
#include <typeinfo>

Object::~Object ()
    {}

bool Object::IsNull () const
    { return false; }

int Object::Compare (Object const& object) const
{
    if (typeid (*this) == typeid (object))
	return CompareTo (object);
    else if (typeid (*this).before (typeid (object)))
	return -1;
    else
	return 1;
}
