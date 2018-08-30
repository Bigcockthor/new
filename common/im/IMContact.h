// IMContact.h: interface for the IMContact class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMCONTACT_H__C321755C_D6E4_46E9_BD47_A0F0F336BC3B__INCLUDED_)
#define AFX_IMCONTACT_H__C321755C_D6E4_46E9_BD47_A0F0F336BC3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IM/IMTypes.h"
#include "im/imdefine.h"

class  IMContact  
{
public:
enum {
	IM_STATUS_ONLINE,
	IM_STATUS_OFFLINE,
	IM_STATUS_AWAY,
	IM_STATUS_INVIS,
	IM_NR_STATUS
};
public:
	


	uint32 uin;
	string nick;
	uint8 face;
	uint8 gender;
	uint8 age;
	string country;
	string province;
	string city;

	string email;
	string address;
	string zipcode;
	string tel;

	// 得到自己的口令,这个功能的开放比较可怕,如果要开放插件结构的话，要对这个功能作限制 [9/14/2003 14:16 why]
	string passwd;

	string name;
	uint8 blood;
	string college;
	string profession;
	string homepage;
	string intro;

	uint32 status;

	int type;
	uint32 ip;
	uint16 port;
	uint32 realIP;
	
	uint8 video;
	uint8 audio;
	
	uint8 level;

	
	IMContact& operator=(const IMContact& x)
	{
		uin = x.uin;
		nick = x.nick;
		face = x.face;
		gender = x.gender;
		age = x.age;
		country = x.country;
		province = x.province;
		city = x.city;

		email = x.email;
		address = x.address;
		zipcode = x.zipcode;
		tel = x.tel;

		name = x.name;
		blood = x.blood;
		college = x.college;
		profession = x.profession;
		homepage = x.homepage;
		intro = x.intro;

		status = x.status;

		type = x.type;
		ip = x.ip;
		port = x.port;
		realIP = x.realIP;
	
		video = x.video;
		audio = x.audio;
	
		level = x.level;
		return *this;
	}
	IMContact()
	{
		uin = 0;
		face = 0;
		gender = 0;
		age = 0;
		blood = 0;

		status = IMContact::IM_NR_STATUS;

		ip = 
			realIP = 0;
		port = 0;
		video = 0;
		audio = 0;
		level = VipLevel::NOT_VIP;
		m_isValid = false;
	}

	virtual ~IMContact()
	{

	}

	bool isValid()
	{
		return m_isValid;
	}
	void setValid(bool isvalid)
	{
		m_isValid = isvalid;
	}
private:
	bool m_isValid;
};



#endif // !defined(AFX_IMCONTACT_H__C321755C_D6E4_46E9_BD47_A0F0F336BC3B__INCLUDED_)
