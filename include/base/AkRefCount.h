/*********************************************
 * Copyright 2016 Aiks Group
 * ******************************************/
#ifndef AIKS_BASE_REFCOUNT_H
#define AIKS_BASE_REFCOUNT_H

#include "AkTypes.h"

namespace aiks {

class RefCount
{
private:
		Int32 _refCount;
public:
		RefCount();
		~RefCount();
		void add();
		void release();
		Int32 getCount() const;
}

}

#endif
