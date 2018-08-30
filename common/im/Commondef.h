#ifndef ROOM_SET_DEFINE_KSDJJFSDFKSDJLDSFLSJDFLJSDF
#define ROOM_SET_DEFINE_KSDJJFSDFKSDJLDSFLSJDFLJSDF
#include "include/Markup.h"
#include <vector>
#include <string>
#include <atlstr.h>
#include "im/Commondef.h"
using namespace std;


#define ACTIVELEVEL_LIMIT 100


class CGameStartCheck
{
private:
	CGameStartCheck(){};
public:
	static bool Start(CString configpath,int partnerid,UINT32 uin)
	{
		CMarkup xml;
		bool uinmultienter = true;
		CString keystr;
		if (xml.Load(configpath))
		{
			if (xml.FindElem("CONFIG"))
			{
				if (xml.FindChildElem("UINENTER"))
				{
					uinmultienter = (atoi(xml.GetChildAttrib("MULTI"))==1?true:false);
				}
				if (xml.FindChildElem("KEY"))
				{
					keystr = xml.GetChildData();
				}
			}
			if (!uinmultienter)
			{
				HANDLE mutexHandle = NULL;
				CString mutexstr;
				mutexstr.Format("%d_IM_%s",partnerid,keystr);
				mutexHandle = CreateMutex(NULL, FALSE, mutexstr); 
				if (GetLastError()== ERROR_ALREADY_EXISTS)
				{
					return false;
				}
			}
			else
			{
				HANDLE mutexHandle = NULL;
				CString mutexstr;
				mutexstr.Format("%d_IM_%s_%lu",partnerid,keystr,uin);
				mutexHandle = CreateMutex(NULL, FALSE, mutexstr); 
				if (GetLastError()== ERROR_ALREADY_EXISTS)
				{
					return false;
				}
			}
		}
		else
		{
			HANDLE mutexHandle = NULL;
			CString mutexstr;
			mutexstr.Format("%d_IM_GAME",partnerid);
			mutexHandle = CreateMutex(NULL, FALSE, mutexstr); 
			if (GetLastError()== ERROR_ALREADY_EXISTS)
			{
				return false;
			}
		}
		return true;
	}
};
class CChatRoomUserSet
{
public:
	CChatRoomUserSet()
	{
		m_bListViewSingleMode = true;
		m_bGfNotReserve = false;
		m_bgiftNotEffect = false;
		m_bSingleShowGift = false;
		m_bSendTexByEnter = true;
		m_bPrivateViewShowGift = true;
		m_bEnterLeavePrompt = false;
		m_bHighVipELRoomPrompt = false;
		m_bMiddleVipELRoomPrompt = false;
		m_bJuniorVipELRoomPrompt = false;
		m_bNoShake = false;
		m_bVideoAutoScal = false;
	
	}
	bool m_bGfNotReserve;
	bool m_bgiftNotEffect;
	bool m_bListViewSingleMode;
	bool m_bSingleShowGift;//����ֻ��ʾһ����¼
	bool m_bSendTexByEnter;//1�س�����,0��ctr���س�
	bool m_bPrivateViewShowGift;//˽�����Ƿ���ʾ����
	bool m_bEnterLeavePrompt; //�û����������Ƿ���ʾ
	bool m_bHighVipELRoomPrompt;//�߻���������Ƿ���ʾ
	bool m_bMiddleVipELRoomPrompt;//�л���������Ƿ���ʾ
	bool m_bJuniorVipELRoomPrompt;//�ͻ���������Ƿ���ʾ
	bool m_bNoShake;//������
	bool m_bVideoAutoScal; //��Ƶ�ؼ��Ƿ��Զ��Ŵ�
bool Load(CString strPath)
{
	bool ret = false;
	CMarkup xml;
	if (xml.Load(strPath))
	{
		ret = true;
		if (xml.FindElem("USERSET"))
		{
			if (xml.FindChildElem("USERLISTSINGLEVIEW"))
				m_bListViewSingleMode = (atoi(xml.GetChildData())==0?false:true);
			if (xml.FindChildElem("GIFTNOTRESERVE"))
				m_bGfNotReserve = (atoi(xml.GetChildData())==0?false:true);
			if (xml.FindChildElem("GIFTNOTEFFECT"))
				m_bgiftNotEffect = (atoi(xml.GetChildData())==0?false:true);
			if (xml.FindChildElem("SINGLESHOWGIFT"))
				m_bSingleShowGift = (atoi(xml.GetChildData())==1?true:false);
			if (xml.FindChildElem("SENDTEXTBYENTER"))
				m_bSendTexByEnter =  (atoi(xml.GetChildData())==1?true:false);
			if (xml.FindChildElem("PRIVATESHOWGIFT"))
				m_bPrivateViewShowGift = (atoi(xml.GetChildData())==1?true:false);
			if (xml.FindChildElem("PROMPTENTERLEAVEROOM"))
				m_bEnterLeavePrompt = (atoi(xml.GetChildData())==1?true:false);
			if (xml.FindChildElem("HIGHVIPENTERLEAVERROOM"))
				m_bHighVipELRoomPrompt = (atoi(xml.GetChildData())==1?true:false);
			if (xml.FindChildElem("MIDDLEVIPENTERLEAVERROOM"))
				m_bMiddleVipELRoomPrompt = (atoi(xml.GetChildData())==1?true:false);
			if (xml.FindChildElem("JUNIORVIPENTERLEAVERROOM"))
				m_bJuniorVipELRoomPrompt = (atoi(xml.GetChildData())==1?true:false);
			if (xml.FindChildElem("NOSHAKE"))
				m_bNoShake = (atoi(xml.GetChildData())==1?true:false);
			if (xml.FindChildElem("VIDEOAUTOSCAL"))
				m_bVideoAutoScal = (atoi(xml.GetChildData())==1?true:false);
		}
	}
	else
	{
		
		Save(strPath);
	}
	return ret;
}
bool Save(CString strPath)
{
	bool bret = false;
	CMarkup xml;
	//if (xml.Load(strPath))
	//{
	//	bret = true;
	//	if (xml.FindElem("USERSET"))
	//	{
	//		if (xml.FindChildElem("USERLISTSINGLEVIEW"))
	//		{
	//			xml.SetChildData(m_bListViewSingleMode?1:0);
	//		}
	//		if (xml.FindChildElem("GIFTNOTRESERVE"))
	//		{
	//			xml.SetChildData(m_bGfNotReserve?1:0);

	//		}
	//		if (xml.FindChildElem("GIFTNOTEFFECT"))
	//		{
	//			xml.SetChildData(m_bgiftNotEffect?1:0);

	//		}
	//		if (xml.FindChildElem("SINGLESHOWGIFT"))
	//		{
	//			xml.SetChildData(m_bSingleShowGift?1:0);

	//		}
	//		if (xml.FindChildElem("SENDTEXTBYENTER"))
	//		{
	//			xml.SetChildData(m_bSendTexByEnter?1:0);
	//		}
	//		if (xml.FindChildElem("AUTOREPLY"))
	//		{

	//		}
	//	}
	//	xml.Save(strPath);
	//}
	//else
	{
		CMarkup xml;
		xml.AddElem("USERSET");
		xml.AddChildElem("USERLISTSINGLEVIEW",m_bListViewSingleMode?1:0);
		xml.AddChildElem("GIFTNOTRESERVE",m_bGfNotReserve?1:0);
		xml.AddChildElem("GIFTNOTEFFECT",m_bgiftNotEffect?1:0);
		xml.AddChildElem("SINGLESHOWGIFT",m_bSingleShowGift?1:0);
		xml.AddChildElem("SENDTEXTBYENTER",m_bSendTexByEnter?1:0);
		xml.AddChildElem("PRIVATESHOWGIFT",m_bPrivateViewShowGift?1:0);
		xml.AddChildElem("PROMPTENTERLEAVEROOM",m_bEnterLeavePrompt?1:0);
		xml.AddChildElem("HIGHVIPENTERLEAVERROOM",m_bHighVipELRoomPrompt?1:0);
		xml.AddChildElem("MIDDLEVIPENTERLEAVERROOM",m_bMiddleVipELRoomPrompt?1:0);
		xml.AddChildElem("JUNIORVIPENTERLEAVERROOM",m_bJuniorVipELRoomPrompt?1:0);
		xml.AddChildElem("NOSHAKE",m_bNoShake);
		xml.AddChildElem("VIDEOAUTOSCAL",m_bVideoAutoScal?1:0);
		//xml.AddChildElem("AUTOREPLY");
		
		xml.Save(strPath);
	}
	return bret;
}
};

