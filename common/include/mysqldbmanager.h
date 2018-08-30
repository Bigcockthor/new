/***************************************************************************
 *                                                                         *
 *   copyright            : (C) 2002 by tiny                         *
 ***************************************************************************/

#ifndef _DB_MANAGER_H
#define _DB_MANAGER_H
#include <string>
#include "include/icqtypes.h"
#include "include/Markup.h"
#include "include/queue.h"
#include "include/slab.h"
#include "include/list.h"
#include "mysql/include/mysql.h"
#include "include/icqsocket.h"
using namespace std;



#ifndef WRITE_STR
#define WRITE_STR(req, str)		req.writeString((str), strlen(str))
#endif

#ifndef WRITE_BUF
#define WRITE_BUF(req, buf, len) req.writeBuffer((void *)(buf), (len));
#endif

class DBInfo 
{
public:
	string host;
	uint16 port;
	string db;
	string user;
	string passwd;
	uint16 update;
	uint16 query;
	uint8 minCN;
	uint8 maxCN;
	string charset;

	DBInfo &operator =(DBInfo &in)
	{
		host	= in.host;
		port	= in.port;
		db		= in.db;
		user	= in.user;
		passwd	= in.passwd;
		update	= in.update;
		query	= in.query;
		minCN	= in.minCN;
		maxCN	= in.maxCN;
		charset = in.charset;

		return *this;
	}

	void ReadDbSetting(CMarkup &xml, char *attrib);
};

#define DBREQUEST	1
#define DBREQUESTEX	2
#define MAX_SQL		4096
#define MAX_SQL_EX	20480
#define DB_UPDATE_OK 0

char *conv10(uint32 num, char *bufEnd);

typedef SyncList<MYSQL *> DBConnectionPool;

class DBRequestBase;
class UserManager;
class DNSUser;
class UdpInPacket;



typedef void (UserManager::*DBReqCallBack)(DBRequestBase *);


MYSQL *mysqlInit(DBInfo &info);
void mysqlClose(MYSQL *mysql);

void ProcessDbRequest(MYSQL *&mydb, DBRequestBase *req, DBInfo *info = NULL);

class DBRequestBase 
{
	friend class DBTaskProcessor;
public:
	
	virtual ~DBRequestBase();

	ListHead listItem;

	uint32 lastId;

	union {
		MYSQL_RES *res;
		int ret;
	};

	inline void Callback(void);

	bool isUpdate;
	bool isGetLastId;

	virtual int sqlLen() = 0;
	virtual char* sqlbuf() = 0;

protected:

	UdpInPacket *in;



	uint8 dbtype;

	DBRequestBase();
};

class DBRequest :public DBRequestBase
{
friend class DBTaskManager;
public:
	DBRequest(bool mIsUpdate, MYSQL *mysql);
	virtual ~DBRequest();

	void writeString(const char *text, int n) {
		if (cursor - sql + n <= MAX_SQL) {
			memcpy(cursor, text, n);
			cursor += n;
		}
	}
	void writeBuffer(void *buf, int n) {
		if (cursor - sql + (n << 1) < MAX_SQL - 2) {
			*cursor++ = '\'';
			cursor += mysql_real_escape_string(my, cursor, (const char *)buf, n);
			*cursor++ = '\'';
		}
	}
	DBRequest &operator <<(ICQ_STR &str) {
		if (cursor - sql + (str.len << 1) < MAX_SQL - 2) {
			*cursor++ = '\'';
			cursor += mysql_real_escape_string(my, cursor, str.text, str.len);
			*cursor++ = '\'';
		}
		return *this;
	}
	DBRequest &operator <<(char c) {
		if (cursor - sql + sizeof(c) <= MAX_SQL)
			*cursor++ = c;
		return *this;
	}
	DBRequest &operator <<(uint8 num) {
		*this << (uint32) num;
		return *this;
	}
	DBRequest &operator <<(uint16 num) {
		*this <<(uint32) num;
		return *this;
	}
	DBRequest &operator <<(uint32 num) {
		char buf[32] = {0};
		snprintf(buf, sizeof(buf)-1, "%u", num);
		writeString(buf, strlen(buf));
		return *this;
	}
	DBRequest &operator <<(int num) {
		char buf[32] = {0};
		snprintf(buf, sizeof(buf)-1, "%d", num);
		writeString(buf, strlen(buf));
		return *this;
	}
	DBRequest &operator <<(uint64 num) {
		char buf[32] = {0};
#ifdef _WIN32
		snprintf(buf, sizeof(buf)-1, "%I64u", num);
#else
		snprintf(buf, sizeof(buf)-1, "%llu", num);
#endif
		writeString(buf, strlen(buf));
		return *this;
	}
	DBRequest &operator <<(int64 num) {
		char buf[32] = {0};
#ifdef _WIN32
		snprintf(buf, sizeof(buf)-1, "%I64d", num);
#else
		snprintf(buf, sizeof(buf)-1, "%lld", num);
#endif
		writeString(buf, strlen(buf));
		return *this;
	}
	virtual int sqlLen() {
		return cursor - sql;
	}
	virtual char* sqlbuf() {
		return sql;
	}

protected:


