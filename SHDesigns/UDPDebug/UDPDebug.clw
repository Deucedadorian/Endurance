; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDumpMemDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "udpdebug.h"
LastPage=0

ClassCount=18
Class1=CAddWDlg
Class2=CChildFrame
Class3=CChildTFrame
Class4=CChildTView
Class5=CChildView
Class6=CChildWFrame
Class7=CDelWDlg
Class8=CDumpDlg
Class9=CEditIntDlg
Class10=CEditVarDlg
Class11=CIPAddr
Class12=CMainFrame
Class13=CPopupDlg
Class14=CStructWin
Class15=CUDPDebugApp
Class16=CAboutDlg
Class17=CWatchView

ResourceCount=14
Resource1=IDR_MAINFRAME
Resource2=IDR_STOOLBAR
Resource3=IDR_UDPDEBTTYPE
Resource4=IDR_UDPDEBWTYPE
Resource5=IDD_ABOUTBOX
Resource6=IDR_WTOOLBAR
Resource7=IDR_UDPDEBTYPE
Resource8=IDR_UNUSED
Resource9=IDD_EDITVAR
Resource10=IDD_ADDWATCH
Resource11=IDD_EDITINT
Resource12=IDD_DUMPMEM
Resource13=IDD_IPADDR
Class18=CDumpMemDlg
Resource14=IDD_DUMPRAM

[CLS:CAddWDlg]
Type=0
BaseClass=CDialog
HeaderFile=AddWDlg.h
ImplementationFile=AddWDlg.cpp

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CChildTFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildTFrame.h
ImplementationFile=ChildTFrame.cpp
Filter=M
VirtualFilter=mfWC

[CLS:CChildTView]
Type=0
BaseClass=CWnd
HeaderFile=ChildTView.h
ImplementationFile=ChildTView.cpp

[CLS:CChildView]
Type=0
BaseClass=CWnd
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp

[CLS:CChildWFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildWFrm.h
ImplementationFile=ChildWFrm.cpp

[CLS:CDelWDlg]
Type=0
BaseClass=CDialog
HeaderFile=DelWDlg.h
ImplementationFile=DelWDlg.cpp

[CLS:CDumpDlg]
Type=0
BaseClass=CPopupDlg
HeaderFile=DumpDlg.h
ImplementationFile=DumpDlg.cpp

[CLS:CEditIntDlg]
Type=0
BaseClass=CDialog
HeaderFile=EditIntDlg.h
ImplementationFile=EditIntDlg.cpp

[CLS:CEditVarDlg]
Type=0
BaseClass=CDialog
HeaderFile=EditVarDlg.h
ImplementationFile=EditVarDlg.cpp

[CLS:CIPAddr]
Type=0
BaseClass=CDialog
HeaderFile=IPAddr.h
ImplementationFile=IPAddr.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CPopupDlg]
Type=0
BaseClass=CDialog
HeaderFile=PopupDlg.h
ImplementationFile=PopupDlg.cpp

[CLS:CStructWin]
Type=0
BaseClass=CDbgView
HeaderFile=StructWin.h
ImplementationFile=StructWin.cpp

[CLS:CUDPDebugApp]
Type=0
BaseClass=CWinApp
HeaderFile=UDPDebug.h
ImplementationFile=UDPDebug.cpp
Filter=T
LastObject=CUDPDebugApp
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=UDPDebug.cpp
ImplementationFile=UDPDebug.cpp
LastObject=CAboutDlg

[CLS:CWatchView]
Type=0
BaseClass=CTreeView
HeaderFile=WatchView.h
ImplementationFile=WatchView.cpp

[DLG:IDD_ADDWATCH]
Type=1
Class=CAddWDlg
ControlCount=20
Control1=IDC_ADDR,combobox,1344340226
Control2=IDC_CHAR,button,1342308361
Control3=IDC_INT,button,1342177289
Control4=IDC_LONGINT,button,1342177289
Control5=IDC_FLOAT,button,1342177289
Control6=IDC_STRING,button,1342177289
Control7=IDC_STRUCT,button,1342177289
Control8=IDC_SLENGTH,edit,1350631552
Control9=IDC_MTYPE,button,1342373897
Control10=IDC_MTYPE2,button,1342242825
Control11=IDC_MTYPE3,button,1342242825
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308866
Control14=IDC_HEX,button,1342242819
Control15=IDC_STRUCTLIST,combobox,1344471299
Control16=IDOK,button,1342242817
Control17=IDCANCEL,button,1342242816
Control18=IDC_STATIC,static,1342308353
Control19=IDC_STATIC,button,1342177287
Control20=IDC_SIGNED,button,1342242819

[DLG:IDD_DELETWATCH]
Type=1
Class=CDelWDlg

[DLG:IDD_DUMPMEM]
Type=1
Class=CDumpDlg
ControlCount=8
Control1=IDC_ADDRESS,combobox,1344340226
Control2=IDC_MSIZE,button,1342308361
Control3=IDC_WORD,button,1342177289
Control4=IDC_LONG,button,1342177289
Control5=IDC_MEMDATA,static,1350701056
Control6=IDOK,button,1342242817
Control7=IDC_READ,button,1342242816
Control8=IDC_STATIC,static,1342308866

