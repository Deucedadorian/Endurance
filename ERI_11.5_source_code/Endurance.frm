VERSION 5.00
Object = "{82D1F7B2-21F5-11D5-8CE1-0080C86ADD99}#1.0#0"; "LED.ocx"
Object = "{943CA7D1-C26F-4EA9-901A-2EA9BCAB0A49}#1.0#0"; "SaxComm8.ocx"
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Object = "{BD856031-3F73-11D3-94AA-00104B6CDBC6}#1.0#0"; "freeSize.ocx"
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form frmEndurance 
   Caption         =   "Endurance Remote Interface"
   ClientHeight    =   5370
   ClientLeft      =   225
   ClientTop       =   825
   ClientWidth     =   10410
   Icon            =   "Endurance.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   ScaleHeight     =   5370
   ScaleWidth      =   10410
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdConnect 
      Caption         =   "Connect"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   51
      Top             =   4800
      Width           =   2535
   End
   Begin VB.Frame fraTestMode 
      Caption         =   "Test mode ="
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   6120
      TabIndex        =   49
      Top             =   4440
      Visible         =   0   'False
      Width           =   1695
      Begin VB.CommandButton cmdMode 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   120
         TabIndex        =   50
         Top             =   240
         Visible         =   0   'False
         Width           =   1455
      End
   End
   Begin VB.CommandButton cmdCommand 
      Caption         =   "Run"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Index           =   1
      Left            =   120
      TabIndex        =   48
      Top             =   4200
      Width           =   2535
   End
   Begin VB.Frame Frame6 
      Caption         =   "Running hours"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1815
      Left            =   120
      TabIndex        =   42
      Top             =   2280
      Width           =   2535
      Begin MSWinsockLib.Winsock skWinSock 
         Left            =   1800
         Top             =   360
         _ExtentX        =   741
         _ExtentY        =   741
         _Version        =   393216
      End
      Begin VB.CommandButton cmdCommand 
         Caption         =   "Reset service hours"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   735
         Index           =   3
         Left            =   120
         TabIndex        =   45
         Top             =   960
         Width           =   2295
      End
      Begin VB.Label lblTotalHours 
         Caption         =   "Total hours"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   44
         Top             =   360
         Width           =   2175
      End
      Begin VB.Label lblServiceHours 
         Caption         =   "Service hours"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   43
         Top             =   600
         Width           =   2175
      End
   End
   Begin VB.Frame fraConnected 
      Caption         =   "Not connected "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   6120
      TabIndex        =   39
      Top             =   3600
      Width           =   4215
      Begin VB.Timer tmrFlasher 
         Left            =   3720
         Top             =   240
      End
      Begin VB.Label lblVersion 
         Alignment       =   2  'Center
         Caption         =   "Program version ="
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   40
         Top             =   360
         Width           =   2895
      End
   End
   Begin VB.Frame Frame5 
      Caption         =   "Previous states"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   2760
      TabIndex        =   34
      Top             =   3120
      Width           =   3255
      Begin freeSize.freeSizer freeSizer1 
         Left            =   2040
         Top             =   240
         _ExtentX        =   1588
         _ExtentY        =   1376
         ResizeObjects   =   -1  'True
         MoveObjects     =   -1  'True
         MinFormWidth    =   9800
         MinFormHeight   =   6900
         SmartSizing     =   -1  'True
         SmartPositioning=   -1  'True
      End
      Begin VB.Label lblPreviousState 
         Caption         =   "Previous state"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   36
         Top             =   600
         Width           =   1935
      End
      Begin VB.Label lblPreviousState 
         Caption         =   "Previous state"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   35
         Top             =   360
         Width           =   1935
      End
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   6120
      TabIndex        =   32
      Top             =   4560
      Width           =   4215
   End
   Begin VB.Frame fraEvents 
      Caption         =   "Events "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2055
      Left            =   120
      TabIndex        =   29
      Top             =   120
      Width           =   2535
      Begin VB.CommandButton cmdCommand 
         Caption         =   "Clear event counts"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   735
         Index           =   5
         Left            =   120
         TabIndex        =   46
         Top             =   1200
         Width           =   2295
      End
      Begin VB.Label lblUpSwitches 
         Caption         =   "Up switches"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   33
         Top             =   840
         Width           =   2175
      End
      Begin VB.Label lblBrakeStops 
         Caption         =   "Brake stops"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   31
         Top             =   600
         Width           =   2175
      End
      Begin VB.Label lblMotorStarts 
         Caption         =   "Motor starts"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   30
         Top             =   360
         Width           =   2175
      End
   End
   Begin VB.Frame Frame4 
      Height          =   2415
      Left            =   6120
      TabIndex        =   25
      Top             =   120
      Width           =   4215
      Begin VB.CommandButton cmdCommand 
         Caption         =   "Clear Max"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   735
         Index           =   4
         Left            =   2280
         TabIndex        =   47
         Top             =   1560
         Width           =   1815
      End
      Begin MSFlexGridLib.MSFlexGrid grid 
         Height          =   1215
         Left            =   120
         TabIndex        =   37
         Top             =   240
         Width           =   3975
         _ExtentX        =   7011
         _ExtentY        =   2143
         _Version        =   393216
         Rows            =   4
         Cols            =   3
         FixedRows       =   0
         FixedCols       =   0
         ScrollBars      =   0
         BorderStyle     =   0
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin VB.OptionButton optUnits 
         Caption         =   "Meters/second"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   28
         Top             =   2040
         Width           =   1935
      End
      Begin VB.OptionButton optUnits 
         Caption         =   "Kilometers/hour"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   27
         Top             =   1800
         Width           =   2055
      End
      Begin VB.OptionButton optUnits 
         Caption         =   "Miles/hour"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   26
         Top             =   1560
         Value           =   -1  'True
         Width           =   1575
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Comm status"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1215
      Left            =   2760
      TabIndex        =   21
      Top             =   4080
      Width           =   3255
      Begin LEDcontrolProject.LED ledReceive 
         Height          =   180
         Left            =   120
         TabIndex        =   41
         Top             =   600
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED ledSend 
         Height          =   180
         Left            =   120
         TabIndex        =   22
         Top             =   360
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin VB.Label lblTestWarning 
         Alignment       =   2  'Center
         Caption         =   "Warning program was compiled for testing only"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   735
         Left            =   1560
         TabIndex        =   52
         Top             =   240
         Visible         =   0   'False
         Width           =   1455
      End
      Begin VB.Label Label1 
         Caption         =   "Receive"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   1
         Left            =   360
         TabIndex        =   24
         Top             =   600
         Width           =   975
      End
      Begin VB.Label Label1 
         Caption         =   "Send"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   0
         Left            =   360
         TabIndex        =   23
         Top             =   360
         Width           =   735
      End
   End
   Begin VB.Timer tmrSend 
      Enabled         =   0   'False
      Interval        =   4000
      Left            =   5520
      Top             =   360
   End
   Begin VB.Frame Frame2 
      Caption         =   "Current state"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3015
      Left            =   2760
      TabIndex        =   0
      Top             =   120
      Width           =   3255
      Begin VB.Timer tmrNetworkTimeout 
         Interval        =   60000
         Left            =   2160
         Top             =   240
      End
      Begin VB.Timer tmrRepeatSound 
         Left            =   2760
         Top             =   2160
      End
      Begin VB.Timer tmrFlash 
         Interval        =   300
         Left            =   2760
         Top             =   1680
      End
      Begin VB.Timer tmrCheckRestore 
         Interval        =   1000
         Left            =   2760
         Top             =   1200
      End
      Begin VB.Timer tmrDisconnect 
         Enabled         =   0   'False
         Interval        =   5000
         Left            =   2760
         Top             =   720
      End
      Begin SaxComm8Ctl.SaxComm SaxComm1 
         Height          =   495
         Left            =   1680
         TabIndex        =   38
         Top             =   2160
         Visible         =   0   'False
         Width           =   495
         _cx             =   873
         _cy             =   873
         Enabled         =   -1  'True
         Settings        =   "57600,n,8,1"
         BackColor       =   1
         Columns         =   80
         AutoProcess     =   2
         AutoScrollColumn=   0   'False
         AutoScrollKeyboard=   -1  'True
         AutoScrollRow   =   -1  'True
         AutoSize        =   0
         BackSpace       =   0
         CaptureFilename =   ""
         CaptureMode     =   0
         CDTimeOut       =   0
         ColorFilter     =   0
         Columns         =   80
         CommEcho        =   0   'False
         CommPort        =   "PCI SoftV92 Modem"
         CommSpy         =   0   'False
         CommSpyInput    =   0   'False
         CommSpyOutput   =   0   'False
         CommSpyProperties=   0   'False
         CommSpyWarnings =   0   'False
         CommSpyEvents   =   0   'False
         CTSTimeOut      =   0
         DialMode        =   0
         DialTimeOut     =   60000
         DSRTimeOut      =   0
         Echo            =   0   'False
         Emulation       =   4
         EndOfLineMode   =   0
         ForeColor       =   15
         Handshaking     =   4
         IgnoreOnComm    =   0   'False
         InBufferSize    =   16384
         InputEcho       =   -1  'True
         InputLen        =   0
         InTimeOut       =   0
         OutTimeOut      =   0
         LookUpSeparator =   "|"
         LookUpText      =   ""
         LookUpTimeOut   =   10000
         NullDiscard     =   0   'False
         OutBufferSize   =   16384
         ParityReplace   =   ""
         Rows            =   25
         RThreshold      =   1
         RTSEnable       =   -1  'True
         ScrollRows      =   0
         SThreshold      =   1
         XferProtocol    =   5
         XferStatusDialog=   2
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Terminal"
            Size            =   9
            Charset         =   255
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         StatusbarVisible=   -1  'True
         ToolbarVisible  =   -1  'True
         StatusDialog    =   2
         UseTAPI         =   -1  'True
         BorderStyle     =   1
         SerialNumber    =   "1280-2458161-47"
         PhoneNumber     =   ""
         ProjectFilename =   ""
         CommSpyTransfer =   0   'False
         AutoZModem      =   -1  'True
      End
      Begin LEDcontrolProject.LED edState 
         Height          =   180
         Index           =   0
         Left            =   240
         TabIndex        =   11
         Top             =   360
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
      End
      Begin LEDcontrolProject.LED edState 
         Height          =   180
         Index           =   1
         Left            =   240
         TabIndex        =   12
         Top             =   600
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED edState 
         Height          =   180
         Index           =   2
         Left            =   240
         TabIndex        =   13
         Top             =   840
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED edState 
         Height          =   180
         Index           =   3
         Left            =   240
         TabIndex        =   14
         Top             =   1080
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED edState 
         Height          =   180
         Index           =   4
         Left            =   240
         TabIndex        =   15
         Top             =   1320
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED edState 
         Height          =   180
         Index           =   5
         Left            =   240
         TabIndex        =   16
         Top             =   1560
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED edState 
         Height          =   180
         Index           =   6
         Left            =   240
         TabIndex        =   17
         Top             =   1800
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED edState 
         Height          =   180
         Index           =   7
         Left            =   240
         TabIndex        =   18
         Top             =   2040
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED edState 
         Height          =   180
         Index           =   8
         Left            =   240
         TabIndex        =   19
         Top             =   2280
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
      End
      Begin LEDcontrolProject.LED edState 
         Height          =   180
         Index           =   9
         Left            =   240
         TabIndex        =   20
         Top             =   2520
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
      End
      Begin VB.Label lblState 
         Caption         =   "Warning"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   9
         Left            =   480
         TabIndex        =   10
         Top             =   2520
         Width           =   2655
      End
      Begin VB.Label lblState 
         Caption         =   "Fault "
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   8
         Left            =   480
         TabIndex        =   9
         Top             =   2280
         Width           =   2655
      End
      Begin VB.Label lblState 
         Caption         =   "High wind"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   7
         Left            =   480
         TabIndex        =   8
         Top             =   2040
         Width           =   1575
      End
      Begin VB.Label lblState 
         Caption         =   "Generate high"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   6
         Left            =   480
         TabIndex        =   7
         Top             =   1800
         Width           =   1695
      End
      Begin VB.Label lblState 
         Caption         =   "Generate low"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   5
         Left            =   480
         TabIndex        =   6
         Top             =   1560
         Width           =   1695
      End
      Begin VB.Label lblState 
         Caption         =   "Motor"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   4
         Left            =   480
         TabIndex        =   5
         Top             =   1320
         Width           =   735
      End
      Begin VB.Label lblState 
         Caption         =   "Free-wheel"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   3
         Left            =   480
         TabIndex        =   4
         Top             =   1080
         Width           =   1455
      End
      Begin VB.Label lblState 
         Caption         =   "Cutin"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   2
         Left            =   480
         TabIndex        =   3
         Top             =   840
         Width           =   615
      End
      Begin VB.Label lblState 
         Caption         =   "Calm"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   1
         Left            =   480
         TabIndex        =   2
         Top             =   600
         Width           =   615
      End
      Begin VB.Label lblState 
         Caption         =   "Halt"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   0
         Left            =   480
         TabIndex        =   1
         Top             =   360
         Width           =   855
      End
   End
   Begin VB.Image Image1 
      BorderStyle     =   1  'Fixed Single
      Height          =   915
      Left            =   6120
      Picture         =   "Endurance.frx":058A
      Stretch         =   -1  'True
      Top             =   2640
      Width           =   4200
   End
   Begin VB.Menu mnuSettings 
      Caption         =   "Settings"
      Begin VB.Menu mnuSettingsSerialPort 
         Caption         =   "Local connection settings"
      End
      Begin VB.Menu mnuRemoteConnectionSettings 
         Caption         =   "Remote connection settings"
         Enabled         =   0   'False
         Begin VB.Menu mnuRemotIPSettings 
            Caption         =   "IP settings"
         End
         Begin VB.Menu mnuRemotePassword 
            Caption         =   "Password"
         End
      End
      Begin VB.Menu mnuSettingsNotifications 
         Caption         =   "Notifications"
      End
      Begin VB.Menu mnuSettingsTimeclock 
         Caption         =   "Time clock"
         Begin VB.Menu mnuSettingsTimeclockTime 
            Caption         =   "Time"
         End
         Begin VB.Menu mnuSettingsTimeDate 
            Caption         =   "Date"
         End
      End
      Begin VB.Menu mnuSettingsSiteName 
         Caption         =   "Site name"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuTest 
      Caption         =   "Test"
      Begin VB.Menu mnuTestSnoop 
         Caption         =   "Snoop"
      End
      Begin VB.Menu mnuTestClearRegistry 
         Caption         =   "Clear registry"
      End
      Begin VB.Menu mnuTestStackInfo 
         Caption         =   "Stack info"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuTestFlashWriteCount 
         Caption         =   "Flash write count"
      End
      Begin VB.Menu mnuTestFlashTimestamp 
         Caption         =   "Flash timestamp"
         Begin VB.Menu mnuTestTimeStampResult 
            Caption         =   ""
         End
      End
      Begin VB.Menu mnuTestFirmwareUpdate 
         Caption         =   "Firmware update"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuRecords 
      Caption         =   "Records"
      Begin VB.Menu mnuRecordsDownload 
         Caption         =   "Download"
      End
      Begin VB.Menu mnuRecordsTriggers 
         Caption         =   "Triggers"
      End
      Begin VB.Menu mnuRecordsInterval 
         Caption         =   "Recording interval"
      End
   End
