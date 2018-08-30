#ifndef INC_ELASTICSEARCHTTP_H
#define INC_ELASTICSEARCHTTP_H

#include "include/baseHttpClient.h"
#include "json/json.h"


#define SORT_ASC		"asc"		//升序
#define SORT_DESC		"desc"		//降序
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
	//大于等于
	void SetGte(Json::Value& val);

	//大于
	void SetGt(Json::Value& val);

	//小于等于
	void SetLte(Json::Value& val);

	//小于
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

//条件查询基类
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


//条件查询
class CTLSearchBool:public CTLSearchJson
{
public:
	CTLSearchBool();
	~CTLSearchBool();

	//添加子查询 must mustnot should 追加
	void AddBoolChild(CTLSearchBoolChild& child);

	//清理查询条件
	void ResetChild();
private:

};

class CTLSearchSort:public CTLSearchJson
{
public:
	CTLSearchSort();
	virtual ~CTLSearchSort();

public:
	//设置排序 默认按时间降序
	void SetSort(const char* key = SEARCH_TIME, const char* sort = SORT_DESC);

	//追加排序
	void AppSort(const char* key = SEARCH_TIME, const char* sort = SORT_DESC);

};

class CTLSearchQuery:public CTLSearchJson
{
public:
	CTLSearchQuery();
	~CTLSearchQuery();

public:
	//设置多重bool字句查询
	void SetBoolSearch(CTLSearchBool& boolSearch);

	//设置字段匹配查询
	void SetMatchSeach(CTLSearchMatch& matchSearch);

	//设置排序
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


	//设置查询文档索引 标题名字
	void SetSearchIndex(const char* searchIndex);

	//设置查询文档索引追加日期 根据日期创建的索引
	void SetSearchIndexWithDate(const char* searchIndex);

	//设置查询条件 不设置取所有数据
	void SetReqFilter(Json::Value& val);


	//设置分页数据大小
	void SetNum(uint32 size);

	//设置游标 和分页配合使用
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

