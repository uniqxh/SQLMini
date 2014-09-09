// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A352B158_D8A7_4991_940A_16B993FBE37A__INCLUDED_)
#define AFX_STDAFX_H__A352B158_D8A7_4991_940A_16B993FBE37A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls

#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


#endif // _AFX_NO_AFXCMN_SUPPORT
#include "SkinPPWTL.h" //在这个地方加   
#pragma comment(lib,"SkinPPWTL.lib")   


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A352B158_D8A7_4991_940A_16B993FBE37A__INCLUDED_)
