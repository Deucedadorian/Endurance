VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmNetworkTimedOut 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   3180
   ClientLeft      =   15
   ClientTop       =   15
   ClientWidth     =   6765
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3180
   ScaleWidth      =   6765
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdDisconnect 
      Caption         =   "Disconnect"
      Height          =   735
      Left            =   3480
      TabIndex        =   4
      Top             =   2280
      Width           =   3135
   End
   Begin VB.Timer tmrStayConnected 
      Left            =   1680
      Top             =   2040
   End
   Begin VB.CommandButton cmdStayConnected 
      Caption         =   "Stay connected"
      Height          =   735
      Left            =   120
      TabIndex        =   3
      Top             =   2280
      Width           =   3255
   End
   Begin VB.Frame Frame1 
      Height          =   855
      Left            =   120
      TabIndex        =   1
      Top             =   1320
      Width           =   6495
      Begin MSComctlLib.ProgressBar pbDisconnect 
         Height          =   495
         Left            =   240
         TabIndex        =   2
         Top             =   240
         Width           =   6135
         _ExtentX        =   10821
         _ExtentY        =   873
         _Version        =   393216
         Appearance      =   1
      End
   End
   Begin VB.Label lblWarning 
      Caption         =   "The  network connection is about to disconnect due to inactivity. "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   6255
   End
End
Attribute VB_Name = "frmNetworkTimedOut"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim mResponseTime As Integer
Dim mTimeLeft As Integer


Private Sub cmdDisconnect_Click()
    frmEndurance.Disconnect
    Unload Me
End Sub

Private Sub cmdStayConnected_Click()
    
    frmEndurance.LoadConnectionSettings
    Unload Me
    
End Sub

Private Sub Form_Load()
    tmrStayConnected.Interval = 1000
    tmrStayConnected.Enabled = True
    mTimeLeft = mResponseTime
End Sub

Public Property Get ResponseTime() As Integer
    ResponseTime = mResponseTime
End Property

Public Property Let ResponseTime(ByVal NewResponseTime As Integer)
    mResponseTime = NewResponseTime
End Property



Private Sub tmrStayConnected_Timer()
    If mTimeLeft <> 0 Then
        mTimeLeft = mTimeLeft - 1
        pbDisconnect = ((mResponseTime - mTimeLeft) / mResponseTime) * pbDisconnect.Max
        Me.Frame1.Caption = Format(mTimeLeft) + " seconds before disconnect."
    Else
        frmEndurance.Disconnect
        Unload Me
    End If
End Sub
