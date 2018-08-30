#ifndef IMPRODUCT_DEFINE_KSDJJFSDFKSDJLDSFLSJDFLJSDF
#define IMPRODUCT_DEFINE_KSDJJFSDFKSDJLDSFLSJDFLJSDF
#include <string>
#include "imdefine.h"
#include "include/Markup.h"
#include "Projectdefine.h"
#include "include/md5class.h"
using namespace std;
/************************************************************************/
/* �й���IM�Ĳ�����                                                                     */
/************************************************************************/
class CIMProductInfo
{
public:
	CIMProductInfo()
	{
		m_moneyName = "IM��";
		m_proname = "IM";
		m_roomAccess = false;
		m_id = 0;
	};
	~CIMProductInfo(){};
public:
	string GetProductName()
	{
		return m_proname;
	}
	string GetAppName()
	{
		return m_appname.c_str();
	}
	//�õ�Ӧ�ó��������
	string GetAppFullName()
	{
		string temp = m_appname + ".exe";
		return temp.c_str();
	}
	string GetMoneyName()
	{
		return m_moneyName;
	}
	//�õ�IM��������������
	string GetImDomain()//Ҫ�����ȥ����
	{
		return m_domain;
	}
	string GetImSubDomain()
	{
		return m_subdomain;
	}
	string GetLoginImDomain()
	{
		return m_loginDomain;
	}
	string GetHallUrl()
	{
		return "http://"+m_domain+"/roomlist.php";
	}

	//ע��Э��˵��URL
	string GetRegAreeUrl()
	{

		return  "http://"+m_domain+"/regaree.PHP";

		
	}

	//�һ�����
	string GetPwdurl()
	{

		//return "http://"+m_domain+"/user.php?action=checkuserid";
		// readmine #2336
		return "http://"+m_domain+"/login.php?action=checkuserid";
	}
	string GetCompanyUrl()
	{
		return "http://"+m_domain;
	}

	//�õ������������,�Ĵ�����ǵ�RC���ҲҪ��
	static string GetIMClassName()
	{
		return "ZYIM#32770";
	}

	//�õ����³����������������,�Ĵ�����ǵ�RC���ҲҪ��
	static string GetIMUpdateClassName()
	{
		return "ZYIMUPDATE#32770";
	}
	//�õ����뷿���Э��ǰ�涨����ֶ�
	string GetEnterRoomPreUrl()
	{
		CString pid ;
		pid.Format("%lu",m_id);
		string md5tmp = CMD5::MD5(pid).substr(0,5);
		md5tmp = "rm" + md5tmp;
		return  md5tmp;
		//return m_roomurl;

	}
	string GetDomainMiddleName()
	{
		string::size_type nbeig = m_domain.find('.');
		string::size_type nend = m_domain.rfind('.');
		if (nbeig>0 || nend>nbeig)
		{
			string tem = m_domain.substr(nbeig+1,nend-nbeig-1);
			return tem;
		}
		else
			return "";
		

	}
	string GetSubDomainPreName()
	{
		string::size_type nbeig = m_subdomain.find('.');
		if (nbeig>0)
		{
			string tem = m_subdomain.substr(0,nbeig);
			return tem;
		}
		else
			return "";
	}
	
	string GetLoginServerURL()
	{ 
		return "http://"+m_fetchIMLoginServerURL;
	}
	uint32 GetGreateGFDispTime(){return m_greate_disp_times;};
private:
	string  m_fetchIMLoginServerURL;  // ��ȡIM��¼��������url
	string m_moneyName;  //����
	string m_domain;    //������
	string m_subdomain; //������
	uint32 m_broadCasePrice; //С���ȼ۸�
	uint8  m_roomAccess; //ͬһ�����������������
	string m_sRoomAccess;
	string m_roomurl;
	string m_proname;
	uint32	m_greate_disp_times;									//�󽱲��Ž���
	string m_appname;
	string m_loginDomain;
	uint32 m_id;
public:
	uint32 GetPartnerID()
	{
		return m_id;
	}
	void SetPartnerID(uint32 id)
	{
		m_id = id;
	}
	void SetRoomUrl(string roomurl)
	{
		m_roomurl = roomurl;
	}
	void SetImName(string imname)
	{
		m_proname= imname;
	}
	void SetMoneyName(string moneyname)
	{
		m_moneyName = moneyname;
	}
	void SetDomain(string domain)
	{
		m_domain = domain;
	}
	void SetSubDomain(string subdomain)
	{
		m_subdomain = subdomain;
	}
	void SetLoginDomain(string logindomain)
	{
		m_loginDomain = logindomain;
	}
	void SetAppNam(string appname)
	{
		m_appname = appname;
	}
	uint8 GetEnterRoomLimit()
	{
		return m_roomAccess;
	}

