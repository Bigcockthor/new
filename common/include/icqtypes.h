/***************************************************************************
 *                                                                         *
 *   copyright            : (C) 2002 by eph                         *
 ***************************************************************************/

#ifndef _ICQ_TYPES__H
#define _ICQ_TYPES__H

#ifndef uint8
	typedef unsigned char uint8;
#endif


#ifndef uint16
	typedef unsigned short uint16;
#endif

#ifndef uint32
	typedef unsigned int uint32;
#endif

#ifndef uint64
	typedef unsigned long long uint64;
#endif

#ifndef int64
	typedef long long int64;
#endif

#ifndef ICQ_STR
  typedef  struct _ICQ_STR {
  	const char *text;
  	uint16 len;
  }ICQ_STR;
#endif


template <typename T>
void ClearSTLArray(T &l)
 {
	 while(l.size())
	 {
		 delete *(l.begin());
		 l.erase(l.begin());
	 }
 }

#endif

