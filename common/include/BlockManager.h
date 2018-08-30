#pragma once
#include "include/sync.h"
#include "icqtypes.h"
#include <string>
#include <map>


namespace WingUtil
{
	using namespace std;


	typedef std::map<uint64, uint32> BlockMap;


	class BlockManager
	{
	public:
		BlockManager(void);
		virtual ~BlockManager(void);

		virtual void AddBlockItem(uint64 item, uint32 expire);
		virtual void DelBlackItem(uint64 item);

		virtual bool CheckItem(uint64 item);

		virtual void clear(void);
	private:
		Mutex blockMutex;
		BlockMap	blockItemsMap;

	};

}
