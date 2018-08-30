/***************************************************************************
 *                                                                         *
 *   copyright            : (C) 2002 by tiny                         *
 ***************************************************************************/

#ifndef _tinyD_LIST_H_
#define _tinyD_LIST_H_


#ifndef LIST_ENTRY
#define LIST_ENTRY(ptr, type, member) \
	((type *) ((char *) (ptr) - (unsigned long) (&((type *) 0)->member)))
#endif

#ifndef LIST_FOR_EACH
#define LIST_FOR_EACH(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)
#endif


class  ListHead {
public:
	ListHead() {
		prev = next = this;
	}
	~ListHead()
	{
		remove();
	}
	bool isEmpty() {
		return ( next == this);
	}
	ListHead *removeHead();
	void add(ListHead *item);
	void addHead(ListHead *item);
	void remove();


	ListHead *prev, *next;
};


#endif
