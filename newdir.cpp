// newdir.cpp : implementation file
//

#include "stdafx.h"
#include "DBMS.h"
#include "DBMSDlg.h"
#include "newdir.h"
//#include "SQLMini.h"
#include <shlwapi.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// newdir dialog


newdir::newdir(CWnd* pParent /*=NULL*/)
	: CDialog(newdir::IDD, pParent)
{
	//{{AFX_DATA_INIT(newdir)
	m_dirname = _T("");
	m_path = _T("");
	//}}AFX_DATA_INIT
}


void newdir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(newdir)
	DDX_Text(pDX, IDC_EDIT1, m_dirname);
	DDX_Text(pDX, IDC_EDIT2, m_path);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(newdir, CDialog)
	//{{AFX_MSG_MAP(newdir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// newdir message handlers

void newdir::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void newdir::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(1);
	CString dirpath=m_path+"dirname.txt";
	CStdioFile dirname(dirpath,CFile::modeWrite|CFile::modeCreate);
	dirname.WriteString(m_dirname);
	dirname.Close();
	CDialog::OnOK();
}

BOOL newdir::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN) 
	{
		OnOK();
		return true;
	} 

	return CDialog::PreTranslateMessage(pMsg);
}