End
Attribute VB_Name = "frmEndurance"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private ReceiveString As String
Public SendString As String
Public SaveState As String
Private LastState As StateEnum
Private InTray As Boolean
Private Connected As Boolean
Private Snooping As Boolean
Private SoundRepeatInterval As Integer
Private SendDate As Boolean
Private NetworkTimeLeft As Integer
Private TimeOutRespondTime As Integer
Private ConnectionType As ConnectionTypeEnum
Private NetworkTimeoutEnabled As Boolean
Public SendInterval As Integer
Private TestOnSent As Boolean
Private TestOffSent As Boolean
Public TestModeSent As Boolean
Public TestMode As TestModeEnum
Private ReceiveTimeOutInterval As Integer
Private IPInfoRequestSent As Boolean
Private MotorOnSent As Boolean
Private BrakeSent As Boolean
Private StackRequestSent As Boolean
Private ManualDisconnected As Boolean
Private mRunCount As Integer
Private mHaltCount As Integer
Public RecordRequestDate As String

Public ProgramSerialNumber As String
Public PendingPassword As String

Public DateToSend As String
Public TimeToSend As String

Public RecIntervalString As String

Public DisplayingTime As Boolean
Public AdjustingTime    As Boolean

Public SendTriggerString As String

Public Enum ConnectionTypeEnum
    SerialPort
    Network
End Enum


Private Notifications(0 To 11, 1 To 4) As Variant

Public R As New clsReceiveString

Public SendState As CommStateEnum

Public ET As New clsRecTranslator

Private Retrying As Boolean

Public Enum CommStateEnum
    notconnected
    SendingNulls
    WaitingForRun
    WaitingForHalt
    WaitingForClearSVC
    WaitingForClearMax
    WaitingForClearEvent
    WaitingForTestOn
    WaitingForTestOff
    WatingForCommTest
    WaitingForIPInfo
    WaitingForIPConfirm
    WaitingForNetmaskConfirm
    WaitingForNameServerConfirm
    WaitingForGatewayConfirm
    WaitingForPortConfirm
    WaitingForIPApplied
    WaitingForMotor
    WaitingForBrake
    WaitingForPasswordKey
    WaitingForStackReport
    WaitingForSiteName
    WaitingForSiteNameConfirm
    WaitingForFlashWrites
    QueryTestMode
    RequestRecordInfo
    RequestMainRecords
    CancelMainRecords
    SendingHello
    SettingRecordInterval
    GettingRecordInterval
    SendingDate
    SendingTime
    RequestDate
    requesttime
    WaitingForTriggers
    SendingTriggers
    SendingPassword
    ChangingPassword
    ApplyingNewPassword
    DisableWatchdog
