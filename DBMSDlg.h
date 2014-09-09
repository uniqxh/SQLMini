// DBMSDlg.h : header file
//

#if !defined(AFX_DBMSDLG_H__B7084E01_A990_4D7A_9FB3_3BC9904FCCAC__INCLUDED_)
#define AFX_DBMSDLG_H__B7084E01_A990_4D7A_9FB3_3BC9904FCCAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDBMSDlg dialog

class CDBMSDlg : public CDialog
{
// Construction
public:
	void Update();
	void Delete();
	void Drop();
	void Insert();
	void Select();
	void writedata();
	void readdata();
	void showtree();
	void Create();
	CString projectpath;//工程文件路经
	CString PATH;//绝对路径

	CDBMSDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDBMSDlg)
	enum { IDD = IDD_DBMS_DIALOG };
	CListCtrl	m_list;
	CTreeCtrl	m_tree;
	CString	m_sql;
	CString	m_runtime;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBMSDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDBMSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void Onnew();
	afx_msg void Onrun();
	afx_msg void Onexit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBMSDLG_H__B7084E01_A990_4D7A_9FB3_3BC9904FCCAC__INCLUDED_)
