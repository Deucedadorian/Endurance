VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmNetworkTimeout 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   1890
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   4335
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1890
   ScaleWidth      =   4335
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer tmrTimeOut 
      Left            =   3360
      Top             =   120
   End
   Begin MSComctlLib.ProgressBar ProgressBar 
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   1320
      Width           =   4095
      _ExtentX        =   7223
      _ExtentY        =   873
      _Version        =   393216
      Appearance      =   1
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   735
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   4095
   End
   Begin VB.Label lblConnecting 
      Alignment       =   2  'Center
      Caption         =   "Connecting"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   3975
   End
End
Attribute VB_Name = "frmNetworkTimeout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim SecondsRemaining As Integer
Dim SecondsStart As Integer

Private Sub cmdCancel_Click()
    ConnectionLog ("User clicked cancel before a socket was established")
    frmEndurance.Disconnect
    Unload Me
End Sub

Private Sub Form_Load()
    
    tmrTimeOut.Enabled = True
    tmrTimeOut.Interval = 1000
    SecondsRemaining = 10
    SecondsStart = SecondsRemaining
    
End Sub

Private Sub tmrTimeOut_Timer()
    
    SecondsRemaining = SecondsRemaining - 1
    ProgressBar = ProgressBar.Max - (SecondsRemaining / SecondsStart) * ProgressBar.Max
    If SecondsRemaining = 0 Then
        ConnectionLog ("Could not establish a socket")
        frmEndurance.Disconnect
        Unload Me
    End If
    
End Sub
