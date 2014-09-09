#include <algorithm>
#include <cconio>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

ofstream fTABout;
ifstream fTABin;
string rootpath;

struct Column//每列
{
	string cname;
	short attribute;
	vector<int> intkey;
	vector<string> charkey;
};

struct Table//表
{	
	string tname;
	FILE * Tablefp;
	vector<Column> ColumnList;
};

vector<Table> TableList;//表目录

struct Item
{
	short NumOrChar;
	string Value;
	int intValue;
};

bool ClsProc();
bool CommitProc(bool isDDL);
bool CreateProc();
bool DeleteProc();
bool DescProc();
bool DropProc();
bool ErrorProc();
bool ExceptionProc();
bool ExitProc();
bool InsertProc();
bool RollbackProc();
bool SelectProc();
bool UpdateProc();
