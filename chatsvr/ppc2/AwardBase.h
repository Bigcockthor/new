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
		STAR_XIAO_LIUHUAN_5,									//0 	С����	
		STAR_XIAO_SUNLAN_2,										//1 	С���
		STAR_XIAO_ZHANGXUEYOU_4,									//2 	С��ѧ��
		STAR_XIAO_ZHOUJIELUN_3,									//3 	С�ܽ���
		STAR_XIAO_LIYUCHUN_6,										//4 	С���
		STAR_XIAO_HANHONG_4,										//5 	С����
		STAR_XIAO_WANGFEI_6,										//6 	С����
		STAR_XIAO_CAIYILIN_5,										//7 	С������
		STAR_XIAO_TIANWAN_25,										//8 	С����	
		STAR_DALU_NAN,											//9 	��½��
		STAR_DALU_NV,											//10	��½Ů
		STAR_GANGTAI_NAN,										//11	��̨��
		STAR_GANGTAI_NV,										//12	��̨Ů
		STAR_DA_LIUHUAN_15,										//13 	������				
		STAR_DA_SUNLAN_10,											//14 	�����		
		STAR_DA_ZHANGXUEYOU_12,									//15 	����ѧ��
		STAR_DA_ZHOUJIELUN_10,										//16 	���ܽ���
		STAR_DA_LIYUCHUN_25,										//17 	�����
		STAR_DA_HANHONG_15,										//18 	�󺫺�
		STAR_DA_WANGFEI_30,										//19 	������
		STAR_DA_CAIYILIN_20,										//20 	�������
		STAR_DA_TIANWAN_50,										//21 	������	
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
	
	uint8 awardedValue[13];										//��ǰ����upֵ

	uint8 dynamic[ZZAward::STAR_DA_TIANWAN_50+1];			//ĳ����󿪽�����
	uint8 minTimes[ZZAward::STAR_DA_TIANWAN_50+1];			//ĳ����С��������

	

	const static double upValue[ZZAward::STAR_DA_TIANWAN_50+1];	//�⳥����
	
	/*
	 *	����ĳ�������С���ִ���
	 */
	void SetItemTimes(uint8 itemIndex, uint8 itemMinTimes, uint8 dynamicTimes);	

	/*
	 *	��ʼ���⳥����
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