End Enum
'-------------------------------------------------------------------------------------------
' Create an Icon in System Tray Needs
Private nid As NOTIFYICONDATA ' trayicon variable

Private Type NOTIFYICONDATA
    cbSize As Long
    hWnd As Long
    uId As Long
    uFlags As Long
    uCallBackMessage As Long
    hIcon As Long
    szTip As String * 64
End Type

Private Const NIM_ADD = &H0
Private Const NIM_MODIFY = &H1
Private Const NIM_DELETE = &H2
Private Const WM_MOUSEMOVE = &H200
Private Const NIF_MESSAGE = &H1
Private Const NIF_ICON = &H2
Private Const NIF_TIP = &H4
Private Const WM_LBUTTONDBLCLK = &H203 'Double-click
Private Const WM_LBUTTONDOWN = &H201 'Button down
Private Const WM_LBUTTONUP = &H202 'Button up
Private Const WM_RBUTTONDBLCLK = &H206 'Double-click
Private Const WM_RBUTTONDOWN = &H204 'Button down
Private Const WM_RBUTTONUP = &H205 'Button up

Private Declare Function Shell_NotifyIcon Lib "shell32" Alias "Shell_NotifyIconA" (ByVal dwMessage As Long, pnid As NOTIFYICONDATA) As Boolean
'----------------------------------------------------------------------------------------------------


Private Sub cmdClearMaxValues_Click()
    
    If SaxComm1.PortOpen = False Then
        frmSelectSerialPort.Sax = SaxComm1
        frmSelectSerialPort.Show
    End If
    
    SendString = "@!C04#" + vbCr + vbLf
    
    Transmit SendString
    
    
    tmrSend.Enabled = True

End Sub

Private Sub cmdCommand_Click(Index As Integer)

    If Index = 1 Then
        Select Case cmdCommand(1).Caption
            Case "Halt"
                SendState = WaitingForHalt
            Case "Run"
                SendState = WaitingForRun
        End Select
    Else
        SendState = Index + 1
    End If

    SetNetworkTimeout

End Sub

Private Sub cmdConnect_Click()
    
    
    Select Case cmdConnect.Caption
        
        Case "Connect"
            
            ConnectionLog ("Connect button clicked")
            
            ManualDisconnected = False
            frmEndurance.Disconnect
            frmEndurance.LoadConnectionSettings
            frmEndurance.Connect
            
            
        Case "Disconnect"
        
            ConnectionLog ("Disconnect button clicked")
            
            ManualDisconnected = True 'Don't need to notify user that he disconnected
            
            Disconnect
            
    End Select
        
    mnuRemoteConnectionSettings.Enabled = False
    mnuSettingsTimeclock.Enabled = False
    


End Sub

Private Sub cmdExit_Click()

    End
End Sub

Private Sub cmdMode_Click()

    frmCommTest.Show 1

End Sub

Private Sub cmdTest_Click()
    SendDate = True
End Sub



Private Sub Command1_Click()

End Sub

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)

    Select Case KeyCode
    
        Case 117 'F6
            If mnuTest.Visible = True Then
                mnuTest.Visible = False
            Else
                mnuTest.Visible = True
            End If
            SaveSetting App.EXEName, "Settings", "mnuTest.Visible", mnuTest.Visible
        Case 118 'F7
            frmClearReg.Show 1
        Case 119
            Me.tmrRepeatSound.Enabled = False
        Case 113 'F2
            MotorOnSent = False
            SendState = WaitingForMotor
        Case 114 'F3
            BrakeSent = False
            SendState = WaitingForBrake
        Case 115 'F4
            If cmdMode.Visible Then
                TestOnSent = False
                SendState = WaitingForTestOn
            Else
                frmF4.Show
            End If
        Case 116 'F5
            TestOffSent = False
            SendState = WaitingForTestOff
        Case 122 'F11
            frmConnectionLog.Show
            
        Case 123 'F12
            StackRequestSent = False
            SendState = WaitingForStackReport
    End Select
    
End Sub

Private Sub Form_Load()
    On Error Resume Next
    
    Dim i As Integer
    Dim StartPort As String
    
    Debug.Print App.Path
    
    Me.Caption = "Endurance Remote Interface - version " + Format(App.Major) + "." + Format(App.Minor)

    LoadNotifications
    mnuTestSnoop.Checked = GetSetting(App.EXEName, "Settings", "Snooping", False)
    mnuTest.Visible = GetSetting(App.EXEName, "Settings", "mnuTest.Visible", False)
    If mnuTestSnoop.Checked Then frmSnoop.Show
    
    If Dir("c:\Endurance data files", vbDirectory) = "" Then
        MkDir "c:\Endurance data files"
    End If
    
    LastState = UnknownState
    
    With grid
        For i = 0 To grid.Cols - 1
            grid.ColWidth(i) = grid.Width / grid.Cols
        Next i
        For i = 0 To grid.Rows - 1
            grid.RowHeight(i) = grid.Height / grid.Rows
        Next i
        
        For i = 0 To .Cols - 1
            .ColAlignment(i) = flexAlignCenterCenter
        Next i
    
    End With
    grid.TextMatrix(0, 1) = "Current"
    grid.TextMatrix(0, 2) = "Maximum"
    grid.TextMatrix(1, 0) = "Wind"
    grid.TextMatrix(2, 0) = "Power"
    grid.TextMatrix(3, 0) = "RPM"

    optUnits(GetSetting(App.EXEName, "Settings", "optUnits", 2)) = True
    
    ReceiveTimeOutInterval = GetSetting(App.EXEName, "Settings", "ReceiveTimeOutInterval", 30)
    
    LoadConnectionSettings
    
    ConnectionLog ("---------------------------")
    ConnectionLog ("ERI started")
    Connect
    
End Sub

Private Sub Form_Resize()
    Static count As Double
    
    Dim i As Integer
    
    count = count + 1
    
    
    If Me.WindowState = vbMinimized Then
            
            Me.WindowState = vbNormal
            InTray = True
            minimize_to_tray

    Else
    
        With grid
            For i = 0 To grid.Cols - 1
                grid.ColWidth(i) = grid.Width / grid.Cols
            Next i
            For i = 0 To grid.Rows - 1
                grid.RowHeight(i) = grid.Height / grid.Rows
            Next i
            
            For i = 0 To .Cols - 1
                .ColAlignment(i) = flexAlignCenterCenter
            Next i
        
        End With
        
    End If
    

End Sub

Private Sub lblState_MouseMove(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)

'    Halt
'    Calm
'    CutIn
'    FreeWheel
'    Motor
'    GenerateLow
'    GenerateHigh
'    HighWind
'    Fault
'    Warning
'    UnknownState
    
    Select Case Index
        Case Halt
            lblState(Index).ToolTipText = "Halt - Will not start until run command is sent - brake applied"
        Case Calm
            lblState(Index).ToolTipText = "Calm - Wind too light to start - brake applied"
        Case Cutin
            lblState(Index).ToolTipText = "Cut-in - Rotor not spinning in low wind - brake released"
        Case FreeWheel
            lblState(Index).ToolTipText = "Free-wheel - Idling in low wind - brake released"
        Case Motor
            lblState(Index).ToolTipText = "Motoring - Motor up to starting speed - brake released"
        Case GenerateLow
            lblState(Index).ToolTipText = "Generate low - Producing power at 120 volts - brake released"
        Case GenerateHigh
            lblState(Index).ToolTipText = "Generate high - Producing power at 240 volts - brake released"
        Case HighWind
            lblState(Index).ToolTipText = "High wind - wind too strong - brake applied"
        Case Fault
            lblState(Index).ToolTipText = "Fault - Will not run until run command is sent - brake applied"
        Case Warning
            lblState(Index).ToolTipText = "Warning - will restart after time delay - brake applied"
    End Select

End Sub



Private Sub mnuRecordsDownload_Click()
    
    If R.ProgramVersion >= "8.2.0" Then
        frmRecords2.Show
    Else
        MsgBox ("Must be connected to version 8.2.0 or higher for this function")
    End If

End Sub

Private Sub mnuRecordsInterval_Click()

    If R.ProgramVersion >= "8.4.0" Then
        R.RecordIntervalReceived = False
        SendState = GettingRecordInterval
        frmRecordInterval.Show
        frmRecordInterval.WaitForResponse
    Else
        MsgBox ("Must be connected to version 8.4.0 or higher for this function")
    End If


End Sub

Private Sub mnuRecordsTriggers_Click()
    If R.ProgramVersion >= "8.4.0" Then
        R.TriggersReceived = False
        SendState = WaitingForTriggers
        frmTrigger.Show
    Else
        MsgBox ("Must be connected to version 8.4.0 or higher for this function")
    End If
End Sub

Private Sub mnuRemotePassword_Click()
    frmChangePassword.Show
End Sub