	uint32 GetBraodCasePrice()
	{
		return m_broadCasePrice;
	}
	void SetGreenChannelURL(const string& url)
	{
		m_fetchIMLoginServerURL = url;
	}
public:
	void BuildServerInfo(ParterInfo& paternifo)
	{

		if (paternifo.moneyName.length()>0)
		{
			string temp = paternifo.moneyName;
			temp = temp.erase(0,temp.find_first_not_of(" "));
			m_moneyName = temp.erase(temp.find_last_not_of(" ")+1);
		}
		if (paternifo.domainName.length()>0)
		{
			string temp = paternifo.domainName;
			temp = temp.erase(0,temp.find_first_not_of(" "));
			m_domain = temp.erase(temp.find_last_not_of(" ")+1);
		}
		if(paternifo.domainNameEx.length() > 0)
		{
			string temp = paternifo.domainNameEx;
			temp = temp.erase(0,temp.find_first_not_of(" "));
			m_subdomain = temp.erase(temp.find_last_not_of(" ")+1);
		}
		m_broadCasePrice = paternifo.broadCasePrice;
		m_roomAccess = paternifo.roomAccess;
		m_greate_disp_times = paternifo.greate_disp_times;
		m_sRoomAccess = paternifo.sRoomAccess;
		
	}
	string GetRoomAccess()
	{
		return m_sRoomAccess;
	}
	void SaveInfo(string filedir)
	{

		string filepath = filedir + "partner.xml";
		CMarkup xml;
		xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"gb2312\"?> "));
		xml.AddElem(_T("partner"));
		xml.AddChildElem(_T("id"),m_id);
		xml.AddChildElem(_T("roomurl"),m_roomurl.c_str());
		xml.AddChildElem(_T("imname"),m_proname.c_str());
		xml.AddChildElem(_T("moneyname"),m_moneyName.c_str());
		xml.AddChildElem(_T("domain"),m_domain.c_str());
		xml.AddChildElem(_T("subdomain"),m_subdomain.c_str());
		xml.AddChildElem(_T("logindomain"),m_loginDomain.c_str());
		xml.AddChildElem(_T("appname"),m_appname.c_str());
		xml.AddChildElem(_T("api"),m_fetchIMLoginServerURL.c_str());
		xml.Save(filepath.c_str());
	}

	void LoadFileInfo(string filedir)
	{
		string filepath = filedir + "partner.xml";
		CMarkup xml;
		if (xml.Load(filepath.c_str()))
		{
			if (xml.FindElem("partner"))
			{
				while (xml.FindChildElem())
				{
					CString tag = xml.GetChildTagName();
					
					if (tag.CompareNoCase("id")==0)
					{
						CString str = xml.GetChildData();
						m_id = atoi(str.GetBuffer());
						str.ReleaseBuffer();
					}


					if (tag.CompareNoCase("roomurl")==0)
					{
						CString str = xml.GetChildData();
						m_roomurl = str.GetBuffer();
						str.ReleaseBuffer();
					}
					if (tag.CompareNoCase("imname")==0)
					{
						CString str = xml.GetChildData();
						m_proname = str.GetBuffer();
						str.ReleaseBuffer();
					}
					if (tag.CompareNoCase("moneyname")==0)
					{
						CString str = xml.GetChildData();
						m_moneyName = str.GetBuffer();
						str.ReleaseBuffer();
					}
					if (tag.CompareNoCase("domain")==0)
					{
						CString str = xml.GetChildData();
						m_domain = str.GetBuffer();
						str.ReleaseBuffer();
					}
					if (tag.CompareNoCase("subdomain")==0)
					{
						CString str = xml.GetChildData();
						m_subdomain = str.GetBuffer();
						str.ReleaseBuffer();
					}
					if (tag.CompareNoCase("logindomain")==0)
					{
						CString str = xml.GetChildData();
						m_loginDomain = str.GetBuffer();
						str.ReleaseBuffer();
					}
					if (tag.CompareNoCase("appname")==0)
					{
						CString str = xml.GetChildData();
						m_appname = str.GetBuffer();
						str.ReleaseBuffer();
					}
					if(tag.CompareNoCase("api") == 0)
					{
						m_fetchIMLoginServerURL = xml.GetChildData().GetBuffer();
					}
				}
				
			}
			//xml.Close();
		}
	}
};


#endif