class GiftInfo
{
public:
	GiftInfo()
	{
		m_giftname = "����";
		m_price = 1000;
		m_bFlash = false;
		m_soundName = "";
		m_swfname = "";
		m_swfw = 0;
		m_swfh = 0;
		m_local = false;
		m_nkind = 0;
		m_tip = "";
		m_hBitmap = NULL;
	}
	GiftInfo(CString &name,uint64 price,CString soundname, bool bFlash,CString swfname,int w,int h,CString tip,int kind)
	{
		m_giftname = name;
		m_price = price;
		m_soundName = soundname;
		m_bFlash = bFlash;
		m_swfname = swfname;
		m_swfw = w;
		m_swfh = h;
		m_tip = tip;
		m_nkind = kind;
		m_hBitmap = NULL;
	}

	GiftInfo(uint32 id,CString& name,CString &bmp,CString &gif,uint64 price,CString soundname,bool bFlash,CString swfname,int w,int h, bool Local,CString tip,int kind, LPCTSTR gifurl)
	{
		m_hBitmap = NULL;
		m_id = id;
		m_giftname = name;
		m_bmp = bmp;
		m_gif = gif;
		m_price = price;
		m_soundName = soundname;
		m_bFlash = bFlash;
		m_swfname = swfname;
		m_swfw = w;
		m_swfh = h;
		m_local = Local;
		m_tip = tip;
		m_nkind = kind;
		m_gifurl = gifurl;
	}
	~GiftInfo()
	{
		if(m_hBitmap)
		{
			DeleteObject(m_hBitmap);
			m_hBitmap = NULL;
		}
	}
	uint32 m_id;
	CString m_giftname;
	CString m_bmp;
	CString m_gif;
	uint64  m_price;
	CString m_soundName;//�����ļ�ID;
	CString m_swfname;//swf�ļ�
	bool     m_bFlash;//�Ƿ�����
	HBITMAP m_hBitmap;
	int m_swfw;
	int m_swfh;
	bool   m_local;   //׷����ʱ��Ϣ
	CString m_tip;//�������ʾ��Ϣ
	int  m_nkind; //0��ͨ���1��������,2�������
	CString m_gifurl;
};
typedef vector<GiftInfo> GiftVector;
typedef vector<GiftVector> GiftVectors;
class GiftTabInfo
{
public:
	GiftTabInfo()
	{
		m_titlename="����";
	
		m_index = 0;
		m_bLucky = false;
		m_giftBackColor = RGB(255,255,255);
		m_TablFontColor = RGB(0,0,0);
	}
	GiftTabInfo(CString name,uint8 index,bool blucky,COLORREF backrgb,COLORREF fontrgb)
	{
		m_titlename=name;
		
		m_index = index;
		m_bLucky = blucky;
		m_giftBackColor = backrgb;
		m_TablFontColor = fontrgb;
	}

	CString m_titlename;
	bool    m_bLucky;// is gifts is lucky gifts
	uint8	m_index;
	COLORREF m_giftBackColor;
	COLORREF m_TablFontColor;
};
typedef vector<GiftTabInfo> GiftTabVector;

class CImRGBTool
{
private:
	CImRGBTool(){};
public:
	static 	COLORREF GetRGB( CString rgbstr,int& r,int& g,int& b )
	{
		CString rstr;
		CString gstr;
		CString bstr;

		rgbstr.Trim();
		if (rgbstr.GetLength()<=5)
			return 0;

		rgbstr = rgbstr.Right(rgbstr.GetLength() - rgbstr.Find('(')-1);
		rstr = rgbstr.Left(rgbstr.Find(','));
		r = atoi(rstr);
		rgbstr = rgbstr.Right(rgbstr.GetLength() - rgbstr.Find(',')-1);
		gstr = rgbstr.Left(rgbstr.Find(','));
		g = atoi(gstr);
		rgbstr = rgbstr.Right(rgbstr.GetLength() - rgbstr.Find(',')-1);
		bstr = rgbstr.Left(rgbstr.GetLength()-1);
		b = atoi(bstr);
		return RGB(r,g,b);
	}
};