Private Sub mnuRemotIPSettings_Click()
    IPInfoRequestSent = False
    SendState = WaitingForIPInfo
    frmRemoteConnectionSettings.Show

End Sub

Private Sub mnuSettingsNotifications_Click()
    frmNotifications.Show 1
End Sub

Private Sub mnuSettingsSerialPort_Click()
    With frmSelectSerialPort
    
        If GetSetting(App.EXEName, "Settings", "ConnectionType", "SerialPort") = "SerialPort" Then
            .optConnectionType(0) = True
            .mnuTimeOut.Visible = False
        Else
            frmSelectSerialPort.optConnectionType(1) = True
            .mnuTimeOut.Visible = True
        End If
        
    
        frmSelectSerialPort.Sax = SaxComm1
        frmSelectSerialPort.Show
        
    End With
End Sub

Private Sub MSFlexGrid1_Click()

End Sub

Private Sub mnuSettingsSiteName_Click()

    frmSiteName.StartName = R.SiteName
    frmSiteName.Show
End Sub

Private Sub mnuSettingsTimeclockTime_Click()
    If R.ProgramVersion < "8.2.0" Then
        MsgBox ("Must be connected to version 8.2.0 or higher for this function")
    Else
        DisplayingTime = True
        R.DateTimeReceived = False
        SendState = requesttime
    End If

End Sub

Private Sub mnuSettingsTimeDate_Click()

    If R.ProgramVersion < "8.2.0" Then
        MsgBox ("Must be connected to version 8.2.0 or higher for this function")
    Else
    
        R.DateTimeReceived = False
        SendState = RequestDate
    End If
    
End Sub

Private Sub mnuTestClearRegistry_Click()
frmClearReg.Show 1
End Sub


Private Sub mnuTestFirmwareUpdate_Click()
    frmFirmwareUpdate.Show
End Sub

Private Sub mnuTestFlashWriteCount_Click()
    SendState = WaitingForFlashWrites
End Sub

Private Sub mnuTestSnoop_Click()

    If mnuTestSnoop.Checked Then
        mnuTestSnoop.Checked = False
        Unload frmSnoop
    Else
        mnuTestSnoop.Checked = True
        frmSnoop.Show
    End If
    
    SaveSetting App.EXEName, "Settings", "Snooping", mnuTestSnoop.Checked
    
End Sub

Private Sub mnuTestStackInfo_Click()
            StackRequestSent = False
            SendState = WaitingForStackReport

End Sub

Private Sub optUnits_Click(Index As Integer)

    SaveSetting App.EXEName, "Settings", "optUnits", Index
End Sub

Private Sub SaxComm1_Receive()
    ProcessIncomming SaxComm1.Input
End Sub