	char sql[MAX_SQL];
	char *cursor;

	DECLARE_SLAB(DBRequest)
private:
	MYSQL *my;
};


class DBRequestEx : public DBRequestBase{
friend class DBTaskManager;
public:
	DBRequestEx(bool mIsUpdate);
	virtual ~DBRequestEx();

	void writeString(const char *text, int n) {
		if (cursor - sql + n <= MAX_SQL_EX) {
			memcpy(cursor, text, n);
			cursor += n;
		}
	}
	void writeBuffer(void *buf, int n) {
		if (cursor - sql + (n << 1) < MAX_SQL_EX - 2) {
			*cursor++ = '\'';
			cursor += mysql_escape_string(cursor, (const char *)buf, n);
			*cursor++ = '\'';
		}
	}
	DBRequestEx &operator <<(ICQ_STR &str) {
		if (cursor - sql + (str.len << 1) < MAX_SQL_EX - 2) {
			*cursor++ = '\'';
			cursor += mysql_escape_string(cursor, str.text, str.len);
			*cursor++ = '\'';
		}
		return *this;
	}
	DBRequestEx &operator <<(char *s)
	{
		int len = strlen(s);

		writeString(s, len);

		return *this;
	}
	DBRequestEx &operator <<(char c) {
		if (cursor - sql + sizeof(c) <= MAX_SQL_EX)
			*cursor++ = c;
		return *this;
	}
	DBRequestEx &operator <<(uint8 num) {
		*this << (uint32) num;
		return *this;
	}
	DBRequestEx &operator <<(uint16 num) {
		*this <<(uint32) num;
		return *this;
	}
	DBRequestEx &operator <<(uint32 num) {
		char buf[16];
		char *p = conv10(num, buf + sizeof(buf));
		writeString(p, buf + sizeof(buf) - p);
		return *this;
	}

	virtual int sqlLen() {
		return cursor - sql;
	}
	virtual char* sqlbuf() {
		return sql;
	}


protected:

	char sql[MAX_SQL_EX];
	char *cursor;

	DECLARE_SLAB(DBRequestEx)
};


class MysqlConnection
{
public:
	MysqlConnection(DBConnectionPool &p);
	~MysqlConnection();

	static void PingMysqlPoolCNS(DBConnectionPool &pool, DBInfo &info);

	MYSQL *db;
private:
	DBConnectionPool &pool;
};

class MysqlRow
{
public:
	MysqlRow(MYSQL_RES *res);
	bool GetFieldValue(int idx, uint8 &v);
	bool GetFieldValue(int idx, uint16 &v);
	bool GetFieldValue(int idx, uint32 &v);
	bool GetFieldValue(int idx, uint64 &v);
	bool GetFieldValue(int idx, int64 &v);
	bool GetFieldValue(int idx, string &v);
	bool Eof()
	{
		return (!row || !lengths);
	}
	void MoveNext(MYSQL_RES *res);

private:

	MYSQL_ROW row;
	unsigned long *lengths;
};



#endif