/*
�ܵ����ݶ���
*/
class CTrackItem
{
public:
	CTrackItem()
		: m_type(0)
		,m_sourceUserId(0)
		,m_sourceUserNick(_T(""))
		,m_sourceUserLevelPath(_T(""))
		,m_destUserId(0)
		,m_destUserNick(_T(""))
		,m_destUserLevelPath(_T(""))
		,m_giftCount(0)
		,m_giftUnit(_T("��"))
		,m_giftName(_T(""))
		,m_strLuckContent(_T(""))
		,m_contentText(_T(""))
		,m_scrollNum(1)
		,m_alreadyShow(false)
	{

	}
public:
	int m_scrollNum;    // ��������
	bool m_alreadyShow; // �Ƿ��Ѿ���ʾ��
	int  m_type;     // �ܵ����ͣ�0--����  1--��������m_type=1ʱ��m_contentText��Ч��
	uint32 m_giftId;    // ����ID
	uint32 m_sourceUserId;    // �����û�ID
	CString m_sourceUserNick;   // �����û��ǳ�
	CString m_sourceUserLevelPath;   // �����û��ȼ�gifͼƬ·��
	CString m_roomInfo;                       // ������Ϣ
	uint32  m_destUserId;                     // Ŀ���û�ID
	CString  m_destUserNick;              //  Ŀ���û��ǳ�
	CString  m_destUserLevelPath;    //  Ŀ���û��ȼ�gifͼ��·��
	CString  m_giftGifPath;                  //  ����ͼƬgif·��
	uint32    m_giftCount;                    // ��������
	CString  m_giftUnit;                    //  ���ﵥλ
	CString  m_giftName;                   // ��������
	CString  m_strLuckContent;        //  ף����
	CString  m_strTime;                      // ����ʱ��
	CString  m_contentText;             //  ͨ�õ����ݣ���m_type=1ʱ��Ч
};
// �ܵ����壬��ɫ
class CTrackSet
{
public:
	struct BaseInfo
	{
		COLORREF m_clr;
		CString       m_fontName;
		int               m_fontSize;
	};
	CTrackSet()
		:m_transparentValue(0)
		,m_stepNormal(1)
		,m_scrollmode (1)
		,m_nscrolltextremaincount(5)
		,m_clrBackground(RGB(0,0,0))
	{
		InitBaseInfo(RGB(255,255,255),_T("����"),20,&m_sourceUserInfo);
		InitBaseInfo(RGB(239,255,2),_T("����"),20,&m_presentInfo);
		InitBaseInfo(RGB(255,255,255),_T("����"),20,&m_destUserInfo);
		InitBaseInfo(RGB(255,239,2),_T("����"),20,&m_giftDetailInfo);
		InitBaseInfo(RGB(255,0,0),_T("����"),20,&m_commonInfo);
		InitBaseInfo(RGB(255,0,0),_T("����"),20,&m_roomInfo);
		InitBaseInfo(RGB(255,0,0),_T("����"),20,&m_timeInfo);
	}
private:
	bool ReadTrackItemSet(CMarkup& xml,const CString& key,COLORREF& clr, CString& fontName,int& fontSize)
	{
		if(xml.FindChildElem(key))
		{
			xml.IntoElem();
			int r,g,b;
			r = g = b = 0;
			if(xml.FindChildElem("textcolor"))
				clr = CImRGBTool::GetRGB(xml.GetChildData(),r,g,b);
			if(xml.FindChildElem("textfont"))
				fontName = xml.GetChildData();
			if(xml.FindChildElem("textfontsize"))
				fontSize = atoi(xml.GetChildData());
			xml.OutOfElem();

			return true;
		}
		return false;
	}
public:
	bool Load(CString configxml)
	{
		CMarkup xml;
		if (xml.Load(configxml))
		{
			if (xml.FindElem("config"))
			{
				m_ver = xml.GetAttrib("ver");
			}
			if(xml.FindChildElem("trackset"))
			{
				xml.IntoElem();
				if(xml.FindChildElem("backgroundcolor"))
				{
					int r,g,b;
					r=g=b=0;
					SetTrackBackgroundColor(CImRGBTool::GetRGB(xml.GetChildData(),r,g,b));
				}
				if(xml.FindChildElem("transparentvalue"))
					SetTransparentValue(atoi(xml.GetChildData()));
				if(xml.FindChildElem("roomscrollnormal"))
					SetScrollStep(atoi(xml.GetChildData()));
				if (xml.FindChildElem("roomscrollmode"))
				{
					SetScrollMode(atoi(xml.GetChildData()));
				}
				if (xml.FindChildElem("scrolltextremaincount")) 
				{
					m_nscrolltextremaincount = atoi(xml.GetChildData());
				}
				CString fontName = _T("����");
				int fontSize = 20;
				COLORREF clr = RGB(255,255,255);
				if(ReadTrackItemSet(xml,"sourceuser",clr,fontName,fontSize))
					SetSourceUserInfo(clr,fontName,fontSize);
				if(ReadTrackItemSet(xml,"present",clr,fontName,fontSize))
					SetPresentInfo(clr,fontName,fontSize);
				if(ReadTrackItemSet(xml,"destuser",clr,fontName,fontSize))
					SetDestUserInfo(clr,fontName,fontSize);
				if(ReadTrackItemSet(xml,"giftdetail",clr,fontName,fontSize))
					SetGiftDetailInfo(clr,fontName,fontSize);
				if(ReadTrackItemSet(xml,"common",clr,fontName,fontSize))
					SetCommonInfo(clr,fontName,fontSize);
				if(ReadTrackItemSet(xml,"roominfo",clr,fontName,fontSize))
					SetRoomInfo(clr,fontName,fontSize);
				if(ReadTrackItemSet(xml,"timeinfo",clr,fontName,fontSize))
					SetTimeInfo(clr,fontName,fontSize);
				xml.OutOfElem();
			}
			return true;
		}
		return false;
	}


	
	void SetSourceUserInfo(COLORREF clr,const CString& strFont,int fontSize) { InitBaseInfo(clr,strFont,fontSize,&m_sourceUserInfo);}
	const BaseInfo* GetSourceUserInfo() const { return &m_sourceUserInfo;}

	void SetPresentInfo(COLORREF clr,const CString& strFont,int fontSize) { InitBaseInfo(clr,strFont,fontSize,&m_presentInfo);}
	const BaseInfo* GetPresentInfo() const        { return &m_presentInfo; } 

	void SetDestUserInfo(COLORREF clr,const CString& strFont,int fontSize) { InitBaseInfo(clr,strFont,fontSize,&m_destUserInfo);}
	const BaseInfo* GetDestUserInfo()const      { return &m_destUserInfo; } 

	void SetGiftDetailInfo(COLORREF clr,const CString& strFont,int fontSize) { InitBaseInfo(clr,strFont,fontSize,&m_giftDetailInfo);}
	const BaseInfo* GetGiftDetailInfo()const      { return &m_giftDetailInfo; }

	void SetCommonInfo(COLORREF clr,const CString& strFont,int fontSize) { InitBaseInfo(clr,strFont,fontSize,&m_commonInfo);}
	const BaseInfo* GetCommonInfo()const     {  return &m_commonInfo;}

	void SetRoomInfo(COLORREF clr,const CString& strFont,int fontSize) { InitBaseInfo(clr,strFont,fontSize,&m_roomInfo);}
	const BaseInfo* GetRoomInfo()const         { return &m_roomInfo; }

