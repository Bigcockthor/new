// tlcrypto.cpp : 定义控制台应用程序的入口点。
//
#include "tlcrypto.h"
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include "base64.h"
#include "sync.h"
#define AES_KEYLEN 16


#define DES_DECRYPT 0
#define DES_ENCRYPT 1

Mutex	g_lock;
CTLCrypto::CTLCrypto()
{

}

std::string CTLCrypto::DesEncrptyWithBase64(std::string& strData, const char* pKey, const char* pIv)
{
	return DesEncrptyWithBase64(strData.c_str(), strData.length(), pKey, pIv);
}

std::string CTLCrypto::DesDecrptyWithBase64(std::string& strData, const char* pKey, const char* pIv)
{
	return DesDecrptyWithBase64(strData.c_str(), strData.length(), pKey, pIv);
}

//std::string CTLCrypto::AesEncryptWithBase64(std::string& strData, const char* pKey, const char* pIv)
//{
//	return AesEncryptWithBase64(strData.c_str(), strData.length(), pKey, pIv);
//}
//
//std::string CTLCrypto::AesDecryptWithBase64(std::string& strData, const char* pKey, const char* pIv)
//{
//	return AesDecryptWithBase64(strData.c_str(), strData.length(), pKey, pIv);
//}

std::string CTLCrypto::DesEncrptyWithBase64(const char* pData, long lDataLen, const char* pKey, const char* pIv)
{
	std::string strRet;
	unsigned char* outBuffer = NULL;
	int outLen = DesCrypt((unsigned char*)pData, (unsigned char* *)&outBuffer, lDataLen, (unsigned char*)pKey, (unsigned char*)pIv, DES_ENCRYPT);
	strRet = talk_base::Base64::encodeFromArray((const char *)outBuffer, outLen);
	if(outBuffer)
	{
		free(outBuffer);

	}
	return strRet;
}

std::string CTLCrypto::DesDecrptyWithBase64(const char* pData, long lDataLen, const char* pKey, const char* pIv)
{
	std::string strRet;
	unsigned char* outBuffer = NULL;
	strRet = talk_base::Base64::decode(std::string(pData, lDataLen));
	int outLen = DesCrypt((unsigned char*)strRet.c_str(), (unsigned char* *)&outBuffer, strRet.size(), (unsigned char*)pKey, (unsigned char*)pIv, DES_DECRYPT);
	
	if(outBuffer)
	{
		strRet = std::string((const char*)outBuffer, outLen);
		free(outBuffer);
	}
	return strRet;
}

//std::string CTLCrypto::AesEncryptWithBase64(const char* pData, long lDataLen, const char* pKey, const char* pIv)
//{
//	std::string strRet;
//	unsigned char* outBuffer = NULL;
//	long lNewLen = 0;
//	int outLen = AesEncrypt((unsigned char*)pData, (unsigned char* *)&outBuffer, lDataLen, (unsigned char*)pKey);
//	strRet = talk_base::Base64::encodeFromArray((const char *)outBuffer, outLen);
//	if(outBuffer)
//	{
//		free(outBuffer);
//
//	}
//	return strRet;
//}
//
//std::string CTLCrypto::AesDecryptWithBase64(const char* pData, long lDataLen, const char* pKey, const char* pIv)
//{
//	unsigned char* outBuffer = NULL;
//	std::string strRet = talk_base::Base64::decode(std::string(pData, lDataLen));
//	int outLen = AesDecrypt((unsigned char*)strRet.c_str(), (unsigned char* *)&outBuffer, strRet.size(), (unsigned char*)pKey);
//	if(outBuffer)
//	{
//		strRet = std::string((const char*)outBuffer, outLen);
//		free(outBuffer);
//	}
//	return strRet;
//}



int CTLCrypto::DesCrypt( unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key, unsigned char * iv, int nCryptType )
{
	MutexObject obj(&g_lock);
	BIO *bio, *mbio, *cbio;
	unsigned char *dst;
	int outlen;
	mbio = BIO_new( BIO_s_mem( ) );
	cbio = BIO_new( BIO_f_cipher( ) );
	BIO_set_cipher( cbio , EVP_des_cbc( ) , key , iv ,nCryptType);
	bio = BIO_push( cbio , mbio );
	BIO_write( bio , inbuf , inlen );
	BIO_flush( bio );
	outlen = BIO_get_mem_data( mbio , (unsigned char **) & dst );
	* outbuf = ( unsigned char * ) malloc( outlen + 1);
	memset(* outbuf, '\0', outlen +1);
	memcpy(* outbuf , dst , outlen );
	BIO_free_all( bio );
	CRYPTO_cleanup_all_ex_data();
	return outlen;
}

