/***********************************************************************************************
// �ļ���:     tlcrypto.h
// ������:     ���˽�
// Email:      linux_xuyunjie@163.com
// ����ʱ��:   2014/5/13 11:11:32
// ��������:   ���ܽ������
// �汾��Ϣ:   1.0V
************************************************************************************************/
#ifndef INC_TLCRYPTO_H
#define INC_TLCRYPTO_H
#include <string>



class CTLCrypto
{
public:
	static std::string DesEncrptyWithBase64(const char* pData, long lDataLen, const char* pKey, const char* pIv);
	static std::string DesEncrptyWithBase64(std::string& strData, const char* pKey, const char* pIv);

	static std::string DesDecrptyWithBase64(const char* pData, long lDataLen, const char* pKey, const char* pIv);
	static std::string DesDecrptyWithBase64(std::string& strData, const char* pKey, const char* pIv);

	//static std::string AesEncryptWithBase64(const char* pData, long lDataLen, const char* pKey, const char* pIv);
	//static std::string AesEncryptWithBase64(std::string& strData, const char* pKey, const char* pIv);

	//static std::string AesDecryptWithBase64(const char* pData, long lDataLen, const char* pKey, const char* pIv);
	//static std::string AesDecryptWithBase64(std::string& strData, const char* pKey, const char* pIv);


private:
	CTLCrypto();
	//static 	int AesEncrypt(unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key);

	//static int AesDecrypt(unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key);

	static int DesCrypt(unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key, unsigned char * iv, int nCryptType );


};


#endif 