	void SetTimeInfo(COLORREF clr,const CString& strFont,int fontSize) { InitBaseInfo(clr,strFont,fontSize,&m_timeInfo); }
	const BaseInfo* GetTimerInfo()const         { return &m_timeInfo;}
	// ����ɫ
	void SetTrackBackgroundColor(COLORREF clr) { m_clrBackground = clr; }
	COLORREF GetTrackBackgroundColor() const   { return m_clrBackground; }

	// ͸��ֵ
	void SetTransparentValue(int value)             { m_transparentValue = value; }
	int    GetTransparentValue()const                  { return m_transparentValue;   }

	// ��������
	void SetScrollStep(int value)                          { m_stepNormal = value; }
	int   GetScrollStep()const                                { return m_stepNormal;  }

	void SetScrollMode(int value)						{m_scrollmode = value;}
	int  GetScrollMode()								{return m_scrollmode;}

	void SetScrollRemain(int value)						{m_nscrolltextremaincount = value;}
	int  GetScrollRemain()								{return m_nscrolltextremaincount;}
private:
	void InitBaseInfo(COLORREF clr,const CString& fontName,int fontSize,BaseInfo* info)
	{
		info->m_clr = clr;
		info->m_fontName = fontName;
		info->m_fontSize = fontSize;
	}

private:
	BaseInfo   m_sourceUserInfo;
	BaseInfo   m_roomInfo;
	BaseInfo   m_presentInfo;
	BaseInfo   m_destUserInfo;
	BaseInfo   m_giftDetailInfo;
	BaseInfo   m_timeInfo;
	BaseInfo   m_commonInfo;    // ͨ�õ���Ϣ������Ϣ��eg:����ͨ�棬�н���Ϣ�ȣ�
	COLORREF m_clrBackground;   // ����ɫ
	int             m_transparentValue;   // ͸��ֵ
	int             m_stepNormal;            // ������������λΪ���أ�����Ϊ���õĲ���+3
	int				m_scrollmode;
	int				m_nscrolltextremaincount; //���Ʈ����Ʈ��ָһֱƮ��������
	CString			m_ver; //�汾��
};

typedef struct UserPrivilegeColor
{
	CString strPrivilege;
	COLORREF color;
	UserPrivilegeColor()
	{
		color = 0;
		strPrivilege = "";
	}
}UserPriColor, *LPUserPriColor;

typedef std::vector<UserPriColor> PriColorList;
class CChatUserListConfig
{
private:
	PriColorList m_vecUserPriColor;
	CString m_ver;
public:
	bool Load(CString xmlconfig)
	{
		m_vecUserPriColor.clear();
		CMarkup xml;
		if (xml.Load(xmlconfig))
		{
			if (xml.FindElem("config"))
			{
				m_ver = xml.GetAttrib("ver");
				if (xml.FindChildElem("userlistcolor"))
				{
					xml.IntoElem();
					CString sKey, sValue;
					while (xml.FindChildElem())
					{
						sKey = xml.GetChildTagName();
						sValue = xml.GetChildData();
						if (sValue.Find("RGB(")>=0)
						{
							int r = 0;
							int g = 0;
							int b = 0;
							UserPriColor tempPriColor;
							tempPriColor.color = CImRGBTool::GetRGB(sValue,r,g,b);
							tempPriColor.strPrivilege = sKey;
							m_vecUserPriColor.push_back(tempPriColor);
						}
					}
				}
			}
		}
		return m_vecUserPriColor.size() > 0;
	}

	const PriColorList& GetPriColorList()
	{
		return m_vecUserPriColor;
	}

	COLORREF GetPriColor(LPCTSTR sPrivilegeName)
	{
		if(sPrivilegeName == NULL||*sPrivilegeName == '\0') return 0;
		for(int i = 0;i<m_vecUserPriColor.size();i++)
		{
			if(m_vecUserPriColor[i].strPrivilege.CompareNoCase(sPrivilegeName) == 0)
				return m_vecUserPriColor[i].color;
		}
		return 0;
	}
};

class CChatUserSortConfig
{
public:
	CChatUserSortConfig()
	{

	}
public:
	vector<CString>	m_sortfileds;
	CString m_ver;
	bool Load(CString configxml)
	{
		CMarkup xml;
		if (xml.Load(configxml))
		{
			if (xml.FindElem("config"))
			{
				m_ver = xml.GetAttrib("ver");
			}
			if (xml.FindChildElem("sortfields"))
			{
				xml.IntoElem();
				while(xml.FindChildElem("field"))
				{
					m_sortfileds.push_back(xml.GetChildData());
				}
				xml.OutOfElem();
			}
		}
		

		CString infields[]={
			"��Ȩ","վ��","��վ��","����","������","����","����",\
			"����","�о�","�Ӿ�","����","���","����","����","����","����",\
			"����","����","����","����","����","����","�׽��Ա",\
			"�߻�","�л�","����","����","����","�赸","����","����",\
			"����","����","����","�ͷ�","����"
		};
		int fieldssize = 36;
		if (!m_sortfileds.empty())
		{

			for (vector<CString>::iterator it = m_sortfileds.begin(); it!=m_sortfileds.end();it++)
			{
				bool binfileds = false;
				for (int i =0;i<fieldssize;i++)
				{
					if (infields[i].CompareNoCase(*it) ==0)
					{
						binfileds = true;
						break;
					}
				}
				if (!binfileds)
				{
					m_sortfileds.clear();
					break;
				}
			}
		}

		if (m_sortfileds.empty())
		{
			for (int i =0;i<fieldssize;i++)
			{
				m_sortfileds.push_back(infields[i]);
			}

		}
		return true;
	}
	
};
class CChatRoomSet
{
public:
	CChatRoomSet()
	{
		/*m_bshowjuniorvipEnter = 1;
		m_bshowmiddleEnter = 1;
		m_bshowHighVipEnter = 1;
		m_bshowGoldenEnter = true;*/
		m_showwinprice= true;
		m_showBuyMoney = true;
		m_micListDefColor = RGB(0,0,255);
		m_htmlsbhightcolor=" #D2D2FF";
		m_htmlsbshadowcolor=" #3C3CFF";
		m_htmlsb3dhightcolor=" #A3AEBD";
		m_htmlsbtrackcolor=" #CACAFF";
		m_htmlsbdrakshadowkcolor=" #C1C1FF"; 
		m_htmlsbbasecolor=" #46A9F3";
		m_htmlsbColor=" #0000D9"; 
		m_htmlBackColr = RGB(255,255,255);
		m_bshowGiftDlg = true;
		bChatMsgOnGiftShow = true;
		m_nGiftMsgMaxCount = 40;
		m_nGiftMsgCountRemain = 20;
		m_nChatMsgMaxCount = 80;
		m_nChatMsgCountRemain = 40;
		m_showScrollGift = true;
		m_chatTextUIMode = 0;
		m_bShowRoomTtileUrl = true;
	}
	/*bool m_bshowjuniorvipEnter;
	bool m_bshowmiddleEnter;
	bool m_bshowHighVipEnter;
	bool m_bshowRicherEnter;
	bool m_bshowGoldenEnter;*/
	bool m_bshowGiftDlg;
	bool m_showwinprice;
	bool bChatMsgOnGiftShow; //2����Ƶ��������˵����ˢ����
	bool m_showBuyMoney;
	int m_nGiftMsgMaxCount;//ˢ���������ʾ��������Ϣ
	int m_nGiftMsgCountRemain; //ˢ����������������Ϣ
	int m_nChatMsgMaxCount;//������������������Ϣ
	int m_nChatMsgCountRemain;//������������������Ϣ
	int  m_chatTextUIMode;  //���䷢�Ͱ�ť���������λ�õ�����
	bool m_bShowRoomTtileUrl;//�����б����Ƿ���ʾURL
	COLORREF m_htmlBackColr;
	
