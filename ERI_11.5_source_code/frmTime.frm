VERSION 5.00
Object = "{BD856031-3F73-11D3-94AA-00104B6CDBC6}#1.0#0"; "freeSize.ocx"
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.Form frmTime 
   Caption         =   "Tower time"
   ClientHeight    =   2760
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3345
   ControlBox      =   0   'False
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   ScaleHeight     =   2760
   ScaleWidth      =   3345
   StartUpPosition =   2  'CenterScreen
   Begin VB.Timer tmrAdjust 
      Enabled         =   0   'False
      Interval        =   3000
      Left            =   2400
      Top             =   1200
   End
   Begin freeSize.freeSizer freeSizer1 
      Left            =   840
      Top             =   1440
      _ExtentX        =   1588
      _ExtentY        =   1376
      ResizeObjects   =   -1  'True
      MoveObjects     =   -1  'True
      SmartSizing     =   -1  'True
      SmartPositioning=   -1  'True
   End
   Begin VB.CommandButton cmdEqual 
      Caption         =   "Set Turbine time to computer time"
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
      Left            =   120
      TabIndex        =   2
      Top             =   960
      Width           =   3135
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
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
      Left            =   120
      TabIndex        =   1
      Top             =   1800
      Width           =   3135
   End
   Begin MSComCtl2.DTPicker DTPicker1 
      Height          =   735
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3135
      _ExtentX        =   5530
      _ExtentY        =   1296
      _Version        =   393216
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Times New Roman"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Format          =   59506690
      CurrentDate     =   37406
   End
End
Attribute VB_Name = "frmTime"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdEqual_Click()
    
    DTPicker1.Value = Time
    DTPicker1_Change
    
    
End Sub

Private Sub cmdOK_Click()
    Unload Me
End Sub

Private Sub DTPicker1_Change()
    Dim Temp As String
    
    With frmEndurance
        .AdjustingTime = True
        Temp = Format(DTPicker1.Hour, "00") + ":"
        Temp = Temp + Format(DTPicker1.Minute, "00") + ":"
        Temp = Temp + Format(DTPicker1.Second, "00")
        
        .R.DateTimeReceived = False
        .TimeToSend = Temp
        .SendState = SendingTime
        tmrAdjust.Enabled = True
    End With
    
End Sub

Public Sub SendTime()
    
End Sub


Private Sub Form_Unload(Cancel As Integer)
    
    With frmEndurance
        .DisplayingTime = False
        .AdjustingTime = False
    End With

End Sub


Private Sub tmrAdjust_Timer()
    
    With frmEndurance
        .AdjustingTime = False
    End With
    
    tmrAdjust.Enabled = False

End Sub
