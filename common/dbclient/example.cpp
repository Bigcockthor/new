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
        //Login��������, result->errorCode��0��ʾ�ɹ�, ���óɹ���infoָ���û���Ϣ
        delete result;
    }
};

int main(int argc,char * argv[])
{
    // ��ʼ��
    dataport::CDBClientBase::GlobalDbCltInit();
    CDbClientTest *example = new CDbClientTest;
    example->open(2,"http://192.168.20.20:8008","123456");

    // API����, ���ؽ�����Իص��ķ�ʽ
    example->Login (1, 10001, "a", "123", "127.0.0.1", "", "pc", "hz", NULL);

    /* >>>>>>>> �¼�ѭ��, �߼����� <<<<<<<<<<< */

    // �ͷ���Դ
    example->close ();

    delete example;
    return 0 ;
}