	COLORREF m_micListDefColor;
	CString m_htmlsbhightcolor;
	CString m_htmlsbshadowcolor;
	CString m_htmlsb3dhightcolor;
	CString m_htmlsbtrackcolor;
	CString m_htmlsbdrakshadowkcolor; 
	CString m_htmlsbbasecolor;
	CString m_htmlsbColor; 
	
	//CTrackSet   m_trackSet;   // �ܵ�������ɫ����������
	//CChatUserListConfig m_userlistconfig; //�����б���ɫ
	//CChatUserSortConfig m_sortusersconfig;  //��������
	bool       m_showScrollGift;  // �Ƿ���ʾƮ��
	CString m_ver;

public:
	bool Load(CString strPath)
	{
		bool ret = false;
		CMarkup xml;
		if (xml.Load(strPath))
		{
			ret = true;
			if (xml.FindElem("roomset"))
			{
				m_ver = xml.GetAttrib("ver");
				/*if (xml.FindChildElem("showjuniorvipenter"))
				{
					this->m_bshowjuniorvipEnter = atoi(xml.GetChildData())>0?true:false;
				}
				if (xml.FindChildElem("showmiddlevipenter"))
				{
					this->m_bshowmiddleEnter = atoi(xml.GetChildData())?true:false;
				}
				if (xml.FindChildElem("showhighvipenter"))
				{
					this->m_bshowHighVipEnter = atoi(xml.GetChildData())?true:false;
				}
				if (xml.FindChildElem("showgoldenenter"))
				{
					this->m_bshowGoldenEnter = atoi(xml.GetChildData())?true:false;
				}
				if (xml.FindChildElem("showricherenter"))
				{
					this->m_bshowRicherEnter = atoi(xml.GetChildData())?true:false;
				}*/

				if (xml.FindChildElem("showwinprice"))
				{
					this->m_showwinprice = atoi(xml.GetChildData())==0?false:true;
				}
				if (xml.FindChildElem("showbuymoney"))
				{
					this->m_showBuyMoney = atoi(xml.GetChildData())==0?false:true;
				}
 				if (xml.FindChildElem("showscroll"))
 				{
 					this->m_showScrollGift = atoi(xml.GetChildData())>0?true:false;
 				}
				if (xml.FindChildElem("miclistcolor"))
				{
					xml.IntoElem();
				
					if (xml.FindChildElem("default"))
					{
						int r = 0;
						int g = 0;
						int b = 0;
						CString temp = xml.GetChildData();
						m_micListDefColor = CImRGBTool::GetRGB(temp,r,g,b);
					}
					xml.OutOfElem();

				}
				if (xml.FindChildElem("backgroundcolor"))
				{

					CString temp = xml.GetChildData();
					int r=0;
					int b=0;
					int g=0;
					this->m_htmlBackColr = 	CImRGBTool::GetRGB(temp,r,g,b);
				}
				if (xml.FindChildElem("roomhtmlscroll"))
				{
					xml.IntoElem();
					if (xml.FindChildElem("highlightcolor"))
					{
						this->m_htmlsbhightcolor=xml.GetChildData();
					}
					if (xml.FindChildElem("shadowcolor"))
					{
						this->m_htmlsbshadowcolor=xml.GetChildData();
					}
					if (xml.FindChildElem("d3lightcolor"))
					{
						this->m_htmlsb3dhightcolor=xml.GetChildData();
					}
					if (xml.FindChildElem("trackcolor"))
					{
						this->m_htmlsbtrackcolor=xml.GetChildData();
					}
					if (xml.FindChildElem("darkshadowcolor"))
					{
						this->m_htmlsbdrakshadowkcolor=xml.GetChildData();
					}
					if (xml.FindChildElem("basecolor"))
					{
						this->m_htmlsbbasecolor=xml.GetChildData();
					}
					if (xml.FindChildElem("color"))
					{
						this->m_htmlsbColor=xml.GetChildData();
					}

					xml.OutOfElem();

				}
				
				
				if (xml.FindChildElem("showgiftdlg"))
				{
					this->m_bshowGiftDlg = atoi(xml.GetChildData())?true:false;
				}
				if (xml.FindChildElem("chatmsgongiftshow"))
				{
					this->bChatMsgOnGiftShow = atoi(xml.GetChildData())?true:false;
				}

				if (xml.FindChildElem("chatmsgmaxcount")) 
				{
					this->m_nChatMsgMaxCount = atoi(xml.GetChildData());
				}

				if (xml.FindChildElem("chatmsgcountremain")) 
				{
					this->m_nChatMsgCountRemain = atoi(xml.GetChildData());
				}

				if (xml.FindChildElem("giftmsgmascount"))
				{
					this->m_nGiftMsgMaxCount = atoi(xml.GetChildData());
				}

				if (xml.FindChildElem("giftmsgcountremain")) 
				{
					this->m_nGiftMsgCountRemain = atoi(xml.GetChildData());
				}
		
				if (xml.FindChildElem("chattextuimode"))
				{
					this->m_chatTextUIMode = atoi(xml.GetChildData());
				}
				if (xml.FindChildElem("showroomurltile"))
				{
					this->m_bShowRoomTtileUrl = ( atoi(xml.GetChildData())>0?true:false);
				}
			}
		}
		return ret;
	}

	bool Save(CString path)
	{

	}
	
};
class GameConfigSet
{
public:
	GameConfigSet(){};
	~GameConfigSet(){};
	static bool Load(CString strPath, CChatUserListConfig& m_userlistconfig)
	{
		return true;
	}

};
struct ColorTip_Item
{
public:
	ColorTip_Item()
	{
		m_itemName = "����";
		m_itemTxt = "";
	}
	CString m_itemName;
	CString m_itemTxt;
};
class SelectColor_Tip
{
public:
	SelectColor_Tip(){}
	vector<ColorTip_Item> m_Items;


