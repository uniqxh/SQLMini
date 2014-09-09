#include "stdafx.h"
#include "BPlus_tree.h"
using namespace std;
struct Item            //表中每一数据项的结构
{
	bool flag; //该数据项数据类型，0：字符型，1：整型
	CString strValue;      //如果该项为字符型，存放相应字符型值
	int intValue;       //如果该项为整型，存放相应整型值
};

struct Column               //表中每一列的结构
{
	CString CName;            //该列的字段名
	CString len;           //该列的属性0：整型，〉=1:字符型
	bool iskey;//1是主键，0不是
	bool isnull;//0可以为空，1不可以
	bool isindex;
	CString vname;//类型名
	vector<CString> strkey;  //记录每列数据项
	void init()
	{
		iskey=0;
		isnull=0;
		isindex=0;
	}
};

struct Table                 //表结构
{
		CString TName;            //该表表名
		CBPlusTree *index;
		int col;
		vector<Column> ColumnList;  //记录该表中各列的向量
		void init()
		{
			col=-1;
			index=NULL;
		}
};

vector<Table> TableList;     //记录当前系统中所有表的向量
