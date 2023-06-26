VERSION 5.00
Begin VB.Form frmNetworkTimeoutSettings 
   Caption         =   "Network timeout settings"
   ClientHeight    =   4770
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   6060
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   4770
   ScaleWidth      =   6060
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox chkStayConnected 
      Caption         =   "Never time out"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   8
      Top             =   2520
      Width           =   2295
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   855
      Left            =   120
      TabIndex        =   7
      Top             =   3720
      Width           =   2775
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Height          =   855
      Left            =   3000
      TabIndex        =   6
      Top             =   3720
      Width           =   2895
   End
   Begin VB.Frame Frame2 
      Caption         =   "User response time"
      Height          =   1095
      Left            =   120
      TabIndex        =   2
      Top             =   1320
      Width           =   5775
      Begin VB.HScrollBar hsbResponseTime 
         Height          =   375
         Left            =   120
         Max             =   500
         Min             =   1
         TabIndex        =   5
         Top             =   360
         Value           =   20
         Width           =   1575
      End
      Begin VB.Label lblResponseTime 
         Alignment       =   2  'Center
         Caption         =   "20 seconds"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   15.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   1800
         TabIndex        =   3
         Top             =   240
         Width           =   1815
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Network time out interval"
      Height          =   1095
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5775
      Begin VB.HScrollBar hsbNetworkTimeoutInterval 
         Height          =   375
         Left            =   240
         Max             =   500
         Min             =   1
         TabIndex        =   4
         Top             =   360
         Value           =   30
         Width           =   1455
      End
      Begin VB.Label lblNetworkTimeoutInterval 
         Alignment       =   2  'Center
         Caption         =   "30 minutes"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   15.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   1800
         TabIndex        =   1
         Top             =   360
         Width           =   1815
      End
   End
End
Attribute VB_Name = "frmNetworkTimeoutSettings"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'Private mConnector As MVconnector

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()
    SaveSetting App.EXEName, "Settings", "NetworkTimeOut", Me.hsbNetworkTimeoutInterval
    SaveSetting App.EXEName, "Settings", "TimeOutResponseTime", Me.hsbResponseTime
    
    If chkStayConnected = Checked Then
        SaveSetting App.EXEName, "Settings", "NetworkTimeoutEnabled", False
    
    Else
        SaveSetting App.EXEName, "Settings", "NetworkTimeoutEnabled", True
    
    End If
    
    frmEndurance.LoadConnectionSettings
    
    Unload Me
    
End Sub

Private Sub Form_Load()
    
    hsbNetworkTimeoutInterval = GetSetting(App.EXEName, "Settings", "NetworkTimeOut", 30)
    hsbResponseTime = GetSetting(App.EXEName, "Settings", "TimeOutResponseTime", 20)
    
    If GetSetting(App.EXEName, "Settings", "NetworkTimeoutEnabled", True) Then
        chkStayConnected = Unchecked
    Else
        chkStayConnected = Checked
    End If
    
    UpdateResponseTime
    UpdateNetworkTimeoutInterval
    
End Sub


Public Sub UpdateResponseTime()
    lblResponseTime = Format(hsbResponseTime) + " seconds"
End Sub

Public Sub UpdateNetworkTimeoutInterval()
    Me.lblNetworkTimeoutInterval = Format(Me.hsbNetworkTimeoutInterval) + " minutes"
End Sub

Private Sub hsbNetworkTimeoutInterval_Change()
    UpdateNetworkTimeoutInterval
End Sub

Private Sub hsbNetworkTimeoutInterval_Scroll()
    UpdateNetworkTimeoutInterval
End Sub

Private Sub hsbResponseTime_Change()
    UpdateResponseTime
End Sub

Private Sub hsbResponseTime_Scroll()
    UpdateResponseTime
End Sub


'Public Property Let Connector(ByVal NewConnector As MVconnector)
'    Set mConnector = NewConnector
'End Property
