#include "Container.h"

Container::Container () :
    count (0)
    {}

unsigned int Container::Count () const
    { return count; }

bool Container::IsEmpty () const
    { return Count () == 0; }

bool Container::IsFull () const
    { return false; }