	void Load(CString driPath)
	{   
		CMarkup Color_xml;
		CString strPath_Tip = driPath;
		strPath_Tip+= "\\";
		CString strPath=driPath + "face\\ColorTip\\ColorTip.xml";

		ColorTip_Item item;

		if( Color_xml.Load(strPath) )
		{  
			Color_xml.IntoElem();
			if( Color_xml.FindElem("ColorTip"))
			{

				int index = 1;
				CString strTemp;
				strTemp.Format("ColorTip%d",index);
// 				CString strTxt;
// 				strTxt.Format("����%d",index);

				while(Color_xml.FindChildElem(strTemp))
				{
					
					item.m_itemName =Color_xml.GetChildAttrib("NAME");
					item.m_itemTxt = Color_xml.GetChildData();
					item.m_itemTxt.Replace("&lg;","<");
					item.m_itemTxt.Replace("&gt;",">");
					item.m_itemTxt.Replace("%path%",strPath_Tip);
					this->m_Items.push_back(item);
					index++;
					strTemp.Format("ColorTip%d",index);
					/*strTxt.Format("����%d",index);*/

				}
			}
		}
	}

};

class CEmotionItem
{
public: 
	CEmotionItem(){};
	CString m_tip;
	CString m_shortcut;
};
class CEmotionItems
{
public:
	CEmotionItems(){};
	bool Load(CString config)
	{

		LPCTSTR emotionstip[] = {
			"΢Ц",  "Ʋ��"  ,"ɫ" ,"����","����", "����"  ,"����",  "����", "˯",  "���", "����", "��ŭ","��Ƥ", "����" ,"����",

			"�ѹ�",  "��",  "�亹",  "ץ��",  "��",  "͵Ц",  "�ɰ�",  "����","����","����","��","����","����","��Ц", "���",

			"�ܶ�","����",  "����",  "��",  "��",  "��ĥ",  "˥",  "����",  "�ô�", "�ټ�", "����", "�ٱ�",  "����", "�ܴ���", "��Ц",

			"��ߺ�", "�Һߺ�", "��Ƿ", "����", "ί��", "�����", "����", "����", "��","����", "�˵�",  "����", "ơ��", "����", "ƹ��",

			"����", "��", "��ͷ", "õ��", "��л", "ʾ��", "����", "����", "����", "����", "ը��", "��", "Ƥ��", "ư��", "���",


			"����", "̫��", "����", "ӵ��", "ǿ", "��", "����", "ʤ��", "��ȭ", "����", "ȭͷ", "�", "����", "NO", "OK",
			"����","����","��Ц","��","���˾�","������","����","������","����","������","����","��ҡ","û�����","��","��ð",
			"����","������","���","����","����","��ͬ��","����","NO","�鲻�Խ�","����","������","������","������","С��˼","����",
		};

		LPCTSTR emotions[]  = {
			"/:wx", "/:pz", "/:se", "/:fd", "/:dy", "/:ll", "/:hx", "/:bz", "/:shui", "/:dk",
			"/:gg", "/:fn", "/:tp", "/:cy", "/:jy", "/:ng", "/:kuk", "/:lengh", "/:zk", "/:tuu",
			"/:tx", "/:ka", "/:baiy", "/:am", "/:jie", "/:kun", "/:jk", "/:lh", "/:hanx", "/:db",
			"/:fendou", "/:zhm", "/:yiw", "/:xu", "/:yun", "/:zhem", "/:shuai", "/:kl", "/:qiao", "/:zj",
			"/:ch", "/:kb", "/:gz", "/:qd", "/:huaix", "/:zhh", "/:yhh", "/:hq", "/:bs", "/:wq",
			"/:kk", "/:yx", "/:qq", "/:xia", "/:kel", "/:cd", "/:xig", "/:pj", "/:lq", "/:pp",
			"/:kf", "/:fan", "/:zt", "/:mg", "/:dx", "/:sa", "/:xin", "/:xs", "/:dg", "/:shd",
			"/:zhd", "/:dao", "/:zq", "/:pch", "/:bb", "/:yl", "/:ty", "/:lw", "/:yb", "/:qiang",
			"/:ruo", "/:ws", "/:shl", "/:bq", "/:gy", "/:qt", "/:cj", "/:aini", "/:bu", "/:hd",


			"/:wgy", "/:bc", "/:cx", "/:qa", "/:nrj", "/:cbm", "/:hy", "/:wll", "/:lk", "/:bkq",
			"/:la", "/:swy", "/:wrlj", "/:gh", "/:gm", "/:gl", "/:zsb", "/:nh", "/:ms", "/:zx",
			"/:bty", "/:sj", "/:no", "/:qbzj", "/:hwl", "/:hgg", "/:wpp", "/:hhh", "/:xys", "/:jo",
		};
		for (int i =0;i<120;i++)
		{
			CEmotionItem item;
			item.m_shortcut = emotions[i];
			item.m_tip = emotionstip[i];
			m_items.push_back(item);
		}
		/*CMarkup xml;
		if (xml.Load(config))
		{
		if (xml.FindElem("config"))
		{
		while(xml.FindChildElem("item"))
		{
		xml.IntoElem();
		CEmotionItem item;
		if (xml.FindChildElem("tip"))
		item.m_tip = xml.GetChildData();
		if (xml.FindChildElem(""))
		item.m_shortcut = xml.GetChildData();
		m_items.push_back(item);
		xml.OutOfElem();
		}
		}
		return true;
		}
		return false;*/
		return true;
	}
vector<CEmotionItem> m_items;
};
class CTinyDirs
{
public:
	/************************************************************************/
	/* �õ��û����Թ��õĴ���Ŀ¼                                                                     */
	/************************************************************************/
	static bool GetSystemPersonDir(CString& dir)
	{
		char path[MAX_PATH]={0};
		if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL|CSIDL_FLAG_CREATE, NULL, 0, path))) 
		{
			dir = path;
			return true;
		}
		else
			return false;
	}
};



class UserLoginTag
{
public:
	UserLoginTag()
	{
		m_mutex = NULL;
	};
	~UserLoginTag()
	{
		Realse();
	}
private:
	HANDLE m_mutex;
public:
	
	void   Realse()
	{
		if (m_mutex!=NULL)
			CloseHandle(m_mutex);
		m_mutex = NULL;
	}
	/************************************************************************/
	/*@param1 �̼Һ�
	  @param2 �û��� 
	  @ret true �Ѿ����û���½,falseû�д��û��Ѿ���½
	/************************************************************************/
	bool IsUserLogined(int partnerid,uint32 uin)
	{
		bool bexist = false;
		CString tag;
		tag.Format("winim_%d_%lu",partnerid,uin);
		HANDLE mutex = CreateMutex(NULL, FALSE, tag);
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			CloseHandle(mutex);
			mutex = NULL; 
			bexist = true;

		}
		else
		{
			CloseHandle(mutex);
			bexist = false;
			mutex = NULL;
		}
		
