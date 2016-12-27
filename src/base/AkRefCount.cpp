/*********************************************
 * Copyright 2016 Aiks Group
 * ******************************************/
#ifndef AIKS_BASE_REFCOUNT_H
#define AIKS_BASE_REFCOUNT_H

#include "AkTypes.h"

namespace aiks {

class AkRefCount
{
private:
		s32 _refCount;
public:
		AkRefCount();
		~AkRefCount();
		void add();
		void release();
		Int32 getCount() const;
}

}

#endif
