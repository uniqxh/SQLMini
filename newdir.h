#if !defined(AFX_NEWDIR_H__90F1913F_A52E_49C6_8311_278529862857__INCLUDED_)
#define AFX_NEWDIR_H__90F1913F_A52E_49C6_8311_278529862857__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// newdir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// newdir dialog

class newdir : public CDialog
{
// Construction
public:
	newdir(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(newdir)
	enum { IDD = IDD_newdir };
	CString	m_dirname;
	CString	m_path;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(newdir)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(newdir)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWDIR_H__90F1913F_A52E_49C6_8311_278529862857__INCLUDED_)