		return bexist;
	}

	 bool CreateUserLoginTag(int partnerid,uint32 uin)
	{
		CString tag;
		tag.Format("winim_%d_%lu",partnerid,uin);
		m_mutex = CreateMutex(NULL, FALSE, tag);
		static HANDLE tempMutex = NULL;
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			if( tempMutex )
			{
				CloseHandle(tempMutex);
			    tempMutex = NULL; 
			}
		}
		else
		{
			tempMutex = m_mutex;
		}
		return (m_mutex != NULL);
	}
	 
};
/*tzw modify add start;*/
class AppliCation
{
public:
	AppliCation()
	{
		appname = "";	
		apptype = false;	
		apppath = "";	
		appbmpname = "";
		m_index = 0;
		m_roomtype = 0;
		m_roomid = 0;
	}
	AppliCation(CString name,int type,CString path,CString bmpname,int id,int roomid,int roomtype )
	{
		appname = name;
		apptype = type;
		apppath = path;
		appbmpname = bmpname;
		m_index = id;
		m_roomid = roomid;
		m_roomtype = roomtype;
	}
	~AppliCation()
	{

	}
public:
	CString appname;	//Ӧ������;
	int		apptype;	//Ӧ������;
	CString apppath;	//Ӧ��·��;
	CString appbmpname;	//Ӧ��ͼƬ����;
	int m_index;
	int m_roomid;		//����ID;
	int m_roomtype;		//��������;
};
typedef vector<AppliCation> AppVector;
typedef vector<AppVector> AllAppVector;
/*tzw modify add end;*/

/*
 * ������ʾ��������
*/
class GeneralMsgType
{
public:
	enum
	{
		MSG_PUBLIC = 0x0001,
		MSG_PRIVATE = 0x0002,
		MSG_SCROLLBROAD = 0x0004,
		MSG_SYSTEMBORAD = 0x0008,
		
	};
};
class StampItem
{
public:
	StampItem()
	{
		m_name="";
		m_time = 1;
		m_price =1000;
		m_tip  = "";
		m_isgif = 0;
		m_largename = "";
		m_smallname = "";
		m_id = 0;
		m_fontname = "";
		m_fontcolor = RGB( 0, 0, 0 );
		m_stampbmp = "" ;
	}
	~StampItem()
	{

	}
	StampItem(uint16 uid, CString name, uint32 time, uint64 price,int isgif, CString largename, CString smallname,CString tip,CString fontname, COLORREF  fontcolor, CString stampbmp)
	{
		m_id = uid;
		m_name = name;
		m_time = time;
		m_price = price;
		m_isgif = isgif;
		m_largename = largename;
		m_smallname = smallname;
		m_tip = tip;
		m_fontname = fontname;
		m_fontcolor = fontcolor;
		m_stampbmp = stampbmp;
	}
public:
	CString m_name;
	uint32  m_time;
	uint64  m_price;
	CString m_tip;
	int m_isgif;
	CString m_largename;
	CString m_smallname;
	uint16 m_id;
	CString m_fontname;
	COLORREF  m_fontcolor;
	CString   m_stampbmp;
};

typedef vector<StampItem> StampVector;
typedef vector<StampVector> StampVectors;

class StampItemTabInfo
{
public:
	StampItemTabInfo()
	{
		m_tabIndex = 0;
		m_stampName = "����";
	}
	~StampItemTabInfo() 
	{

	}
	StampItemTabInfo(CString stampName, int tabIndex)
	{
		m_tabIndex = tabIndex;
		m_stampName = stampName;
	}
public:
	int m_tabIndex;
	CString m_stampName;
};
typedef vector<StampItemTabInfo> StampTabVector;

class  StampHistroy
{
public:
	StampHistroy()
	{
		m_name="";
		m_text = "";
		m_index = -1;
		m_id = -1;
		m_isgif = -1;
	}
	~StampHistroy()
	{

	}
	StampHistroy(uint16 uid, CString name,int isgif, CString text,  int index )
	{
		m_id = uid;
		m_name = name;
		m_isgif = isgif;
		m_text = text;
		m_index = index;
	}
public:
	uint16 m_id;
	CString m_name;
	int  m_isgif;
	CString m_text;
	int m_index;
};
typedef vector<StampHistroy>  StampHistroyVec;
typedef  vector<StampHistroyVec>   StampHistroyVecs;

class CAppcenterCount
{
public:
	CAppcenterCount()
	{
		m_AppCenterID = 0;
		m_AppCenterCount = 0;
	}
	~CAppcenterCount()
	{
	}
public:
	int    m_AppCenterID;               //   Ӧ�ó���id
	int    m_AppCenterCount;        //   Ӧ�ó������

};
class CURLSite
{
public:
	enum
	{
		IMGUP_SITE,
		IMGS_SITE,
		HALL_SITE,
		GIFT_SITE,
		WEB_SITE,
		LOG_SITE,
		UPGRADE_SITE,
		BACKSTAGE_STIE,
		CDNSTATICURL_STIE,
		LIMITE_SITE
	};
	CURLSite():m_verion(0),m_startCode(0){};
	~CURLSite(){};
CString m_site[LIMITE_SITE];
uint32 m_verion;
uint8   m_startCode;
 bool  Load(CString &xmlfile)
 {
	 CMarkup xml;
	 if (xml.Load(xmlfile))
	 {
		 if(xml.FindElem("URLSET"))
		 {
			 if(xml.FindChildElem("version"))
				 m_verion = strtoul(xml.GetChildData().GetBuffer(),NULL,10);
			 if(xml.FindChildElem("startcode"))
				 m_startCode = atoi(xml.GetChildData().GetBuffer());

			
			 while(xml.FindChildElem())
			 {
				 CString tag = xml.GetChildTagName();
				 if (tag.CompareNoCase("imgup")==0)
				 {
					 m_site[IMGUP_SITE] = xml.GetChildData();
				 }
				 else if (tag.CompareNoCase("imgs")==0)
				 {
					 m_site[IMGS_SITE] = xml.GetChildData();
				 }
				 else if (tag.CompareNoCase("hall")==0)
				 {
					 m_site[HALL_SITE] = xml.GetChildData();
				 }
				 else if (tag.CompareNoCase("gift")==0)
				 {
					 m_site[GIFT_SITE] = xml.GetChildData();
				 }
				 else if (tag.CompareNoCase("web")==0)
				 {
					 m_site[WEB_SITE] = xml.GetChildData();
				 }
				 else if (tag.CompareNoCase("log")==0)
				 {
					 m_site[LOG_SITE] = xml.GetChildData();
				 }
				 else if (tag.CompareNoCase("upgrade")==0)
				 {
					 m_site[UPGRADE_SITE] = xml.GetChildData();
				 }
				 else if (tag.CompareNoCase("backstage")==0)
				 {
					 m_site[BACKSTAGE_STIE] = xml.GetChildData();
				 }
				 else if (tag.CompareNoCase("cdnurl")==0)
				 {
					 m_site[CDNSTATICURL_STIE] = xml.GetChildData();
				 }
			 }
			 
			 return true;
		 }	 
	 }
	 return false;
 }
 bool SetSite(int nindex,const char* sitestr)
 {
	 if (nindex <0||nindex>=LIMITE_SITE)
		 return false;
	 m_site[nindex] = sitestr;
	 return true;
 }
 CString GetSite(int nindex)
 {
	 if (nindex <0||nindex>=LIMITE_SITE)
		 return "";
	 return m_site[nindex];
 }

