#ifndef COMMONDEF_LKSJDLFKJDSLFKJSLDFJSDLFKJLSDKFJLSDKF
#define COMMONDEF_LKSJDLFKJDSLFKJSLDFJSDLFKJLSDKFJLSDKF

enum 
{
	MB_INPACKET	= ACE_Message_Block::MB_USER +1,				//报文处理
	MB_D_TIMEOUT,												//房间超时检查机制
	MB_CACHEREQ,												//db cache处理返回
	MB_SWITCH_MSG,												//Msg Switch消息
	MB_RELOADROOMINFO,											//重读房间信息
	MB_GLOBLE_MSG,												//全局小喇叭
	MG_GLOBLE_GREAT_GIFT,										//全局大礼广播
};


#endif
