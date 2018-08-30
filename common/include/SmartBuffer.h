#ifndef SmartBufferH
#define SmartBufferH

#pragma	pack(1)

#include <stdio.h>
#include <string.h>

class  DFSmartBuffer
{
public:
	DFSmartBuffer();
	virtual ~DFSmartBuffer();

public:
	bool IsEmpty() const {return m_pszBuffer == NULL;}	
	void Free();

	char* GetDataBuffer(long& lLength) const;
	char* GetDataBuffer() const { return m_pszBuffer; }

	int GetDataLength() const{ return m_cbBuffer;}
	int GetAllocLength()const{ return m_cbAlloc;}
	int GetSpecLength() const{ return m_cbAlloc - m_cbBuffer;}
    void SetDataLength(long lLength);

	//char* AppendData(const char* pszData, long lLength);
	char* AppendDataEx(const char* pszData, long lLength);
	void  RemoveData(const char* pStart, long lLength);
	char* CommitData(long lLength);		//增加数据的长度（必要时重新分配内存）。返回原来的指针，用于填充数据

	void AppendString(char* lpszText);
	void AppendData(int lVal);
	void AppendData(double fVal);

	DFSmartBuffer& operator = (const DFSmartBuffer& buffer);
	friend bool operator == (DFSmartBuffer& b1, DFSmartBuffer& b2);

	DFSmartBuffer& operator << (char* lpszText)
	{		
		AppendString(lpszText);
		return *this;
	}

	DFSmartBuffer& operator << (int val)
	{
		AppendData(val);
		return *this;
	}

	DFSmartBuffer& operator << (double val)
	{
		AppendData(val);
		return *this;
	}

protected:
	char* AllocBuffer(long lLength, long lGrowLength = 0);
	void  EmptyBuffer();
protected:
	char*	m_pszBuffer;
	long	m_cbAlloc;
	long	m_cbBuffer;
	
#ifdef _DEBUG
	long	m_nAllocCount;
#endif
};

bool operator == (DFSmartBuffer& b1, DFSmartBuffer& b2);



//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack()
#endif  //INC_SMARTBUFFER_H