Public Sub ProcessReceiveString()
    Dim i As Integer
    
    tmrSend.Enabled = False
    
    Static LastState As StateEnum
    
    
    tmrDisconnect.Enabled = False
    tmrDisconnect.Interval = ReceiveTimeOutInterval * 1000
    tmrDisconnect.Enabled = True
    
   ' ResizeGrid
    
    
    If optUnits(0) Then
        TMatrix 1, 1, Format(R.WindSpeed * 2.234, "##0.0") + " mph"
        TMatrix 1, 2, Format(R.MaxWindSpeed * 2.234, "##0.0") + " mph"
    End If
    
    If optUnits(1) Then
        TMatrix 1, 1, Format(R.WindSpeed * 3.6, "##0.0") + " km/h"
        TMatrix 1, 2, Format(R.MaxWindSpeed * 3.6, "##0.0") + " km/h"
    End If
    
    If optUnits(2) Then
        TMatrix 1, 1, Format(R.WindSpeed, "##0.0") + " m/s"
        TMatrix 1, 2, Format(R.MaxWindSpeed, "##0.0") + " m/s"
    End If
    
    TMatrix 2, 1, Format(R.Power, "0") + " watts"
    TMatrix 2, 2, Format(R.Maxpower, "0") + " watts"
    TMatrix 3, 1, Format(R.rpm, "0")
    TMatrix 3, 2, Format(R.Maxrpm, "0")
    
    
    For i = 0 To edState.count - 1
        If i <> R.State(0) Then
            edState(i).State = LEDOff
        Else
            edState(i).State = LEDon
        End If
    Next i
    
    If R.State(0) = Warning Then
        lblState(9) = R.StateLabel(0)
    Else
        lblState(9) = "Warning"
    End If
    
    If R.State(0) = Fault Then
        lblState(8) = R.StateLabel(0)
    Else
        lblState(8) = "Fault"
    End If

    lblPreviousState(0) = R.StateLabel(1)
    lblPreviousState(1) = R.StateLabel(2)
    lblMotorStarts.Caption = "Motor starts = " + Format(R.MotorStarts, "0")
    lblBrakeStops.Caption = "Brake stops = " + Format(R.BrakeStops, "0")
    lblTotalHours.Caption = "Total hours = " + Format(R.TotalHours, "0")
    lblServiceHours.Caption = "Service hours = " + Format(R.ServiceHours, "0")
    
    If R.ServiceHours >= 6000 Then
        lblServiceHours.ForeColor = vbRed
    Else
        lblServiceHours.ForeColor = vbBlack
    End If
    
    lblUpSwitches.Caption = "Up switches = " + Format(R.UpSwitches, "0")

    Select Case SendState
        
        Case WaitingForClearEvent
            If R.MotorStarts + R.BrakeStops + R.UpSwitches = 0 Then
                SendState = SendingNulls
            End If
        
        Case WaitingForClearMax
            If R.Maxrpm = 0 And R.Maxpower = 0 And R.MaxWindSpeed = 0 Then SendState = SendingNulls
        
        Case WaitingForClearSVC
            If R.ServiceHours = 0 Then SendState = SendingNulls
        
        Case WaitingForHalt
            If R.State(0) = Halt Then
                SendState = SendingNulls
                If cmdCommand(1).Caption <> "Run" Then cmdCommand(1).Caption = "Run"
            End If
        
        Case WaitingForRun
            If R.State(0) <> Halt Then
                SendState = SendingNulls
                If cmdCommand(1).Caption <> "Halt" Then cmdCommand(1).Caption = "Halt"
            End If
        
        Case WaitingForTestOn
            If TestOnSent Then SendState = SendingNulls
        
        Case WaitingForTestOff
            If TestOffSent Then SendState = SendingNulls
        
        Case WaitingForStackReport
            If StackRequestSent Then SendState = SendingNulls
            
        Case WaitingForIPInfo
            If R.IPInfoReceived Then
                SendState = SendingNulls
                frmRemoteConnectionSettings.IPAddress = R.IPAddress
                frmRemoteConnectionSettings.Gateway = R.Gateway
                frmRemoteConnectionSettings.NameServer = R.NameServer
                frmRemoteConnectionSettings.Netmask = R.Netmask
                frmRemoteConnectionSettings.Port = R.Port
            End If
            
        Case WatingForCommTest
            If TestModeSent Then SendState = SendingNulls
    
        Case WaitingForIPConfirm
            If R.IPInfoReceived Then

                If R.IPAddress = frmRemoteConnectionSettings.IPAddress Then
                    SendState = WaitingForNetmaskConfirm
                    frmRemoteConnectionSettings.IPAddress = R.IPAddress
                End If
            End If
        
        Case WaitingForNetmaskConfirm

            If R.IPInfoReceived Then
                If R.Netmask = frmRemoteConnectionSettings.Netmask Then
                    SendState = WaitingForNameServerConfirm
                    frmRemoteConnectionSettings.Netmask = R.Netmask
                End If
            End If
        
        Case WaitingForNameServerConfirm
            
            If R.IPInfoReceived Then
                If R.NameServer = frmRemoteConnectionSettings.NameServer Then
                    SendState = WaitingForGatewayConfirm
                    frmRemoteConnectionSettings.NameServer = R.NameServer
                End If
            End If
        
        Case WaitingForGatewayConfirm
            If R.IPInfoReceived Then
                If R.Gateway = frmRemoteConnectionSettings.Gateway Then
                    SendState = WaitingForPortConfirm
                    frmRemoteConnectionSettings.Gateway = R.Gateway
                End If
            End If
        
        Case WaitingForPortConfirm

            If R.IPInfoReceived Then
                If R.Port = frmRemoteConnectionSettings.Port Then
                    SendState = WaitingForIPApplied
                    frmRemoteConnectionSettings.Port = R.Port
                End If
            End If
            
        Case WaitingForIPApplied
            If R.IPApplied Then SendState = SendingNulls
            End
        
        Case WaitingForMotor
            If MotorOnSent Then SendState = SendingNulls
        
        Case WaitingForBrake
            If BrakeSent Then SendState = SendingNulls
        
        Case WaitingForPasswordKey
            If R.PasswordKeyReceived Then
                If R.SiteName = "" Then
                    ProgramSerialNumber = ""
                    frmEndurance.mnuTestTimeStampResult.Caption = ProgramSerialNumber
                    R.PasswordAccepted = False
                    R.PasswordTested = False
                    SendState = SendingPassword
                End If
            End If
            
        Case SendingPassword
            If R.PasswordTested Then
                If R.PasswordAccepted Then
                    SendState = WaitingForSiteName
                Else
                    ManualDisconnected = True 'Don't need to notify user that he disconnected
                    Disconnect
                    MsgBox ("Password rejected")
                    Exit Sub
                End If
            End If
            
        Case SendingHello
            ProcessHello 'First response string received
            
        
        Case WaitingForSiteName
            If R.SiteName <> "" Then
                Me.Caption = "Connected to " + R.SiteName + " using ERI version" + Format(App.Major) + "." + Format(App.Minor)
                frmEndurance.mnuSettingsSiteName.Enabled = True
                If R.ProgramVersion >= "8.0.4" Then
                    SendState = QueryTestMode
                Else
                    SendState = SendingNulls
                End If
            End If
        
        Case WaitingForSiteNameConfirm
            If R.SiteName = frmSiteName.SendName Then
                frmSiteName.txtName = R.SiteName
                Me.Caption = "Connected to " + R.SiteName
                frmEndurance.mnuSettingsSiteName.Enabled = True
                SendState = SendingNulls
                Unload frmSiteName
            End If
        
        Case WaitingForFlashWrites
            If R.FlashInfoReceived Then
                frmFlashWrites.lblFlashWrites = "Flash writes = " + Format(R.FlashWrites)
                frmFlashWrites.lblFreeMemory = "Available SRAM = " + Format(R.FreeMemory)
                frmFlashWrites.Show
                SendState = SendingNulls
            End If
        
        Case QueryTestMode
            If R.QueryTestModeReceived Then
                
                If R.QueryTestMode Then
                    Me.lblTestWarning.Visible = True
                Else
                    Me.lblTestWarning.Visible = False
                End If
                
                SendState = SendingNulls
            End If
            
        Case RequestRecordInfo
            
            If R.ReceivedRecInfo Then
            
                With frmRecords2
                    .grid.TextMatrix(0, 1) = Format(R.Recordmax)
                    .grid.TextMatrix(1, 1) = Format(R.RecordCount)
                    If R.RecordCount > 0 Then
                        .pbRecords.Max = R.RecordCount
                        .grid.TextMatrix(2, 1) = R.RecordOldest.DateString + ", " + R.RecordOldest.TimeString
                        .grid.TextMatrix(3, 1) = R.RecordNewest.DateString + ", " + R.RecordNewest.TimeString
                        .cmdDownload.Enabled = True
                    Else
                        .grid.TextMatrix(2, 1) = "N/A"
                        .grid.TextMatrix(3, 1) = "N/A"
                        .cmdDownload.Enabled = False
                    End If
                    .pbRecords.Value = 0
                    .lblProgress = ""

                    .fraBuffer.Enabled = True
                    .cmdDownload.Enabled = True

                End With
                
                SendState = SendingNulls
            
            End If
            
            
        Case SettingRecordInterval
            If R.RecordIntervalReceived Then
                frmRecordInterval.UpdateInterval
                SendState = SendingNulls
            End If
        
        Case GettingRecordInterval
            If R.RecordIntervalReceived Then
                frmRecordInterval.UpdateInterval
                SendState = SendingNulls
            End If
            
            
        Case RequestMainRecords
            
            If R.RecordsStarted Then
                SendState = SendingNulls
                SendInterval = 2000
            End If
        
        Case CancelMainRecords
            
            If R.RecordsCanceled Then
                SendState = SendingNulls
            End If
            
        Case SendingDate
            If R.DateTimeReceived Then
                SendState = SendingNulls
            End If
            
        Case SendingTime
        
            If R.DateTimeReceived Then
                SendState = SendingNulls
            End If
        
        Case RequestDate
            If R.DateTimeReceived Then
                frmDate.Calendar.Year = R.TowerYear
                frmDate.Calendar.Month = R.TowerMonth
                frmDate.Calendar.Day = R.TowerDay
                frmDate.Show
                SendState = SendingNulls
            End If
        
        Case requesttime
            
            If R.DateTimeReceived Then
                frmTime.DTPicker1.Hour = R.TowerHour
                frmTime.DTPicker1.Minute = R.TowerMinute
                frmTime.DTPicker1.Second = R.TowerSecond
                frmTime.Show
                SendState = SendingNulls
            End If
            
        Case WaitingForTriggers, SendingTriggers
        
            If R.TriggersReceived Then
                frmTrigger.UpdateTriggers
                SendState = SendingNulls
            End If
            
        Case SendingNulls
            
            If DisplayingTime And Not AdjustingTime Then
            
                If frmTime.DTPicker1.Hour <> R.TowerHour Then
                    frmTime.DTPicker1.Hour = R.TowerHour
                End If
                
                If frmTime.DTPicker1.Minute <> R.TowerMinute Then
                    frmTime.DTPicker1.Minute = R.TowerMinute
                End If
                    
                If frmTime.DTPicker1.Second <> R.TowerSecond Then
                    frmTime.DTPicker1.Second = R.TowerSecond
                End If
            End If
        
        Case ChangingPassword
            If R.NewPasswordValidated Then
                R.NewPasswordApplied = False
                SendState = ApplyingNewPassword
            End If
            'Need to verify that the password was received ok.
        
        Case ApplyingNewPassword
            If R.NewPasswordApplied Then
                frmChangePassword.lblSending = "New password applied"
                Unload frmChangePassword
                SendState = SendingNulls
            End If
            
        Case DisableWatchdog
            If R.WatchdogSet Then
                Unload frmFirmwareUpdate
                SendState = SendingNulls
                StartDownloadManager
            End If
            
        Case Else
            
            SendState = SendingNulls
    End Select
    
    
    If R.State(0) <> LastState Then
        LastState = R.State(0)
        If Me.WindowState = vbMinimized Then
            Me.WindowState = vbNormal
        End If
    End If
    
    tmrFlash.Enabled = False
    If ConnectionType = Network Then
        If fraConnected.Caption <> "Connected (via network) to ..." Then
            fraConnected.Caption = "Connected (via network) to ..."
            mnuTestFirmwareUpdate.Enabled = True
        End If
    Else
        If fraConnected.Caption <> "Connected  (via serial port) to ..." Then
            fraConnected.Caption = "Connected  (via serial port) to ..."
            mnuTestFirmwareUpdate.Enabled = False
        End If
    End If
    fraConnected.Enabled = True
    If lblVersion <> "Program version " + R.ProgramVersion Then
        lblVersion = "Program version " + R.ProgramVersion
    End If
    Connected = True

    
    ConnectionCleanup
    
    ModeButtonSet
    
    CheckNotifications
    
    If R.State(0) = Halt Then
        If Me.cmdCommand(1).Caption <> "Run" Then cmdCommand(1).Caption = "Run"
    Else
        If Me.cmdCommand(1).Caption <> "Halt" Then cmdCommand(1).Caption = "Halt"
    End If
    
    tmrSend_Timer
    tmrSend.Interval = SendInterval
    tmrSend.Enabled = True
    
    
End Sub

Public Function StateString(i As Integer) As String
    Select Case i
        Case 0
            StateString = "Halt"
        Case 1
            StateString = "Calm"
        Case 2
            StateString = "Cutin"
        Case 3
            StateString = "Free-wheel"
        Case 4
            StateString = "Motor"
        Case 5
            StateString = "Generate low"
        Case 6
            StateString = "Generate high"
        Case 7
            StateString = "High wind"
        Case 8
            StateString = "Fault"
        Case 9
            StateString = "Warning"
    End Select
End Function

Public Sub Transmit(S As String)
    
    If Connected Then
    
        If ledSend.State = LEDOff Then
            ledSend.Flash
        End If
        
        If ConnectionType = SerialPort Then
             SaxComm1.Output = S
            If mnuTestSnoop.Checked Then
               frmSnoop.Transmit S
            End If
        Else
            If skWinSock.State = sckConnected Then
                skWinSock.SendData S
                If mnuTestSnoop.Checked Then
                   frmSnoop.Transmit S
                End If
            End If
        End If
         
         
     End If

End Sub


Private Sub skWinSock_Connect()

    Do
        DoEvents
    
    Loop Until skWinSock.State = sckConnected Or skWinSock.State = sckError

    Select Case skWinSock.State
        
        Case sckConnected
            Debug.Print "Socket connected"
                tmrSend.Enabled = True
                Connected = True
                ConnectionLog ("Socket established")
        Case sckError
            Debug.Print "Socket error"
            tmrSend.Enabled = False
            ConnectionLog ("Socket error")
        Case Else
            Debug.Print "Socket state = " + Format(skWinSock.State)
            tmrSend.Enabled = False
            ConnectionLog (Format(skWinSock.State))
                
    End Select

    Unload frmNetworkTimeout

End Sub

Private Sub skWinSock_DataArrival(ByVal bytesTotal As Long)
    
    Dim A As String
    
    skWinSock.GetData A
    ProcessIncomming A

