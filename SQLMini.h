#include "stdafx.h"
#include "BPlus_tree.h"
using namespace std;
struct Item            //����ÿһ������Ľṹ
{
	bool flag; //���������������ͣ�0���ַ��ͣ�1������
	CString strValue;      //�������Ϊ�ַ��ͣ������Ӧ�ַ���ֵ
	int intValue;       //�������Ϊ���ͣ������Ӧ����ֵ
};

struct Column               //����ÿһ�еĽṹ
{
	CString CName;            //���е��ֶ���
	CString len;           //���е�����0�����ͣ���=1:�ַ���
	bool iskey;//1��������0����
	bool isnull;//0����Ϊ�գ�1������
	bool isindex;
	CString vname;//������
	vector<CString> strkey;  //��¼ÿ��������
	void init()
	{
		iskey=0;
		isnull=0;
		isindex=0;
	}
};

struct Table                 //��ṹ
{
		CString TName;            //�ñ����
		CBPlusTree *index;
		int col;
		vector<Column> ColumnList;  //��¼�ñ��и��е�����
		void init()
		{
			col=-1;
			index=NULL;
		}
};

vector<Table> TableList;     //��¼��ǰϵͳ�����б������
