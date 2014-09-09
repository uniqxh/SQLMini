// DBMSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DBMS.h"
#include "DBMSDlg.h"
#include "newdir.h"
#include "SQLMini.h"
#include <shlwapi.h>
#include "BPlus_tree.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBMSDlg dialog

CDBMSDlg::CDBMSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBMSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBMSDlg)
	m_sql = _T("");
	m_runtime = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDBMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBMSDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Text(pDX, IDC_EDIT1, m_sql);
	DDX_Text(pDX, IDC_runtime, m_runtime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDBMSDlg, CDialog)
	//{{AFX_MSG_MAP(CDBMSDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
	ON_BN_CLICKED(IDC_new, Onnew)
	ON_BN_CLICKED(IDC_run, Onrun)
	ON_BN_CLICKED(IDC_exit, Onexit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBMSDlg message handlers

BOOL CDBMSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	
	
	// TODO: Add extra initialization here
	::GetModuleFileName( NULL, PATH.GetBuffer(100), 100 );
	PATH.ReleaseBuffer();
	PATH = PATH.Left(PATH.ReverseFind(_T('\\'))-5)+"Project";
//	if(!DirectoryExist(PATH))
		CreateDirectory(PATH, NULL);
	PATH+='\\';

	m_tree.ModifyStyle(0,TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS);
	m_tree.SetBkColor(RGB(204,232,207));
	m_tree.SetTextColor(RGB(0,0,250));
	
	

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDBMSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDBMSDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDBMSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


BOOL CDBMSDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN) 
	{
		return true;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CDBMSDlg::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	HTREEITEM str=m_tree.GetSelectedItem();
	CString strtable=m_tree.GetItemText(str);
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	int i,j,k;
	for(i=0;i<TableList.size();i++)
	{
		if(TableList[i].TName==strtable)
		{
			for(j=0;j<TableList[i].ColumnList.size();j++)
			{
				m_list.InsertColumn(j,TableList[i].ColumnList[j].CName);
				//AfxMessageBox(TableList[i].ColumnList[j].CName);
				m_list.SetColumnWidth(j,100);
				if(j==0)
					for(k=0;k<TableList[i].ColumnList[j].strkey.size();k++)
					{
							m_list.InsertItem(k,TableList[i].ColumnList[j].strkey[k]);
					}
				else
				for(k=0;k<TableList[i].ColumnList[j].strkey.size();k++)
				{
						m_list.SetItemText(k,j,TableList[i].ColumnList[j].strkey[k]);
				}
			}
			break;
		}
	}//*/
	*pResult = 0;

}

void CDBMSDlg::Create()
{
	CString runtime;
	long starttime=GetTickCount();
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	CString substr;
	Table newtable;
	Column col;
	int pos=6,pos1,i;

	//2013.7.2 update
	while(m_sql[pos]==' ')pos++;
	pos1=m_sql.Find(' ',pos);
	substr=m_sql.Mid(pos,pos1-pos);
	substr.MakeLower();
	if(substr!="table")
	{
		AfxMessageBox(substr+"语法错误！！");
		return ;
	}
	pos=pos1;
	while(m_sql[pos]==' ')pos++;
	pos1=pos;
	while((m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z')||m_sql=='-')pos1++;
	substr=m_sql.Mid(pos,pos1-pos);
	//检查表名是否存在
	for(i=0;i<TableList.size();i++)
	{
		if(TableList[i].TName==substr)
			break;
	}
	if(i!=TableList.size())
	{
		AfxMessageBox("表已经存在！");
		return ;
	}
	newtable.TName=substr;
	pos=pos1;
	while(m_sql[pos]==' ')pos++;
	if(m_sql[pos]!='(')
	{
		AfxMessageBox(m_sql[pos]+"语法错误！！");
		return ;
	}
	pos++;
	while(m_sql.Find(',',pos)!=-1)
	{
		col.init();
		while(m_sql[pos]==' ')pos++;
		pos1=pos;
		while((m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z')||m_sql=='-')pos1++;
		substr=m_sql.Mid(pos,pos1-pos);
	//	MessageBox(substr);
		col.CName=substr;
		pos=pos1;
		while(m_sql[pos]==' ')pos++;
		pos1=pos;
		while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
		substr=m_sql.Mid(pos,pos1-pos);
	//	MessageBox(substr);
		substr.MakeLower();
		col.vname=substr;
		if(substr=="char")
		{
			pos=pos1;
			while(m_sql[pos]==' ')pos++;
			if(m_sql[pos]!='(')
			{
				AfxMessageBox(m_sql[pos]+"语法错误！！");
				return ;
			}
			pos++;
			while(m_sql[pos]==' ')pos++;
			pos1=pos;
			while(m_sql[pos1]>='0'&&m_sql[pos1]<='9')pos1++;
			substr=m_sql.Mid(pos,pos1-pos);
	//		MessageBox(substr);
			col.len=substr;
			pos=pos1;
			while(m_sql[pos]==' ')pos++;
			if(m_sql[pos]!=')')
			{
				AfxMessageBox(m_sql[pos]+"语法错误！！");
				return ;
			}
			pos++;
			while(m_sql[pos]==' ')pos++;
			pos1=pos;
		}
		else
		{
			col.len="0";
			pos=pos1;
			while(m_sql[pos]==' ')pos++;
			pos1=pos;
		}
		while(m_sql[pos]!=',')
		{
			pos1=m_sql.Find(' ',pos);
			substr=m_sql.Mid(pos,pos1-pos);
	//		MessageBox(substr);
			substr.MakeLower();
			pos=pos1;
			if(substr=="not")
			{
				while(m_sql[pos]==' ')pos++;
				pos1=pos;
				while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
				substr=m_sql.Mid(pos,pos1-pos);
	//			MessageBox(substr);
				substr.MakeLower();
				if(substr=="null")
				{
					col.isnull=1;
				}
				else
				{
					AfxMessageBox("语法错误！！");
					return ;
				}
				while(m_sql[pos1]==' ')pos1++;
				pos=pos1;
			}
			else if(substr=="primary")
			{
				while(m_sql[pos]==' ')pos++;
				pos1=pos;
				while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
				substr=m_sql.Mid(pos,pos1-pos);
	//			MessageBox(substr);
				substr.MakeLower();
				if(substr=="key")
				{
					col.iskey=1;
					col.isindex=1;
				}
				else
				{
					AfxMessageBox("语法错误！！");
					return ;
				}
				while(m_sql[pos1]==' ')pos1++;
				pos=pos1;
			}
			else
			{
				AfxMessageBox("语法错误！！");
				return ;
			}
		}
		pos++;
		newtable.ColumnList.push_back(col);
	}
	col.init();
		while(m_sql[pos]==' ')pos++;
		pos1=pos;
		while((m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z')||m_sql=='-')pos1++;
		substr=m_sql.Mid(pos,pos1-pos);
//		MessageBox(substr);
		col.CName=substr;
		pos=pos1;
		while(m_sql[pos]==' ')pos++;
		pos1=pos;
		while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
		substr=m_sql.Mid(pos,pos1-pos);
//		MessageBox(substr);
		substr.MakeLower();
		col.vname=substr;
		if(substr=="char")
		{
			pos=pos1;
			while(m_sql[pos]==' ')pos++;
			if(m_sql[pos]!='(')
			{
				AfxMessageBox(m_sql[pos]+"语法错误！！");
				return ;
			}
			pos++;
			while(m_sql[pos]==' ')pos++;
			pos1=pos;
			while(m_sql[pos1]>='0'&&m_sql[pos1]<='9')pos1++;
			substr=m_sql.Mid(pos,pos1-pos);
//			MessageBox(substr);
			col.len=substr;
			pos=pos1;
			while(m_sql[pos]==' ')pos++;
			if(m_sql[pos]!=')')
			{
				AfxMessageBox(m_sql[pos]+"语法错误！！");
				return ;
			}
			pos++;
			while(m_sql[pos]==' ')pos++;
			pos1=pos;
		}
		else
		{
			col.len="0";
			pos=pos1;
			while(m_sql[pos]==' ')pos++;
			pos1=pos;
		}
		while(m_sql[pos]!=')')
		{
			pos1=m_sql.Find(' ',pos);
			substr=m_sql.Mid(pos,pos1-pos);
//			MessageBox(substr);
			substr.MakeLower();
			pos=pos1;
			if(substr=="not")
			{
				while(m_sql[pos]==' ')pos++;
				pos1=pos;
				while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
				substr=m_sql.Mid(pos,pos1-pos);
//				MessageBox(substr);
				substr.MakeLower();
				if(substr=="null")
				{
					col.isnull=1;
				}
				else
				{
					AfxMessageBox("语法错误！！");
					return ;
				}
				while(m_sql[pos1]==' ')pos1++;
				pos=pos1;
			}
			else if(substr=="primary")
			{
				while(m_sql[pos]==' ')pos++;
				pos1=pos;
				while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
				substr=m_sql.Mid(pos,pos1-pos);
//				MessageBox(substr);
				substr.MakeLower();
				if(substr=="key")
				{
					col.iskey=1;
					col.isindex=1;
				}
				else
				{
					AfxMessageBox("语法错误！！");
					return ;
				}
				while(m_sql[pos1]==' ')pos1++;
				pos=pos1;
			}
		}

	newtable.ColumnList.push_back(col);

	for(i=0;i<newtable.ColumnList.size();i++)
		if(newtable.ColumnList[i].isindex==1)
			newtable.col=i;
	substr=newtable.TName;
	substr+=".db";
	CString newfilepath=projectpath+"\\"+substr;
	CStdioFile dirname(newfilepath,CFile::modeCreate);
	dirname.Close();
	
	TableList.push_back(newtable);
	showtree();
	
	long endtime=GetTickCount();
	runtime.Format("%dms",endtime-starttime);
	m_runtime=runtime;
	UpdateData(0);
	MessageBox("创建成功！");

}

void CDBMSDlg::showtree()
{
	m_tree.DeleteAllItems();

	CString dirpath=PATH+"dirname.txt";
	CStdioFile dirname(dirpath,CFile::modeRead);
	CString dir;
	dirname.ReadString(dir);
	dirname.Close();
	CString path=PATH+dir;
	projectpath=path;
	CreateDirectory(path, NULL );

	HTREEITEM root=m_tree.InsertItem(dir);
	path+="\\*.db";
	CFileFind   finder; 
	BOOL   isfind=finder.FindFile(path); 	
	while(isfind)
	{
		isfind=finder.FindNextFile();
		CString   file=finder.GetFileTitle();
		m_tree.InsertItem(file,root);		
	}//*/
	m_tree.UpdateData(1);
}

void CDBMSDlg::readdata()
{
	TableList.clear();
	CString newfilepath=projectpath+"\\sqlmini.xdb";
	CStdioFile newfile(newfilepath,CFile::modeRead);
	CString strdata,substr,substr1,subdata;
	Column column;
	
	fstream fin;
	int pos=0,pos1=0,pos2=0,num=0,i=0,j;
	while(newfile.ReadString(strdata))
	{
		Table table;
		table.init();
		if(strdata=="")
			break;
		strdata.TrimLeft();
		strdata.TrimRight();
		pos=strdata.Find(' ',0);
		substr=strdata.Mid(0,pos);
		table.TName=substr;
		pos++;
		pos1=strdata.Find(' ',pos);
		num=atoi(strdata.Mid(pos,pos1-pos));
		//AfxMessageBox(strdata.Mid(pos,pos1-pos));
		pos=pos1+1;
		for(j=0;j<num;j++)
		{
			//写入字段名
			pos1=strdata.Find(' ',pos);
			substr=strdata.Mid(pos,pos1-pos);
			column.CName=substr;
			pos=pos1+1;
			//写入字段类型

			pos1=strdata.Find(' ',pos);
			substr=strdata.Mid(pos,pos1-pos);
			column.vname=substr;
			pos=pos1+1;
			//写入字段长度

			pos1=strdata.Find(' ',pos);
			substr=strdata.Mid(pos,pos1-pos);
			column.len=substr;
			//写入字段是否为关键字

			column.iskey=strdata[++pos1]=='0'?0:1;
			//写入字段是否为空
			column.isnull=strdata[pos1+2]=='0'?0:1;

			//写入字段是否有索引
			column.isindex=strdata[pos1+4]=='0'?0:1;
			if(column.isindex==1&&column.iskey==1)
				table.col=j;

			table.ColumnList.push_back(column);
			pos=pos1+6;
		}
		CString tablepath=projectpath+"\\"+table.TName+".db";
		CStdioFile fp(tablepath,CFile::modeRead);
		while(fp.ReadString(subdata))
		{
			if(subdata=="")
				break;
			pos=pos1=0;
			for(j=0;j<num;j++)
			{
				if(j==num-1)
					substr1=subdata.Mid(pos,subdata.GetLength()-pos);
				else
				{
					pos1=subdata.Find(' ',pos);
					substr1=subdata.Mid(pos,pos1-pos);
				}
				//AfxMessageBox(table.ColumnList[j].CName);
				table.ColumnList[j].strkey.push_back(substr1);
				pos=pos1+1;
			}
		}
		fp.Close();
		TableList.push_back(table);
	}
	newfile.Close();
	int num1,num2;
	string str1;
	CString str2;
	for(i=0;i<TableList.size();i++)
	{
		num1=TableList[i].col;
		str2=projectpath+"\\"+TableList[i].TName+".index";
		if(TableList[i].ColumnList[0].strkey.size()>0&&num1>=0)
		{	
			if(TableList[i].index==NULL)
				TableList[i].index=new CBPlusTree();
			for(j=0;j<TableList[i].ColumnList[num1].strkey.size();j++)
			{
				num2=atoi(TableList[i].ColumnList[num1].strkey[j]);
				TableList[i].index->insert(num2,j);
			}
			str1=str2.GetBuffer(0);
			TableList[i].index->printAll(str1);
		}
		else
		{
			CFileFind   finder;
			CStdioFile dirname;
			if(finder.FindFile(str2))
			{
				dirname.Remove(str2);
			}
		}
	}
}

void CDBMSDlg::writedata()
{
	CString newfilepath=projectpath+"\\sqlmini.xdb";
	CStdioFile newfile(newfilepath,CFile::modeWrite|CFile::modeCreate);
	CString strdata,str;
	int i,j,k,num;
	for(i=0;i<TableList.size();i++)
	{
		strdata.Format("%s %d",TableList[i].TName,TableList[i].ColumnList.size());
		for(j=0;j<TableList[i].ColumnList.size();j++)
		{
			strdata+=' '+TableList[i].ColumnList[j].CName+' '+TableList[i].ColumnList[j].vname+' '+TableList[i].ColumnList[j].len;
			str.Format(" %d %d %d",TableList[i].ColumnList[j].iskey,TableList[i].ColumnList[j].isnull,TableList[i].ColumnList[j].isindex);
			strdata+=str;
		}
		strdata+='\n';
		newfile.WriteString(strdata);
		newfilepath=projectpath+"\\"+TableList[i].TName+".db";
		CStdioFile cf(newfilepath,CFile::modeWrite|CFile::modeCreate);
		num=TableList[i].ColumnList[0].strkey.size();
		for(j=0;j<num;j++)
		{
			strdata="";
			for(k=0;k<TableList[i].ColumnList.size();k++)
			{
				strdata+=TableList[i].ColumnList[k].strkey[j]+' ';
			}
			strdata.TrimRight();
			strdata+='\n';
			cf.WriteString(strdata);
		}
		cf.Close();
	}
	newfile.Close();
}

void CDBMSDlg::Select()
{
	CString runtime;
	long starttime=GetTickCount();
	long endtime;
	vector<Column> selectlist;
	Table tal;
	Column col;
	bool flag;
	m_sql.TrimLeft();
	m_sql.TrimRight();
	m_sql+=' ';
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	int pos=7,pos1=7,pos2=0,i,j,k,m,ii;
	CString substr,subop,subvalue;
	while(m_sql[pos]==' ')pos++;
	pos1=m_sql.Find(' ',pos);
	substr=m_sql.Mid(pos,pos1-pos);
	if(substr=='*')
		flag=1;
	else
	{
		while((pos1=m_sql.Find(',',pos))!=-1)
		{
			substr=m_sql.Mid(pos,pos1-pos);
			substr.TrimLeft();
			substr.TrimRight();
			col.CName=substr;
			selectlist.push_back(col);
			pos=pos1+1;
		}
		while(m_sql[pos]==' ')pos++;
		pos1=m_sql.Find(' ',pos);
		substr=m_sql.Mid(pos,pos1-pos);
		substr.TrimLeft();
		col.CName=substr;
		selectlist.push_back(col);
		flag=0;
	}
	pos=pos1+1;
	while(m_sql[pos]==' ')pos++;
	pos1=m_sql.Find(' ',pos);
	substr=m_sql.Mid(pos,pos1-pos);
	substr.TrimLeft();
	substr.TrimRight();
	substr.MakeLower();
	if(substr!="from")
	{
		AfxMessageBox("语法错误！！！");
		return ;
	}
	pos=pos1+1;
	while(m_sql[pos]==' ')pos++;
	pos1=m_sql.Find(' ',pos);
	substr=m_sql.Mid(pos,pos1-pos);
	for(i=0;i<TableList.size();i++)
	{
		if(TableList[i].TName==substr)
		{
			if(flag==1)
				for(j=0;j<TableList[i].ColumnList.size();j++)
				{
					col.CName=TableList[i].ColumnList[j].CName;
					selectlist.push_back(col);
				}
			break;
		}
	}
	if(i==TableList.size())
	{
		AfxMessageBox("所查询表不存在！！！");
		return ;
	}
	pos=pos1+1;
	if(pos==m_sql.GetLength())
	{
		for(m=0;m<selectlist.size();m++)
		{
			m_list.InsertColumn(m,selectlist[m].CName);
			m_list.SetColumnWidth(m,60);
			for(j=0;j<TableList[i].ColumnList.size();j++)
			{
				if(selectlist[m].CName==TableList[i].ColumnList[j].CName)
				{
					if(m==0)
						for(k=0;k<TableList[i].ColumnList[j].strkey.size();k++)
						{
								m_list.InsertItem(k,TableList[i].ColumnList[j].strkey[k]);
						}
					else
					for(k=0;k<TableList[i].ColumnList[j].strkey.size();k++)
					{
							m_list.SetItemText(k,m,TableList[i].ColumnList[j].strkey[k]);
					}
				}
			}
		}
	}
	else
	{
		tal=TableList[i];
		while(m_sql[pos]==' ')pos++;
		pos1=m_sql.Find(' ',pos);
		substr=m_sql.Mid(pos,pos1-pos);
		substr.MakeLower();
		if(substr!="where")
		{
			AfxMessageBox("语法错误！！！");
			return ;
		}
		pos=pos1+1;
		while(m_sql[pos]==' ')pos++;
		pos1=pos+1;
		while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
		substr=m_sql.Mid(pos,pos1-pos);//属性
		substr.TrimLeft();
		substr.TrimRight();
		//AfxMessageBox(substr);
		pos=pos1;
		while(m_sql[pos]==' ')pos++;
		pos1=pos+1;
		while(!((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z')))pos1++;
		subop=m_sql.Mid(pos,pos1-pos);//操作符
		subop.TrimLeft();
		subop.TrimRight();
		//AfxMessageBox(subop);
		pos=pos1;
		while(m_sql[pos]==' ')pos++;
		pos1=pos+1;
		while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
		subvalue=m_sql.Mid(pos,pos1-pos);//值
		subvalue.TrimLeft();
		subvalue.TrimRight();
		//AfxMessageBox(subvalue);

		for(j=0;j<TableList[i].ColumnList.size();j++)
		{
			if(tal.ColumnList[j].CName==substr)
			{
				if(tal.ColumnList[j].isindex!=1)
				{
					if(subop=='>')
					{
						for(k=0;k<tal.ColumnList[j].strkey.size();k++)
						{
							//暂时先处理int和字符类型，其他留着
							if(tal.ColumnList[j].vname=="int")
							{
								int aa,bb;
								aa=atoi(subvalue);
								bb=atoi(tal.ColumnList[j].strkey[k]);
								if ( bb < aa )
								{
									for(m=0;m<tal.ColumnList.size();m++)
									{
										for(ii=0;ii<selectlist.size();ii++)
										{
											if(selectlist[ii].CName==tal.ColumnList[m].CName)
											{
												selectlist[ii].strkey.push_back(tal.ColumnList[m].strkey[k]);
												break;
											}
										}
									}
								}
							}else							
							if(tal.ColumnList[j].strkey[k] > subvalue)
							{
								for(m=0;m<tal.ColumnList.size();m++)
								{
									for(ii=0;ii<selectlist.size();ii++)
									{
										if(selectlist[ii].CName==tal.ColumnList[m].CName)
										{
											selectlist[ii].strkey.push_back(tal.ColumnList[m].strkey[k]);
											break;
										}
									}
								}
							}
						}
					}
					else if(subop=='=')
					{
						for(k=0;k<tal.ColumnList[j].strkey.size();k++)
						{					
							if(tal.ColumnList[j].strkey[k] == subvalue)
							{
								for(m=0;m<tal.ColumnList.size();m++)
								{
									for(ii=0;ii<selectlist.size();ii++)
									{
										if(selectlist[ii].CName==tal.ColumnList[m].CName)
										{
											selectlist[ii].strkey.push_back(tal.ColumnList[m].strkey[k]);
											break;
										}
									}
								}
							}
						}
					}
					else if(subop== '<')
					{
						for(k=0;k<tal.ColumnList[j].strkey.size();k++)
						{
							//暂时先处理int和字符类型，其他留着
							if(tal.ColumnList[j].vname=="int")
							{
								int aa,bb;
								aa=atoi(subvalue);
								bb=atoi(tal.ColumnList[j].strkey[k]);
								if ( bb < aa )
								{
									for(m=0;m<tal.ColumnList.size();m++)
									{
										for(ii=0;ii<selectlist.size();ii++)
										{
											if(selectlist[ii].CName==tal.ColumnList[m].CName)
											{
												selectlist[ii].strkey.push_back(tal.ColumnList[m].strkey[k]);
												break;
											}
										}
									}
								}
							}else
							{
								if(tal.ColumnList[j].strkey[k] < subvalue)
								{
									for(m=0;m<tal.ColumnList.size();m++)
									{
										for(ii=0;ii<selectlist.size();ii++)
										{
											if(selectlist[ii].CName==tal.ColumnList[m].CName)
											{
												selectlist[ii].strkey.push_back(tal.ColumnList[m].strkey[k]);
												break;
											}
										}
									}
								}
							}
						}
					}
					else if(subop== "!=")
					{
						for(k=0;k<tal.ColumnList[j].strkey.size();k++)
						{
							//暂时先处理int和字符类型，其他留着
							if(tal.ColumnList[j].vname=="int")
							{
								int aa,bb;
								aa=atoi(subvalue);
								bb=atoi(tal.ColumnList[j].strkey[k]);
								if ( bb != aa )
								{
									for(m=0;m<tal.ColumnList.size();m++)
									{
										for(ii=0;ii<selectlist.size();ii++)
										{
											if(selectlist[ii].CName==tal.ColumnList[m].CName)
											{
												selectlist[ii].strkey.push_back(tal.ColumnList[m].strkey[k]);
												break;
											}
										}
									}
								}
							}else
							if(tal.ColumnList[j].strkey[k] != subvalue)
							{
								for(m=0;m<tal.ColumnList.size();m++)
								{
									for(ii=0;ii<selectlist.size();ii++)
									{
										if(selectlist[ii].CName==tal.ColumnList[m].CName)
										{
											selectlist[ii].strkey.push_back(tal.ColumnList[m].strkey[k]);
											break;
										}
									}
								}
							}
						}
					}
					break;
				}
				else
				{
					if(TableList[i].index!=NULL)
					{
						int pos,i1;
						vector<DataType> res;
						if(subop=='<')pos=0;
						else if(subop=="<=")pos=1;
						else if(subop=='=')pos=2;
						else if(subop==">=")pos=3;
						else if(subop=='>')pos=4;
						int str1;
						str1=atoi(subvalue);
						res=TableList[i].index->select(str1,pos);
						for(m=0;m<tal.ColumnList.size();m++)
						{
							for(ii=0;ii<selectlist.size();ii++)
							{
								if(selectlist[ii].CName==tal.ColumnList[m].CName)
								{
									for(i1=0;i1<res.size();i1++)
									{
										selectlist[ii].strkey.push_back(tal.ColumnList[m].strkey[res[i1]]);
									}
									break;
								}
							}
						}
					}
				}
			}
			
		}

		endtime=GetTickCount();
		endtime/=5;starttime/=5;

		//将结果显示
		for(m=0;m<selectlist.size();m++)
		{
			m_list.InsertColumn(m,selectlist[m].CName);
			//AfxMessageBox(tal.ColumnList[j].CName);
			m_list.SetColumnWidth(m,100);
			for(j=0;j<selectlist[m].strkey.size();j++)
			{
				if(m==0)
					m_list.InsertItem(j,selectlist[m].strkey[j]);
				else
					m_list.SetItemText(j,m,selectlist[m].strkey[j]);
			}
		}
	}
	runtime.Format("%dms",endtime-starttime);
	m_runtime=runtime;
	UpdateData(0);


}

void CDBMSDlg::Onnew() 
{
	// TODO: Add your control notification handler code here
	newdir dlg;
	dlg.m_path=PATH;
	UpdateData(0);
	if(dlg.DoModal()==IDOK)
	{
		showtree();
		CString newfilepath=projectpath+"\\sqlmini.xdb";
		CStdioFile fp;
		CFileFind   finder; 	
		if(finder.FindFile(newfilepath))
		{
			readdata();
		}
		else 
		{
			fp.Open(newfilepath,CFile::modeCreate);
		}
	}
}

void CDBMSDlg::Onrun() 
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	if(projectpath=="")
	{
		AfxMessageBox("请先新建工程！！！");
		return ;
	}
	m_sql.TrimLeft();
	m_sql.TrimRight();
	int pos=0;
	CString substr;
	pos=m_sql.Find(' ',0);
	substr=m_sql.Mid(0,pos);
	substr.TrimLeft();
	substr.TrimRight();
	substr.MakeLower();
	if(substr=="create")
		Create();
	else if(substr=="select")
		Select();
	else if(substr=="insert")
		Insert();
	else if(substr=="drop")
		Drop();
	else if(substr=="delete")
		Delete();
	else if(substr=="update")
		Update();
}

void CDBMSDlg::Onexit()
{
	// TODO: Add your control notification handler code here
	if(MessageBox("确定退出？？","退出",MB_ICONEXCLAMATION|MB_OKCANCEL)==IDCANCEL)
        return;
	CFileFind   finder;
	CString dirpath=PATH+"dirname.txt";
	CStdioFile dirname;
	if(finder.FindFile(dirpath))
	{
		dirname.Remove(dirpath);
		writedata();
	}	
	OnOK();
}

void CDBMSDlg::Insert()
{
	CString runtime;
	long starttime=GetTickCount();
	vector<Column> insertlist;
	Column col;
	bool flag;
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	m_sql.TrimLeft();
	m_sql.TrimRight();
	int pos=0,pos1=11,pos2=0,i,j,k,pos3;
	CString substr,subvalue,subtable,strnull="NULL";
	substr=m_sql.Mid(0,11);
	substr.MakeLower();
	if(substr!="insert into")
	{
		AfxMessageBox(substr+"语法错误！");
		return ;
	}
	pos=pos1+1;
	while(m_sql[pos]==' ')pos++;
	pos1=pos;
//	pos1=m_sql.Find(' ',pos);
	while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='0'&&m_sql[pos1]<='9'))pos1++;
	substr=m_sql.Mid(pos,pos1-pos);
	substr.TrimLeft();
	substr.TrimRight();
	for(i=0;i<TableList.size();i++)
	{
		if(TableList[i].TName==substr)
			break;
	}
	if(i==TableList.size())
	{
		AfxMessageBox("要更新的表不存在！");
		return ;
	}
	pos=pos1;
	while(m_sql[pos]==' ')pos++;
	if(m_sql[pos]=='(')
	{
		flag=0;
		pos++;
		pos1=m_sql.Find(')',pos);
		subtable=m_sql.Mid(pos,pos1-pos);
		subtable.TrimLeft();
		subtable.TrimRight();
		//MessageBox(subtable);
		pos3=pos2=0;
		while((pos3=subtable.Find(',',pos2))!=-1)
		{
			substr=subtable.Mid(pos2,pos3-pos2);
			substr.TrimLeft();
			substr.TrimRight();
			col.CName=substr;
			insertlist.push_back(col);
			pos2=pos3+1;
		}
		substr=subtable.Mid(pos2,subtable.GetLength()-pos2);
		substr.TrimLeft();
		substr.TrimRight();
		col.CName=substr;
		insertlist.push_back(col);
		pos=pos1+1;
	//	if(TableList[i].ColumnList.size()==insertlist.size())
	//		flag=1;
	}
	else 
	{
		for(j=0;j<TableList[i].ColumnList.size();j++)
		{
			col.CName=TableList[i].ColumnList[j].CName;
			insertlist.push_back(col);
		}
	}

	pos1=m_sql.Find('(',pos);
	substr=m_sql.Mid(pos,pos1-pos);
	substr.TrimLeft();
	substr.TrimRight();
	substr.MakeLower();
	//MessageBox(substr);
	if(substr!="values")  //error
	{
		AfxMessageBox("语法错误！");
		return ;
	}
	pos=pos1+1;
	pos1=m_sql.Find(')',pos);
	subvalue=m_sql.Mid(pos,pos1-pos);
	subvalue.TrimLeft();
	subvalue.TrimRight();
	//MessageBox(subvalue);
	pos=pos1=0;
	j=0;
	while((pos1=subvalue.Find(',',pos))!=-1)
	{
		substr=subvalue.Mid(pos,pos1-pos);
		substr.TrimLeft();
		substr.TrimRight();
		if(j>=insertlist.size())
		{
			AfxMessageBox("插入数据不匹配！！");
			return ;
		}
		insertlist[j++].strkey.push_back(substr);
		pos=pos1+1;
	}
	substr=subvalue.Mid(pos,subvalue.GetLength()-pos);
	substr.TrimLeft();
	substr.TrimRight();
	if(j>insertlist.size())
	{
		AfxMessageBox("插入数据不匹配！！");
		return ;
	}
	insertlist[j++].strkey.push_back(substr);
	if(j!=insertlist.size())
	{
		AfxMessageBox("插入数据不匹配！！");
		return ;
	}

	//检查数据的primary key 和 not null
	for(j=0;j<TableList[i].ColumnList.size();j++)
	{
		for(k=0;k<insertlist.size();k++)
		{
			if(TableList[i].ColumnList[j].CName==insertlist[k].CName)
			{
				if(TableList[i].ColumnList[j].iskey==1)
				{
					for(int ii=0;ii<TableList[i].ColumnList[j].strkey.size();ii++)
						if(TableList[i].ColumnList[j].strkey[ii]==insertlist[k].strkey[0])
						{
							AfxMessageBox("插入数据错误！！（primary key）");
							return ;
						}
					if(ii==TableList[i].ColumnList[j].strkey.size())
					{
						int str1;
						str1=atoi(insertlist[k].strkey[0]);
						if(TableList[i].index==NULL)
							TableList[i].index=new CBPlusTree();
						TableList[i].index->insert(str1,ii);
					}
				}
				break;
			}
		}
		if(k==insertlist.size()&&(TableList[i].ColumnList[j].isnull==1||TableList[i].ColumnList[j].iskey==1))
		{
			AfxMessageBox("插入数据错误！！（not null or primary key）");
			return ;
		}
	}

	for(j=0;j<TableList[i].ColumnList.size();j++)
	{
		for(k=0;k<insertlist.size();k++)
		{
			if(TableList[i].ColumnList[j].CName==insertlist[k].CName)
			{
				TableList[i].ColumnList[j].strkey.push_back(insertlist[k].strkey[0]);
				break;
			}
		}
		if(k==insertlist.size())
			TableList[i].ColumnList[j].strkey.push_back(strnull);
	}
	long endtime=GetTickCount();
	runtime.Format("%dms",(endtime-starttime)/10);
	m_runtime=runtime;
	UpdateData(0);
	MessageBox("插入成功！！");
}

void CDBMSDlg::Drop()
{
	CString runtime;
	long starttime=GetTickCount();
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	m_sql.TrimLeft();
	m_sql.TrimRight();
	int pos=0,pos1=10,pos2=0,i;
	CString substr,subvalue,subtable,strnull;
	substr=m_sql.Mid(0,10);
	substr.MakeLower();
	if(substr!="drop table")
	{
		AfxMessageBox(substr+"语法错误！");
		return ;
	}
	pos=pos1+1;
	substr=m_sql.Mid(pos,m_sql.GetLength()-pos);
	substr.TrimLeft();
	substr.TrimRight();
	bool flag=false;
	for(i=0;i<TableList.size();i++)
	{
		if(TableList[i].TName==substr)
		{
			flag=true;
			TableList[i].ColumnList.clear();
			TableList.erase(&TableList[i]);
		//	break;
		}
	}
	if(!flag)
		AfxMessageBox("不存在此表！！");
	else
	{
		CFileFind   finder;
		CString dirpath=projectpath+"\\"+substr+".db";
		CStdioFile dirname;
		if(finder.FindFile(dirpath))
		{
			dirname.Remove(dirpath);
			showtree();
		}

		long endtime=GetTickCount();
		runtime.Format("%dms",endtime-starttime);
		m_runtime=runtime;
		UpdateData(0);

		MessageBox("表删除成功！");
	}

}

void CDBMSDlg::Delete()
{
	CString runtime;
	long starttime=GetTickCount();
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	m_sql.TrimLeft();
	m_sql.TrimRight();
	m_sql+=' ';
	int pos=0,pos1=11,pos2=0,i,j,k,m;
	CString substr,subvalue,subtable,subop;
//	vector<CString>::iterator it;
	substr=m_sql.Mid(0,11);
	substr.MakeLower();
	if(substr!="delete from")
	{
		AfxMessageBox(substr+"语法错误！");
		return ;
	}
	pos=pos1+1;
	while(m_sql[pos]==' ')pos++;
	pos1=m_sql.Find(' ',pos);
	substr=m_sql.Mid(pos,pos1-pos);
	for(i=0;i<TableList.size();i++)
		if(TableList[i].TName==substr)
			break;
	if(i==TableList.size())
	{
		AfxMessageBox("不存在此表，请先创建！！！");
		return ;
	}
	pos=pos1+1;
	if(pos==m_sql.GetLength())
	{
		for(j=0;j<TableList[i].ColumnList.size();j++)
		{
			TableList[i].ColumnList[j].strkey.clear();
		}
		return;
	}
	else
	{
		while(m_sql[pos]==' ')pos++;
		pos1=m_sql.Find(' ',pos);
		substr=m_sql.Mid(pos,pos1-pos);
		substr.MakeLower();
		if(substr!="where")
		{
			AfxMessageBox("语法错误！！！");
			return ;
		}
		pos=pos1+1;
		while(m_sql[pos]==' ')pos++;
		pos1=pos+1;
		while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
		substr=m_sql.Mid(pos,pos1-pos);//属性
		substr.TrimLeft();
		substr.TrimRight();
		//AfxMessageBox(substr);
		pos=pos1;
		while(m_sql[pos]==' ')pos++;
		pos1=pos+1;
		while(!((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z')))pos1++;
		subop=m_sql.Mid(pos,pos1-pos);//操作符
		subop.TrimLeft();
		subop.TrimRight();
		//AfxMessageBox(subop);
		pos=pos1;
		while(m_sql[pos]==' ')pos++;
		pos1=pos+1;
		while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
		subvalue=m_sql.Mid(pos,pos1-pos);//值
		subvalue.TrimLeft();
		subvalue.TrimRight();
		//AfxMessageBox(subvalue);
		for(j=0;j<TableList[i].ColumnList.size();j++)
		{
			if(TableList[i].ColumnList[j].CName==substr)
			{
				if(subop=='>')
				{
					for(k=0;k<TableList[i].ColumnList[j].strkey.size();k++)
					{
						//暂时先处理int和字符类型，其他留着
						if(TableList[i].ColumnList[j].vname=="int")
						{
							int aa,bb;
							aa=atoi(subvalue);
							bb=atoi(TableList[i].ColumnList[j].strkey[k]);
							if ( bb > aa )
							{
								for(m=0;m<TableList[i].ColumnList.size();m++)
									TableList[i].ColumnList[m].strkey.erase(&TableList[i].ColumnList[m].strkey[k]);
									k--;
							}
						}else
						
						if(TableList[i].ColumnList[j].strkey[k] > subvalue)
						{
							for(m=0;m<TableList[i].ColumnList.size();m++)
								TableList[i].ColumnList[m].strkey.erase(&TableList[i].ColumnList[m].strkey[k]);
							k--;
						}
					}
				}
				else if(subop=='=')
				{
					for(k=0;k<TableList[i].ColumnList[j].strkey.size();k++)
					{					
							if(TableList[i].ColumnList[j].strkey[k] == subvalue)
							{
								for(m=0;m<TableList[i].ColumnList.size();m++)
									TableList[i].ColumnList[m].strkey.erase(&TableList[i].ColumnList[m].strkey[k]);
								k--;
							}
					}
				}
				else if(subop== '<')
				{
					for(k=0;k<TableList[i].ColumnList[j].strkey.size();k++)
					{
						//暂时先处理int和字符类型，其他留着
						if(TableList[i].ColumnList[j].vname=="int")
						{
							int aa,bb;
							aa=atoi(subvalue);
							bb=atoi(TableList[i].ColumnList[j].strkey[k]);
							if ( bb < aa )
							{
								for(m=0;m<TableList[i].ColumnList.size();m++)
									TableList[i].ColumnList[m].strkey.erase(&TableList[i].ColumnList[m].strkey[k]);
									k--;
							}
						}else
						if(TableList[i].ColumnList[j].strkey[k] < subvalue)
						{
							for(m=0;m<TableList[i].ColumnList.size();m++)
								TableList[i].ColumnList[m].strkey.erase(&TableList[i].ColumnList[m].strkey[k]);
							k--;
						}
					}
				}
				else if(subop== "!=")
				{
					for(k=0;k<TableList[i].ColumnList[j].strkey.size();k++)
					{
						if(TableList[i].ColumnList[j].strkey[k] != subvalue)
						{
							for(m=0;m<TableList[i].ColumnList.size();m++)
								TableList[i].ColumnList[m].strkey.erase(&TableList[i].ColumnList[m].strkey[k]);
							k--;
						}
					}
				}
				else if(subop== ">=")
				{
					for(k=0;k<TableList[i].ColumnList[j].strkey.size();k++)
					{
						//暂时先处理int和字符类型，其他留着
						if(TableList[i].ColumnList[j].vname=="int")
						{
							int aa,bb;
							aa=atoi(subvalue);
							bb=atoi(TableList[i].ColumnList[j].strkey[k]);
							if ( bb >= aa )
							{
								for(m=0;m<TableList[i].ColumnList.size();m++)
									TableList[i].ColumnList[m].strkey.erase(&TableList[i].ColumnList[m].strkey[k]);
									k--;
							}
						}else						
						if(TableList[i].ColumnList[j].strkey[k] >= subvalue)
						{
							for(m=0;m<TableList[i].ColumnList.size();m++)
								TableList[i].ColumnList[m].strkey.erase(&TableList[i].ColumnList[m].strkey[k]);
							k--;
						}
					}
				}
				else if(subop== "<=")
				{
					for(k=0;k<TableList[i].ColumnList[j].strkey.size();k++)
					{
						//暂时先处理int和字符类型，其他留着
						if(TableList[i].ColumnList[j].vname=="int")
						{
							int aa,bb;
							aa=atoi(subvalue);
							bb=atoi(TableList[i].ColumnList[j].strkey[k]);
							if ( bb <= aa )
							{
								for(m=0;m<TableList[i].ColumnList.size();m++)
									TableList[i].ColumnList[m].strkey.erase(&TableList[i].ColumnList[m].strkey[k]);
									k--;
							}
						}else						
						if(TableList[i].ColumnList[j].strkey[k] <= subvalue)
						{
							for(m=0;m<TableList[i].ColumnList.size();m++)
								TableList[i].ColumnList[m].strkey.erase(&TableList[i].ColumnList[m].strkey[k]);
							k--;
						}
					}
				}
				break;
			}
			
		}
	}
	
	long endtime=GetTickCount();
	runtime.Format("%dms",(endtime-starttime)/10);
	m_runtime=runtime;
	UpdateData(0);
	MessageBox("数据删除成功！！");
	writedata();
	readdata();
}

void CDBMSDlg::Update()
{
	CString runtime;
	long starttime=GetTickCount();
	vector<Column> updatelist;
	Column col;
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	m_sql+=' ';
	int pos=6,pos1=6,pos2=0,i,j,k,pos3;
	CString substr,subvalue,subtable,subop;
	pos=pos1+1;
	while(m_sql[pos]==' ')pos++;
	pos1=m_sql.Find(' ',pos);
	substr=m_sql.Mid(pos,pos1-pos);
	substr.TrimLeft();
	substr.TrimRight();
	for(i=0;i<TableList.size();i++)
	{
		if(TableList[i].TName==substr)
			break;
	}
	if(i==TableList.size())
	{
		AfxMessageBox("要更新的表不存在！");
		return ;
	}
	pos=pos1;
	while(m_sql[pos]==' ')pos++;
	pos1=m_sql.Find(' ',pos);
	substr=m_sql.Mid(pos,pos1-pos);
	substr.MakeLower();
	if(substr!="set")
	{
		AfxMessageBox("语法错误！");
		return ;
	}
	pos=pos1;
	while(m_sql.Find(',',pos)!=-1)
	{
		pos1=m_sql.Find(',',pos);
		pos2=pos3=0;
		subtable=m_sql.Mid(pos,pos1-pos);
		subtable.TrimLeft();
		subtable.TrimRight();
		subtable+=' ';
		while((subtable[pos2]>='a'&&subtable[pos2]<='z')||(subtable[pos2]>='0'&&subtable[pos2]<='9')||(subtable[pos2]>='A'&&subtable[pos2]<='Z'))pos2++;
		substr=subtable.Mid(pos3,pos2-pos3);
		col.CName=substr;
		for(j=0;TableList[i].ColumnList.size();j++)
		{
			if(TableList[i].ColumnList[j].CName==substr)
				break;
		}
		if(j==TableList[i].ColumnList.size())
		{
			AfxMessageBox("有无关属性！");
			return ;
		}
		pos3=pos2;
		while(subtable[pos3]==' ')pos3++;
		if(subtable[pos3++]!='=')
		{
			AfxMessageBox("语法错误！");
			return ;
		}
		while(subtable[pos3]==' ')pos3++;
		pos2=pos3;
		while((subtable[pos2]>='a'&&subtable[pos2]<='z')||(subtable[pos2]>='0'&&subtable[pos2]<='9')||(subtable[pos2]>='A'&&subtable[pos2]<='Z'))pos2++;
		substr=subtable.Mid(pos3,pos2-pos3);
		col.strkey.push_back(substr);
		updatelist.push_back(col);
		col.strkey.clear();
		pos=pos1+1;
	}
	while(m_sql[pos]==' ')pos++;
	pos1=pos;
	while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
	substr=m_sql.Mid(pos,pos1-pos);
	col.strkey.clear();
	col.CName=substr;
	for(j=0;TableList[i].ColumnList.size();j++)
	{
		if(TableList[i].ColumnList[j].CName==substr)
			break;
	}
	if(j==TableList[i].ColumnList.size())
	{
		AfxMessageBox("有无关属性！");
		return ;
	}
	pos=pos1;
	while(m_sql[pos]==' ')pos++;
	if(m_sql[pos++]!='=')
	{
		AfxMessageBox("语法错误！");
		return ;
	}
	while(m_sql[pos]==' ')pos++;
	pos1=pos;
	while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
	substr=m_sql.Mid(pos,pos1-pos);
	//AfxMessageBox(substr);
	col.strkey.push_back(substr);
	updatelist.push_back(col);
	col.strkey.clear();
	pos=pos1;
	while(m_sql[pos]==' ')pos++;
	pos1=m_sql.Find(' ',pos);
	substr=m_sql.Mid(pos,pos1-pos);
	substr.MakeLower();
	//AfxMessageBox(substr);
	if(substr!="where")
	{
		AfxMessageBox("语法错误！");
		return ;
	}
	pos=pos1+1;
	while(m_sql[pos]==' ')pos++;
	pos1=pos;
	while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
	substr=m_sql.Mid(pos,pos1-pos);
	//MessageBox(substr);
	pos=pos1;
	while(m_sql[pos]==' ')pos++;
	if(m_sql[pos++]!='=')
	{
		AfxMessageBox("语法错误！");
		return ;
	}
	while(m_sql[pos]==' ')pos++;
	pos1=pos;
	while((m_sql[pos1]>='a'&&m_sql[pos1]<='z')||(m_sql[pos1]>='0'&&m_sql[pos1]<='9')||(m_sql[pos1]>='A'&&m_sql[pos1]<='Z'))pos1++;
	subvalue=m_sql.Mid(pos,pos1-pos);
	
	for(j=0;j<TableList[i].ColumnList.size();j++)
	{
		if(TableList[i].ColumnList[j].CName==substr)
		{
			for(k=0;k<TableList[i].ColumnList[j].strkey.size();k++)
			{
				//找到数据位置
				if(TableList[i].ColumnList[j].strkey[k]==subvalue)
				{
					//检查数据是否符合要求
					for(int jj=0;jj<TableList[i].ColumnList.size();jj++)
					{
						for(int kk=0;kk<updatelist.size();kk++)
						{
							if(TableList[i].ColumnList[jj].CName==updatelist[kk].CName)
							{
								if(TableList[i].ColumnList[jj].iskey==1)
								{
									for(int ii=0;ii<TableList[i].ColumnList[jj].strkey.size();ii++)
										if(TableList[i].ColumnList[jj].strkey[ii]==updatelist[kk].strkey[0])
										{
											AfxMessageBox("数据更新错误！（primary key）");
											return ;
										}
								}
								break;
							}
						}
					}

					//更新数据
					for(jj=0;jj<TableList[i].ColumnList.size();jj++)
					{
						for(int kk=0;kk<updatelist.size();kk++)
						{
							if(TableList[i].ColumnList[jj].CName==updatelist[kk].CName)
							{
								TableList[i].ColumnList[jj].strkey[k]=updatelist[kk].strkey[0];
								break;
							}
						}
					}
				}
			}
			break;
		}
	}

	long endtime=GetTickCount();
	runtime.Format("%dms",(endtime-starttime)/10);
	m_runtime=runtime;
	UpdateData(0);
	MessageBox("更新成功！！");

}
