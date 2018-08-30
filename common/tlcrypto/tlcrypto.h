/***********************************************************************************************
// 文件名:     tlcrypto.h
// 创建者:     徐运杰
// Email:      linux_xuyunjie@163.com
// 创建时间:   2014/5/13 11:11:32
// 内容描述:   加密解密相关
// 版本信息:   1.0V
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
