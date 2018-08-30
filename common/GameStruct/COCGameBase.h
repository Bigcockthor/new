#ifndef	COC_GAME_MAGR_H
#define COC_GAME_MAGR_H
#include "dbclient/dbclient4coc.h"
#include "msgswitch/beanstalkclient.h"
namespace BigRoom
{
	class User;
}
using namespace BigRoom;
class UdpInPacket;
namespace TaoleGame  
{  
	//µ¼³öÀà  
	class GameBase
	{  
	public:  
		GameBase(){};  
		virtual ~GameBase(){};  
	public:
		virtual void HandleGameDbResult(dataport::CDBClientResult* result){};	
		virtual int HandleGamePacket(UdpInPacket *in, User* user){ return 0;};
		virtual void HandleBeanstalkMsg(Beanstalk::BCMessageBase *bcMsg){};
		virtual void HandUserGameTimeOut(User * user){};
		virtual int OnLoginGame(User * user){return 0;};
		virtual int	OnHandleGameTimeout(){return 0;};
	};  
}
#endif