End Sub

Private Sub skWinSock_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    ConnectionLog ("Socket error-" + Format(Number) + " - " + Description)
    
    Debug.Print "Socket error - attempting reconnect"
    
    tmrDisconnect.Enabled = False
    tmrSend.Enabled = False
    ConnectionLog ("Atempting to reconnect")
    Retrying = True
    Disconnect
    Retrying = True
    LoadConnectionSettings
    Connect

    
    

End Sub

Private Sub tmrCheckRestore_Timer()
CheckNotifications
End Sub

Private Sub tmrDisconnect_Timer()
    Connected = False
    Me.fraConnected.Caption = "Not connected"
    Me.lblVersion = ""
    Debug.Print "tmrDisconnect expired"
    tmrDisconnect.Enabled = False
    ConnectionLog ("Lost comminucations - timed out")
    DisConnectionCleanup
    
    If ConnectionType = Network Then
        Disconnect
        Retrying = True
        Connect
    End If
End Sub

Private Sub tmrFlash_Timer()
    
    If fraConnected.Enabled Then
        fraConnected.Enabled = False
    Else
        fraConnected.Enabled = True
    End If
    
End Sub

Private Sub tmrGrid_Timer()
    ResizeGrid
End Sub

Private Sub tmrNetworkTimeout_Timer()
    NetworkTimeLeft = NetworkTimeLeft - 1
    tmrNetworkTimeout.Interval = 60000
    tmrNetworkTimeout.Enabled = True
    
    If NetworkTimeLeft = 0 Then

        tmrNetworkTimeout.Enabled = False
'        frmNetworkTimedOut.Connector = Me
        frmNetworkTimedOut.ResponseTime = TimeOutRespondTime
        frmNetworkTimedOut.Show 1
        
    End If

End Sub

Private Sub tmrRepeatSound_Timer()
    PlaySound tmrRepeatSound.Tag
    tmrRepeatSound.Interval = SoundRepeatInterval * 1000
    tmrRepeatSound.Enabled = True
End Sub


Private Sub tmrSend_Timer()
    Dim StringToSend As String

        Select Case SendState
            Case notconnected
                StringToSend = "@!C00#" + vbCr + vbLf
            Case SendingNulls
                StringToSend = "@!C00#" + vbCr + vbLf
            Case WaitingForClearEvent
                StringToSend = "@!C05#" + vbCr + vbLf
            Case WaitingForClearMax
                StringToSend = "@!C04#" + vbCr + vbLf
            Case WaitingForClearSVC
                StringToSend = "@!C03#" + vbCr + vbLf
            Case WaitingForHalt
                StringToSend = "@!C02#" + vbCr + vbLf
            Case WaitingForRun
                StringToSend = "@!C01#" + vbCr + vbLf
            Case WaitingForTestOn
                StringToSend = "@!C06#" + vbCr + vbLf
                TestOnSent = True
            Case WaitingForTestOff
                StringToSend = "@!C07#" + vbCr + vbLf
                TestOffSent = True
            Case WaitingForIPInfo
                StringToSend = "@!C51#" + vbCr + vbLf
                IPInfoRequestSent = True
            Case WatingForCommTest
                TestModeSent = True
                StringToSend = "@!C" + Format(TestMode) + "0#" + vbCr + vbLf
            Case WaitingForIPConfirm
                R.IPInfoReceived = False
                StringToSend = "@!C61 " + frmRemoteConnectionSettings.IPAddress + "#" + vbCr + vbLf
            Case WaitingForNetmaskConfirm
                R.IPInfoReceived = False
                StringToSend = "@!C62 " + frmRemoteConnectionSettings.Netmask + "#" + vbCr + vbLf

            Case WaitingForNameServerConfirm
                R.IPInfoReceived = False
                StringToSend = "@!C63 " + frmRemoteConnectionSettings.NameServer + "#" + vbCr + vbLf
            Case WaitingForGatewayConfirm
                R.IPInfoReceived = False
                StringToSend = "@!C64 " + frmRemoteConnectionSettings.Gateway + "#" + vbCr + vbLf
            Case WaitingForPortConfirm
                R.IPInfoReceived = False
                StringToSend = "@!C65 " + frmRemoteConnectionSettings.Port + "#" + vbCr + vbLf
            Case WaitingForIPApplied
                R.IPApplied = False
                StringToSend = "@!C66#" + vbCr + vbLf
            Case WaitingForMotor
                MotorOnSent = True
                StringToSend = "@!C67#" + vbCr + vbLf
            Case WaitingForBrake
                BrakeSent = True
                StringToSend = "@!C68#" + vbCr + vbLf
            Case WaitingForPasswordKey
                StringToSend = "@!C54#" + vbCr + vbLf
            Case WaitingForStackReport
                StackRequestSent = True
                StringToSend = "@!C69#" + vbCr + vbLf
            Case WaitingForSiteName
                StringToSend = "@!C71#" + vbCr + vbLf
            Case WaitingForSiteNameConfirm
                StringToSend = "@!C72" + frmSiteName.SendName + "#" + vbCr + vbLf
            Case WaitingForFlashWrites
                StringToSend = "@!C73#" + vbCr + vbLf
            Case QueryTestMode
                StringToSend = "@!C74#" + vbCr + vbLf
            Case RequestRecordInfo
                StringToSend = "@!C75-" + Format(R.RecordBuffer) + "#" + vbCr + vbLf
            Case RequestMainRecords
                SendInterval = 8000 'May take a while for a response
                StringToSend = "@!C76," + RecordRequestDate + "-" + Format(R.RecordBuffer) + "#" + vbCr + vbLf
            Case CancelMainRecords
                StringToSend = "@!C77#" + vbCr + vbLf
            Case SendingHello
                StringToSend = "@!C78 " + Format(100 * App.Major + App.Minor) + "#" + vbCr + vbLf
            Case SendingDate
                StringToSend = "@!C08Date=" + DateToSend + "#" + vbCr + vbLf
            Case SendingTime
                StringToSend = "@!C09Time=" + TimeToSend + "#" + vbCr + vbLf
            
            Case RequestDate
                StringToSend = "@!C81#" + vbCr + vbLf
                
            Case requesttime
                StringToSend = "@!C82#" + vbCr + vbLf
                
            Case WaitingForTriggers
                StringToSend = "@!C83#" + vbCr + vbLf
            
            Case SendingTriggers
                StringToSend = "@!C84-" + SendTriggerString + "#" + vbCr + vbLf
                
            Case GettingRecordInterval
                StringToSend = "@!C85#" + vbCr + vbLf

            
            Case SettingRecordInterval
                StringToSend = "@!C79 " + RecIntervalString + "#" + vbCr + vbLf
                
            Case SendingPassword
                StringToSend = "@!C86 " + R.EncryptedPassword + "#" + vbCr + vbLf
                
            Case ChangingPassword
                StringToSend = "@!C87 " + PendingPassword + "#" + vbCr + vbLf
            
            Case ApplyingNewPassword
                StringToSend = "@!C88 " + "Set new password" + "#" + vbCr + vbLf
                
            Case DisableWatchdog
                StringToSend = "@!C89 " + "Disable watchdog" + "#" + vbCr + vbLf
                
        End Select
            
    Transmit StringToSend
    
End Sub

'------------------------
'--- create tray icon ---
'------------------------
Sub minimize_to_tray()
Me.Hide
nid.cbSize = Len(nid)
nid.hWnd = Me.hWnd
nid.uId = vbNull
nid.uFlags = NIF_ICON Or NIF_TIP Or NIF_MESSAGE
nid.uCallBackMessage = WM_MOUSEMOVE
nid.hIcon = Me.Icon ' the icon will be your Form1 project icon
nid.szTip = "Right click to restore Endurance Remote Interface" & vbNullChar
Shell_NotifyIcon NIM_ADD, nid
End Sub

'---------------------------------------------------
'-- Tray icon actions when mouse click on it, etc --
'---------------------------------------------------
Private Sub Form_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)

    Dim msg As Long
    Dim sFilter As String
    msg = X / Screen.TwipsPerPixelX
    
    Select Case msg
        Case WM_LBUTTONDOWN
'            Me.Show ' show form
'            Shell_NotifyIcon NIM_DELETE, nid ' del tray icon
        Case WM_LBUTTONUP
        Case WM_LBUTTONDBLCLK
        Case WM_RBUTTONDOWN
        Case WM_RBUTTONUP
            Me.Show
            InTray = False
            Shell_NotifyIcon NIM_DELETE, nid
        Case WM_RBUTTONDBLCLK
    End Select
    
End Sub

'------------------------------
'--- form Actions On unload ---
'------------------------------
Private Sub Form_Unload(Cancel As Integer)
    
    Shell_NotifyIcon NIM_DELETE, nid ' del tray icon
    
    SaveSetting App.EXEName, "Settings", "frmEndurance.Top", Me.Top
    SaveSetting App.EXEName, "Settings", "frmEndurance.Left", Me.Left
    SaveSetting App.EXEName, "Settings", "frmEndurance.Width", Me.Width
    SaveSetting App.EXEName, "Settings", "frmEndurance.Height", Me.Height
    
    
    
