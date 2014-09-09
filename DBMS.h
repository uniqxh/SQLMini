// DBMS.h : main header file for the DBMS application
//

#if !defined(AFX_DBMS_H__F885B0DC_ECC5_43E6_AF78_07ED22525839__INCLUDED_)
#define AFX_DBMS_H__F885B0DC_ECC5_43E6_AF78_07ED22525839__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#define SKINSPACE _T("/SPATH:") ////  注意：这个必须添加在#include的下面！！！
/////////////////////////////////////////////////////////////////////////////
// CDBMSApp:
// See DBMS.cpp for the implementation of this class
//

class CDBMSApp : public CWinApp
{
public:
	CDBMSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBMSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDBMSApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBMS_H__F885B0DC_ECC5_43E6_AF78_07ED22525839__INCLUDED_)
