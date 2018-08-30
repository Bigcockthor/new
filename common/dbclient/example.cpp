#include "dbclient.h"

using namespace dataport;

class CDbClientTest:
    public CDBClientBase
{
public:
    CDbClientTest(int nMaxThreadNum,const string & strUrl,const string & strSecret)
        : CDBClientBase (nMaxThreadNum,strUrl.c_str(),strSecret.c_str())
    {
    }

public:
    void OnResult (CDBClientResult *result)
    {
        //Login函数返回, result->errorCode非0表示成功, 调用成功后info指向用户信息
        delete result;
    }
};

int main(int argc,char * argv[])
{
    // 初始化
    dataport::CDBClientBase::GlobalDbCltInit();
    CDbClientTest *example = new CDbClientTest;
    example->open(2,"http://192.168.20.20:8008","123456");

    // API调用, 返回结果都以回调的方式
    example->Login (1, 10001, "a", "123", "127.0.0.1", "", "pc", "hz", NULL);

    /* >>>>>>>> 事件循环, 逻辑代码 <<<<<<<<<<< */

    // 释放资源
    example->close ();

    delete example;
    return 0 ;
}

