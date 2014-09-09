; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDBMSDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DBMS.h"

ClassCount=5
Class1=CDBMSApp
Class2=CDBMSDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DBMS_DIALOG
Class4=newfile
Class5=newdir
Resource4=IDD_newdir

[CLS:CDBMSApp]
Type=0
HeaderFile=DBMS.h
ImplementationFile=DBMS.cpp
Filter=N

[CLS:CDBMSDlg]
Type=0
HeaderFile=DBMSDlg.h
ImplementationFile=DBMSDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CAboutDlg]
Type=0
HeaderFile=DBMSDlg.h
ImplementationFile=DBMSDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DBMS_DIALOG]
Type=1
Class=CDBMSDlg
ControlCount=8
Control1=IDC_EDIT1,edit,1350631428
Control2=IDC_TREE1,SysTreeView32,1350631424
Control3=IDC_new,button,1342242816
Control4=IDC_run,button,1342242816
Control5=IDC_LIST1,SysListView32,1350631425
Control6=IDC_exit,button,1342242816
Control7=IDC_STATIC,static,1342308866
Control8=IDC_runtime,edit,1476460672

[CLS:newfile]
Type=0
HeaderFile=newfile.h
ImplementationFile=newfile.cpp
BaseClass=CDialog
Filter=D
LastObject=newfile
VirtualFilter=dWC

[DLG:IDD_newdir]
Type=1
Class=newdir
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308866
Control4=IDC_STATIC,static,1342308866
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_EDIT2,edit,1476462720

[CLS:newdir]
Type=0
HeaderFile=newdir.h
ImplementationFile=newdir.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

