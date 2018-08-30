#ifndef INC_ELASTICSEARCHTTP_H
#define INC_ELASTICSEARCHTTP_H

#include "include/baseHttpClient.h"
#include "json/json.h"


#define SORT_ASC		"asc"		//����
#define SORT_DESC		"desc"		//����
#define SEARCH_TIME		"@timestamp"

class CTLSearchJson:public Json::Value
{
public:
	CTLSearchJson(const char* fileName);
	virtual ~CTLSearchJson();

public:
	virtual std::string GetFastJson();

public:
	const std::string  m_fileName;

};




class CTLSearchRange:public CTLSearchJson
{
public:
	CTLSearchRange(const char* rangeFiled);
	~CTLSearchRange();
	//���ڵ���
	void SetGte(Json::Value& val);

	//����
	void SetGt(Json::Value& val);

	//С�ڵ���
	void SetLte(Json::Value& val);

	//С��
	void SetLe(Json::Value& val);
private:
	void ResetRoot();
	void AddKeyVal(const char* key, Json::Value& val);

public:
	const std::string m_rangeFiled;
};

class CTLSearchMatch:public CTLSearchJson
{
public:
	CTLSearchMatch();
	~CTLSearchMatch();

	void SetMatchKeyVal(const char* key, Json::Value& val);
private:

};

class CTLSearchMatchAll:public CTLSearchJson
{
public:
	CTLSearchMatchAll();
	~CTLSearchMatchAll();
};

//������ѯ����
class CTLSearchBoolChild:public CTLSearchJson
{
protected:
	CTLSearchBoolChild(const char* boolName);
	~CTLSearchBoolChild();

	void AddRange(CTLSearchRange& range);
	void AddMatch(CTLSearchMatch& match);
public:
	
};



//
class CTLSearchMust:public CTLSearchBoolChild
{
public:
	CTLSearchMust();
	~CTLSearchMust();

	
};

// and not
class CTLSearchMustNot:public CTLSearchBoolChild
{
public:
	CTLSearchMustNot();
	~CTLSearchMustNot();
};

//or
class CTLSearchShould:public CTLSearchBoolChild
{
public:
	CTLSearchShould();
	~CTLSearchShould();
};


//������ѯ
class CTLSearchBool:public CTLSearchJson
{
public:
	CTLSearchBool();
	~CTLSearchBool();

	//����Ӳ�ѯ must mustnot should ׷��
	void AddBoolChild(CTLSearchBoolChild& child);

	//�����ѯ����
	void ResetChild();
private:

};

class CTLSearchSort:public CTLSearchJson
{
public:
	CTLSearchSort();
	virtual ~CTLSearchSort();

public:
	//�������� Ĭ�ϰ�ʱ�併��
	void SetSort(const char* key = SEARCH_TIME, const char* sort = SORT_DESC);

	//׷������
	void AppSort(const char* key = SEARCH_TIME, const char* sort = SORT_DESC);

};

class CTLSearchQuery:public CTLSearchJson
{
public:
	CTLSearchQuery();
	~CTLSearchQuery();

public:
	//���ö���bool�־��ѯ
	void SetBoolSearch(CTLSearchBool& boolSearch);

	//�����ֶ�ƥ���ѯ
	void SetMatchSeach(CTLSearchMatch& matchSearch);

	//��������
	void SetSort(CTLSearchSort& sort);


};

class CTLSearchDate:public CTLSearchJson
{
public:
	CTLSearchDate();
	~CTLSearchDate();

public:
	void SetFromTo(uint64 startTime, uint32 endTime);

};

 

class CTLElasticSearch:public CTLSearchJson, public CTLHttpReqBase
{
public:
	CTLElasticSearch(CTLhttpClientChannel* channel, const char* host, const char* path, uint16 port);
	~CTLElasticSearch();
	
	
	//
	
	void SendReq();


	//���ò�ѯ�ĵ����� ��������
	void SetSearchIndex(const char* searchIndex);

	//���ò�ѯ�ĵ�����׷������ �������ڴ���������
	void SetSearchIndexWithDate(const char* searchIndex);

	//���ò�ѯ���� ������ȡ��������
	void SetReqFilter(Json::Value& val);


	//���÷�ҳ���ݴ�С
	void SetNum(uint32 size);

	//�����α� �ͷ�ҳ���ʹ��
	void SetFrom(uint64 from);

public:
	virtual void OnResp(int nCode, void* pData, int nLen);

private:
	void AddFilterKeyVal(Json::Value& root,Json::Value& val);

private:
	std::string m_defaultTime;
	std::string m_filter;
	Json::Value m_jsFilterRoot;
	Json::Value m_startTime;
	Json::Value m_endTime;
	std::string m_index;
	uint32		m_size;
	uint64		m_from;
};

void CTLElasticSearch::SendReq()
{
	string str = GetFastJson();
	SetReqData(str.c_str(), str.length());
}




#endif