End Sub




Public Sub ModeButtonSet()
    Static LastState As Boolean
    Static NotFirstTime As Boolean
    
    Dim x0 As Double
    Dim x1 As Double
    Dim x2 As Double
    Dim x3 As Double
    Dim Spacing As Double
    
    

    If Not R.JumperIn Then
        If cmdMode.Caption <> R.TestModeString Then
            cmdMode.Caption = R.TestModeString
        End If
    End If



    'If TestState = R.JumperIn Then Exit Sub

    
    Spacing = Me.fraConnected.Left - (Frame3.Left + Frame3.Width)
    
    If R.JumperIn Then
        If (LastState <> R.JumperIn) Or Not NotFirstTime Then
            cmdExit.Move fraConnected.Left, cmdExit.Top, fraConnected.Width, cmdExit.Height
            fraTestMode.Visible = False
            fraTestMode.Enabled = False
            Unload frmCommTest
            cmdMode.Visible = False
        End If
    Else
'        TestState = False
        If (LastState <> R.JumperIn) Or Not NotFirstTime Then
            x0 = cmdExit.Left
            x1 = x0 + cmdExit.Width / 2 - Spacing / 2
            x2 = x1 + Spacing
            x3 = cmdExit.Left + cmdExit.Width
            cmdExit.Move x2, cmdExit.Top, x3 - x2, cmdExit.Height
            
            fraTestMode.Move x0, cmdExit.Top - Spacing, x1 - x0, cmdExit.Height + Spacing
            
            cmdMode.Move Spacing, 3 * Spacing, fraTestMode.Width - 2 * Spacing, fraTestMode.Height - 4 * Spacing
            fraTestMode.Visible = True
            fraTestMode.Enabled = True
            cmdMode.Enabled = True
            cmdMode.Visible = True
        End If
    End If
    
    LastState = R.JumperIn
    NotFirstTime = True
    freeSizer1.Rebuild

End Sub

Public Sub CheckRestore()
    
    Dim NeedRestore As Boolean
    Dim SoundFile As String
    
    Static LastState As StateEnum
    Static LastConnected As Boolean
    Static LastService As Double
    
    If InTray Or (Me.WindowState = vbMinimized) Then
    
        If R.State(0) <> LastState Then
            LastState = R.State(0)
            If LastState > 7 Then NeedRestore = True
        End If

        If LastConnected = True Then
            If Me.fraConnected.Caption = "Not connected" Then

                NeedRestore = True
                LastConnected = False
                Me.Caption = "Endurance Remote Interface - version " + Format(App.Major) + "." + Format(App.Minor)
                
            End If
        Else
            If Me.fraConnected.Caption <> "Not connected" Then
                LastConnected = True
            End If
        End If
        
        
        
        
        If NeedRestore Then
            If Me.WindowState = vbMinimized Then
                Me.WindowState = vbNormal
            End If
            If InTray Then
                Me.Show
                InTray = False
                Shell_NotifyIcon NIM_DELETE, nid
            End If
            PlaySound App.Path + "\chord.wav"
        End If
        
    End If
    
    
    
End Sub

Public Sub ConnectionCleanup()
    cmdCommand(1).Enabled = True
    cmdCommand(3).Enabled = True
    cmdCommand(4).Enabled = True
    cmdCommand(5).Enabled = True
    tmrFlash.Enabled = False
    fraConnected.Enabled = True
    
    If cmdConnect.Caption <> "Disconnect" Then
        Me.cmdConnect.Caption = "Disconnect"
    End If
    
End Sub
Public Sub DisConnectionCleanup()
    Dim C As Object
    Dim i As Integer
    
    SendState = notconnected

    cmdCommand(1).Enabled = False
    cmdCommand(3).Enabled = False
    cmdCommand(4).Enabled = False
    cmdCommand(5).Enabled = False
    tmrFlash.Enabled = True
    
    Me.ProgramSerialNumber = ""
    Me.mnuTestTimeStampResult.Caption = ""

    
    Me.cmdConnect.Caption = "Connect"
    Me.Caption = "Endurance Remote Interface - version " + Format(App.Major) + "." + Format(App.Minor)
    R.ClearSiteName
    Me.lblTestWarning.Visible = False
    
    For i = 0 To edState.count
        edState(0).State = LEDOff
    Next i
    
    mnuTestFirmwareUpdate.Enabled = False

    
End Sub


Public Sub CheckNotifications()
    
    Dim NeedNotify As Boolean
    Dim NeedRestore As Boolean
    Dim SoundFile As String
    Dim NotifyString As String
    
    Static LastState As StateEnum
    Static LastConnected As Boolean
    Static LastService As Double
    
    'If InTray Or (Me.WindowState = vbMinimized) Then
    If R.State(0) = Halt Then
'        Stop
    End If
        If R.State(0) <> LastState Then
            LastState = R.State(0)
            If Notifications(LastState, 1) = "Yes" Then
                NeedNotify = True
                SoundFile = Notifications(LastState, 2)
                SoundRepeatInterval = Notifications(LastState, 3)
                NotifyString = Notifications(LastState, 4)
            End If
        End If

        If LastConnected = True Then

            If Me.fraConnected.Caption = "Not connected" Then
            'Disconnection has occured
                If Not ManualDisconnected Then
                    If Not Retrying Then
                        If Notifications(10, 1) = "Yes" Then
                            NeedNotify = True
                            SoundFile = Notifications(10, 2)
                            SoundRepeatInterval = Notifications(10, 3)
                            NotifyString = Notifications(10, 4)
                        End If
                    End If
                End If
                
                LastConnected = False

            End If
        Else
            If Me.fraConnected.Caption <> "Not connected" Then
                LastConnected = True
            End If
        End If
        
        
        
        
        If NeedNotify Then
'        Stop
            PlaySound SoundFile
            tmrRepeatSound.Tag = SoundFile
            tmrRepeatSound.Interval = SoundRepeatInterval * 1000
            tmrRepeatSound.Enabled = True
            If SoundRepeatInterval > 0 Then
                frmCancelSound.Label1 = NotifyString
            End If
            If Me.WindowState = vbMinimized Then
                Me.WindowState = vbNormal
            End If
            If InTray Then
                Me.Show
                InTray = False
                Shell_NotifyIcon NIM_DELETE, nid
            End If
            
            PlaySound SoundFile
        End If
        
    'End If

End Sub

