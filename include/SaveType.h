#ifndef __SAVE_TYPE_H__
#define __SAVE_TYPE_H__


//�����������Ͷ���
enum SAVE_DATA_TYPE
{
    SAVE_MONEY = 1,        //���
	SAVE_DIAMOND,          //��ʯ
	SAVE_POINT,            //����
	SAVE_LOGIN_TIMES,      //��¼����

	SAVE_FACTION_LEVEL,    //���ȼ�


	SAVE_USER_ALL,         //�����û���������
	SAVE_FACTION_ALL,      //��������������
};






//����DB����
enum SAVE_DB_TYPE
{
	SAVE_DB_ATONCE,        //ʵʱ����(ͬ������DB��redis)
	SAVE_DB_REDIS,         //��ʱ����(�ȱ���redis,��redis��ʱ����DB)
	SAVE_DB_OFFLINE,       //���߱���(���ݸı�,�����͵�DB��,����ʱ����һ�ξ���)
};
    
//ʵʱ����DB���������ͼ���
static int g_nSaveDBSetAtOnce[] =
{
	SAVE_MONEY,
	SAVE_DIAMOND,
	SAVE_POINT,
};

//�жϱ���DB����
inline int GetSaveDBType(int nType)
{
	int nums = sizeof(g_nSaveDBSetAtOnce) / sizeof(g_nSaveDBSetAtOnce[0]);
	for (int i = 0; i < nums; i++)
	{
		if (g_nSaveDBSetAtOnce[i] == nType)
			return SAVE_DB_ATONCE;
	}
	return SAVE_DB_REDIS;
}

#endif