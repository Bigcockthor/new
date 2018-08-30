 #include "AwardBase.h"
#include "include/log.h"
#include "include/coretime.h"
#include "option.h"

const double ZZAward::upValue[] = {5.0, 2.0, 4.0, 3.0, 6.0, 4.0, 6.0, 5.0, 25.0, 3.2, 3.2, 3.2, 3.2, 15.0, 10.0, 12.0, 10.0, 25.0, 15.0, 30.0, 20.0, 50.0};



AwardBase::AwardBase(void)
{
	srand(time(NULL));
}

AwardBase::~AwardBase(void)
{
}

ZZOption::ZZOption()
{
} 

ZZOption::~ZZOption()
{
	
}

ZZOption & ZZOption::operator=( ZZOption &w )
{
	setting = w.setting;

	return *this;
}

ZZAward::ZZAward() : inited(false)
{
	memset(minTimes, 0, sizeof(minTimes));
	memset(dynamic, 0, sizeof(dynamic));
}


void ZZAward::UpdateOption( AwardBaseOption *option )
{
	opt = *(ZZOption *)option;

	inited = true;
}

char ZZAward::Award(double *upV)
{
	if (inited == false)
		return -1;

	if (awards.size() == 0)
		RandForAward();

	if (awards.size() == 0)
		return -1;

	uint8 ret = awards[0];
	awards.erase(awards.begin());


	upV[ret] = upValue[ret];
	if (ret == 8 || ret == 21)
		upV[9] = upV[10] = upV[11] =upV[12]  = upValue[9];
	else if (ret == 0 || ret == 1 || ret == 13 || ret == 14)
		upV[9] =  upValue[9];
	else if (ret == 2 || ret == 3 || ret == 15 || ret == 16)
		upV[11] =  upValue[9];
	else if (ret == 4 || ret == 5 || ret == 17 || ret == 18)
		upV[10] =  upValue[9];
	else if (ret == 6 || ret == 7 || ret == 19 || ret == 20)
		upV[12] =  upValue[9];

	return ret;
}

ZZAward::~ZZAward()
{

}



void ZZAward::ReSortAward( AwardList &l, AwardList &l2 )
{
	while(l.size())
	{
		uint8 idx = uint8(rand() % l.size());

		l2.push_back(l[idx]);

		l.erase(l.begin()+idx);		
	}
}

uint8 ZZAward::GetBigStep()
{
	return uint8(4 + rand() % 10);
}

uint8 ZZAward::GetPrize( uint8 modSed )
{
	uint8 ret = uint8((rand() * talk_base::TimeStamp()) % modSed);

	while (ret >= ZZAward::STAR_XIAO_TIANWAN_25 && ret < ZZAward::STAR_DA_LIUHUAN_15)
	{
		ret = uint8(rand() % modSed);
	}

	return ret;
}

void ZZAward::InitUpValue(uint8 awardid, double *upV)
{

	upV[awardid] = upValue[awardid];
	if (awardid == 8 || awardid == 21)
		upV[ZZAward::STAR_DALU_NAN] = upV[ZZAward::STAR_DALU_NV] = 
		upV[ZZAward::STAR_GANGTAI_NAN] =upV[ZZAward::STAR_GANGTAI_NV]  = upValue[9];
	else if (awardid == 0 || awardid == 1 || awardid == 13 || awardid == 14)
		upV[9] =  upValue[9];
	else if (awardid == 2 || awardid == 3 || awardid == 15 || awardid == 16)
		upV[11] =  upValue[9];
	else if (awardid == 4 || awardid == 5 || awardid == 17 || awardid == 18)
		upV[10] =  upValue[9];
	else if (awardid == 6 || awardid == 7 || awardid == 19 || awardid == 20)
		upV[12] =  upValue[9];
}

void ZZAward::RandForAward()
{

	AwardList tempList;
	

	for (uint8 i=0; i<=STAR_DA_TIANWAN_50; i++)
	{
		if ((i < STAR_DALU_NAN || i > STAR_GANGTAI_NV))
		{
			uint8 randCount = uint8(dynamic[i] ? (rand32() % dynamic[i]): 0);
			uint8 iCount = minTimes[i] + randCount;

			for (uint8 iTimes = 0; iTimes < iCount; iTimes++)
			{
				if (tempList.size() < LOOP_MAX_ITEMS)
					tempList.push_back(i);
				else
					LOG(1)("max items  %d\n", i);
			}
		}
	}

	awards.clear();
	if (tempList.size())
	{
		uint8 iPos = 0;
		uint8 iOldIdx1 = 0;
		uint8 iOldIdx2 = 0;
		do 
		{
			iPos = uint8(rand32() % tempList.size());
			uint32 lastRand1 = rand32() % 40;
			uint32 lastRand2 = rand32() % 20;
			if (tempList[iPos] < STAR_XIAO_TIANWAN_25 ||  (iOldIdx1 < STAR_XIAO_TIANWAN_25 && iOldIdx2 < STAR_XIAO_TIANWAN_25) || 
				(iOldIdx1 >= STAR_XIAO_TIANWAN_25 && lastRand1 == 1) || (iOldIdx2 >= STAR_XIAO_TIANWAN_25 && lastRand2 == 1)) 
			{
				awards.push_back(tempList[iPos]);
				iOldIdx1 = tempList[iPos];
				tempList.erase(tempList.begin()+iPos);
			}
		} while (tempList.size());
	}

	if (awards.size())
		awards[0] = uint8(rand32() % STAR_XIAO_TIANWAN_25);


	uint8 iBig = 0, iSmall = 0;	
	for (uint8 i=0; i<awards.size(); i++)
	{
#ifdef _WIN32
		LOG(1)("%d\n", awards[i]);
#endif

		if (awards[i] >= STAR_XIAO_TIANWAN_25)
			iBig++;
		else 
			iSmall++;
	}
	LOG(1)("award count = %d big=%d small = %d\n", awards.size(), iBig, iSmall);

	inited = true;

	return;
}

void ZZAward::SetItemTimes( uint8 itemIndex, uint8 itemMinTimes, uint8 dynamicTimes )
{
	if (itemIndex <= STAR_DA_TIANWAN_50)
	{
		minTimes[itemIndex] = itemMinTimes;
		if (dynamicTimes > 0)
		{
			dynamic[itemIndex] = dynamicTimes + 1;
		}

	}


}