[DLG:IDD_EDITINT]
Type=1
Class=CEditIntDlg
ControlCount=4
Control1=IDC_INTVAL,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_PROMPT,static,1342308353

[DLG:IDD_EDITVAR]
Type=1
Class=CEditVarDlg
ControlCount=4
Control1=IDC_DATA,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_VNAME,static,1342308352

[DLG:IDD_IPADDR]
Type=1
Class=CIPAddr
ControlCount=3
Control1=IDC_IP_ADDR,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDC_STATIC,static,1342308865

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889

[TB:IDR_WTOOLBAR]
Type=1
Class=?
Command1=ID_LOADW
Command2=ID_SAVEW
Command3=ID_ADDW
Command4=ID_DELETEW
Command5=ID_MODIFY
Command6=ID_EDITDATA
Command7=ID_AUTO
Command8=ID_UPDATE
Command9=ID_NEWWVIEW
Command10=ID_DUMP
Command11=ID_CONTEXT_HELP
CommandCount=11

[TB:IDR_STOOLBAR]
Type=1
Class=?
Command1=ID_FILE_PRINT
Command2=ID_RECONNECT
Command3=ID_TIMESTAMP
Command4=ID_LOGFILE
Command5=ID_NEWWVIEW
Command6=ID_DUMP
Command7=ID_CONTEXT_HELP
CommandCount=7

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_VIEW_TOOLBAR
Command3=ID_VIEW_STATUS_BAR
Command4=ID_HELP_FINDER
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_UDPDEBTYPE]
Type=1
Class=?
Command1=ID_READLASTSYM
Command2=ID_READLASTBSYM
Command3=ID_LOADLASTSTRUCT
Command4=ID_READSYM
Command5=ID_READBSYM
Command6=ID_LOADSTRUCT
Command7=IDM_DUMP_RAM
Command8=IDM_RESET
Command9=ID_APP_EXIT
Command10=ID_NEWWVIEW
Command11=ID_DUMP
Command12=ID_SHOWSYM
Command13=ID_DEF_LIST
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_RECONNECT
Command17=ID_LOGFILE
Command18=ID_TIMESTAMP
Command19=ID_AUTOCR
Command20=ID_CLS
Command21=IDM_WRAP
Command22=IDM_PAUSE
Command23=ID_WINDOW_CASCADE
Command24=ID_WINDOW_TILE_HORZ
Command25=ID_WINDOW_TILE_VERT
Command26=ID_WINDOW_ARRANGE
Command27=ID_HELP_FINDER
Command28=ID_APP_ABOUT
CommandCount=28

[MNU:IDR_UNUSED]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
CommandCount=6

[MNU:IDR_UDPDEBWTYPE]
Type=1
Class=?
Command1=ID_READLASTSYM
Command2=ID_READLASTBSYM
Command3=ID_LOADLASTSTRUCT
Command4=ID_READSYM
Command5=ID_READBSYM
Command6=ID_LOADSTRUCT
Command7=IDM_DUMP_RAM
Command8=IDM_RESET
Command9=ID_APP_EXIT
Command10=ID_NEWWVIEW
Command11=ID_DUMP
Command12=ID_SHOWSYM
Command13=ID_DEF_LIST
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_ADDW
Command17=ID_DELETEW
Command18=ID_MODIFY
Command19=ID_AUTO
Command20=ID_SAVEW
Command21=ID_LOADW
Command22=ID_EDITDATA
Command23=ID_UPDATE
Command24=ID_WINDOW_CASCADE
Command25=ID_WINDOW_TILE_HORZ
Command26=ID_WINDOW_TILE_VERT
Command27=ID_WINDOW_ARRANGE
Command28=ID_HELP_FINDER
Command29=ID_APP_ABOUT
CommandCount=29

[MNU:IDR_UDPDEBTTYPE]
Type=1
Class=?
Command1=ID_READLASTSYM
Command2=ID_READLASTBSYM
Command3=ID_LOADLASTSTRUCT
Command4=ID_READSYM
Command5=ID_READBSYM
Command6=ID_LOADSTRUCT
Command7=IDM_DUMP_RAM
Command8=IDM_RESET
Command9=ID_APP_EXIT
Command10=ID_NEWWVIEW
Command11=ID_DUMP
Command12=ID_SHOWSYM
Command13=ID_DEF_LIST
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_WINDOW_CASCADE
Command17=ID_WINDOW_TILE_HORZ
Command18=ID_WINDOW_TILE_VERT
Command19=ID_WINDOW_ARRANGE
Command20=ID_HELP_FINDER
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_EDIT_PASTE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_HELP
Command7=ID_CONTEXT_HELP
Command8=ID_UPDATE
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_EDIT_UNDO
CommandCount=14

[DLG:IDD_DUMPRAM]
Type=1
Class=CDumpMemDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MEM_START,edit,1350631552
Control4=IDC_MEM_SIZE,edit,1350631552
Control5=IDC_STATIC,static,1342308866
Control6=IDC_STATIC,static,1342308866
Control7=IDC_STATIC,static,1342308352

[CLS:CDumpMemDlg]
Type=0
HeaderFile=DumpMemDlg.h
ImplementationFile=DumpMemDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDumpMemDlg
VirtualFilter=dWC

