// IMContact.cpp: implementation of the IMContact class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "im/IMContact.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMContact::IMContact()
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

IMContact::~IMContact()
{

}

bool IMContact::isValid()
{
	return m_isValid;
}
void IMContact::setValid(bool isvalid)
{
	m_isValid = isvalid;
}

