#pragma once
#include "include/icqtypes.h"
#include "include/coretime.h"
#include <vector>
#include "room/RoomCommon.h"


class AwardBaseOption
{
public:
	AwardBaseOption(){}
	virtual ~AwardBaseOption(){};
};

class AwardBase
{
public:
	AwardBase(void);
	virtual ~AwardBase(void);
	
	virtual void UpdateOption(AwardBaseOption *option) = 0;
};

class ZZOption : public AwardBaseOption
{
public:
	ZZOption();
	virtual ~ZZOption();
	ZZOption &operator =(ZZOption &w);

	ZZSetting setting;
};

typedef std::vector<uint8> AwardList;




class ZZAward : public AwardBase
{
public:
	enum StartName
	{
		STAR_XIAO_LIUHUAN_5,									//0 	小刘欢	
		STAR_XIAO_SUNLAN_2,										//1 	小孙楠
		STAR_XIAO_ZHANGXUEYOU_4,									//2 	小张学友
		STAR_XIAO_ZHOUJIELUN_3,									//3 	小周杰伦
		STAR_XIAO_LIYUCHUN_6,										//4 	小李宇春
		STAR_XIAO_HANHONG_4,										//5 	小韩红
		STAR_XIAO_WANGFEI_6,										//6 	小王菲
		STAR_XIAO_CAIYILIN_5,										//7 	小蔡依林
		STAR_XIAO_TIANWAN_25,										//8 	小天王	
		STAR_DALU_NAN,											//9 	大陆男
		STAR_DALU_NV,											//10	大陆女
		STAR_GANGTAI_NAN,										//11	港台男
		STAR_GANGTAI_NV,										//12	港台女
		STAR_DA_LIUHUAN_15,										//13 	大刘欢				
		STAR_DA_SUNLAN_10,											//14 	大孙楠		
		STAR_DA_ZHANGXUEYOU_12,									//15 	大张学友
		STAR_DA_ZHOUJIELUN_10,										//16 	大周杰伦
		STAR_DA_LIYUCHUN_25,										//17 	大李宇春
		STAR_DA_HANHONG_15,										//18 	大韩红
		STAR_DA_WANGFEI_30,										//19 	大王菲
		STAR_DA_CAIYILIN_20,										//20 	大蔡依林
		STAR_DA_TIANWAN_50,										//21 	大天王	
	};

	enum
	{
		LOOP_MAX_ITEMS = 200,
	};

	ZZAward();
	~ZZAward();

	virtual void UpdateOption(AwardBaseOption *option);
	char Award(double *upV);
	inline uint32 rand32()
	{
		return (((rand() * talk_base::TimeStamp())<< 15) | (rand() & 0x7fff));
	}

	ZZOption opt;
	
	uint8 awardedValue[13];										//当前开奖up值

	uint8 dynamic[ZZAward::STAR_DA_TIANWAN_50+1];			//某项最大开奖次数
	uint8 minTimes[ZZAward::STAR_DA_TIANWAN_50+1];			//某项最小开奖次数

	

	const static double upValue[ZZAward::STAR_DA_TIANWAN_50+1];	//赔偿倍数
	
	/*
	 *	设置某项最大最小出现次数
	 */
	void SetItemTimes(uint8 itemIndex, uint8 itemMinTimes, uint8 dynamicTimes);	

	/*
	 *	初始华赔偿倍数
	 */
	void InitUpValue(uint8 awardid, double *upV);


	void RandForAward();

private:
	bool inited;
	
	AwardList awards;
	


	void ReSortAward(AwardList &l, AwardList &l2);

	uint8 GetBigStep();

	uint8 GetPrize(uint8 modSed);



};