 bool Save(const CString& path)
 {
	 CMarkup xml;
	 if(xml.Load(path))
	 {
		 if(xml.FindElem("URLSET"))
		 {
			 char buffer[64] = { 0 };
			 if(xml.FindChildElem("version"))
			 {
				 sprintf(buffer,"%u",m_verion);
				 xml.SetChildData(buffer);
			 }
			 else
			 {
				 sprintf(buffer,"%u",m_verion);
				 xml.AddChildElem("version",buffer);
			 }

			 if(xml.FindChildElem("startcode"))
			 {
				 sprintf(buffer,"%d",m_startCode);
				 xml.SetChildData(buffer);
			 }
			 else
			 {
				 sprintf(buffer,"%d",m_startCode);
				 xml.AddElem("startcode",buffer);
			 }

			
			 if(xml.FindChildElem("imgup"))
				 xml.SetChildData(m_site[IMGUP_SITE]);
			 else
				 xml.AddChildElem("imgup",m_site[IMGUP_SITE]);

			 if(xml.FindChildElem("hall"))
				 xml.SetChildData(m_site[HALL_SITE]);
			 else
				 xml.AddChildElem("hall",m_site[HALL_SITE]);

			 if(xml.FindChildElem("gift"))
				 xml.SetChildData(m_site[GIFT_SITE]);
			 else
				 xml.AddChildElem("gift",m_site[GIFT_SITE]);

			 if(xml.FindChildElem("web"))
				 xml.SetChildData(m_site[WEB_SITE]);
			 else
				 xml.AddChildElem("web",m_site[WEB_SITE]);

			 if(xml.FindChildElem("log"))
				 xml.SetChildData(m_site[LOG_SITE]);
			 else
				 xml.AddChildElem("log",m_site[LOG_SITE]);

			 if(xml.FindChildElem("upgrade"))
				 xml.SetChildData(m_site[UPGRADE_SITE]);
			 else
				 xml.AddChildElem("upgrade",m_site[UPGRADE_SITE]);

			 if(xml.FindChildElem("backstage"))
				 xml.SetChildData(m_site[BACKSTAGE_STIE]);
			 else
				 xml.AddChildElem("backstage",m_site[BACKSTAGE_STIE]);

			 if(xml.FindChildElem("cdnurl"))
				 xml.SetChildData(m_site[CDNSTATICURL_STIE]);
			 else
				 xml.AddChildElem("cdnurl",m_site[CDNSTATICURL_STIE]);
		 }	  
	 }
	 else
	 {
		 xml.SetDoc(_T("<?xml version=\"1.0\"?>"));
		xml.AddElem("URLSET");
		 char buffer[64] = { 0 };
		 sprintf(buffer,"%u",m_verion);
		 xml.AddChildElem("version",buffer);
		// xml.SetAttrib("ver",buffer);

		 memset(buffer,0,64);
		 sprintf(buffer,"%d",m_startCode);
		 xml.AddChildElem("startcode",buffer);
		// xml.SetAttrib("code",buffer);

		 xml.AddChildElem("imgup",m_site[IMGUP_SITE]);
		 xml.AddChildElem("imgs",m_site[IMGS_SITE]);

		 xml.AddChildElem("hall",m_site[HALL_SITE]);
		 xml.AddChildElem("gift",m_site[GIFT_SITE]);

		 xml.AddChildElem("web",m_site[WEB_SITE]);
		 xml.AddChildElem("log",m_site[LOG_SITE]);

		 xml.AddChildElem("upgrade",m_site[UPGRADE_SITE]);
		 xml.AddChildElem("backstage",m_site[BACKSTAGE_STIE]);

		 xml.AddChildElem("cdnurl",m_site[CDNSTATICURL_STIE]); 
	 }
	 xml.Save(path);
	 return true;
 }
};
class CURLProtocol
{
public:
	static  void GetDefineUrlPotocol(const CString& filePath,std::vector<std::wstring>& vecRet)
	{
		CMarkup xml;
		if(xml.Load(filePath))
		{
			if (xml.FindElem("protocol"))
			{
				if (xml.FindChildElem("key"))
				{
					xml.IntoElem();
					while(xml.FindChildElem("item"))
					{
						USES_CONVERSION;
						vecRet.push_back(A2W(xml.GetChildData()));
					}
					xml.OutOfElem();
				}
			}
		}
	}
};
typedef vector< CAppcenterCount >  AppcenterVec; 


#define UPDATE_TIMEOUT		60000*2
typedef struct
{
	uint32 uin;             //�û���
	DWORD type;				//Ҫ���µ����
	DWORD partnerID;		//�ͻ����̼Һ�
	CString urlTail;		//url��׺
	CString version;		//��ǰ�ͻ��˵İ汾��
	CString filePath;		//���ص��ļ���
	CString extraPath;		//��Ҫ��ѹ����·��
	CString webIP;			//վ��IP
	bool bNeedNotify;		//�Ƿ���Ҫ֪ͨ
	bool bNeedExtra;		//�Ƿ���Ҫ��ѹ
	bool bBreakContinu;		//�Ƿ�Ҫ�ϵ�����
	DWORD dwUserData;		//�û��Զ�������ݣ���Ϊ����ʶ��ı�ʶ
} ResDownloadWork;

//----------------------------------------------------
enum ResDownLoadState
{
	DOWNLOAD_SUCCESS,
	DOWNLOAD_DLERROR,
	DOWNLOAD_FILEERROR,
};

enum ResDownloadType
{
	UPDATE_GIFTCONFIG_XML,
	UPDATE_GIFTRES_BMP,
	UPDATE_GIFTRES_OTHER,
};
#endif

