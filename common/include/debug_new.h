#pragma once


#ifdef _DEBUG 
#ifdef DEBUG_NEW
#define new DEBUG_NEW
#endif
#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif


#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC2__ __FILE__ "("__STR1__(__LINE__)") : "

#ifdef NDEBUG
#define FIXME __pragma(message(__LOC2__ "error C666: found FIXME in release build!"))
#else
#define FIXME
#endif


#endif 