//int CTLCrypto::AesEncrypt( unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key)
//{
//	int ret;
//	EVP_CIPHER_CTX ctx;
//	int outl;
//	int tmp;
//	int nDataLen = 0;
//	nDataLen = inlen;
//	//圆整需要加密的数据
//	if(inlen % AES_BLOCK_SIZE)
//	{
//		nDataLen = (inlen/AES_BLOCK_SIZE+1)*AES_BLOCK_SIZE;
//	}
//
//	char* szData = new char[nDataLen+1];
//	char* out = new char[inlen + AES_BLOCK_SIZE];
//	memset(out, 0, inlen + AES_BLOCK_SIZE);
//	memset(szData, 0, nDataLen+1);
//	memcpy(szData, inbuf, inlen);
//
//	EVP_CIPHER_CTX_init(&ctx);
//
//	ret = EVP_EncryptInit_ex(&ctx, EVP_aes_128_ecb(), NULL, (unsigned char*)key, NULL);
//	assert(ret == 1);
//
//	ret = EVP_CIPHER_CTX_set_padding(&ctx, 0);
//	assert(ret == 1);
//
//	ret = EVP_EncryptUpdate(&ctx, (unsigned char*)out, &outl, (unsigned char*)szData, nDataLen);
//	assert(ret == 1);
//	assert(outl == nDataLen);    
//	tmp = outl;
//
//	ret = EVP_EncryptFinal_ex(&ctx, (unsigned char*)&out[outl], &outl);
//	assert(ret == 1);
//	assert(outl == 0);   
//	outl += tmp;
//
//
//	* outbuf = ( unsigned char * ) malloc( outl + 1);
//	memset(* outbuf, '\0', outl +1);
//	memcpy(* outbuf , out , outl );
//	ret = EVP_CIPHER_CTX_cleanup(&ctx);
//	delete [] szData;
//	delete [] out;	
//	return outl;
//}
//
//
//int CTLCrypto::AesDecrypt( unsigned char * inbuf , unsigned char * * outbuf , int inlen , unsigned char * key)
//{
//	int ret;
//	EVP_CIPHER_CTX ctx;
//	int outl;
//	int tmp;
//	int nDataLen = 0;
//	nDataLen = inlen;
//	if(inlen % AES_BLOCK_SIZE)
//	{
//		nDataLen = (inlen/AES_BLOCK_SIZE+1)*AES_BLOCK_SIZE;
//	}
//
//	char* szData = new char[nDataLen+1];
//	char* out = new char[inlen + AES_BLOCK_SIZE];
//	memset(out, 0, inlen + AES_BLOCK_SIZE);
//	memset(szData, 0, nDataLen+1);
//	memcpy(szData, inbuf, inlen);
//
//	EVP_CIPHER_CTX_init(&ctx);
//
//	ret = EVP_DecryptInit_ex(&ctx, EVP_aes_128_ecb(), NULL, (unsigned char*)key, NULL);
//	assert(ret == 1);
//
//
//	ret = EVP_CIPHER_CTX_set_padding(&ctx, 0);
//	assert(ret == 1);
//
//	ret = EVP_DecryptUpdate(&ctx, (unsigned char*)out, &outl, (unsigned char*)szData, nDataLen);
//	assert(ret == 1);
//	assert(outl == nDataLen);   
//	tmp = outl;
//
//	ret = EVP_DecryptFinal_ex(&ctx, (unsigned char*)&out[outl], &outl);
//	assert(ret == 1);
//	assert(outl == 0);   
//	outl += tmp;
//
//	* outbuf = ( unsigned char * ) malloc( outl + 1);
//	memset(* outbuf, '\0', outl +1);
//	memcpy(* outbuf , out , outl );
//	ret = EVP_CIPHER_CTX_cleanup(&ctx);
//	delete [] szData;
//	delete [] out;	
//	return outl;
//}