Public Sub LoadNotifications()
    Notifications(0, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnHalt", "Yes")
    Notifications(1, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnCalm", "No")
    Notifications(2, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnCutin", "No")
    Notifications(3, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnFreeWheel", "No")
    Notifications(4, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnMotor", "No")
    Notifications(5, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnGenerateLow", "No")
    Notifications(6, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnGenerateHigh", "No")
    Notifications(7, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnHighWind", "Yes")
    Notifications(8, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnFault", "Yes")
    Notifications(9, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnWarning", "Yes")
    Notifications(10, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnCommLost", "Yes")
    Notifications(11, 1) = GetSetting(App.EXEName, "Settings", "RestoreOnService", "Yes")
    
    
    Notifications(0, 2) = GetSetting(App.EXEName, "Settings", "HaltSound", App.Path + "\windows xp hardware fail.wav")
    Notifications(1, 2) = GetSetting(App.EXEName, "Settings", "CalmSound", "None")
    Notifications(2, 2) = GetSetting(App.EXEName, "Settings", "CutinSound", "None")
    Notifications(3, 2) = GetSetting(App.EXEName, "Settings", "FreeWheelSound", "None")
    Notifications(4, 2) = GetSetting(App.EXEName, "Settings", "MotorSound", "None")
    Notifications(5, 2) = GetSetting(App.EXEName, "Settings", "GenerateLowSound", "None")
    Notifications(6, 2) = GetSetting(App.EXEName, "Settings", "GenerateHighSound", "None")
    Notifications(7, 2) = GetSetting(App.EXEName, "Settings", "HighWindsound", App.Path + "\windows xp hardware fail.wav")
    Notifications(8, 2) = GetSetting(App.EXEName, "Settings", "FaultSound", App.Path + "\windows xp hardware fail.wav")
    Notifications(9, 2) = GetSetting(App.EXEName, "Settings", "WarningSound", App.Path + "\windows xp hardware fail.wav")
    Notifications(10, 2) = GetSetting(App.EXEName, "Settings", "CommLostSound", App.Path + "\windows xp hardware fail.wav")
    Notifications(11, 2) = GetSetting(App.EXEName, "Settings", "ServiceSound", App.Path + "\windows xp hardware fail.wav")
    
    Notifications(0, 3) = GetSetting(App.EXEName, "Settings", "HaltRepeat", 1)
    Notifications(1, 3) = GetSetting(App.EXEName, "Settings", "CalmRepeat", 0)
    Notifications(2, 3) = GetSetting(App.EXEName, "Settings", "CutinRepeat", 0)
    Notifications(3, 3) = GetSetting(App.EXEName, "Settings", "FreeWheelRepeat", 0)
    Notifications(4, 3) = GetSetting(App.EXEName, "Settings", "MotorRepeat", 0)
    Notifications(5, 3) = GetSetting(App.EXEName, "Settings", "GenerateLowRepeat", 0)
    Notifications(6, 3) = GetSetting(App.EXEName, "Settings", "GenerateHighRepeat", 0)
    Notifications(7, 3) = GetSetting(App.EXEName, "Settings", "HighWindRepeat", 1)
    Notifications(8, 3) = GetSetting(App.EXEName, "Settings", "FaultRepeat", 1)
    Notifications(9, 3) = GetSetting(App.EXEName, "Settings", "WarningRepeat", 1)
    Notifications(10, 3) = GetSetting(App.EXEName, "Settings", "CommLostRepeat", 1)
    Notifications(11, 3) = GetSetting(App.EXEName, "Settings", "ServiceRepeat", 1)

    Notifications(0, 4) = "Entered halt state"
    Notifications(1, 4) = "Entered calm state"
    Notifications(2, 4) = "Entered cutin state"
    Notifications(3, 4) = "Entered free-wheel state"
    Notifications(4, 4) = "Entered motoring state"
    Notifications(5, 4) = "Entered generate high state"
    Notifications(6, 4) = "Entered generate high state"
    Notifications(7, 4) = "Entered high wind state"
    Notifications(8, 4) = "Entered fault state"
    Notifications(9, 4) = "Entered warning state"
    Notifications(10, 4) = "Lost communications"
    Notifications(11, 4) = "Service hours reached 6000"

End Sub

Public Function NotificationArray(i As Integer, j As Integer)
    NotificationArray = Notifications(i, j)
End Function

Private Sub ResizeGrid()
    
    Dim i As Integer
    
    With grid
    
        For i = 0 To grid.Cols - 1
            If grid.ColWidth(i) <> grid.Width / grid.Cols Then
                grid.ColWidth(i) = grid.Width / grid.Cols
            End If
        Next i
        
        For i = 0 To grid.Rows - 1
            If grid.RowHeight(i) <> grid.Height / grid.Rows Then
                grid.RowHeight(i) = grid.Height / grid.Rows
            End If
        Next i
        
        For i = 0 To .Cols - 1
            If .ColAlignment(i) <> flexAlignCenterCenter Then
                .ColAlignment(i) = flexAlignCenterCenter
            End If
        Next i
    
    End With

End Sub

Public Sub Disconnect()
    
    On Error GoTo ErrHandler

    Connected = False
    
    tmrNetworkTimeout.Enabled = False
    
    If ConnectionType = Network Then
        skWinSock.Close
    Else
        SaxComm1.PortOpen = False
    End If
    
    
    Connected = False
    Me.fraConnected.Caption = "Not connected"
    Me.lblVersion = ""
    DisConnectionCleanup
    
    Retrying = False

    
    Exit Sub

ErrHandler:

End Sub

Public Sub Connect()

    Dim i As Integer
    Dim TempString As String
    Dim StartPort As String
    Dim IPAddress As String
    Dim TCPPort As Integer

    SendState = SendingHello

    If ConnectionType = SerialPort Then
        
        ConnectionLog ("Creating serial connection")
        
        StartPort = GetSetting(App.EXEName, "Settings", "SavedSerialPort", "")
        
        If StartPort = "" Then
            frmSelectSerialPort.Sax = SaxComm1
            frmSelectSerialPort.Show
        Else
            SaxComm1.CommPort = StartPort
        End If
        
        SaxComm1.PortOpen = True
        Connected = True
        tmrSend.Enabled = True
    
    Else
        TempString = GetSetting(App.EXEName, "Settings", "NetworkAddress", "192.168.0.61")
        i = InStr(TempString, ":")

        If i = 0 Then
            IPAddress = GetSetting(App.EXEName, "Settings", "NetworkAddress", "192.168.0.61")
            TCPPort = 3500
        Else
            IPAddress = Left(TempString, i - 1)
            TCPPort = Val(Right(TempString, Len(TempString) - i))
        End If
        
        skWinSock.Close
        
        If Not Retrying Then
            frmNetworkTimeout.Show
        End If
        
        ConnectionLog ("Requesting socket for " + IPAddress + ":" + Format(TCPPort))
        skWinSock.Connect IPAddress, TCPPort

    End If
    

End Sub

Public Sub ProcessIncomming(S As String)
Dim i As Integer
Dim C As String

If ledReceive.State = LEDOff Then
    ledReceive.Flash
End If




If mnuTestSnoop.Checked Then
    frmSnoop.Receive S
End If




For i = 1 To Len(S)
    C = Mid(S, i, 1)
    If C = "@" Then
        ReceiveString = "@"
    Else
        ReceiveString = ReceiveString + C
        If C = "#" Then
            R.S = ReceiveString
            
            If R.IsValid Then
                ProcessReceiveString
            Else
                'Connected = False
                tmrFlash.Enabled = True
            End If
        End If
    End If
Next i

End Sub
Public Sub LoadConnectionSettings()
    
    NetworkTimeLeft = GetSetting(App.EXEName, "Settings", "NetworkTimeOut", 10)
    TimeOutRespondTime = GetSetting(App.EXEName, "Settings", "TimeOutResponseTime", 20)
    tmrNetworkTimeout.Interval = 60000
    NetworkTimeoutEnabled = GetSetting(App.EXEName, "Settings", "NetworkTimeoutEnabled", True)
    
    If GetSetting(App.EXEName, "Settings", "ConnectionType", "SerialPort") = "SerialPort" Then
        ConnectionType = SerialPort
        SendInterval = 2000
    Else
        ConnectionType = Network
        SendInterval = 2000
    End If

    If (ConnectionType = Network) And NetworkTimeoutEnabled Then
        tmrNetworkTimeout = True
    Else
        tmrNetworkTimeout = False
    End If

    tmrSend.Interval = SendInterval

End Sub

Public Sub SetNetworkTimeout()
    
    NetworkTimeLeft = GetSetting(App.EXEName, "Settings", "NetworkTimeOut", 10)
    TimeOutRespondTime = GetSetting(App.EXEName, "Settings", "TimeOutResponseTime", 20)
    tmrNetworkTimeout.Interval = 60000

End Sub


Public Sub TMatrix(Row As Integer, Col As Integer, S As String)

    If grid.TextMatrix(Row, Col) <> S Then
        grid.TextMatrix(Row, Col) = S
    End If
    
End Sub

Public Sub ProcessHello()
    'Just received the first response from the tower
    'Figure out what version we have and take the actions
    'that depend on the version number
    

    If R.ProgramVersion <= "6.3.3" Then
        mnuRemoteConnectionSettings.Enabled = False
        mnuSettingsTimeclock.Enabled = False
        mnuTestStackInfo.Enabled = False
    Else
        mnuRemoteConnectionSettings.Enabled = True
        mnuSettingsTimeclock.Enabled = True
        mnuTestStackInfo.Enabled = True
        
        If (R.ProgramVersion >= "8.0.2") And (R.ProgramVersion < "8.6.0") Then
            If R.SiteName = "" Then
                If SendState <> WaitingForSiteNameConfirm Then
                    SendState = WaitingForSiteName
                    ProgramSerialNumber = ""
                    frmEndurance.mnuTestTimeStampResult.Caption = ProgramSerialNumber
                End If
            End If
        End If
        
        If (R.ProgramVersion >= "8.8.0") Then
            mnuRemotePassword.Enabled = True
        Else
            mnuRemotePassword.Enabled = False
        End If
        
    End If
    
    If R.ProgramVersion >= "8.0.4" Then
        Me.mnuTestFlashWriteCount.Enabled = True
    Else
        Me.mnuTestFlashWriteCount.Enabled = False
    End If
    
    If R.ProgramVersion >= "8.6.0" Then
        'First version to require password
        
        SendState = WaitingForPasswordKey
    
        If GetSetting(App.EXEName, "Settings", "xx", False) Then
            'password saved
            R.PasswordKeyReceived = False
            R.Password = GetSetting(App.EXEName, "Settings", "xlz", "")
        Else
            frmEnterPassword.Show 1
        End If
    
    End If
    
    

End Sub

Public Sub StartDownloadManager()
    Dim FileName As String
    Dim ID As Double
    Dim AutoString As String
    Dim IPAddress As String
    
    On Error Resume Next
    
    If Me.skWinSock.State = 7 Then
        
        FileName = App.Path + "\UDPDownload.exe"
        
        If Dir(FileName) <> "" Then
        
            ID = Shell(FileName, vbNormalFocus)
            If ID <> 0 Then
                IPAddress = Me.skWinSock.RemoteHostIP
                AutoString = "%p{ENTER}" + IPAddress + "{ENTER}"
                Debug.Print AutoString
                SendKeys AutoString
            End If
            
        End If
        
    Else
        MsgBox ("You have no network connection")
    End If
    
        
End Sub
