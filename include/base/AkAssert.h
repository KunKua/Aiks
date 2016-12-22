/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/
#ifndef AK_BASE_ASSERT_H
#define AK_BASE_ASSERT_H

#if defined(__cplusplus) && !defined(__RECODE__)
	#define COMPILE_TIME_ASSERT(expr) static_assert(expr, # expr)
#else
	#define COMPILE_TIME_ASSERT(expr)
#endif

#endif
